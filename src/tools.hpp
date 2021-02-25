#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <Windows.h>
#include <napi.h>
#include <sphelper.h>
#include "_napi_macro.h"

using namespace Napi;

Number getProcessID(const CallbackInfo &info)
{
  nm_init;
  nm_ret(GetCurrentProcessId());
}
Number getCurrentProcess(const CallbackInfo &info)
{
  nm_init;
  nm_ret((uintptr_t)GetCurrentProcess());
}
Number openProcess(const CallbackInfo &info)
{
  nm_init;
  DWORD dwDesiredAccess = nm_is_nullishOr(info[0], nm_dword, PROCESS_ALL_ACCESS);
  BOOL bInheritHandle = info[1].ToBoolean() ? TRUE : FALSE;
  DWORD dwProcessId = nm_is_nullishOr(info[2], nm_dword, GetCurrentProcessId());
  nm_ret((uintptr_t)OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId));
}
Value closeHandle(const CallbackInfo &info)
{
  nm_init_cal(1);
  nm_retb(CloseHandle((HANDLE)nmi_qword(0)));
}

Value getMousePos(const CallbackInfo &info)
{
  nm_init;
  POINT pos{0};
  if (GetCursorPos(&pos) == NULL)
    nm_retu;
  auto r = Object::New(env);
  r.Set("x", pos.x);
  r.Set("y", pos.y);
  return r;
}

Value setMousePos(const CallbackInfo &info)
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

Value isKeyPressed(const CallbackInfo &info)
{
  nm_init_cal(1);
  nm_retb(GetKeyState(nmi_int(0)));
}

Value keyDown(const CallbackInfo &info)
{
  nm_init_cal(1);
  keybd_event(nmi_dword(0), 0, 0, 0);
  nm_retu;
}

Value keyUp(const CallbackInfo &info)
{
  nm_init_cal(1);
  keybd_event(nmi_dword(0), 0, KEYEVENTF_KEYUP, 0);
  nm_retu;
}

Value doKeyPress(const CallbackInfo &info)
{
  nm_init_cal(1);
  keyDown(info);
  keyUp(info);
  nm_retu;
}

Value e_mouse_event(const CallbackInfo &info)
{
  nm_init_cal(1);
  DWORD dwFlags = nmi_dword(0);
  DWORD dx = nm_is_nullishOr(info[1], nm_dword, 0);
  DWORD dy = nm_is_nullishOr(info[2], nm_dword, 0);
  DWORD dwData = nm_is_nullishOr(info[3], nm_dword, 0);
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
Value readFromClipboard(const CallbackInfo &info)
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
Value writeToClipboard(const CallbackInfo &info)
{
  nm_init_cal(1);

  if (!OpenClipboard(nullptr))
    nm_retbf;
  EmptyClipboard();

  string output = nmi_str(0);
  HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, output.size());
  if (hMem == NULL)
    nm_retbf;

  memcpy_s(GlobalLock(hMem), output.size(), output.c_str(), output.size());
  GlobalUnlock(hMem);

  SetClipboardData(CF_TEXT, hMem);

  CloseClipboard();
  nm_retbt;
}

Value getScreenHeight(const CallbackInfo &info)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CYSCREEN));
}

Value getScreenWidth(const CallbackInfo &info)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CXSCREEN));
}

Value getWorkAreaWidth(const CallbackInfo &info)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CXFULLSCREEN));
}

Value getWorkAreaHeight(const CallbackInfo &info)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CYFULLSCREEN));
}

Value getPixel(const CallbackInfo &info)
{
  nm_init_cal(2);
  int x = nmi_int(0);
  int y = nmi_int(1);

  HDC dc = GetDC(NULL);
  COLORREF rgbColor = GetPixel(dc, x, y);
  auto r = Object::New(env);
  r.Set("r", Number::New(env, GetRValue(rgbColor)));
  r.Set("g", Number::New(env, GetGValue(rgbColor)));
  r.Set("b", Number::New(env, GetBValue(rgbColor)));
  r.Set("rgb", Number::New(env, rgbColor));
  ReleaseDC(NULL, dc);
  return r;
}

Value beep(const CallbackInfo &info)
{
  nm_init;
  DWORD dwFreq = nmi_is_nullishOr(0, nm_dword, 750);
  DWORD dwDuration = nmi_is_nullishOr(1, nm_dword, 300);
  nm_retb(Beep(dwFreq, dwDuration));
}

