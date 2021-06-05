#pragma once
#include <iostream>
#include <Windows.h>
#include <napi.h>
#include "_napi_macro.h"
#include "_util.hpp"
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

  static nm_api(getHLMessage);
  static nm_api(getCheck);
  static nm_api(rgb);

  nm_api(GetHwnd);

  nm_api(GetX);
  nm_sapi(SetX);

  nm_api(GetY);
  nm_sapi(SetY);

  nm_api(GetWidth);
  nm_sapi(SetWidth);

  nm_api(GetHeight);
  nm_sapi(SetHeight);

  nm_api(GetStyle);
  nm_sapi(SetStyle);

  nm_api(initRegisterClass);
  nm_api(initWindow);
  nm_api(messageLoop);
  nm_api(createWindow);
  nm_api(button);
  nm_api(checkbox);
  nm_api(radio);
  nm_api(groupbox);
  nm_api(text);
  nm_api(input);
  nm_api(textarea);
  nm_api(listbox);
  nm_api(select);
};