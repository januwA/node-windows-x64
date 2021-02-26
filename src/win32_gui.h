#pragma once
#include <iostream>
#include <Windows.h>
#include <napi.h>
#include "_napi_macro.h"
#include "ajanuw.h"

class Win32GuiEvent
{
private:
  
public:
  HMENU id_;
  Napi::FunctionReference click;
  Win32GuiEvent(HMENU id);
  ~Win32GuiEvent();
};

class Win32Gui : public Napi::ObjectWrap<Win32Gui>,
                 public ajanuw::Gui::Win32
{
private:
  Napi::FunctionReference _messageCallback;
  Napi::Env env_;

  LRESULT OnReceiveMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

  std::map<HMENU, Win32GuiEvent*> _eventMap;

public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Value getHLMessage(const Napi::CallbackInfo &info);
  static Napi::Value getCheck(const Napi::CallbackInfo &info);
  static Napi::Value rgb(const Napi::CallbackInfo &info);

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
  Napi::Value button(const Napi::CallbackInfo &info);
  Napi::Value checkbox(const Napi::CallbackInfo &info);
  Napi::Value radio(const Napi::CallbackInfo &info);
  Napi::Value groupbox(const Napi::CallbackInfo &info);
  Napi::Value text(const Napi::CallbackInfo &info);
  Napi::Value input(const Napi::CallbackInfo &info);
  Napi::Value textarea(const Napi::CallbackInfo &info);
  Napi::Value listbox(const Napi::CallbackInfo &info);
  Napi::Value select(const Napi::CallbackInfo &info);
};