#pragma once
#pragma warning(disable : 2664)
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <psapi.h>
#include <napi.h>
#include <regex>
#include "ajanuw.h"

#include <asmjit/asmjit.h>
#include <asmtk/asmtk.h>

using namespace asmjit;
using namespace asmtk;
typedef uintptr_t (*Func)(uintptr_t lpParam);
Value test(const Napi::CallbackInfo &info)
{
  nm_init;
  using namespace asmjit::x86;

  JitRuntime rt;
  CodeHolder code;
  code.init(rt.environment());

  x86::Assembler a(&code);
  AsmParser p(&a);

  asmjit::Error err = p.parse(nmi_str(0).c_str());
  if (err)
  {
    nm_jserr("AsmParser Error: " + std::string(DebugUtils::errorAsString(err)));
    nm_retu;
  }

  Func fn;
  rt.add(&fn, &code);

  uintptr_t v = nm_is_nullishOr(info[1], nm_qword, 0);
  uintptr_t r = fn(v);
  rt.release(fn);
  nm_ret(r);
}
