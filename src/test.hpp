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

void test(const Napi::CallbackInfo &info)
{
  nm_init;
  std::string r = ajanuw::SSString::strFormMem((void *)nmi_qword(0), -1);
  printf("%s\n", r.c_str());
}

/*
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

  // asmjit::Error err = p.parse(nmi_str(0).c_str());

  std::string input = "push rbp\n"
                      "mov rbp,rsp\n"
                      "sub rsp,32\n"

                      "mov rdx,rcx\n"
                      "lea r8, [rcx+10]\n"
                      "mov r9,2\n"
                      "xor rcx,rcx\n";

  input += ("mov rax, 0x" + ajanuw::SSString::strFormNumber((uintptr_t)MessageBoxA, true));

  input += "\ncall rax\n"
           "add rsp,32\n"

           "mov rsp,rbp\npop rbp\nret\n";

  printf("%s\n", input.c_str());
  asmjit::Error err = p.parse(input.c_str());

  if (err)
  {
    nm_jserr("AsmParser ERROR: " + std::string(DebugUtils::errorAsString(err)));
    printf("ERROR: %08x (%s)\n", err, DebugUtils::errorAsString(err));
    nm_retu;
  }

  Func fn;
  rt.add(&fn, &code);

  printf("fn: %p\n", fn);
  getchar();

  uintptr_t r = fn(nmi_qword(1));
  printf("result: %d\n", r);

  rt.release(fn);
  nm_ret(r);
}
*/
