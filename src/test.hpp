#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <psapi.h>
#include <napi.h>
#include <regex>
#include <string>
#include "ajanuw.h"

#include <asmjit/asmjit.h>
#include <asmtk/asmtk.h>

#define O(v) std::cout << v << std::endl
#define WO(v) std::wcout << v << std::endl

typedef int (*Func)();

Napi::Value test(const Napi::CallbackInfo &info)
{
  nm_init;
  std::string s = "00 01 02";
  auto v = ajanuw::SSString::toBytes(s);
  O(v.size());
  for (auto i : v)
    printf("%d\n", i);
  nm_retu;
}
