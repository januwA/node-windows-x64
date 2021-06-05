#pragma warning(disable : 26451 26812 6328)
#pragma once

#include <ostream>
#include <fstream>
#include <napi.h>
#include "_napi_macro.h"
#include "_util.hpp"
#include "ajanuw.h"

#define EX_PROCESS HANDLE hProcess = (HANDLE)nmi_ull(0)

nm_api(memAlloc)
{
  nm_init;

  uintptr_t lpAddress = 0;
  SIZE_T dwSize;
  uint32_t flAllocationType = MEM_COMMIT | MEM_RESERVE;
  uint32_t flProtect = PAGE_EXECUTE_READWRITE;

  if (!info.Length() || info[0].IsNumber())
  {
    dwSize = nmi_is_und(0, ull, 1024);
    nm_ret((uintptr_t)ajanuw::Mem::alloc(dwSize));
  }
  else
  {
    auto o = nmi_o(0);
    dwSize = nmo_get("dwSize", ull);
    lpAddress = nmo_is_und("lpAddress", ull, lpAddress);
    flAllocationType = nmo_is_und("flAllocationType", ui, flAllocationType);
    flProtect = nmo_is_und("flProtect", ui, flProtect);
    nm_ret((uintptr_t)ajanuw::Mem::alloc(dwSize, (LPVOID)lpAddress, flAllocationType, flProtect));
  }
}

nm_api(memAllocEx)
{
  nm_init_cal(1);

  HANDLE hProcess = NULL;
  uintptr_t lpAddress = 0;
  SIZE_T dwSize;
  uint32_t flAllocationType = MEM_COMMIT | MEM_RESERVE;
  uint32_t flProtect = PAGE_EXECUTE_READWRITE;

  if (info[0].IsNumber())
  {
    hProcess = (HANDLE)nmi_ull(0);
    dwSize = nmi_is_und(1, ull, 1024);
    nm_ret((uintptr_t)ajanuw::Mem::allocEx(hProcess, dwSize));
  }
  else
  {
    Napi::Object o = nmi_o(0);
    hProcess = (HANDLE)nmo_get("hProcess", ull);
    dwSize = nmo_get("dwSize", ull);
    lpAddress = nmo_is_und("lpAddress", ull, lpAddress);
    flAllocationType = nmo_is_und("flAllocationType", ui, flAllocationType);
    flProtect = nmo_is_und("flProtect", ui, flProtect);
    nm_ret((uintptr_t)ajanuw::Mem::allocEx(hProcess, dwSize, (LPVOID)lpAddress, flAllocationType, flProtect));
  }
}

nm_api(memFree)
{
  nm_init_cal(1);
  if (nmi_is_s(0))
    nm_retb(ajanuw::Mem::free(nmi_s(0)));
  else
    nm_retb(ajanuw::Mem::free((LPVOID)nmi_ull(0)));
}

nm_api(memFreeEx)
{
  nm_init_cal(2);
  if (nmi_is_s(1))
    nm_retb(ajanuw::Mem::freeEx((HANDLE)nmi_ull(0), nmi_s(1)));
  else
    nm_retb(ajanuw::Mem::freeEx((HANDLE)nmi_ull(0), (LPVOID)nmi_ull(1)));
}

nm_api(memWriteStr)
{
  nm_init_cal(2);
  Napi::String text = info[1].As<Napi::String>();
  Napi::Boolean isWideChar = info[2].ToBoolean();
  if (isWideChar)
  {
    if (nmi_is_s(0))
      ajanuw::Mem::wUstr(nmi_s(0), text.Utf16Value());
    else
      ajanuw::Mem::wUstr((void *)nmi_ull(0), text.Utf16Value());
  }
  else
  {
    if (nmi_is_s(0))
      ajanuw::Mem::wStr(nmi_s(0), text.Utf8Value());
    else
      ajanuw::Mem::wStr((void *)nmi_ull(0), text.Utf8Value());
  }
  nm_retbt;
}

