#include <iostream>
#include <napi.h>
#include "ajanuw.h"
#include "_napi_macro.h"
#include <asmjit/asmjit.h>

extern "C" typedef uintptr_t (*asm_fun_t)();

struct CallbackContext
{
  CallbackContext(Napi::Env env, Napi::Function cb, LPVOID address) : cb(cb),
                                                                      env(env),
                                                                      address(address){};
  Napi::Function cb;
  Napi::Env env;
  LPVOID address;
  int64_t call(uintptr_t *lpRcx, uintptr_t *lpP5)
  {
    uintptr_t *rcx = (lpRcx + 0);
    uintptr_t *rdx = (lpRcx + 1);
    uintptr_t *r8 = (lpRcx + 2);
    uintptr_t *r9 = (lpRcx + 3);

    std::vector<napi_value> args;
    args.push_back(Napi::Number::New(env, *rcx));
    args.push_back(Napi::Number::New(env, *rdx));
    args.push_back(Napi::Number::New(env, *r8));
    args.push_back(Napi::Number::New(env, *r9));

    // 第五个参数直接返回指针，用户需要自己读数据,如:
    // mem_read_dword(lpP5)
    // mem_read_str(mem_read_pointer(lpP5+8)) x64指针大小为8字节
    args.push_back(Napi::Number::New(env, (uintptr_t)lpP5));
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
      count += isWideChar ? ajanuw::SSString::count(nm_ustr(it)) : nm_str(it).length();
      count++;
    }
  }
  return count;
}

extern "C" uintptr_t cccccc(std::vector<CallbackContext *> *vect_cc, void *index, uintptr_t *lpRcx, uintptr_t *lpP5)
{
  return vect_cc->at((size_t)index)->call(lpRcx, lpP5);
}

Napi::Value invoke(const Napi::CallbackInfo &info)
{
  using namespace asmjit;
  using namespace asmjit::x86;

  nm_init_cal(1);
  std::vector<CallbackContext *> vCC;
  Napi::Object o = nmi_obj(0);
  HMODULE hModule = NULL;
  BYTE *lpMethod = nullptr;
  bool bWideChar = false;

  if (nm_getis("method", num))
  {
    bWideChar = nm_getto("isWideChar", bool);
    lpMethod = reinterpret_cast<BYTE *>(nm_getto("method", qword));
  }
  else
  {
    std::string sMethod = nm_getto("method", str);
    bWideChar = ajanuw::SSString::endWith(sMethod, "W");
    Napi::Value js_isWideChar = o.Get("isWideChar");
    if (!nm_is_nullish(js_isWideChar))
      bWideChar = nm_bool(js_isWideChar);

    if (o.Has("module"))
    {
      std::string sModule = nm_getto("module", str);
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
      lpMethod = (BYTE *)ajanuw::CEAddressString::getAddress(sMethod);
  }

  if (lpMethod == NULL)
  {
    nm_jserr("not find method.");
    nm_retu;
  }

  // args: number | pointer | string | function
  Napi::Array args = nm_is_nullishOr(o.Get("args"), nm_arr, Napi::Array::New(env));

  // save strings
  BYTE *strMem = NULL;
  size_t strSizeCount = getStringsCount(args, bWideChar);
  size_t strMemOffset = 0;
  if (strSizeCount)
  {
    strMem = (BYTE *)ajanuw::Mem::alloc(strSizeCount);
    if (strMem == NULL)
    {
      nm_jserr("VirtualAlloc stringMem error.");
      nm_retu;
    }
    ZeroMemory(strMem, strSizeCount);
  }

  size_t argsStackSize = max(args.Length() * sizeof(uintptr_t), Globals::kMaxPhysRegs);

  JitRuntime rt;
  CodeHolder code;
  code.init(rt.environment());
  x86::Assembler a(&code);

  a.push(rbp);
  a.mov(rbp, rsp);
  a.sub(rsp, argsStackSize);

  for (size_t i = 0; i < args.Length(); i++)
  {
    uintptr_t value = NULL;
    if (nm_is_fun(args.Get(i)))
    {
      auto CC = new CallbackContext(env,
                                    args.Get(i).As<Napi::Function>(),
                                    ajanuw::createCallback(&cccccc, i, &vCC));
      vCC.push_back(CC);
      value = (uintptr_t)CC->address;
    }
    else if (nm_is_str(args.Get(i)))
    {
      Napi::String text = args.Get(i).ToString();
      BYTE *addr = strMem + strMemOffset;
      value = (uintptr_t)addr;
      if (bWideChar)
      {
        std::u16string str = text.Utf16Value();
        ajanuw::Mem::wUstr(addr, str);
        strMemOffset += ajanuw::SSString::count(str) + 2;
      }
      else
      {
        std::string str = text.Utf8Value();
        ajanuw::Mem::wStr(addr, str);
        strMemOffset += str.length() + 1;
      }
    }
    else
    {
      // null and undefined to 0
      value = nm_qword(args.Get(i));
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

  a.add(rsp, argsStackSize);
  a.mov(rsp, rbp);
  a.pop(rbp);
  a.ret();

  asm_fun_t fn;
  asmjit::Error err = rt.add(&fn, &code);
  if (err)
  {
    if (strMem)
      ajanuw::Mem::free(strMem);

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
  if (strMem)
    ajanuw::Mem::free(strMem);

  for (auto cc : vCC)
  {
    ajanuw::Mem::free(cc->address);
    delete cc;
  }
  nm_ret(result);
}
