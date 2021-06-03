#pragma warning(disable : 4100)

#pragma once
#include <iostream>
#include <Windows.h>
#include <napi.h>
#include "_napi_macro.h"
#include "ajanuw.h"

class Target : public Napi::ObjectWrap<Target>,
               public ajanuw::Target
{
public:
  using _Mybase = ajanuw::Target;
  static Napi::Object Init(Napi::Env env, Napi::Object exports)
  {
    Napi::Function func = DefineClass(
        env, "Target",
        {
            InstanceAccessor<&Target::GetName>("name"),
            InstanceAccessor<&Target::GetPID>("pid"),
            InstanceAccessor<&Target::GethProcess>("hProcess"),

            InstanceMethod<&Target::setNop>("setNop"),
            InstanceMethod<&Target::setHook>("setHook"),
            InstanceMethod<&Target::moduleScan>("moduleScan"),
        });
    Napi::FunctionReference *constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);

    // constructor->SuppressDestruct();
    env.SetInstanceData(constructor);

    exports.Set("Target", func);
    return exports;
  }

  static Napi::Object NewInstance(Napi::Env env, Napi::Value arg)
  {
    Napi::Object obj = env.GetInstanceData<Napi::FunctionReference>()->New({arg});
    return obj;
  }

  Target(const Napi::CallbackInfo &info)
      : ObjectWrap<Target>(info),
        _Mybase(nmi_dword(0))
  {
  }

  Napi::Value GetName(const Napi::CallbackInfo &info)
  {
    nm_init;
    nm_rets(ajanuw::sstr::wstrToStr(_Mybase::name));
  }
  Napi::Value GetPID(const Napi::CallbackInfo &info)
  {
    nm_init;
    nm_ret(_Mybase::pid);
  }
  Napi::Value GethProcess(const Napi::CallbackInfo &info)
  {
    nm_init;
    nm_ret((uintptr_t)_Mybase::hProcess);
  }
  Napi::Value setNop(const Napi::CallbackInfo &info)
  {
    nm_init_cal(2);
    uint8_t *addr = (uint8_t *)nmi_qword(0);
    size_t size = nmi_dword(1);

    _Mybase::SetNop *r = new _Mybase::SetNop(hProcess, addr, size);

    auto result = Napi::Object::New(env);

    result.Set("enable", Napi::Function::New(
                             env, [=](const Napi::CallbackInfo &info)
                             { r->enable(); },
                             "enable"));

    result.Set("disable", Napi::Function::New(
                              env, [=](const Napi::CallbackInfo &info)
                              { r->disable(); },
                              "disable"));

    result.Set("toggle", Napi::Function::New(
                             env, [=](const Napi::CallbackInfo &info)
                             { r->toggle(); },
                             "toggle"));

    result.Set("delete", Napi::Function::New(
                             env, [=](const Napi::CallbackInfo &info)
                             { delete r; },
                             "delete"));

    result.Set("bSuccess", r->bSuccess);
    result.Set("bEnable", r->bEnable);
    result.Set("addr", (uintptr_t)r->addr);
    result.Set("size", r->size);
    result.Set("origenBytes", Napi::Uint8Array::From(env, Napi::ArrayBuffer::New(env, r->oldBytes.data(), r->oldBytes.size())));
    return result;
  }

  Napi::Value setHook(const Napi::CallbackInfo &info)
  {
    nm_init_cal(2);
    uint8_t *addr = (uint8_t *)nmi_qword(0);
    size_t size = nmi_dword(1);

    std::vector<uint8_t> hookBytes;
    if (nmi_is_str(2))
    {
      hookBytes = ajanuw::Asm::AAScript::asmBytes(nmi_str(2), isX64);
    }
    else
    {
      Napi::ArrayBuffer buf = info[2].As<Napi::ArrayBuffer>();
      hookBytes.resize(buf.ByteLength());
      memcpy_s(hookBytes.data(), hookBytes.size(), buf.Data(), hookBytes.size());
    }

    _Mybase::SetHook *r = new _Mybase::SetHook(hProcess, addr, size, hookBytes);

    Napi::Object result = Napi::Object::New(env);

    result.Set("enable", Napi::Function::New(
                             env, [=](const Napi::CallbackInfo &info)
                             { r->enable(); },
                             "enable"));

    result.Set("disable", Napi::Function::New(
                              env, [=](const Napi::CallbackInfo &info)
                              { r->disable(); },
                              "disable"));

    result.Set("toggle", Napi::Function::New(
                             env, [=](const Napi::CallbackInfo &info)
                             { r->toggle(); },
                             "toggle"));

    result.Set("delete", Napi::Function::New(
                             env, [=](const Napi::CallbackInfo &info)
                             {
                               ajanuw::Mem::freeEx(hProcess, r->newmem);
                               delete r;
                             },
                             "delete"));

    result.Set("bSuccess", r->bSuccess);
    result.Set("bEnable", r->bEnable);
    result.Set("addr", (uintptr_t)r->addr);
    result.Set("newmem", (uintptr_t)r->newmem);
    result.Set("size", r->size);
    result.Set("origenBytes", Napi::Uint8Array::From(env, Napi::ArrayBuffer::New(env, r->oldBytes.data(), r->oldBytes.size())));

    return result;
  }

  Napi::Value moduleScan(const Napi::CallbackInfo &info)
  {
    nm_init_cal(1);
    std::string strbytes = nmi_str(0);
    size_t offset = NULL;

    if (info.Length() > 1)
    {
      offset = nmi_dword(2);
    }

    std::vector<uint8_t *> addrs = _Mybase::moduleScan(strbytes, offset);
    Napi::Array r = Napi::Array::New(env, addrs.size());
    for (size_t i = 0; i < addrs.size(); i++)
    {
      r.Set(i, (uintptr_t)addrs.at(i));
    }
    return r;
  }
};

Napi::Object createTargetWithName(const Napi::CallbackInfo &info)
{
  nm_init;
  auto pid = ajanuw::PE::GetPID(nmi_str(0));
  return Target::NewInstance(env, Napi::Number::New(env, pid));
}

Napi::Object createTargetWithPID(const Napi::CallbackInfo &info)
{
  nm_init;
  return Target::NewInstance(env, info[0].ToNumber());
}