nm_api(memWriteStrEx)
{
  nm_init_cal(3);
  EX_PROCESS;
  const uint8_t ADDR_ARG_INDEX = 1;

  auto text = info[2].As<Napi::String>();
  auto isWideChar = info[3].ToBoolean();
  if (isWideChar)
  {
    if (nmi_is_s(ADDR_ARG_INDEX))
      ajanuw::Mem::wUstrEx(hProcess, nmi_s(ADDR_ARG_INDEX), text.Utf16Value());
    else
      ajanuw::Mem::wUstrEx(hProcess, (void *)nmi_ull(ADDR_ARG_INDEX), text.Utf16Value());
  }
  else
  {
    if (nmi_is_s(ADDR_ARG_INDEX))
      ajanuw::Mem::wStrEx(hProcess, nmi_s(ADDR_ARG_INDEX), text.Utf8Value());
    else
      ajanuw::Mem::wStrEx(hProcess, (void *)nmi_ull(ADDR_ARG_INDEX), text.Utf8Value());
  }
  nm_retbt;
}

nm_api(memWriteBytes)
{
  nm_init_cal(2);
  auto table = nmi_a(1);
  auto bytes = array_to_vector<uint8_t>(table, [](const Napi::Value &i)
                                        { return nm_ui(i); });

  if (nmi_is_s(0))
    ajanuw::Mem::wBytes(nmi_s(0), bytes);
  else
    ajanuw::Mem::wBytes((uint8_t *)nmi_ull(0), bytes);
  nm_retbt;
}

nm_api(memWriteBytesEx)
{
  nm_init_cal(3);
  EX_PROCESS;

  auto table = nmi_a(2);
  auto bytes = array_to_vector<uint8_t>(table, [](const Napi::Value &i)
                                        { return nm_ui(i); });

  if (nmi_is_s(1))
    ajanuw::Mem::wBytesEx(hProcess, nmi_s(1), bytes);
  else
    ajanuw::Mem::wBytesEx(hProcess, (uint8_t *)nmi_ull(1), bytes);
  nm_retbt;
}

nm_api(memWriteWord)
{
  nm_init_cal(2);
  if (nmi_is_s(0))
    ajanuw::Mem::wWord(nmi_s(0), nmi_ui(1));
  else
    ajanuw::Mem::wWord((void *)nmi_ull(0), nmi_ui(1));
  nm_retbt;
}

nm_api(memWriteWordEx)
{
  nm_init_cal(3);
  EX_PROCESS;
  if (nmi_is_s(1))
    ajanuw::Mem::wWordEx(hProcess, nmi_s(1), nmi_ui(2));
  else
    ajanuw::Mem::wWordEx(hProcess, (void *)nmi_ull(1), nmi_ui(2));
  nm_retbt;
}

nm_api(memWriteDword)
{
  nm_init_cal(2);
  if (nmi_is_s(0))
    ajanuw::Mem::wDword(nmi_s(0), nmi_ui(1));
  else
    ajanuw::Mem::wDword((void *)nmi_ull(0), nmi_ui(1));
  nm_retbt;
}

nm_api(memWriteDwordEx)
{
  nm_init_cal(3);
  EX_PROCESS;
  if (nmi_is_s(1))
    ajanuw::Mem::wDwordEx(hProcess, nmi_s(1), nmi_ui(2));
  else
    ajanuw::Mem::wDwordEx(hProcess, (void *)nmi_ull(1), nmi_ui(2));
  nm_retbt;
}

nm_api(memWriteQword)
{
  nm_init_cal(2);
  if (nmi_is_s(0))
    ajanuw::Mem::wQword(nmi_s(0), nmi_ull(1));
  else
    ajanuw::Mem::wQword((void *)nmi_ull(0), nmi_ull(1));
  nm_retbt;
}

nm_api(memWriteQwordEx)
{
  nm_init_cal(3);
  EX_PROCESS;
  if (nmi_is_s(1))
    ajanuw::Mem::wQwordEx(hProcess, nmi_s(1), nmi_ull(2));
  else
    ajanuw::Mem::wQwordEx(hProcess, (void *)nmi_ull(1), nmi_ull(2));
  nm_retbt;
}

nm_api(memWriteFloat)
{
  nm_init_cal(2);
  if (nmi_is_s(0))
    ajanuw::Mem::wFloat(nmi_s(0), nmi_f(1));
  else
    ajanuw::Mem::wFloat((void *)nmi_ull(0), nmi_f(1));
  nm_retbt;
}
nm_api(memWriteFloatEx)
{
  nm_init_cal(3);
  EX_PROCESS;
  if (nmi_is_s(1))
    ajanuw::Mem::wFloatEx(hProcess, nmi_s(1), nmi_f(2));
  else
    ajanuw::Mem::wFloatEx(hProcess, (void *)nmi_ull(1), nmi_f(2));
  nm_retbt;
}

