#include <iostream>
#include <napi.h>
#include "ajanuw.h"
#include "_napi_macro.h"
#include <asmjit/asmjit.h>

extern "C" typedef uintptr_t (*asm_fn_uintptr_t)();
extern "C" typedef int (*asm_fn_int_t)();
extern "C" typedef signed long long (*asm_fn_int64_t)();
extern "C" typedef float (*asm_fn_float_t)();
extern "C" typedef double (*asm_fn_double_t)();

struct CallbackContext
{
  CallbackContext(const Napi::Env &env, const Napi::Function &cb, const LPVOID &address)
      : cb(cb), env(env), address(address){};
  Napi::Function cb;
  Napi::Env env;
  LPVOID address;
  int64_t call(uintptr_t *lpRcx, uintptr_t *lpP5)
  {
    uintptr_t *rcx = (lpRcx + 0);
    uintptr_t *rdx = (lpRcx + 1);
    uintptr_t *r8 = (lpRcx + 2);
    uintptr_t *r9 = (lpRcx + 3);

    std::vector<napi_value> args{
        Napi::Number::New(env, *rcx),
        Napi::Number::New(env, *rdx),
        Napi::Number::New(env, *r8),
        Napi::Number::New(env, *r9),

        // 第五个参数返回其他参数指针，需要自己做指针运算读数据,如:
        // readDword(lpP5)
        // readStr(readPointer(lpP5+8)) x64指针大小为8字节
        Napi::Number::New(env, (uintptr_t)lpP5),
    };

    return cb.Call(args).ToNumber().Int64Value();
  }
};

extern "C" uintptr_t cccccc(std::vector<CallbackContext *> *vect_cc, void *vcc_index, uintptr_t *lpRcx, uintptr_t *lpP5)
{
  return vect_cc->at((size_t)vcc_index)->call(lpRcx, lpP5);
}

/**s
 * 保存整数和指针
 */
void push_r64(asmjit::x86::Assembler &a, auto value, size_t i)
{
  using namespace asmjit;
  using namespace asmjit::x86;

  if (i == 0)
    a.mov(rcx, value);
  else if (i == 1)
    a.mov(rdx, value);
  else if (i == 2)
    a.mov(r8, value);
  else if (i == 3)
    a.mov(r9, value);
  else
  {
    a.mov(rax, value);
    size_t param_offset = 0x20 + ((i - 4) * 8);
    a.mov(ptr(rsp, param_offset), rax);
  }
};

/**
 * 保存浮点数
 */
void push_r128(asmjit::x86::Assembler &a, auto *value, size_t i)
{
  using namespace asmjit;
  using namespace asmjit::x86;

  a.push(rax);
  a.mov(rax, value);

  if (i == 0)
    a.movsd(xmm0, ptr(rax));
  else if (i == 1)
    a.movsd(xmm1, ptr(rax));
  else if (i == 2)
    a.movsd(xmm2, ptr(rax));
  else if (i == 3)
    a.movsd(xmm3, ptr(rax));
  else
  {
    a.movsd(xmm0, ptr(rax));
    size_t param_offset = 0x20 + ((i - 4) * 8);
    a.movsd(ptr(rsp, param_offset), xmm0);
  }
  a.pop(rax);
};

