#include "win32_gui.h"

Win32GuiEvent::Win32GuiEvent(HMENU id) : id_(id)
{
}

Win32GuiEvent::~Win32GuiEvent()
{
}

LRESULT Win32Gui::OnReceiveMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

  switch (message)
  {
  case WM_COMMAND:
  {
    HMENU id = (HMENU)LOWORD(wParam);
    if (_eventMap.count(id))
    {
      Win32GuiEvent *e = _eventMap.at(id);
      if (e->click)
        e->click.Call({});
    }
  }
  break;
  }

  if (_messageCallback)
  {
    return _messageCallback.Call({
                                     Napi::Number::New(env_, (uintptr_t)hWnd),
                                     Napi::Number::New(env_, (uintptr_t)message),
                                     Napi::Number::New(env_, (uintptr_t)wParam),
                                     Napi::Number::New(env_, (uintptr_t)lParam),
                                 })
        .ToNumber()
        .Uint32Value();
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
    if (nm_has(o, "x"))
      ajanuw::Gui::Win32::x_ = nm_get_to(o, "x", int);
    if (nm_has(o, "y"))
      ajanuw::Gui::Win32::y_ = nm_get_to(o, "y", int);
    if (nm_has(o, "width"))
      ajanuw::Gui::Win32::width_ = nm_get_to(o, "width", int);
    if (nm_has(o, "height"))
      ajanuw::Gui::Win32::height_ = nm_get_to(o, "height", int);
    if (nm_has(o, "style"))
      ajanuw::Gui::Win32::style_ = nm_get_to(o, "style", dword);
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
  Napi::Object opt = nmi_obj(0);
  nm_ret((uintptr_t)ajanuw::Gui::Win32::createWindow(
      ajanuw::Gui::Win32CreateOption{
          nm_str(opt.Get("className")),
          nm_is_nullishOr(opt.Get("windowName"), nm_str, ""),
          nm_is_nullishOr(opt.Get("style"), nm_dword, 0),
          nm_is_nullishOr(opt.Get("x"), nm_int, 0),
          nm_is_nullishOr(opt.Get("y"), nm_int, 0),
          nm_int(opt.Get("width")),
          nm_int(opt.Get("height")),
          (HMENU)nm_qword(opt.Get("id")),
          (HWND)(nm_is_nullishOr(opt.Get("parent"), nm_qword, 0)),
      }));
}

Napi::Value Win32Gui::button(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  Napi::Object opt = nmi_obj(0);
  HMENU id = (HMENU)nm_qword(opt.Get("id"));
  if (opt.Has("events"))
  {
    Napi::Object events = nm_obj(opt.Get("events"));
    _eventMap.insert(std::pair<HMENU, Win32GuiEvent *>(id, new Win32GuiEvent{id}));
    if (events.Has("click"))
      _eventMap.at(id)->click = nm_funref(events.Get("click"));
    if (events.Has("keydown"))
      _eventMap.at(id)->click = nm_funref(events.Get("keydown"));
  }

  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);

  nm_ret((uintptr_t)ajanuw::Gui::Win32::button(
      ajanuw::Gui::Win32CreateOption{
          "",
          nm_is_nullishOr(opt.Get("windowName"), nm_str, ""),
          nm_is_nullishOr(opt.Get("style"), nm_dword, 0),
          nm_is_nullishOr(opt.Get("x"), nm_int, 0),
          nm_is_nullishOr(opt.Get("y"), nm_int, 0),
          nm_is_nullishOr(opt.Get("width"), nm_int, dw),
          nm_is_nullishOr(opt.Get("height"), nm_int, dh),
          id,
          (HWND)(nm_is_nullishOr(opt.Get("parent"), nm_qword, 0)),
      }));
}

Napi::Value Win32Gui::checkbox(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  Napi::Object opt = nmi_obj(0);

  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);

  nm_ret((uintptr_t)ajanuw::Gui::Win32::checkbox(
      ajanuw::Gui::Win32CreateOption{
          "",
          nm_is_nullishOr(opt.Get("windowName"), nm_str, ""),
          nm_is_nullishOr(opt.Get("style"), nm_dword, 0),
          nm_is_nullishOr(opt.Get("x"), nm_int, 0),
          nm_is_nullishOr(opt.Get("y"), nm_int, 0),
          nm_is_nullishOr(opt.Get("width"), nm_int, dw),
          nm_is_nullishOr(opt.Get("height"), nm_int, dh),
          (HMENU)nm_qword(opt.Get("id")),
          (HWND)(nm_is_nullishOr(opt.Get("parent"), nm_qword, 0)),
      }));
}

Napi::Value Win32Gui::radio(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  Napi::Object opt = nmi_obj(0);

  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);

  nm_ret((uintptr_t)ajanuw::Gui::Win32::radio(
      ajanuw::Gui::Win32CreateOption{
          "",
          nm_is_nullishOr(opt.Get("windowName"), nm_str, ""),
          nm_is_nullishOr(opt.Get("style"), nm_dword, 0),
          nm_is_nullishOr(opt.Get("x"), nm_int, 0),
          nm_is_nullishOr(opt.Get("y"), nm_int, 0),
          nm_is_nullishOr(opt.Get("width"), nm_int, dw),
          nm_is_nullishOr(opt.Get("height"), nm_int, dh),
          (HMENU)nm_qword(opt.Get("id")),
          (HWND)(nm_is_nullishOr(opt.Get("parent"), nm_qword, 0)),
      }));
}

