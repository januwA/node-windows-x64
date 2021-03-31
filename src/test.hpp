#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <psapi.h>
#include <napi.h>
#include <regex>
#include "ajanuw.h"

#include <asmjit/asmjit.h>
#include <asmtk/asmtk.h>

typedef int (*Func)();

Value test(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_retu;
}
