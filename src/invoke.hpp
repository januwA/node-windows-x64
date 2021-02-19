#include <iostream>
#include <napi.h>
#include "ajanuw.h"
#include "_napi_macro.h"

using namespace Napi;
using namespace ajanuw;

typedef void *(CALLBACK *asm_fun_t)();

struct CallbackContext
{
  CallbackContext(Napi::Env env_, Function cb_) : cb(cb_), env(env_), address(0){};

  Function cb;
  Napi::Env env;

  LPVOID address;

  Value call(uintptr_t *lpRcx, uintptr_t *lpP5)
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
    return cb.Call(args);
  }
};

vector<CallbackContext *> vect_cc;

uintptr_t cccccc(void *_, void *index, uintptr_t *lpRcx, uintptr_t *lpP5)
{
  return vect_cc.at((size_t)index)->call(lpRcx, lpP5).ToNumber().Int64Value();
}

Value invoke(const CallbackInfo &info)
{
  nm_init;
  Object opt = nm_obj(info[0]);
  string sModule = nm_str(opt.Get("module"));
  string sMethod = nm_str(opt.Get("method"));

  uintptr_t lpAddress = nm_IsNullishOr(opt.Get("lpAddress"), nm_qword, 0);
  size_t dwSize = nm_IsNullishOr(opt.Get("dwSize"), nm_qword, 1024);
  DWORD flAllocationType = nm_IsNullishOr(opt.Get("flAllocationType"), nm_dword, MEM_COMMIT | MEM_RESERVE);
  DWORD flProtect = nm_IsNullishOr(opt.Get("flProtect"), nm_dword, PAGE_EXECUTE_READWRITE);

  // method args: number | pointer | string | function
  Array _args = nm_IsNullishOr(opt.Get("args"), nm_arr, Array::New(env));

  // string is wide?
  bool isWideChar = SSString::endWith(sMethod, "W");
  if (!nm_IsNullish(opt.Get("isWideChar")))
    isWideChar = nm_bool(opt.Get("isWideChar"));


  HMODULE hModule = LoadLibraryA(sModule.c_str());
  if (hModule == NULL)
  {
    nm_jserr("not find \"" + sModule + "\" module.");
    nm_retu;
  }

  BYTE *lpMethod = (BYTE *)GetProcAddress(hModule, sMethod.c_str());
  if (lpMethod == NULL)
  {
    nm_jserr("not find \"" + sMethod + "\" method.");
    nm_retu;
  }

  // result:8 + pading:8 + funcode
  BYTE *newmem = (BYTE *)VirtualAlloc((LPVOID)lpAddress, dwSize, flAllocationType, flProtect);
  if (newmem == NULL)
  {
    nm_jserr("VirtualAlloc newmem error.");
    nm_retu;
  }

  // save strings
  size_t dwStrSize = 0;
  size_t strMemOffset = 0;
  BYTE* stringMem = NULL;
  for (size_t i = 0; i < _args.Length(); i++)
  {
    auto a = _args.Get(i);
    if (a.IsString())
    {
      dwStrSize += isWideChar ? SSString::count(a.ToString().Utf16Value()) : a.ToString().Utf8Value().length();
      dwStrSize++;
    }
  }

  if (dwStrSize)
  {
    stringMem = (BYTE*)Mem::alloc(dwStrSize);
    if (stringMem == NULL)
    {
      nm_jserr("VirtualAlloc stringMem error.");
      nm_retu;
    }
  }
  
  uintptr_t *lpResult = (uintptr_t *)newmem;
  asm_fun_t asm_func = (asm_fun_t)(newmem + sizeof(uintptr_t));

  const int size_p_1_4 = 0x0A;
  const int size_p_5 = 0x0F;
  const int rsp_p5 = 0x20; // 其它参数放在堆栈上
  size_t offset = 0x0B;
  vector<size_t> argsOffset{};
  size_t methodOffset = 0;
  size_t resultOffset = 0;

  // 1. init code string
  string codeStr = "55 48 8B EC 48 81 EC 90 01 00 00\n";
  for (size_t i = 0; i < _args.Length(); i++)
  {
    if (i < 4)
    {
      argsOffset.push_back(offset + 2);
      if (i == 0)
        codeStr += "48 B9 00 00 00 00 00 00 00 00\n";
      if (i == 1)
        codeStr += "48 BA 00 00 00 00 00 00 00 00\n";
      if (i == 2)
        codeStr += "49 B8 00 00 00 00 00 00 00 00\n";
      if (i == 3)
        codeStr += "49 B9 00 00 00 00 00 00 00 00\n";
      offset += size_p_1_4;
    }
    else
    {
      argsOffset.push_back(offset + 2);
      char hex_str[1];
      int rsp_offset = rsp_p5 + ((i - 4) * 8);
      sprintf(hex_str, "%0x", rsp_offset);
      codeStr += "48 B8 00 00 00 00 00 00 00 00\n";
      codeStr += "48 89 44 24 " + string{hex_str} + "\n";
      offset += size_p_5;
    }
  }

  methodOffset = offset + 2;
  codeStr += "48 B8 00 00 00 00 00 00 00 00\n"; // set fun
  codeStr += "FF D0\n";
  resultOffset = methodOffset + 0x0C;
  codeStr += "48 B9 00 00 00 00 00 00 00 00\n"; // set result addr
  codeStr += "48 89 01\n";                      // set result
  codeStr += "48 81 C4 90 01 00 00\n";
  codeStr += "48 8B E5\n";
  codeStr += "5D\n";
  codeStr += "C3\n";

  // 2. init code bytes
  vector<BYTE> code = SSString::toBytes(codeStr);
  for (size_t i = 0; i < _args.Length(); i++)
  {
    uintptr_t value;
    if (_args.Get(i).IsFunction())
    {
      auto CC = new CallbackContext(env, _args.Get(i).As<Function>());
      vect_cc.push_back(CC);
      CC->address = createCallback(&cccccc, i);
      value = (uintptr_t)CC->address;
    }
    else if (_args.Get(i).IsString())
    {
      String text = _args.Get(i).ToString();
      BYTE* addr = stringMem + strMemOffset;

      if (isWideChar)
      {
        u16string str = text.Utf16Value();
        Mem::write_str(addr, str);
        strMemOffset += SSString::count(str) + 2;
      }
      else
      {
        string str = text.Utf8Value();
        Mem::write_str(addr, str);
        strMemOffset += str.length() + 1;
      }
      memcpy_s(code.data() + argsOffset[i], sizeof(uintptr_t), &addr, sizeof(uintptr_t));
      continue;
    }
    else
    {
      value = _args.Get(i).ToNumber().Int64Value();
    }
    memcpy_s(code.data() + argsOffset[i], sizeof(uintptr_t), &value, sizeof(uintptr_t));
  }

  memcpy_s(code.data() + methodOffset, sizeof(uintptr_t), &lpMethod, sizeof(uintptr_t)); // method
  memcpy_s(code.data() + resultOffset, sizeof(uintptr_t), &lpResult, sizeof(uintptr_t)); // result

  memcpy_s((BYTE*)asm_func, code.size(), code.data(), code.size());
  
  /*
  printf("pid: %x\n", GetCurrentProcessId());
  printf("fun: %p\n", asm_func);
  getchar();
  */

  asm_func();

  uintptr_t result = *lpResult;
  if (newmem != nullptr) Mem::free(newmem);
  if (stringMem != nullptr) Mem::free(stringMem);
  for (auto cb : vect_cc)
  {
    Mem::free(cb->address);
    delete cb;
  }
  vect_cc.clear();
  nm_ret(result);
}
