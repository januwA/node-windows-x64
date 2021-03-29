#pragma once
#include <iostream>
#include <Windows.h>
#include <napi.h>
#include "_napi_macro.h"
#include "ajanuw.h"

class Target : public Napi::ObjectWrap<Target>,
               public ajanuw::Target
{
private:
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports)
  {
    Napi::Function func = DefineClass(
        env, "Target",
        {
            InstanceAccessor<&Target::GetName>("name"),
            InstanceAccessor<&Target::GetPID>("pid"),
            InstanceAccessor<&Target::GethProcess>("hProcess"),

            InstanceMethod<&Target::setNop>("setNop"),
        });
    Napi::FunctionReference *constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    constructor->SuppressDestruct();

    exports.Set("Target", func);
    return exports;
  }

  Target(const Napi::CallbackInfo &info)
      : ObjectWrap<Target>(info),
        ajanuw::Target::Target(ajanuw::SSString::strToWstr(nmi_str(0)))
  {
  }
  ~Target()
  {
  }

  Napi::Value GetName(const Napi::CallbackInfo &info)
  {
    nm_init;
    nm_rets(ajanuw::SSString::wstrToStr(ajanuw::Target::name));
  }

  Napi::Value GetPID(const Napi::CallbackInfo &info)
  {
    nm_init;
    nm_ret(ajanuw::Target::pid);
  }

  Napi::Value GethProcess(const Napi::CallbackInfo &info)
  {
    nm_init;
    nm_ret((uintptr_t)ajanuw::Target::hProcess);
  }

  Napi::Value setNop(const Napi::CallbackInfo &info)
  {
    nm_init_cal(2);
    BYTE *addr = (BYTE *)nmi_qword(0);
    size_t size = nmi_dword(1);

    ajanuw::Target::SetNop *r = ajanuw::Target::setNop(addr, size);

    Napi::Object result = Napi::Object::New(env);

    result.Set("enable", Napi::Function::New(
                             env, [=](const Napi::CallbackInfo &info) { r->enable(); },
                             "enable"));

    result.Set("disable", Napi::Function::New(
                              env, [=](const Napi::CallbackInfo &info) { r->disable(); },
                              "disable"));

    result.Set("toggle", Napi::Function::New(
                             env, [=](const Napi::CallbackInfo &info) {
                               r->toggle();
                             },
                             "toggle"));

    result.Set("delete", Napi::Function::New(
                             env, [=](const Napi::CallbackInfo &info) {
                               delete r;
                             },
                             "delete"));

    result.Set("bSuccess", r->bSuccess);
    result.Set("bEnable", r->bEnable);
    result.Set("addr", (uintptr_t)r->addr);
    result.Set("size", r->size);
    result.Set("origenBytes", ArrayBuffer::New(env, r->origenBytes.data(), r->origenBytes.size()));

    return result;
  }
};