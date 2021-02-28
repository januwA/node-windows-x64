#include "win32_gui.h"

#define SET_EVENT(type) \
  if (o.Has(#type))    \
  ##type = nm_get_to(#type, funref)

Win32GuiEvent::Win32GuiEvent(Napi::Object o)
{
  SET_EVENT(click);
  SET_EVENT(keydown);
}

Win32GuiEvent::~Win32GuiEvent()
{
}

LRESULT Win32Gui::OnReceiveMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  const std::initializer_list<napi_value> args = {
      Napi::Number::New(env_, (uintptr_t)hWnd),
      Napi::Number::New(env_, (uintptr_t)message),
      Napi::Number::New(env_, (uintptr_t)wParam),
      Napi::Number::New(env_, (uintptr_t)lParam),
  };
  switch (message)
  {
  case WM_COMMAND:
  {
    HMENU id = (HMENU)LOWORD(wParam);
    if (_eventMap.count(id))
    {
      Win32GuiEvent *e = _eventMap.at(id);
      if (e->click)
        e->click.Call(args);
    }
  }
  break;
  }

  if (_messageCallback)
  {
    return _messageCallback.Call(args).ToNumber().Uint32Value();
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
      ajanuw::Gui::Win32(nmi_str(0), nmi_str(1)),
      env_(info.Env())
{
  nm_init;

  if (info.Length() > 2)
  {
    Napi::Object o = nmi_obj(2);
    if (o.Has("x"))
      ajanuw::Gui::Win32::x_ = nm_get_to("x", int);
    if (o.Has("y"))
      ajanuw::Gui::Win32::y_ = nm_get_to("y", int);
    if (o.Has("width"))
      ajanuw::Gui::Win32::width_ = nm_get_to("width", int);
    if (o.Has("height"))
      ajanuw::Gui::Win32::height_ = nm_get_to("height", int);
    if (o.Has("style"))
      ajanuw::Gui::Win32::style_ = nm_get_to("style", dword);
  }
}

Win32Gui::~Win32Gui()
{
}

Napi::Value Win32Gui::getHLMessage(const Napi::CallbackInfo &info)
{
  nm_init;
  auto hl = ajanuw::Gui::Win32::getHLMessage(nmi_dword(0));
  nm_arr_form_vect(r, hl);
  return r;
}

Napi::Value Win32Gui::getCheck(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_retb(ajanuw::Gui::Win32::getCheck((HWND)nmi_qword(0)));
}

Napi::Value Win32Gui::rgb(const Napi::CallbackInfo &info)
{
  nm_init_cal(3);
  nm_ret(ajanuw::Gui::Win32::rgb(nmi_dword(0), nmi_dword(1), nmi_dword(2)));
}

Napi::Value Win32Gui::GetX(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(ajanuw::Gui::Win32::x_);
}
void Win32Gui::SetX(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  nm_init;
  ajanuw::Gui::Win32::x_ = nm_int(value);
}

Napi::Value Win32Gui::GetY(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(ajanuw::Gui::Win32::y_);
}
void Win32Gui::SetY(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  nm_init;
  ajanuw::Gui::Win32::y_ = nm_int(value);
}

Napi::Value Win32Gui::GetWidth(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(ajanuw::Gui::Win32::width_);
}
void Win32Gui::SetWidth(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  nm_init;
  ajanuw::Gui::Win32::width_ = nm_int(value);
}

Napi::Value Win32Gui::GetHeight(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(ajanuw::Gui::Win32::height_);
}
void Win32Gui::SetHeight(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  nm_init;
  ajanuw::Gui::Win32::height_ = nm_int(value);
}

Napi::Value Win32Gui::GetStyle(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(ajanuw::Gui::Win32::style_);
}
void Win32Gui::SetStyle(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  nm_init;
  ajanuw::Gui::Win32::style_ = nm_int(value);
}

Napi::Value Win32Gui::initRegisterClass(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_retb(ajanuw::Gui::Win32::initRegisterClass());
}
Napi::Value Win32Gui::initWindow(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_retb(ajanuw::Gui::Win32::initWindow());
}
Napi::Value Win32Gui::messageLoop(const Napi::CallbackInfo &info)
{
  nm_init;
  if (info.Length() && nmi_is_fun(0))
    _messageCallback = Napi::Persistent(nmi_fun(0));
  nm_ret(ajanuw::Gui::Win32::messageLoop());
}

Napi::Value Win32Gui::createWindow(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  nm_ret((uintptr_t)ajanuw::Gui::Win32::createWindow(getCreateOption(nmi_obj(0), 0, 0)));
}

Napi::Value Win32Gui::button(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  Napi::Object o = nmi_obj(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);
  nm_ret((uintptr_t)ajanuw::Gui::Win32::button(getCreateOption(o, dw, dh)));
}

Napi::Value Win32Gui::checkbox(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  Napi::Object o = nmi_obj(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);
  nm_ret((uintptr_t)ajanuw::Gui::Win32::checkbox(getCreateOption(o, dw, dh)));
}

Napi::Value Win32Gui::radio(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  Napi::Object o = nmi_obj(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);
  nm_ret((uintptr_t)ajanuw::Gui::Win32::radio(getCreateOption(o, dw, dh)));
}

Napi::Value Win32Gui::groupbox(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  Napi::Object o = nmi_obj(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);

  nm_ret((uintptr_t)ajanuw::Gui::Win32::groupbox(getCreateOption(o, dw, dh)));
}

Napi::Value Win32Gui::text(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  Napi::Object o = nmi_obj(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);
  nm_ret((uintptr_t)ajanuw::Gui::Win32::text(getCreateOption(o, dw, dh)));
}

Napi::Value Win32Gui::input(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  Napi::Object o = nmi_obj(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 100, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);
  nm_ret((uintptr_t)ajanuw::Gui::Win32::input(getCreateOption(o, dw, dh)));
}

Napi::Value Win32Gui::textarea(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  Napi::Object o = nmi_obj(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 100, 4);
  int dh = MulDiv(HIWORD(units), 14 * 5, 8);
  nm_ret((uintptr_t)ajanuw::Gui::Win32::textarea(getCreateOption(o, dw, dh)));
}

Napi::Value Win32Gui::listbox(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  Napi::Object o = nmi_obj(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 100, 4);
  int dh = MulDiv(HIWORD(units), 14 * 5, 8);
  nm_ret((uintptr_t)ajanuw::Gui::Win32::listbox(getCreateOption(o, dw, dh)));
}

Napi::Value Win32Gui::select(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  Napi::Object o = nmi_obj(0);
  setEvents(o);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 100, 4);
  int dh = MulDiv(HIWORD(units), 14 * 5, 8);
  nm_ret((uintptr_t)ajanuw::Gui::Win32::select(getCreateOption(o, dw, dh)));
}

ajanuw::Gui::Win32CreateOption Win32Gui::getCreateOption(Napi::Object o, int dw, int dh)
{
  return ajanuw::Gui::Win32CreateOption{
      nm_is_nullishOr(o.Get("className"), nm_str, ""),
      nm_is_nullishOr(o.Get("windowName"), nm_str, ""),
      nm_is_nullishOr(o.Get("style"), nm_dword, 0),
      nm_is_nullishOr(o.Get("x"), nm_int, 0),
      nm_is_nullishOr(o.Get("y"), nm_int, 0),
      nm_is_nullishOr(o.Get("width"), nm_int, dw),
      nm_is_nullishOr(o.Get("height"), nm_int, dh),
      (HMENU)nm_qword(o.Get("id")),
      (HWND)(nm_is_nullishOr(o.Get("parent"), nm_qword, 0)),
  };
}

void Win32Gui::setEvents(Napi::Object options)
{
  if (options.Has("events"))
  {
    HMENU id = (HMENU)nm_qword(options.Get("id"));
    _eventMap.insert(std::pair<HMENU, Win32GuiEvent *>(
        id,
        new Win32GuiEvent{nm_obj(options.Get("events"))}));
  }
}