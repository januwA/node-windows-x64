#pragma once
#include <iostream>
#include <Windows.h>
#include <napi.h>
#include "_napi_macro.h"
#include "ajanuw.h"

using namespace Napi;
using namespace std;
using namespace ajanuw;

Array _toTable(Env env, void* lpData, size_t size)
{
  auto r = Array::New(env, size);
  for (size_t i = 0; i < size; i++)
    r.Set(i, Number::New(env, *(uint8_t*)((uintptr_t)lpData + i)));
   return r;
}
Value word_to_byte_table(const CallbackInfo& info)
{
  nm_init;
  uint32_t data = nm_dword(info[0]);
  return _toTable(env, &data, sizeof(uint16_t));
}
Value dword_to_byte_table(const CallbackInfo& info)
{
  uint32_t data = nm_dword(info[0]);
  return _toTable(info.Env(), &data, sizeof(uint32_t));
}
Value qword_to_byte_table(const CallbackInfo& info)
{
  uint64_t data = nm_qword(info[0]);
  return _toTable(info.Env(), &data, sizeof(uint64_t));
}
Value float_to_byte_table(const CallbackInfo& info)
{
  float data = nm_float(info[0]);
  return _toTable(info.Env(), &data, sizeof(float));
}
Value double_to_byte_table(const CallbackInfo& info)
{
  double data = nm_double(info[0]);
  return _toTable(info.Env(), &data, sizeof(double));
}
Value str_to_byte_table(const CallbackInfo& info)
{
  string data = nm_str(info[0]);
  return _toTable(info.Env(), &data, data.length());
}
Value wstr_to_byte_table(const CallbackInfo& info)
{
  nm_init;
  u16string data = nm_wstr(info[0]);

  uintptr_t size = data.size() * 2;
  vector<uint8_t> bytes = Mem::read_bytes((void*)data.c_str(), size);

  auto r = Array::New(env, size);
  for (size_t i = 0; i < bytes.size(); i++) r.Set(i, bytes.at(i));
  return r;
}

#define BYTE_TABEL_TO(type) \
  nm_init;\
Array data =nm_arr(info[0]);\
size_t len = min(data.Length(), sizeof(type));\
BYTE* mem = (BYTE*)malloc(len);\
if (mem == NULL)\
{\
nm_jserr("malloc error.");\
nm_retu; \
}\
ZeroMemory(mem, len); \
for (size_t i = 0; i < len; i++)\
{\
auto v = nm_dword(data.Get(i)); \
memset(mem + i, v, sizeof(BYTE)); \
}\
auto r = Number::From(env, *(type*)mem); \
free(mem); \
return r; \

Value byte_table_to_word(const CallbackInfo& info)
{
  BYTE_TABEL_TO(WORD)
}
Value byte_table_to_dword(const CallbackInfo& info)
{
  BYTE_TABEL_TO(DWORD)
}

Value byte_table_to_qword(const CallbackInfo& info)
{
  BYTE_TABEL_TO(ULONGLONG)
}
Value byte_table_to_float(const CallbackInfo& info)
{
  BYTE_TABEL_TO(float)
}
Value byte_table_to_double(const CallbackInfo& info)
{
  BYTE_TABEL_TO(double)
}

#define BYTE_TABEL_TO_STR(type)\
nm_init;\
Array data = info[0].As<Array>();\
size_t len = data.Length() + 1;\
BYTE* mem = (BYTE*)malloc(len);\
if (mem == NULL)\
{\
nm_jserr("malloc error.");\
nm_retu; \
}\
ZeroMemory(mem, len);\
for (size_t i = 0; i < len; i++)\
{\
  auto v = nm_dword(data.Get(i)); \
  memset(mem + i, v, sizeof(BYTE));\
}\
auto r = String::From(env, (type*)mem);\
free(mem);\
return r;\

Value byte_table_to_str(const CallbackInfo& info)
{
   BYTE_TABEL_TO_STR(char)
}
Value byte_table_to_wstr(const CallbackInfo& info)
{
  BYTE_TABEL_TO_STR(char16_t)
}
