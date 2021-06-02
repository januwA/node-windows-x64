#include <iostream>
#include <Windows.h>
#include <napi.h>
#include "_napi_macro.h"
#include "ajanuw.h"

Napi::Array _toTable(const Napi::Env &env, void *lpData, size_t size)
{
  auto r = Napi::Array::New(env, size);
  for (size_t i = 0; i < size; i++)
    r.Set(i, Napi::Number::New(env, *((uint8_t *)lpData + i)));
  return r;
}

Napi::Value wordToByteTable(const Napi::CallbackInfo &info)
{
  nm_init;
  uint32_t data = nm_dword(info[0]);
  return _toTable(env, &data, sizeof(uint16_t));
}
Napi::Value dwordToByteTable(const Napi::CallbackInfo &info)
{
  nm_init;
  uint32_t data = nm_dword(info[0]);
  return _toTable(env, &data, sizeof(uint32_t));
}
Napi::Value qwordToByteTable(const Napi::CallbackInfo &info)
{
  nm_init;
  uint64_t data = nm_qword(info[0]);
  return _toTable(env, &data, sizeof(uint64_t));
}
Napi::Value floatToByteTable(const Napi::CallbackInfo &info)
{
  nm_init;
  float data = nm_float(info[0]);
  return _toTable(env, &data, sizeof(float));
}
Napi::Value doubleToByteTable(const Napi::CallbackInfo &info)
{
  nm_init;
  double data = nm_double(info[0]);
  return _toTable(env, &data, sizeof(double));
}
Napi::Value strToByteTable(const Napi::CallbackInfo &info)
{
  nm_init;
  auto str = nm_str(info[0]);
  return _toTable(env, str.data(), ajanuw::SSString::count(str));
}
Napi::Value wstrToByteTable(const Napi::CallbackInfo &info)
{
  nm_init;
  auto ustr = nm_ustr(info[0]);
  return _toTable(env, ustr.data(), ajanuw::SSString::count(ustr));
}

#define BYTE_TABEL_TO(type)                       \
  nm_init;                                        \
  auto table = nm_arr(info[0]);                   \
  size_t len = min(table.Length(), sizeof(type)); \
  auto mem = (uint8_t *)malloc(len);              \
  if (!mem)                                       \
  {                                               \
    nm_jserr("malloc error.");                    \
    nm_retu;                                      \
  }                                               \
  ZeroMemory(mem, len);                           \
  for (size_t i = 0; i < len; i++)                \
  {                                               \
    auto v = nm_dword(table.Get(i));              \
    memset(mem + i, v, sizeof(uint8_t));          \
  }                                               \
  auto r = Napi::Number::From(env, *(type *)mem); \
  free(mem);                                      \
  return r

Napi::Value byteTableToWord(const Napi::CallbackInfo &info)
{
  BYTE_TABEL_TO(uint16_t);
}
Napi::Value byteTableToDword(const Napi::CallbackInfo &info)
{
  BYTE_TABEL_TO(uint32_t);
}

Napi::Value byteTableToQword(const Napi::CallbackInfo &info)
{
  BYTE_TABEL_TO(ULONGLONG);
}
Napi::Value byteTableToFloat(const Napi::CallbackInfo &info)
{
  BYTE_TABEL_TO(float);
}
Napi::Value byteTableToDouble(const Napi::CallbackInfo &info)
{
  BYTE_TABEL_TO(double);
}

#define BYTE_TABEL_TO_STR(type)                  \
  nm_init;                                       \
  auto data = nmi_arr(0);                        \
  size_t len = data.Length() + 1;                \
  auto mem = (uint8_t *)malloc(len);             \
  if (mem == NULL)                               \
  {                                              \
    nm_jserr("malloc error.");                   \
    nm_retu;                                     \
  }                                              \
  ZeroMemory(mem, len);                          \
  for (size_t i = 0; i < len; i++)               \
  {                                              \
    auto v = nm_dword(data.Get(i));              \
    memset(mem + i, v, sizeof(uint8_t));         \
  }                                              \
  auto r = Napi::String::From(env, (type *)mem); \
  free(mem);                                     \
  return r

Napi::Value byteTableToStr(const Napi::CallbackInfo &info)
{
  BYTE_TABEL_TO_STR(char);
}

Napi::Value byteTableToWstr(const Napi::CallbackInfo &info)
{
  BYTE_TABEL_TO_STR(char16_t);
}
