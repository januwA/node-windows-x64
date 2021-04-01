#pragma warning(disable : 26451 26812 6328)
#pragma once

#include <ostream>
#include <Windows.h>
#include <fstream>
#include <napi.h>
#include "_napi_macro.h"
#include "ajanuw.h"

using namespace std;
using namespace Napi;

Value memAlloc(const CallbackInfo &info)
{
  nm_init;

  uintptr_t lpAddress = 0;
  SIZE_T dwSize;
  DWORD flAllocationType = MEM_COMMIT | MEM_RESERVE;
  DWORD flProtect = PAGE_EXECUTE_READWRITE;

  if (!info.Length() || info[0].IsNumber())
  {
    dwSize = nm_is_nullishOr(info[0], nm_qword, 1024);
    nm_ret((uintptr_t)ajanuw::Mem::alloc(dwSize));
  }
  else
  {
    Object opt = nmi_obj(0);
    dwSize = nm_qword(opt.Get("dwSize"));
    lpAddress = nm_is_nullishOr(opt.Get("lpAddress"), nm_qword, lpAddress);
    flAllocationType = nm_is_nullishOr(opt.Get("flAllocationType"), nm_dword, flAllocationType);
    flProtect = nm_is_nullishOr(opt.Get("flProtect"), nm_dword, flProtect);
    nm_ret((uintptr_t)ajanuw::Mem::alloc(dwSize, (LPVOID)lpAddress, flAllocationType, flProtect));
  }
}

Value memAllocEx(const CallbackInfo &info)
{
  nm_init_cal(1);

  HANDLE hProcess = NULL;
  uintptr_t lpAddress = 0;
  SIZE_T dwSize;
  DWORD flAllocationType = MEM_COMMIT | MEM_RESERVE;
  DWORD flProtect = PAGE_EXECUTE_READWRITE;

  if (info[0].IsNumber())
  {
    hProcess = (HANDLE)nmi_qword(0);
    dwSize = nm_is_nullishOr(info[1], nm_qword, 1024);
    nm_ret((uintptr_t)ajanuw::Mem::allocEx(hProcess, dwSize));
  }
  else
  {
    Object opt = nmi_obj(0);
    hProcess = (HANDLE)nm_qword(opt.Get("hProcess"));
    dwSize = nm_qword(opt.Get("dwSize"));
    lpAddress = nm_is_nullishOr(opt.Get("lpAddress"), nm_qword, lpAddress);
    flAllocationType = nm_is_nullishOr(opt.Get("flAllocationType"), nm_dword, flAllocationType);
    flProtect = nm_is_nullishOr(opt.Get("flProtect"), nm_dword, flProtect);
    nm_ret((uintptr_t)ajanuw::Mem::allocEx(hProcess, dwSize, (LPVOID)lpAddress, flAllocationType, flProtect));
  }
}

Value memFree(const CallbackInfo &info)
{
  nm_init_cal(1);
  if (nmi_is_str(0))
    nm_retb(ajanuw::Mem::free(nmi_str(0)));
  else
    nm_retb(ajanuw::Mem::free((LPVOID)nmi_qword(0)));
}

Value memFreeEx(const CallbackInfo &info)
{
  nm_init_cal(2);
  if (nmi_is_str(1))
    nm_retb(ajanuw::Mem::freeEx((HANDLE)nmi_qword(0), nmi_str(1)));
  else
    nm_retb(ajanuw::Mem::freeEx((HANDLE)nmi_qword(0), (LPVOID)nmi_qword(1)));
}

Value memWriteStr(const CallbackInfo &info)
{
  nm_init_cal(2);
  String text = info[1].As<String>();
  Boolean isWideChar = info[2].ToBoolean();
  if (isWideChar)
  {
    if (nmi_is_str(0))
      ajanuw::Mem::wUstr(nmi_str(0), text.Utf16Value());
    else
      ajanuw::Mem::wUstr((void *)nmi_qword(0), text.Utf16Value());
  }
  else
  {
    if (nmi_is_str(0))
      ajanuw::Mem::wStr(nmi_str(0), text.Utf8Value());
    else
      ajanuw::Mem::wStr((void *)nmi_qword(0), text.Utf8Value());
  }
  nm_retbt;
}