nm_api(memWriteDouble)
{
  nm_init_cal(2);
  if (nmi_is_s(0))
    ajanuw::Mem::wDouble(nmi_s(0), nmi_d(1));
  else
    ajanuw::Mem::wDouble((void *)nmi_ull(0), nmi_d(1));
  nm_retbt;
}
nm_api(memWriteDoubleEx)
{
  nm_init_cal(3);
  EX_PROCESS;
  if (nmi_is_s(1))
    ajanuw::Mem::wDoubleEx(hProcess, nmi_s(1), nmi_d(2));
  else
    ajanuw::Mem::wDoubleEx(hProcess, (void *)nmi_ull(1), nmi_d(2));
  nm_retbt;
}

nm_api(memWriteRegionToFile)
{
  nm_init_cal(3);
  std::string filename = nmi_s(0);
  uint32_t size = nmi_ull(2);

  if (nmi_is_s(1))
    ajanuw::Mem::wRegionToFile(filename, nmi_s(1), size);
  else
    ajanuw::Mem::wRegionToFile(filename, (void *)nmi_ull(1), size);
  nm_retbt;
}

nm_api(memWriteRegionToFileEx)
{
  nm_init_cal(4);
  EX_PROCESS;
  std::string filename = nmi_s(1);
  uint32_t size = nmi_ull(3);

  if (nmi_is_s(2))
    ajanuw::Mem::wRegionToFileEx(hProcess, filename, nmi_s(2), size);
  else
    ajanuw::Mem::wRegionToFileEx(hProcess, filename, (void *)nmi_ull(2), size);
  nm_retbt;
}

nm_api(memReadStr)
{
  nm_init_cal(1);
  auto max = nmi_is_und(1, ull, -1);
  auto bWideChar = nmi_b(2);

  if (bWideChar)
    if (nmi_is_s(0))
      nm_rets(ajanuw::Mem::rUstr(nmi_s(0), max));
    else
      nm_rets(ajanuw::Mem::rUstr((char16_t *)nmi_ull(0), max));
  else if (nmi_is_s(0))
    nm_rets(ajanuw::Mem::rStr(nmi_s(0), max));
  else
    nm_rets(ajanuw::Mem::rStr((char *)nmi_ull(0), max));
}

nm_api(memReadStrEx)
{
  nm_init_cal(2);
  EX_PROCESS;
  auto maxSize = nmi_is_und(2, ull, -1);
  auto isWideChar = info[3].ToBoolean();

  if (isWideChar)
  {
    if (nmi_is_s(1))
      nm_rets(ajanuw::Mem::rUstrEx(hProcess, nmi_s(1), maxSize));
    else
      nm_rets(ajanuw::Mem::rUstrEx(hProcess, (char16_t *)nmi_ull(1), maxSize));
  }
  else
  {
    if (nmi_is_s(1))
      nm_rets(ajanuw::Mem::rStrEx(hProcess, nmi_s(1), maxSize));
    else
      nm_rets(ajanuw::Mem::rStrEx(hProcess, (char *)nmi_ull(1), maxSize));
  }
}

nm_api(memReadBytes)
{
  nm_init_cal(2);
  auto size = nmi_ll(1);

  if (size <= 0)
    return Napi::Array::New(env);

  std::vector<uint8_t> result;

  if (nmi_is_s(0))
    result = ajanuw::Mem::rBytes(nmi_s(0), size);
  else
    result = ajanuw::Mem::rBytes((void *)nmi_ull(0), size);

  return span_to_array<uint8_t>(env, result);
}
nm_api(memReadBytesEx)
{
  nm_init_cal(3);
  EX_PROCESS;
  auto size = nmi_ll(2);

  if (size <= 0)
    return Napi::Array::New(env);

  std::vector<uint8_t> result;

  if (nmi_is_s(1))
    result = ajanuw::Mem::rBytesEx(hProcess, nmi_s(1), size);
  else
    result = ajanuw::Mem::rBytesEx(hProcess, (void *)nmi_ull(1), size);

  return span_to_array<uint8_t>(env, result);
}