nm_api(invoke)
{
  using namespace asmjit;
  using namespace asmjit::x86;

  nm_init_cal(1);

  std::vector<CallbackContext *> v_cc; // 储存函数指针
  auto v_cc_push = [&](const Napi::Value &jsVal) -> LPVOID
  {
    auto CC = new CallbackContext(env, jsVal.As<Napi::Function>(), ajanuw::createCallback(&cccccc, v_cc.size(), &v_cc));
    v_cc.push_back(CC);
    return CC->address;
  };

  std::vector<float> v_f; // 储存浮点数
  auto v_f_push = [&](const Napi::Value &jsVal) -> float *
  {
    v_f.push_back(jsVal.ToNumber().FloatValue());
    return v_f.data() + (v_f.size() - 1);
  };

  std::vector<double> v_d; // 储存双浮点数
  auto v_d_push = [&](const Napi::Value &jsVal) -> double *
  {
    v_d.push_back(jsVal.ToNumber().DoubleValue());
    return v_d.data() + (v_d.size() - 1);
  };

  std::vector<char>
      v_str; // 储存utf-8字符串
  auto v_str_push = [&](const Napi::Value &jsVal) -> char *
  {
    auto v = jsVal.ToString().Utf8Value();
    auto offset = v_str.size();
    std::copy(v.begin(), v.end(), std::back_inserter(v_str));
    v_str.push_back('\0');
    return v_str.data() + offset;
  };

  std::vector<wchar_t> v_wstr; // 储存宽字符串
  auto v_wstr_push = [&](const Napi::Value &jsVal) -> wchar_t *
  {
    auto v = jsVal.ToString().Utf16Value();
    auto offset = v_wstr.size();
    std::wstring ws{v.begin(), v.end()};

    std::copy(ws.begin(), ws.end(), std::back_inserter(v_wstr));
    v_wstr.push_back('\0');

    return v_wstr.data() + offset;
  };

  auto o = nmi_o(0);

  HMODULE hModule = NULL;
  uint8_t *lpMethod = nullptr;
  Napi::Array args = nmo_is_und("args", a, Napi::Array::New(env));
  Napi::Array argsType;
  bool bWideChar = false;

  // 函数返回的类型 "uintptr" | "int" | "int64" | "float" | "double"
  std::string retType = nmo_is_und("retType", s, "uintptr");

  // 传入的函数指针，而不是函数名
  if (o.Get("method").IsNumber())
  {
    bWideChar = nmo_get("isWideChar", b);
    lpMethod = reinterpret_cast<uint8_t *>(nmo_get("method", ull));
  }
  else
  {
    std::string sMethod = nmo_get("method", s);

    // 猜测宽字符串
    bWideChar = ajanuw::sstr::endWith(sMethod, "W");

    // 调用者明确了宽字符串
    auto js_isWideChar = o.Get("isWideChar");
    if (!nm_is_un(js_isWideChar))
      bWideChar = nm_b(js_isWideChar);

    // 指定模块名
    if (o.Has("module"))
    {
      auto sModule = nmo_get("module", s);
      hModule = LoadLibraryA(sModule.data());
      if (hModule == NULL)
      {
        nm_err(std::format("not find '{}' module.", sModule));
        nm_retu;
      }
    }

    if (hModule != NULL)
    {
      lpMethod = (uint8_t *)GetProcAddress(hModule, sMethod.c_str());
    }
    else
    {
      try
      {
        lpMethod = (uint8_t *)ajanuw::CEAS::getAddress(sMethod);
      }
      catch (const std::exception &e)
      {
        nm_err(e.what());
        nm_retu;
      }
    }
  }

  if (lpMethod == NULL)
  {
    nm_err("not find method.");
    nm_retu;
  }

  auto argsStackSize = max(args.Length() * sizeof(uintptr_t), Globals::kMaxPhysRegs);

  JitRuntime rt;
  CodeHolder code;
  code.init(rt.environment());
  x86::Assembler a(&code);

  a.push(rbp);
  a.mov(rbp, rsp);
  a.sub(rsp, argsStackSize); // 能够使用的堆栈空间

  if (o.Has("argsType") && args.Length() > 0)
  {
    argsType = o.Get("argsType").As<Napi::Array>();

    // 如果给了 argsType 则要明确每个参数
    if (argsType.Length() != args.Length())
    {
      nm_err("argsType length != args length");
      nm_retu;
    }

    int i = args.Length() - 1;
    for (; i >= 0; i--)
    {
      Napi::Value it = args.Get(i);
      std::string itTyle = argsType.Get(i).ToString().Utf8Value();

      if (itTyle == "int")
        push_r64(a, it.ToNumber().Int32Value(), i);
      else if (itTyle == "uint")
        push_r64(a, it.ToNumber().Uint32Value(), i);
      else if (itTyle == "int64")
        push_r64(a, it.ToNumber().Int64Value(), i);
      else if (itTyle == "uintptr")
        push_r64(a, (uintptr_t)it.ToNumber().Int64Value(), i);
      else if (itTyle == "float")
        push_r128(a, v_f_push(it), i);
      else if (itTyle == "double")
        push_r128(a, v_d_push(it), i);
      else if (itTyle == "str")
        push_r64(a, v_str_push(it), i);
      else if (itTyle == "wstr")
        push_r64(a, v_wstr_push(it), i);
      else if (itTyle == "fn")
        push_r64(a, (uintptr_t)v_cc_push(it), i);
    }
  }
  // 猜测
  else
  {
    for (int i = args.Length() - 1; i >= 0; i--)
    {
      Napi::Value it = args.Get(i);
      uintptr_t value = NULL;

      // js函数 => 函数指针
      if (nm_is_fu(it))
        value = (uintptr_t)v_cc_push(it);
      // js字符串 => 字符串指针
      else if (nm_is_s(it))
        value = bWideChar ? (uintptr_t)v_wstr_push(it)
                          : (uintptr_t)v_str_push(it);
      // 其它类型统一当作数字
      else
        value = nm_ull(it);

      // 前四个整数或指针参数在 rcx、 rdx、 r8 和 r9 寄存器中传递。
      // 前四个浮点参数在前四个 SSE 寄存器 xmm0-xmm3 中传递
      if (i == 0)
        a.mov(rcx, value);
      else if (i == 1)
        a.mov(rdx, value);
      else if (i == 2)
        a.mov(r8, value);
      else if (i == 3)
        a.mov(r9, value);

      // 任何其他参数都在堆栈上传递
      else
      {
        // value存入寄存器避免被截断
        a.mov(rax, value);

        // 0x20 = 32 避免被调用的函数覆盖, 调用方在堆栈上为传入寄存器的参数保留空间。 被调用的函数可以使用此空间将寄存器的内容溢出到堆栈
        // 4 前4个参数被放在了寄存器
        // 8 x64固定的指针大小
        size_t param_offset = 0x20 + ((i - 4) * 8);

        // 将value写入栈中
        // mov [rsp + param_offset] rax
        a.mov(ptr(rsp, param_offset), rax);
      }
    }
  }

  // 将函数指针放入寄存器，避免被截断
  a.mov(rax, lpMethod);
  a.call(rax);

  // 释放堆栈
  a.add(rsp, argsStackSize);
  a.mov(rsp, rbp);
  a.pop(rbp);
  a.ret();

  asmjit::Error err;

  /* #region 对应函数返回类型 */
  asm_fn_uintptr_t fn_uintptr;
  asm_fn_int_t fn_int;
  asm_fn_int64_t fn_int64;
  asm_fn_float_t fn_float;
  asm_fn_double_t fn_double;

  if (retType == "int")
  {
    err = rt.add(&fn_int, &code);
  }
  else if (retType == "int64")
  {
    err = rt.add(&fn_int64, &code);
  }
  else if (retType == "float")
  {
    err = rt.add(&fn_float, &code);
  }
  else if (retType == "double")
  {
    err = rt.add(&fn_double, &code);
  }
  else
  {
    err = rt.add(&fn_uintptr, &code);
  }
  /* #endregion */

  if (err)
  {
    for (auto cc : v_cc)
    {
      ajanuw::Mem::free(cc->address);
      delete cc;
    }
    nm_err("asmjit error.");
    nm_retu;
  }

  Napi::Number result;

  /* #region 对应函数返回类型 */
  if (retType == "int")
  {
    int res = fn_int();
    result = Napi::Number::New(env, res);
    rt.release(fn_int);
  }
  else if (retType == "int64")
  {
    signed long long res = fn_int64();
    result = Napi::Number::New(env, res);
    rt.release(fn_int64);
  }
  else if (retType == "float")
  {
    float res = fn_float();
    result = Napi::Number::New(env, res);
    rt.release(fn_float);
  }
  else if (retType == "double")
  {
    double res = fn_double();
    result = Napi::Number::New(env, res);
    rt.release(fn_double);
  }
  else
  {
    uintptr_t res = fn_uintptr();
    result = Napi::Number::New(env, res);
    rt.release(fn_uintptr);
  }
  /* #endregion */

  for (auto cc : v_cc)
  {
    ajanuw::Mem::free(cc->address);
    delete cc;
  }

  return result;
}