Value memWriteStrEx(const CallbackInfo &info)
{
  nm_init_cal(3);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  const uint8_t ADDR_ARG_INDEX = 1;

  String text = info[2].As<String>();
  Boolean isWideChar = info[3].ToBoolean();
  if (isWideChar)
  {
    if (nmi_is_str(ADDR_ARG_INDEX))
      ajanuw::Mem::wUstrEx(hProcess, nmi_str(ADDR_ARG_INDEX), text.Utf16Value());
    else
      ajanuw::Mem::wUstrEx(hProcess, (void *)nmi_qword(ADDR_ARG_INDEX), text.Utf16Value());
  }
  else
  {
    if (nmi_is_str(ADDR_ARG_INDEX))
      ajanuw::Mem::wStrEx(hProcess, nmi_str(ADDR_ARG_INDEX), text.Utf8Value());
    else
      ajanuw::Mem::wStrEx(hProcess, (void *)nmi_qword(ADDR_ARG_INDEX), text.Utf8Value());
  }
  nm_retbt;
}

Value memWriteBytes(const CallbackInfo &info)
{
  nm_init_cal(2);
  vector<BYTE> vect_bytes;

  if (nmi_is_arr(1))
  {
    Array table = nmi_arr(1);
    for (size_t i = 0; i < table.Length(); i++)
      vect_bytes.push_back(nm_dword(table.Get(i)));
  }
  else
  {
    for (size_t i = 1; i < info.Length(); i++)
      vect_bytes.push_back(nm_dword(info[i]));
  }

  if (nmi_is_str(0))
    ajanuw::Mem::wBytes(nmi_str(0), vect_bytes);
  else
    ajanuw::Mem::wBytes((BYTE *)nmi_qword(0), vect_bytes);
  nm_retbt;
}

Value memWriteBytesEx(const CallbackInfo &info)
{
  nm_init_cal(3);
  HANDLE hProcess = (HANDLE)nmi_qword(0);

  Array table = nmi_arr(2);
  vector<BYTE> vect_bytes(table.Length());

  for (size_t i = 0; i < table.Length(); i++)
    vect_bytes.push_back(nm_dword(table.Get(i)));

  if (nmi_is_str(1))
    ajanuw::Mem::wBytesEx(hProcess, nmi_str(1), vect_bytes);
  else
    ajanuw::Mem::wBytesEx(hProcess, (BYTE *)nmi_qword(1), vect_bytes);
  nm_retbt;
}

Value memWriteWord(const CallbackInfo &info)
{
  nm_init_cal(2);
  if (nmi_is_str(0))
    ajanuw::Mem::wWord(nmi_str(0), nmi_dword(1));
  else
    ajanuw::Mem::wWord((void *)nmi_qword(0), nmi_dword(1));
  nm_retbt;
}

Value memWriteWordEx(const CallbackInfo &info)
{
  nm_init_cal(3);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  if (nmi_is_str(1))
    ajanuw::Mem::wWordEx(hProcess, nmi_str(1), nmi_dword(2));
  else
    ajanuw::Mem::wWordEx(hProcess, (void *)nmi_qword(1), nmi_dword(2));
  nm_retbt;
}

Value memWriteDword(const CallbackInfo &info)
{
  nm_init_cal(2);
  if (nmi_is_str(0))
    ajanuw::Mem::wDword(nmi_str(0), nmi_dword(1));
  else
    ajanuw::Mem::wDword((void *)nmi_qword(0), nmi_dword(1));
  nm_retbt;
}

Value memWriteDwordEx(const CallbackInfo &info)
{
  nm_init_cal(3);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  if (nmi_is_str(1))
    ajanuw::Mem::wDwordEx(hProcess, nmi_str(1), nmi_dword(2));
  else
    ajanuw::Mem::wDwordEx(hProcess, (void *)nmi_qword(1), nmi_dword(2));
  nm_retbt;
}

Value memWriteQword(const CallbackInfo &info)
{
  nm_init_cal(2);
  if (nmi_is_str(0))
    ajanuw::Mem::wQword(nmi_str(0), nmi_qword(1));
  else
    ajanuw::Mem::wQword((void *)nmi_qword(0), nmi_qword(1));
  nm_retbt;
}

Value memWriteQwordEx(const CallbackInfo &info)
{
  nm_init_cal(3);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  if (nmi_is_str(1))
    ajanuw::Mem::wQwordEx(hProcess, nmi_str(1), nmi_qword(2));
  else
    ajanuw::Mem::wQwordEx(hProcess, (void *)nmi_qword(1), nmi_qword(2));
  nm_retbt;
}

Value memWriteFloat(const CallbackInfo &info)
{
  nm_init_cal(2);
  if (nmi_is_str(0))
    ajanuw::Mem::wFloat(nmi_str(0), nmi_float(1));
  else
    ajanuw::Mem::wFloat((void *)nmi_qword(0), nmi_float(1));
  nm_retbt;
}
Value memWriteFloatEx(const CallbackInfo &info)
{
  nm_init_cal(3);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  if (nmi_is_str(1))
    ajanuw::Mem::wFloatEx(hProcess, nmi_str(1), nmi_float(2));
  else
    ajanuw::Mem::wFloatEx(hProcess, (void *)nmi_qword(1), nmi_float(2));
  nm_retbt;
}

