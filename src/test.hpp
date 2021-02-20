#pragma once
#include <iostream>
#include <Windows.h>
#include <napi.h>
#include "ajanuw.h"
#include "asmjit.h"
#include <stdio.h>

using namespace asmjit;
typedef int (*Func)(int test);

void test(const Napi::CallbackInfo &info)
{
  nm_init;
  JitRuntime rt;

  CodeHolder code;
  code.init(rt.environment());

  x86::Assembler a(&code);
  a.mov(x86::rax, x86::rcx);
  a.ret();

  Func fn;
  asmjit::Error err = rt.add(&fn, &code);
  if (err)
    return;

  int result = fn(10);
  printf("%d\n", result);

  rt.release(fn);
}
