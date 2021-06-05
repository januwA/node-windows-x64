#include "win32_gui.h"

#define SET_EVENT(type) \
  if (o.Has(#type))     \
  ##type = nmo_get(#type, pfu)

Win32GuiEvent::Win32GuiEvent(const Napi::Object &o)
{
  SET_EVENT(click);
  SET_EVENT(keydown);
}

LRESULT Win32Gui::OnReceiveMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  std::initializer_list<napi_value> args = {
      Napi::Number::New(_env, (uintptr_t)hWnd),
      Napi::Number::New(_env, (uintptr_t)message),
      Napi::Number::New(_env, (uintptr_t)wParam),
      Napi::Number::New(_env, (uintptr_t)lParam),
  };
  switch (message)
  {
  case WM_COMMAND:
  {
    HMENU winId = (HMENU)LOWORD(wParam);
    if (eventMap.count(winId))
    {
      auto e = eventMap.at(winId);
      if (e->click)
        e->click.Call(args);
    }
  }
  break;
  }

  if (messageCallback)
  {
    return messageCallback.Call(args).ToNumber().Uint32Value();
  }
  return 0;
}

Napi::Object Win32Gui::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
      env, "Win32Gui",
      {
          StaticMethod<&Win32Gui::getHLMessage>("getHLMessage"),
          StaticMethod<&Win32Gui::getCheck>("getCheck"),
          StaticMethod<&Win32Gui::rgb>("rgb"),

          InstanceAccessor<&Win32Gui::GetHwnd, &Win32Gui::SetX>("hwnd"),
          InstanceAccessor<&Win32Gui::GetX, &Win32Gui::SetX>("x"),
          InstanceAccessor<&Win32Gui::GetY, &Win32Gui::SetY>("y"),
          InstanceAccessor<&Win32Gui::GetWidth, &Win32Gui::SetWidth>("width"),
          InstanceAccessor<&Win32Gui::GetHeight, &Win32Gui::SetHeight>("height"),
          InstanceAccessor<&Win32Gui::GetStyle, &Win32Gui::SetStyle>("style"),
          InstanceMethod<&Win32Gui::initRegisterClass>("initRegisterClass"),
          InstanceMethod<&Win32Gui::initWindow>("initWindow"),
          InstanceMethod<&Win32Gui::messageLoop>("messageLoop"),

          InstanceMethod<&Win32Gui::createWindow>("createWindow"),
          InstanceMethod<&Win32Gui::button>("button"),
          InstanceMethod<&Win32Gui::checkbox>("checkbox"),
          InstanceMethod<&Win32Gui::radio>("radio"),
          InstanceMethod<&Win32Gui::groupbox>("groupbox"),
          InstanceMethod<&Win32Gui::text>("text"),
          InstanceMethod<&Win32Gui::input>("input"),
          InstanceMethod<&Win32Gui::textarea>("textarea"),
          InstanceMethod<&Win32Gui::listbox>("listbox"),
          InstanceMethod<&Win32Gui::select>("select"),
      });
  Napi::FunctionReference *constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  constructor->SuppressDestruct();

  exports.Set("Win32Gui", func);
  return exports;
}

Win32Gui::Win32Gui(const Napi::CallbackInfo &info)
    : ObjectWrap<Win32Gui>(info),
      _Mybase(nmi_s(0), nmi_s(1)),
      _env(info.Env())
{
  nm_init;

  if (info.Length() > 2)
  {
    auto o = nmi_o(2);
    if (o.Has("x"))
      _Mybase::x = nmo_get("x", i);
    if (o.Has("y"))
      _Mybase::y = nmo_get("y", i);
    if (o.Has("width"))
      _Mybase::width = nmo_get("width", i);
    if (o.Has("height"))
      _Mybase::height = nmo_get("height", i);
    if (o.Has("style"))
      _Mybase::style = nmo_get("style", ull);
  }
}

nm_api(Win32Gui::getHLMessage)
{
  nm_init;
  auto hl = _Mybase::getHLMessage(nmi_ui(0));
  return span_to_array<uint16_t>(env, hl);
}

nm_api(Win32Gui::getCheck)
{
  nm_init;
  nm_retb(_Mybase::getCheck((HWND)nmi_ull(0)));
}

nm_api(Win32Gui::rgb)
{
  nm_init_cal(3);
  nm_ret(_Mybase::rgb(nmi_ui(0), nmi_ui(1), nmi_ui(2)));
}

nm_api(Win32Gui::GetHwnd)
{
  nm_init;
  nm_ret((uintptr_t)_Mybase::_hWnd);
}

nm_api(Win32Gui::GetX)
{
  nm_init;
  nm_ret(_Mybase::x);
}
nm_sapi(Win32Gui::SetX)
{
  nm_init;
  _Mybase::x = nm_i(value);
}

