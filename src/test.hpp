#pragma once
#include <iostream>
#include <Windows.h>
#include <napi.h>
#include "ajanuw.h"

#include <asmjit/asmjit.h>
#include <asmtk/asmtk.h>

using namespace asmjit;
using namespace asmtk;

typedef int (*Func)();

void test(const Napi::CallbackInfo &info)
{
  nm_init;
  using namespace asmjit::x86;

  JitRuntime rt;
  CodeHolder code;
  code.init(rt.environment());

  x86::Assembler a(&code);
  AsmParser p(&a);
  asmjit::Error err = p.parse(
      "mov eax,1\n"
      "ret\n");

  if (err)
  {
    printf("ERROR: %08x (%s)\n", err, DebugUtils::errorAsString(err));
    return;
  }

  Func fn;
  err = rt.add(&fn, &code);
  if (err)
    return;

  printf("%d\n", fn());

  rt.release(fn);
}
