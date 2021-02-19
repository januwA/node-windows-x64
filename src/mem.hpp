#pragma warning(disable : 26451 26812 6328)
#pragma once

#include <ostream>
#include <Windows.h>
#include <fstream>
#include <napi.h>
#include "_napi_macro.h"
#include "_utils.h"

using namespace std;
using namespace Napi;

Value mem_alloc(const CallbackInfo &info)
{
  nm_init;

  uintptr_t lpAddress = 0;
  SIZE_T dwSize;
  DWORD flAllocationType = MEM_COMMIT | MEM_RESERVE;
  DWORD flProtect = PAGE_EXECUTE_READWRITE;

  if (!info.Length() || info[0].IsNumber())
  {
    dwSize = nm_IsNullishOr(info[0], nm_qword, 1024);
    nm_ret((uintptr_t)Mem::alloc(dwSize));
  }
  else
  {
    Object opt = nm_obj(info[0]);
    dwSize = nm_qword(opt.Get("dwSize"));
    lpAddress = nm_IsNullishOr(opt.Get("lpAddress"), nm_qword, lpAddress);
    flAllocationType = nm_IsNullishOr(opt.Get("flAllocationType"), nm_dword, flAllocationType);
    flProtect = nm_IsNullishOr(opt.Get("flProtect"), nm_dword, flProtect);
    nm_ret((uintptr_t)Mem::alloc(dwSize, (LPVOID)lpAddress, flAllocationType, flProtect)
    );
  }
}

Value mem_free(const CallbackInfo &info)
{
  nm_init_cal(1);
  nm_retb(Mem::free((LPVOID)nm_qword(info[0])));
}

Value mem_write_str(const CallbackInfo &info)
{
  nm_init_cal(2);
  uintptr_t lpAddress = nm_qword(info[0]);
  String text = info[1].As<String>();
  Boolean isWideChar = info[2].ToBoolean();
  if (isWideChar)
    SSString::strToMem((void*)lpAddress, text.Utf16Value());
  else
    SSString::strToMem((void*)lpAddress, text.Utf8Value());
  nm_retbt;
}
Value mem_write_bytes(const CallbackInfo &info)
{
  nm_init_cal(2);
  uintptr_t lpAddress = nm_qword(info[0]);
  vector<BYTE> vect_bytes;

  if (info[1].IsArray())
  {
    Array table = nm_arr(info[1]);
    for (size_t i = 0; i < table.Length(); i++)
      vect_bytes.push_back(nm_dword(table.Get(i)));
  }
  else
  {
    for (size_t i = 1; i < info.Length(); i++)
      vect_bytes.push_back(nm_dword(info[i]));
  }

  Mem::write_bytes((BYTE*)lpAddress, vect_bytes);
  nm_retbt;
}
Value mem_write_word(const CallbackInfo& info)
{
  nm_init_cal(2);
  Mem::write_word((void*)nm_qword(info[0]), nm_dword(info[1]));
  nm_retbt;
}
Value mem_write_dword(const CallbackInfo &info)
{
  nm_init_cal(2);
  Mem::write_dword((void*)nm_qword(info[0]), nm_dword(info[1]));
  nm_retbt;
}
Value mem_write_qword(const CallbackInfo &info)
{
  nm_init_cal(2);
  Mem::write_qword((void*)nm_qword(info[0]), nm_qword(info[1]));
  nm_retbt;
}
Value mem_write_float(const CallbackInfo &info)
{
  nm_init_cal(2);
  Mem::write_float((void*)nm_qword(info[0]), nm_float(info[1]));
  nm_retbt;
}
Value mem_write_double(const CallbackInfo &info)
{
  nm_init_cal(2);
  Mem::write_double((void*)nm_qword(info[0]), nm_double(info[1]));
  nm_retbt;
}
Value mem_write_region_to_file(const CallbackInfo& info)
{
  nm_init_cal(3);
  string filename = nm_str(info[0]);
  uintptr_t lpAddress = nm_qword(info[1]);
  uint32_t size = nm_qword(info[2]);
  Mem::write_region_to_file(filename, (void*)lpAddress, size);
  nm_retbt;
}

Value mem_read_str(const CallbackInfo &info)
{
  nm_init_cal(1);
  uintptr_t lpAddress = nm_qword(info[0]);
  uintptr_t maxSize = nm_IsNullishOr(info[1], nm_qword, -1);
  Boolean isWideChar = info[2].ToBoolean();

  if (isWideChar) nm_rets(SSString::ustrFormMem((void*)lpAddress, maxSize));
  else nm_rets(SSString::strFormMem((void*)lpAddress, maxSize));
}
Value mem_read_bytes(const CallbackInfo &info)
{
  nm_init_cal(2);
  uintptr_t lpAddress = nm_qword(info[0]);
  uintptr_t size = nm_qword(info[1]);
  
  auto bytes = Mem::read_bytes((void*)lpAddress, size);
  Array table = Array::New(env, size);
  for (int i = 0; i < size; i++) table.Set(i, bytes.at(i));
  return table;
}
Value mem_read_word(const CallbackInfo &info)
{
  nm_init_cal(1);
  nm_ret(Mem::read_word((void*)nm_qword(info[0])));
}
Value mem_read_dword(const CallbackInfo &info)
{
  nm_init_cal(1);
  nm_ret(Mem::read_dword((void*)nm_qword(info[0])));
}
Value mem_read_qword(const CallbackInfo &info)
{
  nm_init_cal(1);
  nm_ret(Mem::read_qword((void*)nm_qword(info[0])));
}
Value mem_read_pointer(const CallbackInfo &info)
{
  nm_init_cal(1);
  nm_ret(Mem::read_pointer((void*)nm_qword(info[0])));
}
Value mem_read_float(const CallbackInfo &info)
{
  nm_init;
  nm_ret(Mem::read_float((void*)nm_qword(info[0])));
}
Value mem_read_double(const CallbackInfo &info)
{
  nm_init_cal(1);
  nm_ret(Mem::read_double((void*)nm_qword(info[0])));
}

Value mem_read_region_from_file(const CallbackInfo &info)
{
  nm_init_cal(2);

  string filename = nm_str(info[0]);
  uintptr_t lpAddress = nm_qword(info[1]);
  Mem::read_region_from_file(filename, (void*)lpAddress);
  nm_retbt;
}
