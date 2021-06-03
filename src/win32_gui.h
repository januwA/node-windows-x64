#pragma once
#include <iostream>
#include <Windows.h>
#include <napi.h>
#include "_napi_macro.h"
#include "ajanuw.h"

class Win32GuiEvent
{
public:
  Napi::FunctionReference click;
  Napi::FunctionReference keydown;
  Win32GuiEvent(const Napi::Object &o);
  inline ~Win32GuiEvent(){};
};

class Win32Gui : public Napi::ObjectWrap<Win32Gui>,
                 public ajanuw::Gui::Win32
{
private:
  Napi::FunctionReference messageCallback;
  Napi::Env _env;
  LRESULT OnReceiveMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
  std::map<HMENU, Win32GuiEvent *> eventMap;
  std::unique_ptr<ajanuw::Gui::Win32CreateOption> getCreateOption(const Napi::Object &o, int dw, int dh);
  void setEvents(const Napi::Object &opt);

public:
  using _Mybase = ajanuw::Gui::Win32;
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  Win32Gui(const Napi::CallbackInfo &info);
  inline ~Win32Gui(){};

  static nm_method(getHLMessage);
  static nm_method(getCheck);
  static nm_method(rgb);

  nm_method(GetHwnd);

  nm_method(GetX);
  nm_method_set(SetX);

  nm_method(GetY);
  nm_method_set(SetY);

  nm_method(GetWidth);
  nm_method_set(SetWidth);

  nm_method(GetHeight);
  nm_method_set(SetHeight);

  nm_method(GetStyle);
  nm_method_set(SetStyle);

  nm_method(initRegisterClass);
  nm_method(initWindow);
  nm_method(messageLoop);
  nm_method(createWindow);
  nm_method(button);
  nm_method(checkbox);
  nm_method(radio);
  nm_method(groupbox);
  nm_method(text);
  nm_method(input);
  nm_method(textarea);
  nm_method(listbox);
  nm_method(select);
};