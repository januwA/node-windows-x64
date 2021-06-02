#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <Windows.h>
#include <napi.h>
#include <sphelper.h>
#include "_napi_macro.h"

Napi::Number getProcessID(const Napi::CallbackInfo &info)
{
  nm_init;
  if (info.Length() != NULL)
  {
    nm_ret(ajanuw::PE::GetPID(nmi_str(0)));
  }
  else
  {
    nm_ret(GetCurrentProcessId());
  }
}
Napi::Number getCurrentProcess(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret((uintptr_t)GetCurrentProcess());
}
Napi::Number openProcess(const Napi::CallbackInfo &info)
{
  nm_init;
  uint32_t dwDesiredAccess = nm_is_nullishOr(info[0], nm_dword, PROCESS_ALL_ACCESS);
  BOOL bInheritHandle = info[1].ToBoolean() ? TRUE : FALSE;
  uint32_t dwProcessId = nm_is_nullishOr(info[2], nm_dword, GetCurrentProcessId());
  nm_ret((uintptr_t)OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId));
}
Napi::Value closeHandle(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  nm_retb(CloseHandle((HANDLE)nmi_qword(0)));
}

Napi::Value getMousePos(const Napi::CallbackInfo &info)
{
  nm_init;
  POINT pos{0};
  if (GetCursorPos(&pos) == NULL)
    nm_retu;
  auto r = Napi::Object::New(env);
  r.Set("x", pos.x);
  r.Set("y", pos.y);
  return r;
}

Napi::Value setMousePos(const Napi::CallbackInfo &info)
{
  nm_init_cal(2);
  int x, y;
  if (info[0].IsObject())
  {
    x = nm_int(nmi_obj(0).Get("x"));
    y = nm_int(nmi_obj(0).Get("y"));
  }
  else
  {
    x = nmi_int(0);
    y = nmi_int(1);
  }
  nm_retb(SetCursorPos(x, y));
}

Napi::Value isKeyPressed(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  nm_retb(GetKeyState(nmi_int(0)));
}

Napi::Value keyDown(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  keybd_event(nmi_dword(0), 0, 0, 0);
  nm_retu;
}

Napi::Value keyUp(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  keybd_event(nmi_dword(0), 0, KEYEVENTF_KEYUP, 0);
  nm_retu;
}

Napi::Value doKeyPress(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  keyDown(info);
  keyUp(info);
  nm_retu;
}

Napi::Value e_mouse_event(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  uint32_t dwFlags = nmi_dword(0);
  uint32_t dx = nm_is_nullishOr(info[1], nm_dword, 0);
  uint32_t dy = nm_is_nullishOr(info[2], nm_dword, 0);
  uint32_t dwData = nm_is_nullishOr(info[3], nm_dword, 0);
  ULONG_PTR dwExtraInf = nm_is_nullishOr(info[4], nm_dword, 0);

  /*
  mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
  mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
  */

  INPUT ip;
  ip.type = INPUT_MOUSE;
  ip.mi.dx = dx;
  ip.mi.dy = dy;
  ip.mi.mouseData = dwData;
  ip.mi.time = 0;
  ip.mi.dwExtraInfo = dwExtraInf;
  ip.mi.dwFlags = dwFlags;
  nm_ret(SendInput(INPUT_KEYBOARD, &ip, sizeof(ip)));
}

// https://docs.microsoft.com/en-us/windows/win32/dataxchg/using-the-clipboard
Napi::Value readFromClipboard(const Napi::CallbackInfo &info)
{
  nm_init;
  if (!OpenClipboard(nullptr))
    nm_retbf;

  HGLOBAL hglb = GetClipboardData(CF_TEXT);
  if (!hglb)
    nm_retbf;

  LPTSTR lptstr = (LPTSTR)GlobalLock(hglb);
  if (!lptstr)
    nm_retbf;

  GlobalUnlock(hglb);
  CloseClipboard();
  nm_rets((char *)lptstr);
}

// https://docs.microsoft.com/en-us/windows/win32/dataxchg/using-the-clipboard
Napi::Value writeToClipboard(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);

  if (!OpenClipboard(nullptr))
    nm_retbf;
  EmptyClipboard();

  std::string output = nmi_str(0);
  HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, output.size());
  if (hMem == NULL)
    nm_retbf;

  memcpy_s(GlobalLock(hMem), output.size(), output.c_str(), output.size());
  GlobalUnlock(hMem);

  SetClipboardData(CF_TEXT, hMem);

  CloseClipboard();
  nm_retbt;
}

