#pragma once
#include <iostream>
#include <napi.h>
#include "_napi_macro.h"
#include "_util.hpp"
#include "ajanuw.h"

class VAManage : public Napi::ObjectWrap<VAManage>,
                 public ajanuw::Mem::VAManage
{
private:
  nm_api(GetSize);
  nm_api(GetMemory);
  nm_api(GetPosition);
  nm_sapi(SetPosition);

public:
  using _Mybase = ajanuw::Mem::VAManage;
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  VAManage(const Napi::CallbackInfo &info);
  ~VAManage();
  nm_api(GetPtr);

  nm_api(read);
  nm_api(readByte);
  nm_api(readWord);
  nm_api(readDword);
  nm_api(readQword);
  nm_api(readFloat);
  nm_api(readDouble);
  nm_api(readStr);
  nm_api(readWstr);

  nm_api(write);
  nm_api(writeByte);
  nm_api(writeWord);
  nm_api(writeDword);
  nm_api(writeQword);
  nm_api(writeFloat);
  nm_api(writeDouble);
  nm_api(writeStr);
  nm_api(writeWstr);

  nm_api(loadFromFile);
  nm_api(saveToFile);
  nm_api(destroy);
};