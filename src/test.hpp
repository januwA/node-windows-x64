#pragma once
#include <iostream>
#include <Windows.h>
#include <napi.h>
using namespace Napi;

void test(const CallbackInfo &info)
{
  /* widestr to str
  string s1 = "中文";
  u16string s2;
  s2.resize(s1.length());
  MultiByteToWideChar(CP_UTF8, 0, s1.c_str(), s1.length(), (LPWSTR)s2.data(), s2.length());
  return String::New(info.Env(), s2.c_str());
  */

}