Napi::Value getScreenHeight(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CYSCREEN));
}

Napi::Value getScreenWidth(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CXSCREEN));
}

Napi::Value getWorkAreaWidth(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CXFULLSCREEN));
}

Napi::Value getWorkAreaHeight(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CYFULLSCREEN));
}

Napi::Value getPixel(const Napi::CallbackInfo &info)
{
  nm_init_cal(2);
  int x = nmi_int(0);
  int y = nmi_int(1);

  HDC dc = GetDC(NULL);
  COLORREF rgbColor = GetPixel(dc, x, y);
  auto r = Napi::Object::New(env);
  r.Set("r", Napi::Number::New(env, GetRValue(rgbColor)));
  r.Set("g", Napi::Number::New(env, GetGValue(rgbColor)));
  r.Set("b", Napi::Number::New(env, GetBValue(rgbColor)));
  r.Set("rgb", Napi::Number::New(env, rgbColor));
  ReleaseDC(NULL, dc);
  return r;
}

Napi::Value beep(const Napi::CallbackInfo &info)
{
  nm_init;
  uint32_t dwFreq = nmi_is_nullishOr(0, nm_dword, 750);
  uint32_t dwDuration = nmi_is_nullishOr(1, nm_dword, 300);
  nm_retb(Beep(dwFreq, dwDuration));
}

// https://docs.microsoft.com/en-us/previous-versions/office/developer/speech-technologies/jj127460(v=msdn.10)?redirectedfrom=MSDN
Napi::Value speak(const Napi::CallbackInfo &info)
{
  nm_init;
  std::u16string pwcs = nmi_ustr(0);
  uint32_t dwFlags = SPF_DEFAULT;
  ULONG *pulStreamNumber = NULL;

  CoInitialize(NULL);
  ISpVoice *pSpVoice = NULL;
  if (FAILED(CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, IID_ISpVoice, (void **)&pSpVoice)))
    nm_retu;

  pSpVoice->Speak((LPCWSTR)pwcs.c_str(), dwFlags, pulStreamNumber);
  pSpVoice->Release();
  CoUninitialize();
  nm_retbt;
}

