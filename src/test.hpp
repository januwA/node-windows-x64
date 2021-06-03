#pragma once
#include <iostream>
#include <napi.h>
#include <regex>
#include <string>
#include "ajanuw.h"
#include <chrono>
#include <cstring>

#include <asmjit/asmjit.h>
#include <asmtk/asmtk.h>

#define O(v) std::cout << v << std::endl
#define WO(v) std::wcout << v << std::endl

typedef int (*Func)();

Napi::Value test(const Napi::CallbackInfo &info)
{
  nm_init;
  

  nm_retu;
}
