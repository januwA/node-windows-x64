#include "win32_gui.h"

Napi::Object Win32Gui::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
      env, "Win32Gui",
      {
          InstanceAccessor<&Win32Gui::GetX, &Win32Gui::SetX>("x"),
          InstanceAccessor<&Win32Gui::GetY, &Win32Gui::SetY>("y"),
          InstanceAccessor<&Win32Gui::GetWidth, &Win32Gui::SetWidth>("width"),
          InstanceAccessor<&Win32Gui::GetHeight, &Win32Gui::SetHeight>("height"),
          InstanceAccessor<&Win32Gui::GetStyle, &Win32Gui::SetStyle>("style"),
          InstanceMethod<&Win32Gui::initRegisterClass>("initRegisterClass"),
          InstanceMethod<&Win32Gui::initWindow>("initWindow"),
          InstanceMethod<&Win32Gui::messageLoop>("messageLoop"),
          InstanceMethod<&Win32Gui::createWindow>("createWindow"),

      });
  Napi::FunctionReference *constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  constructor->SuppressDestruct();

  exports.Set("Win32Gui", func);
  return exports;
}

Win32Gui::Win32Gui(const Napi::CallbackInfo &info) : ObjectWrap<Win32Gui>(info)
{
  nm_init;
  auto cname = nmi_str(0);
  auto wname = nmi_str(1);
  gui_ = new ajanuw::Gui::Win32Gui(cname, wname);

  if (info.Length() > 2)
  {
    Napi::Object opt = nmi_obj(2);

    if (opt.Has("x"))
      gui_->x_ = nm_int(opt.Get("x"));
    if (opt.Has("y"))
      gui_->y_ = nm_int(opt.Get("y"));
    if (opt.Has("width"))
      gui_->width_ = nm_int(opt.Get("width"));
    if (opt.Has("height"))
      gui_->height_ = nm_int(opt.Get("height"));
  }
}

Win32Gui::~Win32Gui()
{
}

Napi::Value Win32Gui::GetX(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(gui_->x_);
}
void Win32Gui::SetX(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  nm_init;
  gui_->x_ = nm_int(value);
}

Napi::Value Win32Gui::GetY(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(gui_->y_);
}
void Win32Gui::SetY(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  nm_init;
  gui_->y_ = nm_int(value);
}

Napi::Value Win32Gui::GetWidth(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(gui_->width_);
}
void Win32Gui::SetWidth(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  nm_init;
  gui_->width_ = nm_int(value);
}

Napi::Value Win32Gui::GetHeight(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(gui_->height_);
}
void Win32Gui::SetHeight(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  nm_init;
  gui_->height_ = nm_int(value);
}

Napi::Value Win32Gui::GetStyle(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(gui_->style_);
}
void Win32Gui::SetStyle(const Napi::CallbackInfo &info, const Napi::Value &value)
{
  nm_init;
  gui_->style_ = nm_int(value);
}

Napi::Value Win32Gui::initRegisterClass(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(gui_->initRegisterClass());
}
Napi::Value Win32Gui::initWindow(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_retb(gui_->initWindow());
}
Napi::Value Win32Gui::messageLoop(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  nm_ret(gui_->messageLoop(info.Env(), info[0].As<Napi::Function>()));
}

Napi::Value Win32Gui::createWindow(const Napi::CallbackInfo &info)
{
  nm_init_cal(8);
  std::string lpClassName = nmi_str(0);
  std::string lpWindowName = nmi_str(1);
  DWORD dwStyle = nmi_dword(2);
  int x = nmi_int(3);
  int y = nmi_int(4);
  int nWidth = nmi_int(5);
  int nHeight = nmi_int(6);
  HMENU hMenu = (HMENU)nmi_dword(7);

  nm_ret((uintptr_t)gui_->createWindow(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hMenu));
}
