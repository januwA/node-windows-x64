#include <iostream>
#include <napi.h>
#include "ajanuw.h"
#include "_napi_macro.h"
#include <asmjit/asmjit.h>
#include <asmtk/asmtk.h>

extern "C" typedef uintptr_t (*asm_fun_t)();

struct CallbackContext
{
  CallbackContext(Napi::Env env_, Function cb_, LPVOID address_) : cb(cb_),
                                                                   env(env_),
                                                                   address(address_){};
  Function cb;
  Napi::Env env;
  LPVOID address;
  int64_t call(uintptr_t *lpRcx, uintptr_t *lpP5)
  {
    uintptr_t *rcx = (lpRcx + 0);
    uintptr_t *rdx = (lpRcx + 1);
    uintptr_t *r8 = (lpRcx + 2);
    uintptr_t *r9 = (lpRcx + 3);

    vector<napi_value> args;
    args.push_back(Number::New(env, *rcx));
    args.push_back(Number::New(env, *rdx));
    args.push_back(Number::New(env, *r8));
    args.push_back(Number::New(env, *r9));

    // 第五个参数直接返回指针，用户需要自己读数据,如:
    // mem_read_dword(lpP5)
    // mem_read_str(mem_read_pointer(lpP5+8)) x64指针大小为8字节
    args.push_back(Number::New(env, (uintptr_t)lpP5));
    return cb.Call(args).ToNumber().Int64Value();
  }
};

size_t getStringsCount(Napi::Array args, bool isWideChar)
{
  size_t count = 0;
  for (size_t i = 0; i < args.Length(); i++)
  {
    auto it = args.Get(i);
    if (it.IsString())
    {
      count += isWideChar ? SSString::count(nm_ustr(it)) : nm_str(it).length();
      count++;
    }
  }
  return count;
}

extern "C" uintptr_t cccccc(vector<CallbackContext *> *vect_cc, void *index, uintptr_t *lpRcx, uintptr_t *lpP5)
{
  return vect_cc->at((size_t)index)->call(lpRcx, lpP5);
}

Value invoke(const CallbackInfo &info)
{
  using namespace asmjit;
  using namespace asmtk;
  using namespace asmjit::x86;

  nm_init_cal(1);
  vector<CallbackContext *> vCC;

  Object o = nmi_obj(0);
  HMODULE hModule = NULL;
  BYTE *lpMethod = nullptr;
  bool bWideChar = false;

  if (nm_get_is(o, "method", num))
  {
    bWideChar = nm_get_to(o, "isWideChar", bool);
    lpMethod = reinterpret_cast<BYTE *>(nm_get_to(o, "method", qword));
  }
  else
  {
    string sMethod = nm_get_to(o, "method", str);
    bWideChar = SSString::endWith(sMethod, "W");
    Napi::Value js_isWideChar = nm_get(o, "isWideChar");
    if (!nm_is_nullish(js_isWideChar))
      bWideChar = nm_bool(js_isWideChar);

    if (nm_has(o, "module"))
    {
      string sModule = nm_get_to(o, "module", str);
      hModule = LoadLibraryA(sModule.c_str());
      if (hModule == NULL)
      {
        nm_jserr("not find \"" + sModule + "\" module.");
        nm_retu;
      }
    }
    if (hModule != NULL)
      lpMethod = (BYTE *)GetProcAddress(hModule, sMethod.c_str());
    else
      lpMethod = (BYTE *)ajanuw::CEString::getAddress(sMethod);
  }

  if (lpMethod == NULL)
  {
    nm_jserr("not find method.");
    nm_retu;
  }

  // args: number | pointer | string | function
  Array args = nm_is_nullishOr(nm_get(o, "args"), nm_arr, Array::New(env));

  // save strings
  BYTE *stringMem = NULL;
  size_t strSizeCount = getStringsCount(args, bWideChar);
  size_t strMemOffset = 0;
  if (strSizeCount)
  {
    stringMem = (BYTE *)ajanuw::Mem::alloc(strSizeCount);
    if (stringMem == NULL)
    {
      nm_jserr("VirtualAlloc stringMem error.");
      nm_retu;
    }
    ZeroMemory(stringMem, strSizeCount);
  }

  JitRuntime rt;
  CodeHolder code;
  code.init(rt.environment());
  x86::Assembler a(&code);

  a.push(rbp);
  a.mov(rbp, rsp);
  a.sub(rsp, 0x190);

  for (size_t i = 0; i < args.Length(); i++)
  {
    uintptr_t value = 0;
    if (nm_is_fun(args.Get(i)))
    {
      auto CC = new CallbackContext(env,
                                    args.Get(i).As<Function>(),
                                    createCallback(&cccccc, i, &vCC));
      vCC.push_back(CC);
      value = (uintptr_t)CC->address;
    }
    else if (nm_get_is(args, i, str))
    {
      Napi::String text = nm_get(args, i).ToString();
      BYTE *addr = stringMem + strMemOffset;
      value = (uintptr_t)addr;
      if (bWideChar)
      {
        u16string str = text.Utf16Value();
        ajanuw::Mem::write_ustr(addr, str);
        strMemOffset += ajanuw::SSString::count(str) + 2;
      }
      else
      {
        string str = text.Utf8Value();
        ajanuw::Mem::write_str(addr, str);
        strMemOffset += str.length() + 1;
      }
    }
    else
    {
      // null and undefined to 0
      value = nm_qword(nm_get(args, i));
    }

    if (i < 4)
    {
      if (i == 0)
        a.mov(rcx, value);
      if (i == 1)
        a.mov(rdx, value);
      if (i == 2)
        a.mov(r8, value);
      if (i == 3)
        a.mov(r9, value);
    }
    else
    {
      a.mov(rax, value);
      size_t param_offset = 0x20 + ((i - 4) * 8);
      a.mov(ptr(rsp, param_offset), rax);
    }
  }

  a.mov(rax, lpMethod);
  a.call(rax);

  a.add(rsp, 0x190);
  a.mov(rsp, rbp);
  a.pop(rbp);
  a.ret();

  asm_fun_t fn;
  asmjit::Error err = rt.add(&fn, &code);
  if (err)
  {
    if (stringMem)
      ajanuw::Mem::free(stringMem);

    for (auto cc : vCC)
    {
      ajanuw::Mem::free(cc->address);
      delete cc;
    }
    nm_jserr("asmjit error.");
    nm_retu;
  }
  uintptr_t result = fn();

  rt.release(fn);
  if (stringMem)
    ajanuw::Mem::free(stringMem);

  for (auto cc : vCC)
  {
    ajanuw::Mem::free(cc->address);
    delete cc;
  }
  nm_ret(result);
}