nm_api(memReadWord)
{
  nm_init_cal(1);
  if (nmi_is_s(0))
    nm_ret(ajanuw::Mem::rWord(nmi_s(0)));
  else
    nm_ret(ajanuw::Mem::rWord((void *)nmi_ull(0)));
}
nm_api(memReadWordEx)
{
  nm_init_cal(2);
  EX_PROCESS;
  if (nmi_is_s(1))
    nm_ret(ajanuw::Mem::rWordEx(hProcess, nmi_s(1)));
  else
    nm_ret(ajanuw::Mem::rWordEx(hProcess, (void *)nmi_ull(1)));
}

nm_api(memReadDword)
{
  nm_init_cal(1);
  if (nmi_is_s(0))
    nm_ret(ajanuw::Mem::rDword(nmi_s(0)));
  else
    nm_ret(ajanuw::Mem::rDword((void *)nmi_ull(0)));
}
nm_api(memReadDwordEx)
{
  nm_init_cal(2);
  EX_PROCESS;
  if (nmi_is_s(1))
    nm_ret(ajanuw::Mem::rDwordEx(hProcess, nmi_s(1)));
  else
    nm_ret(ajanuw::Mem::rDwordEx(hProcess, (void *)nmi_ull(1)));
}

nm_api(memReadQword)
{
  nm_init_cal(1);
  if (nmi_is_s(0))
    nm_ret(ajanuw::Mem::rQword(nmi_s(0)));
  else
    nm_ret(ajanuw::Mem::rQword((void *)nmi_ull(0)));
}
nm_api(memReadQwordEx)
{
  nm_init_cal(2);
  EX_PROCESS;
  if (nmi_is_s(1))
    nm_ret(ajanuw::Mem::rQwordEx(hProcess, nmi_s(1)));
  else
    nm_ret(ajanuw::Mem::rQwordEx(hProcess, (void *)nmi_ull(1)));
}

nm_api(memReadPointer)
{
  nm_init_cal(1);
  if (nmi_is_s(0))
    nm_ret(ajanuw::Mem::rPointer(nmi_s(0)));
  else
    nm_ret(ajanuw::Mem::rPointer((void *)nmi_ull(0)));
}
nm_api(memReadPointerEx)
{
  nm_init_cal(2);
  EX_PROCESS;
  if (nmi_is_s(1))
    nm_ret(ajanuw::Mem::rPointerEx(hProcess, nmi_s(1)));
  else
    nm_ret(ajanuw::Mem::rPointerEx(hProcess, (void *)nmi_ull(1)));
}

nm_api(memReadFloat)
{
  nm_init_cal(1);
  if (nmi_is_s(0))
    nm_ret(ajanuw::Mem::rFloat(nmi_s(0)));
  else
    nm_ret(ajanuw::Mem::rFloat((void *)nmi_ull(0)));
}
nm_api(memReadFloatEx)
{
  nm_init_cal(2);
  EX_PROCESS;
  if (nmi_is_s(1))
    nm_ret(ajanuw::Mem::rFloatEx(hProcess, nmi_s(1)));
  else
    nm_ret(ajanuw::Mem::rFloatEx(hProcess, (void *)nmi_ull(1)));
}
nm_api(memReadDouble)
{
  nm_init_cal(1);
  if (nmi_is_s(0))
    nm_ret(ajanuw::Mem::rDouble(nmi_s(0)));
  else
    nm_ret(ajanuw::Mem::rDouble((void *)nmi_ull(0)));
}
nm_api(memReadDoubleEx)
{
  nm_init_cal(2);
  EX_PROCESS;
  if (nmi_is_s(1))
    nm_ret(ajanuw::Mem::rDoubleEx(hProcess, nmi_s(1)));
  else
    nm_ret(ajanuw::Mem::rDoubleEx(hProcess, (void *)nmi_ull(1)));
}

nm_api(memReadRegionFromFile)
{
  nm_init_cal(2);
  auto filename = nmi_s(0);
  if (nmi_is_s(1))
    ajanuw::Mem::rRegionFromFile(filename, nmi_s(1));
  else
    ajanuw::Mem::rRegionFromFile(filename, (void *)nmi_ull(1));
  nm_retbt;
}

nm_api(memReadRegionFromFileEx)
{
  nm_init_cal(3);
  EX_PROCESS;
  auto filename = nmi_s(1);
  if (nmi_is_s(2))
    ajanuw::Mem::rRegionFromFileEx(hProcess, filename, nmi_s(2));
  else
    ajanuw::Mem::rRegionFromFileEx(hProcess, filename, (void *)nmi_ull(2));
  nm_retbt;
}
