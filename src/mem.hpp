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
using namespace ajanuw;

Value mem_alloc(const CallbackInfo &info)
{
  nm_init;

  uintptr_t lpAddress = 0;
  SIZE_T dwSize;
  DWORD flAllocationType = MEM_COMMIT | MEM_RESERVE;
  DWORD flProtect = PAGE_EXECUTE_READWRITE;

  if (!info.Length() || info[0].IsNumber())
  {
    dwSize = nm_is_nullishOr(info[0], nm_qword, 1024);
    nm_ret((uintptr_t)Mem::alloc(dwSize));
  }
  else
  {
    Object opt = nmi_obj(0);
    dwSize = nm_qword(opt.Get("dwSize"));
    lpAddress = nm_is_nullishOr(opt.Get("lpAddress"), nm_qword, lpAddress);
    flAllocationType = nm_is_nullishOr(opt.Get("flAllocationType"), nm_dword, flAllocationType);
    flProtect = nm_is_nullishOr(opt.Get("flProtect"), nm_dword, flProtect);
    nm_ret((uintptr_t)Mem::alloc(dwSize, (LPVOID)lpAddress, flAllocationType, flProtect));
  }
}

Value mem_free(const CallbackInfo &info)
{
  nm_init_cal(1);
  if (nmi_is_str(0))
    nm_retb(Mem::free(nmi_str(0)));
  else
    nm_retb(Mem::free((LPVOID)nmi_qword(0)));
}

Value mem_write_str(const CallbackInfo &info)
{
  nm_init_cal(2);
  String text = info[1].As<String>();
  Boolean isWideChar = info[2].ToBoolean();
  if (isWideChar)
  {
    if (nmi_is_str(0))
      ajanuw::Mem::write_ustr(nmi_str(0), text.Utf16Value());
    else
      ajanuw::Mem::write_ustr((void *)nmi_qword(0), text.Utf16Value());
  }
  else
  {
    if (nmi_is_str(0))
      ajanuw::Mem::write_str(nmi_str(0), text.Utf8Value());
    else
      ajanuw::Mem::write_str((void *)nmi_qword(0), text.Utf8Value());
  }
  nm_retbt;
}
Value mem_write_bytes(const CallbackInfo &info)
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
    Mem::write_bytes(nmi_str(0), vect_bytes);
  else
    Mem::write_bytes((BYTE *)nmi_qword(0), vect_bytes);
  nm_retbt;
}
Value mem_write_word(const CallbackInfo &info)
{
  nm_init_cal(2);
  if (nmi_is_str(0))
    Mem::write_word(nmi_str(0), nmi_dword(1));
  else
    Mem::write_word((void *)nmi_qword(0), nmi_dword(1));
  nm_retbt;
}
Value mem_write_dword(const CallbackInfo &info)
{
  nm_init_cal(2);
  if (nmi_is_str(0))
    Mem::write_dword(nmi_str(0), nmi_dword(1));
  else
    Mem::write_dword((void *)nmi_qword(0), nmi_dword(1));
  nm_retbt;
}
Value mem_write_qword(const CallbackInfo &info)
{
  nm_init_cal(2);
  if (nmi_is_str(0))
    Mem::write_qword(nmi_str(0), nmi_qword(1));
  else
    Mem::write_qword((void *)nmi_qword(0), nmi_qword(1));
  nm_retbt;
}
Value mem_write_float(const CallbackInfo &info)
{
  nm_init_cal(2);
  if (nmi_is_str(0))
    Mem::write_float(nmi_str(0), nmi_float(1));
  else
    Mem::write_float((void *)nmi_qword(0), nmi_float(1));
  nm_retbt;
}
Value mem_write_double(const CallbackInfo &info)
{
  nm_init_cal(2);
  if (nmi_is_str(0))
    Mem::write_double(nmi_str(0), nmi_double(1));
  else
    Mem::write_double((void *)nmi_qword(0), nmi_double(1));
  nm_retbt;
}
Value mem_write_region_to_file(const CallbackInfo &info)
{
  nm_init_cal(3);
  string filename = nmi_str(0);
  uint32_t size = nmi_qword(2);

  if (nmi_is_str(1))
    Mem::write_region_to_file(filename, nmi_str(1), size);
  else
    Mem::write_region_to_file(filename, (void *)nmi_qword(1), size);
  nm_retbt;
}

Value mem_read_str(const CallbackInfo &info)
{
  nm_init_cal(1);
  uintptr_t maxSize = nm_is_nullishOr(info[1], nm_qword, -1);
  Boolean isWideChar = info[2].ToBoolean();

  if (isWideChar)
    if (nmi_is_str(0))
      nm_rets(ajanuw::Mem::read_ustr(nmi_str(0), maxSize));
    else
      nm_rets(ajanuw::Mem::read_ustr((char16_t *)nmi_qword(0), maxSize));
  else if (nmi_is_str(0))
    nm_rets(ajanuw::Mem::read_str(nmi_str(0), maxSize));
  else
    nm_rets(ajanuw::Mem::read_str((char *)nmi_qword(0), maxSize));
}
Value mem_read_bytes(const CallbackInfo &info)
{
  nm_init_cal(2);
  uintptr_t size = nmi_qword(1);
  std::vector<BYTE> result;

  if (nmi_is_str(0))
    result = Mem::read_bytes(nmi_str(0), size);
  else
    result = Mem::read_bytes((void *)nmi_qword(0), size);

  Array table = Array::New(env, size);
  for (int i = 0; i < size; i++)
    table.Set(i, result.at(i));
  return table;
}
Value mem_read_word(const CallbackInfo &info)
{
  nm_init_cal(1);
  if (nmi_is_str(0))
    nm_ret(Mem::read_word(nmi_str(0)));
  else
    nm_ret(Mem::read_word((void *)nmi_qword(0)));
}
Value mem_read_dword(const CallbackInfo &info)
{
  nm_init_cal(1);
  if (nmi_is_str(0))
    nm_ret(Mem::read_dword(nmi_str(0)));
  else
    nm_ret(Mem::read_dword((void *)nmi_qword(0)));
}
Value mem_read_qword(const CallbackInfo &info)
{
  nm_init_cal(1);
  if (nmi_is_str(0))
    nm_ret(Mem::read_qword(nmi_str(0)));
  else
    nm_ret(Mem::read_qword((void *)nmi_qword(0)));
}
Value mem_read_pointer(const CallbackInfo &info)
{
  nm_init_cal(1);
  if (nmi_is_str(0))
    nm_ret(Mem::read_pointer(nmi_str(0)));
  else
    nm_ret(Mem::read_pointer((void *)nmi_qword(0)));
}
Value mem_read_float(const CallbackInfo &info)
{
  nm_init;
  if (nmi_is_str(0))
    nm_ret(Mem::read_float(nmi_str(0)));
  else
    nm_ret(Mem::read_float((void *)nmi_qword(0)));
}
Value mem_read_double(const CallbackInfo &info)
{
  nm_init_cal(1);
  if (nmi_is_str(0))
    nm_ret(Mem::read_double(nmi_str(0)));
  else
    nm_ret(Mem::read_double((void *)nmi_qword(0)));
}

Value mem_read_region_from_file(const CallbackInfo &info)
{
  nm_init_cal(2);

  string filename = nmi_str(0);
  if (nmi_is_str(1))
    Mem::read_region_from_file(filename, nmi_str(1));
  else
    Mem::read_region_from_file(filename, (void *)nmi_qword(1));
  nm_retbt;
}