Napi::Value Win32Gui::groupbox(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  Napi::Object opt = nmi_obj(0);

  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);

  nm_ret((uintptr_t)ajanuw::Gui::Win32::groupbox(
      ajanuw::Gui::Win32CreateOption{
          "",
          nm_is_nullishOr(opt.Get("windowName"), nm_str, ""),
          nm_is_nullishOr(opt.Get("style"), nm_dword, 0),
          nm_is_nullishOr(opt.Get("x"), nm_int, 0),
          nm_is_nullishOr(opt.Get("y"), nm_int, 0),
          nm_is_nullishOr(opt.Get("width"), nm_int, dw),
          nm_is_nullishOr(opt.Get("height"), nm_int, dh),
          (HMENU)nm_qword(opt.Get("id")),
          (HWND)(nm_is_nullishOr(opt.Get("parent"), nm_qword, 0)),
      }));
}

Napi::Value Win32Gui::text(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  Napi::Object opt = nmi_obj(0);

  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);

  nm_ret((uintptr_t)ajanuw::Gui::Win32::text(
      ajanuw::Gui::Win32CreateOption{
          "",
          nm_is_nullishOr(opt.Get("windowName"), nm_str, ""),
          nm_is_nullishOr(opt.Get("style"), nm_dword, 0),
          nm_is_nullishOr(opt.Get("x"), nm_int, 0),
          nm_is_nullishOr(opt.Get("y"), nm_int, 0),
          nm_is_nullishOr(opt.Get("width"), nm_int, dw),
          nm_is_nullishOr(opt.Get("height"), nm_int, dh),
          (HMENU)nm_qword(opt.Get("id")),
          (HWND)(nm_is_nullishOr(opt.Get("parent"), nm_qword, 0)),
      }));
}

Napi::Value Win32Gui::input(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  Napi::Object opt = nmi_obj(0);

  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 100, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);

  nm_ret((uintptr_t)ajanuw::Gui::Win32::input(
      ajanuw::Gui::Win32CreateOption{
          "",
          nm_is_nullishOr(opt.Get("windowName"), nm_str, ""),
          nm_is_nullishOr(opt.Get("style"), nm_dword, 0),
          nm_is_nullishOr(opt.Get("x"), nm_int, 0),
          nm_is_nullishOr(opt.Get("y"), nm_int, 0),
          nm_is_nullishOr(opt.Get("width"), nm_int, dw),
          nm_is_nullishOr(opt.Get("height"), nm_int, dh),
          (HMENU)nm_qword(opt.Get("id")),
          (HWND)(nm_is_nullishOr(opt.Get("parent"), nm_qword, 0)),
      }));
}

Napi::Value Win32Gui::textarea(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  Napi::Object opt = nmi_obj(0);

  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 100, 4);
  int dh = MulDiv(HIWORD(units), 14 * 5, 8);

  nm_ret((uintptr_t)ajanuw::Gui::Win32::textarea(
      ajanuw::Gui::Win32CreateOption{
          "",
          nm_is_nullishOr(opt.Get("windowName"), nm_str, ""),
          nm_is_nullishOr(opt.Get("style"), nm_dword, 0),
          nm_is_nullishOr(opt.Get("x"), nm_int, 0),
          nm_is_nullishOr(opt.Get("y"), nm_int, 0),
          nm_is_nullishOr(opt.Get("width"), nm_int, dw),
          nm_is_nullishOr(opt.Get("height"), nm_int, dh),
          (HMENU)nm_qword(opt.Get("id")),
          (HWND)(nm_is_nullishOr(opt.Get("parent"), nm_qword, 0)),
      }));
}

Napi::Value Win32Gui::listbox(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  Napi::Object opt = nmi_obj(0);

  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 100, 4);
  int dh = MulDiv(HIWORD(units), 14 * 5, 8);

  nm_ret((uintptr_t)ajanuw::Gui::Win32::listbox(
      ajanuw::Gui::Win32CreateOption{
          "",
          nm_is_nullishOr(opt.Get("windowName"), nm_str, ""),
          nm_is_nullishOr(opt.Get("style"), nm_dword, 0),
          nm_is_nullishOr(opt.Get("x"), nm_int, 0),
          nm_is_nullishOr(opt.Get("y"), nm_int, 0),
          nm_is_nullishOr(opt.Get("width"), nm_int, dw),
          nm_is_nullishOr(opt.Get("height"), nm_int, dh),
          (HMENU)nm_qword(opt.Get("id")),
          (HWND)(nm_is_nullishOr(opt.Get("parent"), nm_qword, 0))}));
}

Napi::Value Win32Gui::select(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  Napi::Object opt = nmi_obj(0);

  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 100, 4);
  int dh = MulDiv(HIWORD(units), 14 * 5, 8);

  nm_ret((uintptr_t)ajanuw::Gui::Win32::select(
      ajanuw::Gui::Win32CreateOption{
          "",
          nm_is_nullishOr(opt.Get("windowName"), nm_str, ""),
          nm_is_nullishOr(opt.Get("style"), nm_dword, 0),
          nm_is_nullishOr(opt.Get("x"), nm_int, 0),
          nm_is_nullishOr(opt.Get("y"), nm_int, 0),
          nm_is_nullishOr(opt.Get("width"), nm_int, dw),
          nm_is_nullishOr(opt.Get("height"), nm_int, dh),
          (HMENU)nm_qword(opt.Get("id")),
          (HWND)(nm_is_nullishOr(opt.Get("parent"), nm_qword, 0)),
      }));
}