Napi::Value sleep(const Napi::CallbackInfo &info)
{
  nm_init;
  uint32_t dwMilliseconds = nmi_dword(0);
  Sleep(dwMilliseconds);
  nm_retu;
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-findwindowa
Napi::Value findWindow(const Napi::CallbackInfo &info)
{
  nm_init;
  std::string sClassName = nmi_str(0);
  std::string sWindowName = nmi_str(1);

  BOOL hasLpClassName = info[0].ToBoolean();
  BOOL hasLpWindowName = info[0].ToBoolean();

  LPCSTR lpClassName = hasLpClassName ? sClassName.c_str() : NULL;
  LPCSTR lpWindowName = hasLpWindowName ? sWindowName.c_str() : NULL;

  nm_ret((uintptr_t)FindWindowA(lpClassName, lpWindowName));
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindow
Napi::Value getWindow(const Napi::CallbackInfo &info)
{
  nm_init;
  uintptr_t hWnd = nmi_qword(0);
  UINT uCmd = nmi_dword(1);
  nm_ret((uintptr_t)GetWindow((HWND)hWnd, uCmd));
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowtexta
Napi::Value getWindowCaption(const Napi::CallbackInfo &info)
{
  nm_init;
  uintptr_t hWnd = nmi_qword(0);
  std::u16string usCaption;
  usCaption.resize(1024);
  if (GetWindowTextW((HWND)hWnd, (LPWSTR)usCaption.data(), usCaption.size()) == NULL)
    nm_retu;
  nm_rets(usCaption);
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclassname
Napi::Value getWindowClassName(const Napi::CallbackInfo &info)
{
  nm_init;
  uintptr_t hWnd = nmi_qword(0);
  std::u16string sClassName;
  sClassName.resize(1024);
  if (GetClassNameW((HWND)hWnd, (LPWSTR)sClassName.data(), sClassName.size()) == NULL)
    nm_retu;
  nm_rets(sClassName);
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowthreadprocessid
Napi::Value getWindowProcessID(const Napi::CallbackInfo &info)
{
  nm_init;
  uintptr_t hWnd = nmi_qword(0);

  int lpdwProcessId;
  int id = GetWindowThreadProcessId((HWND)hWnd, (LPDWORD)&lpdwProcessId);

  Napi::Object r = Napi::Object::New(env);
  r.Set("pid", Napi::Number::New(env, lpdwProcessId));
  r.Set("tid", Napi::Number::New(env, id));

  return r;
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getforegroundwindow
Napi::Value getForegroundWindow(const Napi::CallbackInfo &info)
{
  nm_init;
  nm_ret((uintptr_t)GetForegroundWindow());
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendmessage
Napi::Value sendMessage(const Napi::CallbackInfo &info)
{
  nm_init_cal(4);
  uintptr_t hWnd = nmi_qword(0);
  UINT Msg = nmi_dword(1);
  uintptr_t wParam = nmi_qword(2);
  uintptr_t lParam = nmi_qword(3);

  if (nmi_is_str(2) && nmi_is_num(3))
  {
    nm_ret((uintptr_t)SendMessageA((HWND)hWnd, Msg, (WPARAM)nmi_str(2).c_str(), (LPARAM)lParam));
  }
  else if (nmi_is_num(2) && nmi_is_str(3))
  {
    nm_ret((uintptr_t)SendMessageA((HWND)hWnd, Msg, (WPARAM)wParam, (LPARAM)nmi_str(3).c_str()));
  }
  else if (nmi_is_str(2) && nmi_is_str(3))
  {
    nm_ret((uintptr_t)SendMessageA((HWND)hWnd, Msg, (WPARAM)nmi_str(2).c_str(), (LPARAM)nmi_str(3).c_str()));
  }
  else
  {
    nm_ret((uintptr_t)SendMessageA((HWND)hWnd, Msg, (WPARAM)wParam, (LPARAM)lParam));
  }
}

// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/setlocale-wsetlocale?view=msvc-160&viewFallbackFrom=vs-2019
Napi::Value e_setlocale(const Napi::CallbackInfo &info)
{
  nm_init;
  int _Category = nmi_is_nullishOr(0, nm_dword, LC_ALL);
  std::string _Locale = nmi_is_nullishOr(1, nm_str, "chs");
  nm_rets(ajanuw::SSString::setLocale(_Category, _Locale.c_str()));
}

Napi::Value registerSymbol(const Napi::CallbackInfo &info)
{
  nm_init_cal(2);
  ajanuw::Symbol::registerSymbol(nmi_str(0), (LPVOID)nmi_qword(1));
  nm_retu;
}

Napi::Value unregisterSymbol(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  ajanuw::Symbol::unregisterSymbol(nmi_str(0));
  nm_retu;
}

Napi::Value getAddress(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  try
  {
    if (info.Length() == 1)
    {
      nm_ret((uintptr_t)ajanuw::CEAddressString::getAddress(nmi_str(0)));
    }
    else
    {
      nm_ret((uintptr_t)ajanuw::CEAddressString::getAddress(nmi_str(0), (HANDLE)nmi_qword(1)));
    }
  }
  catch (const std::exception &e)
  {
    nm_jserr(e.what());
    nm_retu;
  }
}

Napi::Value aa(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  try
  {
    nm_ret(ajanuw::Asm::AAScript::aa(nmi_str(0), nm_is_nullishOr(info[1], nm_qword, 0)));
  }
  catch (const std::exception &e)
  {
    nm_jserr(e.what());
    nm_retu;
  }
}

Napi::Value asmBytes(const Napi::CallbackInfo &info)
{
  nm_init_cal(1);
  try
  {
    bool isX64 = true;

    if (info.Length() > 1)
    {
      isX64 = nmi_bool(1);
    }

    std::vector<uint8_t> r = ajanuw::Asm::AAScript::asmBytes(nmi_str(0), isX64);
    auto buf = Napi::ArrayBuffer::New(env, r.size());
    memcpy_s((BYTE *)buf.Data(), buf.ByteLength(), r.data(), buf.ByteLength());
    return buf;
  }
  catch (const std::exception &e)
  {
    nm_jserr(e.what());
    nm_retu;
  }
}