nm_api(Win32Gui::GetY)
{
  nm_init;
  nm_ret(_Mybase::y);
}
nm_sapi(Win32Gui::SetY)
{
  nm_init;
  _Mybase::y = nm_i(value);
}

nm_api(Win32Gui::GetWidth)
{
  nm_init;
  nm_ret(_Mybase::width);
}
nm_sapi(Win32Gui::SetWidth)
{
  nm_init;
  _Mybase::width = nm_i(value);
}

nm_api(Win32Gui::GetHeight)
{
  nm_init;
  nm_ret(_Mybase::height);
}
nm_sapi(Win32Gui::SetHeight)
{
  nm_init;
  _Mybase::height = nm_i(value);
}

nm_api(Win32Gui::GetStyle)
{
  nm_init;
  nm_ret(_Mybase::style);
}
nm_sapi(Win32Gui::SetStyle)
{
  nm_init;
  _Mybase::style = nm_i(value);
}

nm_api(Win32Gui::initRegisterClass)
{
  nm_init;
  nm_retb(_Mybase::initRegisterClass());
}
nm_api(Win32Gui::initWindow)
{
  nm_init;
  nm_retb(_Mybase::initWindow());
}
nm_api(Win32Gui::messageLoop)
{
  nm_init;
  if (info.Length() && nmi_is_fu(0))
    messageCallback = nmi_pfu(0);
  nm_ret(_Mybase::messageLoop());
}

nm_api(Win32Gui::createWindow)
{
  nm_init_cal(1);
  nm_ret((uintptr_t)_Mybase::createWindow(getCreateOption(nmi_o(0), 0, 0)));
}

nm_api(Win32Gui::button)
{
  nm_init_cal(1);

  auto o = nmi_o(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);
  nm_ret((uintptr_t)_Mybase::button(getCreateOption(o, dw, dh)));
}

nm_api(Win32Gui::checkbox)
{
  nm_init_cal(1);
  auto o = nmi_o(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);
  nm_ret((uintptr_t)_Mybase::checkbox(getCreateOption(o, dw, dh)));
}

nm_api(Win32Gui::radio)
{
  nm_init_cal(1);

  auto o = nmi_o(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);
  nm_ret((uintptr_t)_Mybase::radio(getCreateOption(o, dw, dh)));
}

nm_api(Win32Gui::groupbox)
{
  nm_init_cal(1);

  auto o = nmi_o(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);

  nm_ret((uintptr_t)_Mybase::groupbox(getCreateOption(o, dw, dh)));
}

nm_api(Win32Gui::text)
{
  nm_init_cal(1);
  auto o = nmi_o(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);
  nm_ret((uintptr_t)_Mybase::text(getCreateOption(o, dw, dh)));
}

nm_api(Win32Gui::input)
{
  nm_init_cal(1);
  auto o = nmi_o(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 100, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);
  nm_ret((uintptr_t)_Mybase::input(getCreateOption(o, dw, dh)));
}

nm_api(Win32Gui::textarea)
{
  nm_init_cal(1);
  auto o = nmi_o(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 100, 4);
  int dh = MulDiv(HIWORD(units), 14 * 5, 8);
  nm_ret((uintptr_t)_Mybase::textarea(getCreateOption(o, dw, dh)));
}

nm_api(Win32Gui::listbox)
{
  nm_init_cal(1);
  auto o = nmi_o(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 100, 4);
  int dh = MulDiv(HIWORD(units), 14 * 5, 8);
  nm_ret((uintptr_t)_Mybase::listbox(getCreateOption(o, dw, dh)));
}

nm_api(Win32Gui::select)
{
  nm_init_cal(1);
  auto o = nmi_o(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 100, 4);
  int dh = MulDiv(HIWORD(units), 14 * 5, 8);
  nm_ret((uintptr_t)_Mybase::select(getCreateOption(o, dw, dh)));
}

std::unique_ptr<ajanuw::Gui::Win32CreateOption> Win32Gui::getCreateOption(const Napi::Object &o, int dw, int dh)
{
  return std::make_unique<ajanuw::Gui::Win32CreateOption>(
      nmo_is_und("className", s, ""),
      nmo_is_und("windowName", s, ""),
      nmo_is_und("style", ui, 0),
      nmo_is_und("x", i, 0),
      nmo_is_und("y", i, 0),
      nmo_is_und("width", i, dw),
      nmo_is_und("height", i, dh),
      (HMENU)nmo_get("id", ull),
      (HWND)(nmo_is_und("parent", ull, 0)));
}

void Win32Gui::setEvents(const Napi::Object &opt)
{
  if (opt.Has("events"))
  {
    HMENU id = (HMENU)nm_ull(opt.Get("id"));
    eventMap[id] = new Win32GuiEvent{nm_o(opt.Get("events"))};
  }
}