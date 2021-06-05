#include <iostream>
#include <napi.h>
#include "ajanuw.h"
#include "_napi_macro.h"
#include <asmjit/asmjit.h>

extern "C" typedef uintptr_t (*asm_fun_t)();

struct CallbackContext
{
  CallbackContext(const Napi::Env &env, const Napi::Function &cb, const LPVOID &address)
      : cb(cb), env(env), address(address){};
  Napi::Function cb;
  Napi::Env env;
  LPVOID address;
  int64_t call(uintptr_t *lpRcx, uintptr_t *lpP5)
  {
    uintptr_t *rcx = (lpRcx + 0);
    uintptr_t *rdx = (lpRcx + 1);
    uintptr_t *r8 = (lpRcx + 2);
    uintptr_t *r9 = (lpRcx + 3);

    std::vector<napi_value> args{
        Napi::Number::New(env, *rcx),
        Napi::Number::New(env, *rdx),
        Napi::Number::New(env, *r8),
        Napi::Number::New(env, *r9),

        // 第五个参数返回其他参数指针，需要自己做指针运算读数据,如:
        // readDword(lpP5)
        // readStr(readPointer(lpP5+8)) x64指针大小为8字节
        Napi::Number::New(env, (uintptr_t)lpP5),
    };

    return cb.Call(args).ToNumber().Int64Value();
  }
};

size_t getStringsCount(const Napi::Array &args, bool isWideChar)
{
  size_t count = 0;
  for (size_t i = 0; i < args.Length(); i++)
  {
    auto it = args.Get(i);
    if (it.IsString())
    {
      count += isWideChar ? ajanuw::sstr::count(nm_us(it)) : nm_s(it).length();
      count++;
    }
  }
  return count;
}

extern "C" uintptr_t cccccc(std::vector<CallbackContext *> *vect_cc, void *index, uintptr_t *lpRcx, uintptr_t *lpP5)
{
  return vect_cc->at((size_t)index)->call(lpRcx, lpP5);
}

nm_api(invoke)
{
  using namespace asmjit;
  using namespace asmjit::x86;

  nm_init_cal(1);
  std::vector<CallbackContext *> vCC;
  auto o = nmi_o(0);
  HMODULE hModule = NULL;
  uint8_t *lpMethod = nullptr;
  bool bWideChar = false;

  if (nmo_is("method", n))
  {
    bWideChar = nmo_get("isWideChar", b);
    lpMethod = reinterpret_cast<uint8_t *>(nmo_get("method", ull));
  }
  else
  {
    auto sMethod = nmo_get("method", s);
    bWideChar = ajanuw::sstr::endWith(sMethod, "W");
    auto js_isWideChar = o.Get("isWideChar");
    if (!nm_is_un(js_isWideChar))
      bWideChar = nm_b(js_isWideChar);

    if (o.Has("module"))
    {
      auto sModule = nmo_get("module", s);
      hModule = LoadLibraryA(sModule.data());
      if (hModule == NULL)
      {
        nm_err(std::format("not find '{}' module.", sModule));
        nm_retu;
      }
    }
    if (hModule != NULL)
      lpMethod = (uint8_t *)GetProcAddress(hModule, sMethod.c_str());
    else
    {
      try
      {
        lpMethod = (uint8_t *)ajanuw::CEAS::getAddress(sMethod);
      }
      catch (const std::exception &e)
      {
        nm_err(e.what());
        nm_retu;
      }
    }
  }

  if (lpMethod == NULL)
  {
    nm_err("not find method.");
    nm_retu;
  }

  // args: number | pointer | string | function
  auto args = nmo_is_und("args", a, Napi::Array::New(env));

  // save strings
  uint8_t *strMem = nullptr;
  auto strSizeCount = getStringsCount(args, bWideChar);
  size_t strMemOffset = 0;
  if (strSizeCount)
  {
    strMem = (uint8_t *)ajanuw::Mem::alloc(strSizeCount);
    if (!strMem)
    {
      nm_err("VirtualAlloc stringMem error.");
      nm_retu;
    }
    ZeroMemory(strMem, strSizeCount);
  }

  auto argsStackSize = max(args.Length() * sizeof(uintptr_t), Globals::kMaxPhysRegs);

  JitRuntime rt;
  CodeHolder code;
  code.init(rt.environment());
  x86::Assembler a(&code);

  a.push(rbp);
  a.mov(rbp, rsp);
  a.sub(rsp, argsStackSize);

  for (size_t i = 0, l = args.Length(); i < l; i++)
  {
    auto it = args.Get(i);
    uintptr_t value = NULL;
    if (nm_is_fu(it))
    {
      auto CC = new CallbackContext(env, it.As<Napi::Function>(), ajanuw::createCallback(&cccccc, i, &vCC));
      vCC.push_back(CC);
      value = (uintptr_t)CC->address;
    }
    else if (nm_is_s(it))
    {
      auto text = it.ToString();
      auto addr = strMem + strMemOffset;
      value = (uintptr_t)addr;
      if (bWideChar)
      {
        auto str = text.Utf16Value();
        ajanuw::Mem::wUstr(addr, str);
        strMemOffset += ajanuw::sstr::count(str) + sizeof(char16_t);
      }
      else
      {
        auto str = text.Utf8Value();
        ajanuw::Mem::wStr(addr, str);
        strMemOffset += str.length() + sizeof(char);
      }
    }
    else
    {
      // other value to number
      value = nm_ull(it);
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
  auto err = rt.add(&fn, &code);
  if (err)
  {
    if (strMem)
      ajanuw::Mem::free(strMem);

    for (auto cc : vCC)
    {
      ajanuw::Mem::free(cc->address);
      delete cc;
    }
    nm_err("asmjit error.");
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
