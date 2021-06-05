#pragma once
#include <iostream>
#include <napi.h>
#include <regex>
#include <string>
#include "ajanuw.h"
#include <memory>

#include <asmjit/asmjit.h>
#include <asmtk/asmtk.h>

#include "./_util.hpp"

#define O(v) std::cout << v << std::endl
#define WO(v) std::wcout << v << std::endl

nm_api(test)
{
  nm_init;

  nm_retu;
}
