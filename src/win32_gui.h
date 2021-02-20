#pragma once
#include <iostream>
#include <Windows.h>
#include <napi.h>
#include "_napi_macro.h"
#include "ajanuw.h"

class Win32Gui : public Napi::ObjectWrap<Win32Gui>,
                 public ajanuw::Gui::Win32
{
private:
  Napi::FunctionReference _cb;
  Napi::Env env_;

  void wndProc_(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  Win32Gui(const Napi::CallbackInfo &info);
  ~Win32Gui();

  Napi::Value GetX(const Napi::CallbackInfo &info);
  void SetX(const Napi::CallbackInfo &info, const Napi::Value &value);

  Napi::Value GetY(const Napi::CallbackInfo &info);
  void SetY(const Napi::CallbackInfo &info, const Napi::Value &value);

  Napi::Value GetWidth(const Napi::CallbackInfo &info);
  void SetWidth(const Napi::CallbackInfo &info, const Napi::Value &value);

  Napi::Value GetHeight(const Napi::CallbackInfo &info);
  void SetHeight(const Napi::CallbackInfo &info, const Napi::Value &value);

  Napi::Value GetStyle(const Napi::CallbackInfo &info);
  void SetStyle(const Napi::CallbackInfo &info, const Napi::Value &value);

  Napi::Value initRegisterClass(const Napi::CallbackInfo &info);
  Napi::Value initWindow(const Napi::CallbackInfo &info);
  Napi::Value messageLoop(const Napi::CallbackInfo &info);

  Napi::Value createWindow(const Napi::CallbackInfo &info);
};