Value memWriteDouble(const CallbackInfo &info)
{
  nm_init_cal(2);
  if (nmi_is_str(0))
    ajanuw::Mem::wDouble(nmi_str(0), nmi_double(1));
  else
    ajanuw::Mem::wDouble((void *)nmi_qword(0), nmi_double(1));
  nm_retbt;
}
Value memWriteDoubleEx(const CallbackInfo &info)
{
  nm_init_cal(3);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  if (nmi_is_str(1))
    ajanuw::Mem::wDoubleEx(hProcess, nmi_str(1), nmi_double(2));
  else
    ajanuw::Mem::wDoubleEx(hProcess, (void *)nmi_qword(1), nmi_double(2));
  nm_retbt;
}

Value memWriteRegionRoRile(const CallbackInfo &info)
{
  nm_init_cal(3);
  string filename = nmi_str(0);
  uint32_t size = nmi_qword(2);

  if (nmi_is_str(1))
    ajanuw::Mem::wRegionToFile(filename, nmi_str(1), size);
  else
    ajanuw::Mem::wRegionToFile(filename, (void *)nmi_qword(1), size);
  nm_retbt;
}

Value memWriteRegionToFileEx(const CallbackInfo &info)
{
  nm_init_cal(4);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  string filename = nmi_str(1);
  uint32_t size = nmi_qword(3);

  if (nmi_is_str(2))
    ajanuw::Mem::wRegionToFileEx(hProcess, filename, nmi_str(2), size);
  else
    ajanuw::Mem::wRegionToFileEx(hProcess, filename, (void *)nmi_qword(2), size);
  nm_retbt;
}

Value memReadStr(const CallbackInfo &info)
{
  nm_init_cal(1);
  uintptr_t maxSize = nm_is_nullishOr(info[1], nm_qword, -1);
  Boolean isWideChar = info[2].ToBoolean();

  if (isWideChar)
    if (nmi_is_str(0))
      nm_rets(ajanuw::Mem::rUstr(nmi_str(0), maxSize));
    else
      nm_rets(ajanuw::Mem::rUstr((char16_t *)nmi_qword(0), maxSize));
  else if (nmi_is_str(0))
    nm_rets(ajanuw::Mem::rStr(nmi_str(0), maxSize));
  else
    nm_rets(ajanuw::Mem::rStr((char *)nmi_qword(0), maxSize));
}

Value memReadStrEx(const CallbackInfo &info)
{
  nm_init_cal(2);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  uintptr_t maxSize = nm_is_nullishOr(info[2], nm_qword, -1);
  Boolean isWideChar = info[3].ToBoolean();

  if (isWideChar)
  {
    if (nmi_is_str(1))
      nm_rets(ajanuw::Mem::rUstrEx(hProcess, nmi_str(1), maxSize));
    else
      nm_rets(ajanuw::Mem::rUstrEx(hProcess, (char16_t *)nmi_qword(1), maxSize));
  }
  else
  {
    if (nmi_is_str(1))
      nm_rets(ajanuw::Mem::rStrEx(hProcess, nmi_str(1), maxSize));
    else
      nm_rets(ajanuw::Mem::rStrEx(hProcess, (char *)nmi_qword(1), maxSize));
  }
}

Value memReadBytes(const CallbackInfo &info)
{
  nm_init_cal(2);
  uintptr_t size = nmi_qword(1);
  std::vector<BYTE> result;

  if (nmi_is_str(0))
    result = ajanuw::Mem::rBytes(nmi_str(0), size);
  else
    result = ajanuw::Mem::rBytes((void *)nmi_qword(0), size);

  Array table = Array::New(env, size);
  for (int i = 0; i < size; i++)
    table.Set(i, result.at(i));
  return table;
}
Value memReadBytesEx(const CallbackInfo &info)
{
  nm_init_cal(3);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  uintptr_t size = nmi_qword(2);
  std::vector<BYTE> result;

  if (nmi_is_str(1))
    result = ajanuw::Mem::rBytesEx(hProcess, nmi_str(1), size);
  else
    result = ajanuw::Mem::rBytesEx(hProcess, (void *)nmi_qword(1), size);

  Array table = Array::New(env, size);
  for (int i = 0; i < size; i++)
    table.Set(i, result.at(i));
  return table;
}

