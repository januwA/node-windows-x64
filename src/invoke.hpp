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
  CallbackContext(
      const Napi::Env &env,
      const Napi::Function &cb,
      LPVOID address,
      std::vector<std::string> args,
      std::string ret)
      : cb(cb), env(env), address(address), _args(args), _ret(ret){};
  Napi::Function cb;
  Napi::Env env;
  LPVOID address;

  std::vector<std::string> _args;
  std::string _ret;
  std::vector<char> _v_str;     // 储存utf-8字符串
  std::vector<wchar_t> _v_wstr; // 储存宽字符串

  Napi::Number call(uintptr_t *lpRcx, uintptr_t *lpP5)
  {
    auto xmm0Ptr = (lpRcx + 4);
    std::vector<napi_value> jsFuncArgs{};

    // 空参数，无法猜测浮点参数返回指针
    if (_args.empty())
    {
      uintptr_t *rcx = (lpRcx + 0);
      uintptr_t *rdx = (lpRcx + 1);
      uintptr_t *r8 = (lpRcx + 2);
      uintptr_t *r9 = (lpRcx + 3);
      jsFuncArgs.push_back(Napi::Number::New(env, *rcx));
      jsFuncArgs.push_back(Napi::Number::New(env, *rdx));
      jsFuncArgs.push_back(Napi::Number::New(env, *r8));
      jsFuncArgs.push_back(Napi::Number::New(env, *r9));

      jsFuncArgs.push_back(Napi::Number::New(env, (uintptr_t)lpRcx));   // 整数和指针
      jsFuncArgs.push_back(Napi::Number::New(env, (uintptr_t)xmm0Ptr)); // 浮点参数指针
      jsFuncArgs.push_back(Napi::Number::New(env, (uintptr_t)lpP5));    // 堆栈上的参数指针
    }
    else
    {
      for (size_t i = 0; i < _args.size(); i++)
      {
        auto argtype = _args.at(i);

        if (argtype == "int")
        {
          if (i == 0)
          {
            auto v = *(int *)(lpRcx + 0);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 1)
          {
            auto v = *(int *)(lpRcx + 1);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 2)
          {
            auto v = *(int *)(lpRcx + 2);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 3)
          {
            auto v = *(int *)(lpRcx + 3);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else
          {
            auto v = *(int *)(lpP5 + (i - 4));
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
        }
        else if (argtype == "uint")
        {
          if (i == 0)
          {
            auto v = *(uint32_t *)(lpRcx + 0);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 1)
          {
            auto v = *(uint32_t *)(lpRcx + 1);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 2)
          {
            auto v = *(uint32_t *)(lpRcx + 2);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 3)
          {
            auto v = *(uint32_t *)(lpRcx + 3);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else
          {
            auto v = *(uint32_t *)(lpP5 + (i - 4));
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
        }
        else if (argtype == "int64")
        {
          if (i == 0)
          {
            auto v = *(int64_t *)(lpRcx + 0);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 1)
          {
            auto v = *(int64_t *)(lpRcx + 1);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 2)
          {
            auto v = *(int64_t *)(lpRcx + 2);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 3)
          {
            auto v = *(int64_t *)(lpRcx + 3);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else
          {
            auto v = *(int64_t *)(lpP5 + (i - 4));
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
        }
        else if (argtype == "float")
        {
          if (i == 0)
          {
            auto v = *(float *)(xmm0Ptr + 0);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 1)
          {
            auto v = *(float *)(xmm0Ptr + 1);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 2)
          {
            auto v = *(float *)(xmm0Ptr + 2);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 3)
          {
            auto v = *(float *)(xmm0Ptr + 3);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else
          {
            auto v = *(float *)(lpP5 + (i - 4));
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
        }
        else if (argtype == "double")
        {
          if (i == 0)
          {
            auto v = *(double *)(xmm0Ptr + 0);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 1)
          {
            auto v = *(double *)(xmm0Ptr + 1);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 2)
          {
            auto v = *(double *)(xmm0Ptr + 2);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 3)
          {
            auto v = *(double *)(xmm0Ptr + 3);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else
          {
            auto v = *(double *)(lpP5 + (i - 4));
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
        }
        else if (argtype == "str")
        {
          char *v;
          if (i == 0)
          {
            v = (char *)*(lpRcx + 0);
          }
          else if (i == 1)
          {
            v = (char *)*(lpRcx + 1);
          }
          else if (i == 2)
          {
            v = (char *)*(lpRcx + 2);
          }
          else if (i == 3)
          {
            v = (char *)*(lpRcx + 3);
          }
          else
          {
            v = (char *)*(lpP5 + (i - 4));
          }
          jsFuncArgs.push_back(Napi::String::New(env, v));
        }
        else if (argtype == "wstr")
        {
          wchar_t *v;
          if (i == 0)
          {
            v = (wchar_t *)*(lpRcx + 0);
          }
          else if (i == 1)
          {
            v = (wchar_t *)*(lpRcx + 1);
          }
          else if (i == 2)
          {
            v = (wchar_t *)*(lpRcx + 2);
          }
          else if (i == 3)
          {
            v = (wchar_t *)*(lpRcx + 3);
          }
          else
          {
            v = (wchar_t *)*(lpP5 + (i - 4));
          }
          jsFuncArgs.push_back(Napi::String::New(env, ajanuw::sstr::wstrToStr(std::wstring{v})));
        }
        else
        {
          if (i == 0)
          {
            auto v = *(lpRcx + 0);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 1)
          {
            auto v = *(lpRcx + 1);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 2)
          {
            auto v = *(lpRcx + 2);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else if (i == 3)
          {
            auto v = *(lpRcx + 3);
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
          else
          {
            auto v = *(lpP5 + (i - 4));
            jsFuncArgs.push_back(Napi::Number::New(env, v));
          }
        }
      }
    }

    if (_ret == "str")
    {
      auto str_ptr = ajanuw::strCachePush(_v_str, cb.Call(jsFuncArgs).ToString().Utf8Value());
      return Napi::Number::New(env, (uintptr_t)str_ptr).ToNumber();
    }
    else if (_ret == "wstr")
    {
      auto wstr_ptr = ajanuw::wstrCachePush(_v_wstr, cb.Call(jsFuncArgs).ToString().Utf16Value());
      return Napi::Number::New(env, (uintptr_t)wstr_ptr).ToNumber();
    }
    else
    {
      return cb.Call(jsFuncArgs).ToNumber();
    }
  }
};

extern "C" int cb_int(std::vector<CallbackContext *> *vect_cc, void *vcc_index, uintptr_t *lpRcx, uintptr_t *lpP5)
{
  return vect_cc->at((size_t)vcc_index)->call(lpRcx, lpP5).Int32Value();
}

extern "C" uint32_t cb_uint(std::vector<CallbackContext *> *vect_cc, void *vcc_index, uintptr_t *lpRcx, uintptr_t *lpP5)
{
  return vect_cc->at((size_t)vcc_index)->call(lpRcx, lpP5).Uint32Value();
}

extern "C" int64_t cb_int64(std::vector<CallbackContext *> *vect_cc, void *vcc_index, uintptr_t *lpRcx, uintptr_t *lpP5)
{
  return vect_cc->at((size_t)vcc_index)->call(lpRcx, lpP5).Int64Value();
}

extern "C" float cb_float(std::vector<CallbackContext *> *vect_cc, void *vcc_index, uintptr_t *lpRcx, uintptr_t *lpP5)
{
  return vect_cc->at((size_t)vcc_index)->call(lpRcx, lpP5).FloatValue();
}

extern "C" double cb_double(std::vector<CallbackContext *> *vect_cc, void *vcc_index, uintptr_t *lpRcx, uintptr_t *lpP5)
{
  return vect_cc->at((size_t)vcc_index)->call(lpRcx, lpP5).DoubleValue();
}

extern "C" uintptr_t cb_ptr(std::vector<CallbackContext *> *vect_cc, void *vcc_index, uintptr_t *lpRcx, uintptr_t *lpP5)
{
  return (uintptr_t)vect_cc->at((size_t)vcc_index)->call(lpRcx, lpP5).Int64Value();
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

#define DEL_VCC                     \
  for (auto cc : v_cc)              \
  {                                 \
    ajanuw::Mem::free(cc->address); \
    delete cc;                      \
  }

nm_api(invoke)
{
  using namespace asmjit;
  using namespace asmjit::x86;

  nm_init_cal(1);

  std::vector<CallbackContext *> v_cc; // 储存函数指针
  std::vector<float> v_f;              // 储存浮点数
  std::vector<double> v_d;             // 储存双浮点数
  std::vector<char> v_str;             // 储存utf-8字符串
  std::vector<wchar_t> v_wstr;         // 储存宽字符串

  auto v_cc_push = [&](
                       const Napi::Value &jsVal,
                       std::vector<std::string> args,
                       std::string ret) -> LPVOID
  {
    LPVOID address;

    // 现在立即确定返回值类型

    if (ret == "int")
    {
      address = ajanuw::createCallback(&cb_int, v_cc.size(), &v_cc);
    }
    else if (ret == "uint")
    {
      address = ajanuw::createCallback(&cb_uint, v_cc.size(), &v_cc);
    }
    else if (ret == "int64")
    {
      address = ajanuw::createCallback(&cb_int64, v_cc.size(), &v_cc);
    }
    else if (ret == "float")
    {
      address = ajanuw::createCallback(&cb_float, v_cc.size(), &v_cc);
    }
    else if (ret == "double")
    {
      address = ajanuw::createCallback(&cb_double, v_cc.size(), &v_cc);
    }
    else if (ret == "str")
    {
      // js函数会返回字符串，将字符串指针个给abi函数
      address = ajanuw::createCallback(&cb_ptr, v_cc.size(), &v_cc);
    }
    else if (ret == "wstr")
    {
      // js函数会返回字符串，将宽字符串指针个给abi函数
      address = ajanuw::createCallback(&cb_ptr, v_cc.size(), &v_cc);
    }
    else
    {
      // 全当作指针处理
      address = ajanuw::createCallback(&cb_ptr, v_cc.size(), &v_cc);
    }
    auto CC = new CallbackContext(
        env,
        jsVal.As<Napi::Function>(),
        address, args, ret);

    v_cc.push_back(CC);
    return CC->address;
  };

  auto v_f_push = [&](const Napi::Value &jsVal) -> float *
  {
    v_f.push_back(jsVal.ToNumber().FloatValue());
    return v_f.data() + (v_f.size() - 1);
  };

  auto v_d_push = [&](const Napi::Value &jsVal) -> double *
  {
    v_d.push_back(jsVal.ToNumber().DoubleValue());
    return v_d.data() + (v_d.size() - 1);
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
        push_r64(a, ajanuw::strCachePush(v_str, it.ToString().Utf8Value()), i);

      else if (itTyle == "wstr")
        push_r64(a, ajanuw::wstrCachePush(v_wstr, it.ToString().Utf16Value()), i);
      else
      {
        if (itTyle.starts_with("fn"))
        {
          std::vector<std::string> args{};
          std::string ret{};
          if (!ajanuw::parseFnHeader(itTyle, &args, &ret))
          {
            push_r64(a, (uintptr_t)v_cc_push(it, args, ret), i);
          }
          else
          {
            DEL_VCC
            nm_err("fn arg type error.");
            nm_retu;
          }
        }
        else
        {
          DEL_VCC
          nm_err("arg type error.");
          nm_retu;
        }
      }
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
        value = (uintptr_t)v_cc_push(it, std::vector<std::string>{}, std::string{"void"});
      // js字符串 => 字符串指针
      else if (nm_is_s(it))
        value = bWideChar ? (uintptr_t)ajanuw::wstrCachePush(v_wstr, it.ToString().Utf16Value())
                          : (uintptr_t)ajanuw::strCachePush(v_str, it.ToString().Utf8Value());
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
    DEL_VCC
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

  DEL_VCC
  return result;
}
