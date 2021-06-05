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

#include "./_util.hpp"

#define O(v) std::cout << v << std::endl
#define WO(v) std::wcout << v << std::endl

typedef int (*Func)();

nm_api(test)
{
  nm_init;

  auto va = ajanuw::Mem::VAManage(10, 0);
  nm_retu;
}
