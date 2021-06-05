#pragma once
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

nm_api(wordToByteTable)
{
  nm_init;
  uint32_t data = nm_ui(info[0]);
  return _toTable(env, &data, sizeof(uint16_t));
}
nm_api(dwordToByteTable)
{
  nm_init;
  uint32_t data = nm_ui(info[0]);
  return _toTable(env, &data, sizeof(uint32_t));
}
nm_api(qwordToByteTable)
{
  nm_init;
  uint64_t data = nm_ull(info[0]);
  return _toTable(env, &data, sizeof(uint64_t));
}
nm_api(floatToByteTable)
{
  nm_init;
  float data = nm_f(info[0]);
  return _toTable(env, &data, sizeof(float));
}
nm_api(doubleToByteTable)
{
  nm_init;
  double data = nm_d(info[0]);
  return _toTable(env, &data, sizeof(double));
}
nm_api(strToByteTable)
{
  nm_init;
  auto str = nm_s(info[0]);
  return _toTable(env, str.data(), ajanuw::sstr::count(str));
}
nm_api(wstrToByteTable)
{
  nm_init;
  auto ustr = nm_us(info[0]);
  return _toTable(env, ustr.data(), ajanuw::sstr::count(ustr));
}

#define BYTE_TABEL_TO(type)                       \
  nm_init;                                        \
  auto table = nm_a(info[0]);                     \
  size_t len = min(table.Length(), sizeof(type)); \
  auto mem = (uint8_t *)malloc(len);              \
  if (!mem)                                       \
  {                                               \
    nm_err("malloc error.");                      \
    nm_retu;                                      \
  }                                               \
  ZeroMemory(mem, len);                           \
  for (size_t i = 0; i < len; i++)                \
  {                                               \
    auto v = nm_ui(table.Get(i));                 \
    memset(mem + i, v, sizeof(uint8_t));          \
  }                                               \
  auto r = Napi::Number::From(env, *(type *)mem); \
  free(mem);                                      \
  return r

nm_api(byteTableToWord)
{
  BYTE_TABEL_TO(uint16_t);
}
nm_api(byteTableToDword)
{
  BYTE_TABEL_TO(uint32_t);
}

nm_api(byteTableToQword)
{
  BYTE_TABEL_TO(ULONGLONG);
}
nm_api(byteTableToFloat)
{
  BYTE_TABEL_TO(float);
}
nm_api(byteTableToDouble)
{
  BYTE_TABEL_TO(double);
}

#define BYTE_TABEL_TO_STR(type)                  \
  nm_init;                                       \
  auto data = nmi_a(0);                          \
  size_t len = data.Length() + 1;                \
  auto mem = (uint8_t *)malloc(len);             \
  if (mem == NULL)                               \
  {                                              \
    nm_err("malloc error.");                     \
    nm_retu;                                     \
  }                                              \
  ZeroMemory(mem, len);                          \
  for (size_t i = 0; i < len; i++)               \
  {                                              \
    auto v = nm_ui(data.Get(i));                 \
    memset(mem + i, v, sizeof(uint8_t));         \
  }                                              \
  auto r = Napi::String::From(env, (type *)mem); \
  free(mem);                                     \
  return r

nm_api(byteTableToStr)
{
  BYTE_TABEL_TO_STR(char);
}

nm_api(byteTableToWstr)
{
  BYTE_TABEL_TO_STR(char16_t);
}
