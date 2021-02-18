#pragma once
#include <iostream>
#include <Windows.h>
#include <napi.h>
#include <fstream>
#include "_napi_macro.h"
#include "_utils.h"

using namespace Napi;
using namespace std;

class VAManage : public Napi::ObjectWrap<VAManage>
{
private:
  /// <summary>
  /// memory size
  /// </summary>
  const uintptr_t size_;
  Napi::Value GetSize(const Napi::CallbackInfo& info);

  LPVOID memory_;
  Napi::Value GetMemory(const Napi::CallbackInfo& info);
  
  /// <summary>
  /// write will change position
  /// </summary>
  uintptr_t position_;
  Napi::Value GetPosition(const Napi::CallbackInfo& info);
  void SetPosition(const Napi::CallbackInfo& info, const Napi::Value& value);
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  VAManage(const Napi::CallbackInfo& info);
  ~VAManage();
  void* ptr();

  Napi::Value read(const Napi::CallbackInfo& info);
  Napi::Value readByte(const Napi::CallbackInfo& info);
  Napi::Value readWord(const Napi::CallbackInfo& info);
  Napi::Value readDword(const Napi::CallbackInfo& info);
  Napi::Value readQword(const Napi::CallbackInfo& info);
  Napi::Value readFloat(const Napi::CallbackInfo& info);
  Napi::Value readDouble(const Napi::CallbackInfo& info);
  Napi::Value readStr(const Napi::CallbackInfo& info);
  Napi::Value readWstr(const Napi::CallbackInfo& info);

  void write(const Napi::CallbackInfo& info);
  void writeByte(const Napi::CallbackInfo& info);
  void writeWord(const Napi::CallbackInfo& info);
  void writeDword(const Napi::CallbackInfo& info);
  void writeQword(const Napi::CallbackInfo& info);
  void writeFloat(const Napi::CallbackInfo& info);
  void writeDouble(const Napi::CallbackInfo& info);
  void writeStr(const Napi::CallbackInfo& info);
  void writeWstr(const Napi::CallbackInfo& info);

  void loadFromFile(const Napi::CallbackInfo& info);
  void saveToFile(const Napi::CallbackInfo& info);
  void destroy(const Napi::CallbackInfo& info);
};