Value memReadWord(const CallbackInfo &info)
{
  nm_init_cal(1);
  if (nmi_is_str(0))
    nm_ret(ajanuw::Mem::rWord(nmi_str(0)));
  else
    nm_ret(ajanuw::Mem::rWord((void *)nmi_qword(0)));
}
Value memReadWordEx(const CallbackInfo &info)
{
  nm_init_cal(2);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  if (nmi_is_str(1))
    nm_ret(ajanuw::Mem::rWordEx(hProcess, nmi_str(1)));
  else
    nm_ret(ajanuw::Mem::rWordEx(hProcess, (void *)nmi_qword(1)));
}

Value memReadDword(const CallbackInfo &info)
{
  nm_init_cal(1);
  if (nmi_is_str(0))
    nm_ret(ajanuw::Mem::rDword(nmi_str(0)));
  else
    nm_ret(ajanuw::Mem::rDword((void *)nmi_qword(0)));
}
Value memReadDwordEx(const CallbackInfo &info)
{
  nm_init_cal(2);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  if (nmi_is_str(1))
    nm_ret(ajanuw::Mem::rDwordEx(hProcess, nmi_str(1)));
  else
    nm_ret(ajanuw::Mem::rDwordEx(hProcess, (void *)nmi_qword(1)));
}

Value memReadQword(const CallbackInfo &info)
{
  nm_init_cal(1);
  if (nmi_is_str(0))
    nm_ret(ajanuw::Mem::rQword(nmi_str(0)));
  else
    nm_ret(ajanuw::Mem::rQword((void *)nmi_qword(0)));
}
Value memReadQwordEx(const CallbackInfo &info)
{
  nm_init_cal(2);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  if (nmi_is_str(1))
    nm_ret(ajanuw::Mem::rQwordEx(hProcess, nmi_str(1)));
  else
    nm_ret(ajanuw::Mem::rQwordEx(hProcess, (void *)nmi_qword(1)));
}

Value memReadPointer(const CallbackInfo &info)
{
  nm_init_cal(1);
  if (nmi_is_str(0))
    nm_ret(ajanuw::Mem::rPointer(nmi_str(0)));
  else
    nm_ret(ajanuw::Mem::rPointer((void *)nmi_qword(0)));
}
Value memReadPointerEx(const CallbackInfo &info)
{
  nm_init_cal(2);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  if (nmi_is_str(1))
    nm_ret(ajanuw::Mem::rPointerEx(hProcess, nmi_str(1)));
  else
    nm_ret(ajanuw::Mem::rPointerEx(hProcess, (void *)nmi_qword(1)));
}

Value memReadFloat(const CallbackInfo &info)
{
  nm_init_cal(1);
  if (nmi_is_str(0))
    nm_ret(ajanuw::Mem::rFloat(nmi_str(0)));
  else
    nm_ret(ajanuw::Mem::rFloat((void *)nmi_qword(0)));
}
Value memReadFloatEx(const CallbackInfo &info)
{
  nm_init_cal(2);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  if (nmi_is_str(1))
    nm_ret(ajanuw::Mem::rFloatEx(hProcess, nmi_str(1)));
  else
    nm_ret(ajanuw::Mem::rFloatEx(hProcess, (void *)nmi_qword(1)));
}
Value memReadDouble(const CallbackInfo &info)
{
  nm_init_cal(1);
  if (nmi_is_str(0))
    nm_ret(ajanuw::Mem::rDouble(nmi_str(0)));
  else
    nm_ret(ajanuw::Mem::rDouble((void *)nmi_qword(0)));
}
Value memReadDoubleEx(const CallbackInfo &info)
{
  nm_init_cal(2);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  if (nmi_is_str(1))
    nm_ret(ajanuw::Mem::rDoubleEx(hProcess, nmi_str(1)));
  else
    nm_ret(ajanuw::Mem::rDoubleEx(hProcess, (void *)nmi_qword(1)));
}

Value memReadRegionFromFile(const CallbackInfo &info)
{
  nm_init_cal(2);

  string filename = nmi_str(0);
  if (nmi_is_str(1))
    ajanuw::Mem::rRegionFromFile(filename, nmi_str(1));
  else
    ajanuw::Mem::rRegionFromFile(filename, (void *)nmi_qword(1));
  nm_retbt;
}

Value memReadRegionFromFileEx(const CallbackInfo &info)
{
  nm_init_cal(3);
  HANDLE hProcess = (HANDLE)nmi_qword(0);
  string filename = nmi_str(1);
  if (nmi_is_str(2))
    ajanuw::Mem::rRegionFromFileEx(hProcess, filename, nmi_str(2));
  else
    ajanuw::Mem::rRegionFromFileEx(hProcess, filename, (void *)nmi_qword(2));
  nm_retbt;
}
