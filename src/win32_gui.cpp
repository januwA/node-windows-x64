#include "win32_gui.h"

void Win32Gui::wndProc_(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  if (_cb)
  {
    _cb.Call({
        Napi::Number::New(env_, (uintptr_t)hWnd),
        Napi::Number::New(env_, (uintptr_t)message),
        Napi::Number::New(env_, (uintptr_t)wParam),
        Napi::Number::New(env_, (uintptr_t)lParam),
    });
  }
}

Napi::Object Win32Gui::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
      env, "Win32Gui",
      {
          StaticMethod<&Win32Gui::getHLMessage>("getHLMessage"),
          StaticMethod<&Win32Gui::getCheck>("getCheck"),

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
    Napi::Object opt = nmi_obj(2);

    if (opt.Has("x"))
      ajanuw::Gui::Win32::x_ = nm_int(opt.Get("x"));
    if (opt.Has("y"))
      ajanuw::Gui::Win32::y_ = nm_int(opt.Get("y"));
    if (opt.Has("width"))
      ajanuw::Gui::Win32::width_ = nm_int(opt.Get("width"));
    if (opt.Has("height"))
      ajanuw::Gui::Win32::height_ = nm_int(opt.Get("height"));
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

Napi::Value Win32Gui::getCheck(const Napi::CallbackInfo& info)
{
  nm_init;
  nm_retb(ajanuw::Gui::Win32::getCheck((HWND)nmi_qword(0)));
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
  nm_ret(ajanuw::Gui::Win32::initRegisterClass());
}
Napi::Value Win32Gui::initWindow(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_retb(ajanuw::Gui::Win32::initWindow());
}
Napi::Value Win32Gui::messageLoop(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  _cb = Napi::Persistent(nmi_fun(0));
  nm_ret(ajanuw::Gui::Win32::messageLoop());
}

Napi::Value Win32Gui::createWindow(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  Napi::Object opt = nmi_obj(0);
  nm_ret((uintptr_t)ajanuw::Gui::Win32::createWindow(
      ajanuw::Gui::Win32CreateOption{
          nm_str(opt.Get("className")),
          nm_str(opt.Get("windowName")),
          nm_dword(opt.Get("style")),
          nm_is_nullishOr(opt.Get("x"), nm_int, 0),
          nm_is_nullishOr(opt.Get("y"), nm_int, 0),
          nm_int(opt.Get("width")),
          nm_int(opt.Get("height")),
          (HMENU)nm_qword(opt.Get("id")),
      }));
}

Napi::Value Win32Gui::button(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  Napi::Object opt = nmi_obj(0);
  LONG units = GetDialogBaseUnits();
  int dw = MulDiv(LOWORD(units), 50, 4);
  int dh = MulDiv(HIWORD(units), 14, 8);

  nm_ret((uintptr_t)ajanuw::Gui::Win32::button(
      ajanuw::Gui::Win32CreateOption{
          "",
          nm_str(opt.Get("windowName")),
          nm_is_nullishOr(opt.Get("style"), nm_dword, 0),
          nm_is_nullishOr(opt.Get("x"), nm_int, 0),
          nm_is_nullishOr(opt.Get("y"), nm_int, 0),
          nm_is_nullishOr(opt.Get("width"), nm_int, dw),
          nm_is_nullishOr(opt.Get("height"), nm_int, dh),
          (HMENU)nm_qword(opt.Get("id")),
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
          nm_str(opt.Get("windowName")),
          nm_is_nullishOr(opt.Get("style"), nm_dword, 0),
          nm_is_nullishOr(opt.Get("x"), nm_int, 0),
          nm_is_nullishOr(opt.Get("y"), nm_int, 0),
          nm_is_nullishOr(opt.Get("width"), nm_int, dw),
          nm_is_nullishOr(opt.Get("height"), nm_int, dh),
          (HMENU)nm_qword(opt.Get("id")),
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
          nm_str(opt.Get("windowName")),
          nm_is_nullishOr(opt.Get("style"), nm_dword, 0),
          nm_is_nullishOr(opt.Get("x"), nm_int, 0),
          nm_is_nullishOr(opt.Get("y"), nm_int, 0),
          nm_is_nullishOr(opt.Get("width"), nm_int, dw),
          nm_is_nullishOr(opt.Get("height"), nm_int, dh),
          (HMENU)nm_qword(opt.Get("id")),
      }));
}