// https://docs.microsoft.com/en-us/previous-versions/office/developer/speech-technologies/jj127460(v=msdn.10)?redirectedfrom=MSDN
Value speak(const CallbackInfo &info)
{
  nm_init;
  u16string pwcs = nmi_ustr(0);
  DWORD dwFlags = SPF_DEFAULT;
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

Value sleep(const CallbackInfo &info)
{
  nm_init;
  DWORD dwMilliseconds = nmi_dword(0);
  Sleep(dwMilliseconds);
  nm_retu;
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-findwindowa
Value findWindow(const CallbackInfo &info)
{
  nm_init;
  string sClassName = nmi_str(0);
  string sWindowName = nmi_str(1);

  BOOL hasLpClassName = info[0].ToBoolean();
  BOOL hasLpWindowName = info[0].ToBoolean();

  LPCSTR lpClassName = hasLpClassName ? sClassName.c_str() : NULL;
  LPCSTR lpWindowName = hasLpWindowName ? sWindowName.c_str() : NULL;

  nm_ret((uintptr_t)FindWindowA(lpClassName, lpWindowName));
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindow
Value getWindow(const CallbackInfo &info)
{
  nm_init;
  uintptr_t hWnd = nmi_qword(0);
  UINT uCmd = nmi_dword(1);
  nm_ret((uintptr_t)GetWindow((HWND)hWnd, uCmd));
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowtexta
Value getWindowCaption(const CallbackInfo &info)
{
  nm_init;
  uintptr_t hWnd = nmi_qword(0);
  char sCaption[1024];
  int r = GetWindowTextA((HWND)hWnd, sCaption, sizeof(sCaption));
  if (r == NULL)
    nm_retu;
  nm_rets(sCaption);
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclassname
Value getWindowClassName(const CallbackInfo &info)
{
  nm_init;
  uintptr_t hWnd = nmi_qword(0);
  char sClassName[1024];
  int r = GetClassNameA((HWND)hWnd, sClassName, sizeof(sClassName));
  if (r == NULL)
    nm_retu;
  nm_rets(sClassName);
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowthreadprocessid
Value getWindowProcessID(const CallbackInfo &info)
{
  nm_init;
  uintptr_t hWnd = nmi_qword(0);

  int lpdwProcessId;
  int id = GetWindowThreadProcessId((HWND)hWnd, (LPDWORD)&lpdwProcessId);

  Object r = Object::New(env);
  r.Set("pid", Number::New(env, lpdwProcessId));
  r.Set("tid", Number::New(env, id));

  return r;
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getforegroundwindow
Value getForegroundWindow(const CallbackInfo &info)
{
  nm_init;
  nm_ret((uintptr_t)GetForegroundWindow());
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendmessage
Value sendMessage(const CallbackInfo &info)
{
  nm_init_cal(4);
  uintptr_t hWnd = nmi_qword(0);
  UINT Msg = nmi_dword(1);
  uint32_t wParam = nmi_dword(2);
  uint32_t lParam = nmi_dword(3);
  nm_ret((uintptr_t)SendMessageA((HWND)hWnd, Msg, (WPARAM)wParam, (LPARAM)lParam));
}

// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/setlocale-wsetlocale?view=msvc-160&viewFallbackFrom=vs-2019
Value e_setlocale(const CallbackInfo &info)
{
  nm_init;
  int _Category = nmi_is_nullishOr(0, nm_dword, LC_ALL);
  string _Locale = nmi_is_nullishOr(1, nm_str, "chs");
  nm_rets(ajanuw::SSString::setLocale(_Category, _Locale.c_str()));
}

Value registerSymbol(const CallbackInfo &info)
{
  nm_init_cal(2);
  ajanuw::Symbol::registerSymbol(nmi_str(0), (LPVOID)nmi_qword(1));
  nm_retu;
}

Value unregisterSymbol(const CallbackInfo &info)
{
  nm_init_cal(1);
  ajanuw::Symbol::unregisterSymbol(nmi_str(0));
  nm_retu;
}

Value getAddress(const CallbackInfo &info)
{
  nm_init_cal(1);
  nm_ret((uintptr_t)ajanuw::CEStringe::getAddress(nmi_str(0)));
}