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

Value test(const Napi::CallbackInfo &info)
{
  nm_init;

  // Napi::String jsStr = Napi::String::New(env, "xx()");
  // napi_value result;
  // napi_run_script(env, jsStr, &result);
  // return Napi::Value::From(env, result);

  auto eval = env.Global().Get("eval").As<Napi::Function>();
  return eval.Call({Napi::String::New(env, "xx()")});
}
