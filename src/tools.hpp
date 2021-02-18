#pragma once
#pragma warning(disable: 4996)

#include <iostream>
#include <Windows.h>
#include <napi.h>
#include <sphelper.h>
#include "_napi_macro.h"

using namespace Napi;

Number getProcessID(const CallbackInfo& info)
{
  nm_init;
  nm_ret(GetCurrentProcessId());
}
Number getCurrentProcess(const CallbackInfo& info)
{
  nm_init;
  nm_ret((uintptr_t)GetCurrentProcess());
}
Number openProcess(const CallbackInfo& info)
{
  nm_init;
  DWORD dwDesiredAccess = info[0].IsNumber() ? nm_dword(info[0]) : PROCESS_ALL_ACCESS;
  BOOL bInheritHandle = info[1].ToBoolean() ? TRUE : FALSE;
  DWORD dwProcessId = nm_IsNullishOr(info[2], nm_dword, GetCurrentProcessId());
  nm_ret((uintptr_t)OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId));
}
Value closeHandle(const CallbackInfo& info)
{
  nm_init;
  nm_ret((uintptr_t)CloseHandle((HANDLE)info[0].ToNumber().Int64Value()));
}

Value getMousePos(const CallbackInfo& info)
{
  nm_init;
  POINT pos{ 0 };
  if (GetCursorPos(&pos) == NULL) nm_retu;
  auto r = Object::New(env);
  r.Set("x", pos.x);
  r.Set("y", pos.y);
  return r;
}

Value setMousePos(const CallbackInfo& info)
{
  nm_init;
  int x, y;
  if (info[0].IsObject())
  {
    x = nm_int(nm_obj(info[0]).Get("x"));
    y = nm_int(nm_obj(info[0]).Get("y"));
  }
  else
  {
    x = nm_int(info[0]);
    y = nm_int(info[1]);
  }
  nm_retb(SetCursorPos(x, y));
}

Value isKeyPressed(const CallbackInfo& info)
{
  nm_init;
  SHORT r = GetKeyState(nm_int(info[0]));
  nm_retb(r == NULL ? FALSE : TRUE);
}

Value keyDown(const CallbackInfo& info)
{
  nm_init;
  keybd_event(nm_dword(info[0]), 0, 0, 0);
  nm_retu;
}

Value keyUp(const CallbackInfo& info)
{
  nm_init;
  keybd_event(info[0].As<Number>().Uint32Value(), 0, KEYEVENTF_KEYUP, 0);
  nm_retu;
}

Value doKeyPress(const CallbackInfo& info)
{
  keyDown(info);
  keyUp(info);
  return info.Env().Undefined();
}

Value e_mouse_event(const CallbackInfo& info)
{
  nm_init;
  DWORD     dwFlags = nm_dword(info[0]);
  DWORD     dx = nm_IsNullishOr(info[1], nm_dword, 0);
  DWORD     dy = nm_IsNullishOr(info[2], nm_dword, 0);
  DWORD     dwData = nm_IsNullishOr(info[3], nm_dword, 0);
  ULONG_PTR dwExtraInf = nm_IsNullishOr(info[4], nm_dword, 0);

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
  SendInput(INPUT_KEYBOARD, &ip, sizeof(ip));
  nm_retu;
}

// https://docs.microsoft.com/en-us/windows/win32/dataxchg/using-the-clipboard
Value readFromClipboard(const CallbackInfo& info)
{
  nm_init;
  if (!OpenClipboard(nullptr)) nm_retbf;

  HGLOBAL hglb = GetClipboardData(CF_TEXT);
  if (!hglb) nm_retbf;

  LPTSTR lptstr = (LPTSTR)GlobalLock(hglb);
  if (!lptstr) nm_retbf;

  GlobalUnlock(hglb);
  CloseClipboard();
  nm_rets((char*)lptstr);
}

// https://docs.microsoft.com/en-us/windows/win32/dataxchg/using-the-clipboard
Value writeToClipboard(const CallbackInfo& info)
{
  nm_init;

  if (!OpenClipboard(nullptr)) nm_retbf;
  EmptyClipboard();

  string output =nm_str(info[0]);
  HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, output.size());
  if (hMem == NULL) nm_retbf;

  memcpy_s(GlobalLock(hMem), output.size(), output.c_str(), output.size());
  GlobalUnlock(hMem);

  SetClipboardData(CF_TEXT, hMem);

  CloseClipboard();
  nm_retbt;
}

Value getScreenHeight(const CallbackInfo& info)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CYSCREEN));
}

Value getScreenWidth(const CallbackInfo& info)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CXSCREEN));
}

Value getWorkAreaWidth(const CallbackInfo& info)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CXFULLSCREEN));
}

Value getWorkAreaHeight(const CallbackInfo& info)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CYFULLSCREEN));
}

Value getPixel(const CallbackInfo& info)
{
  nm_init;
  HDC dc = GetDC(NULL);
  COLORREF rgbColor = GetPixel(dc, 0, 0);
  auto r = Object::New(env);
  r.Set("r", Number::New(env, GetRValue(rgbColor)));
  r.Set("g", Number::New(env, GetGValue(rgbColor)));
  r.Set("b", Number::New(env, GetBValue(rgbColor)));
  r.Set("rgb", Number::New(env, rgbColor));
  ReleaseDC(NULL, dc);
  return r;
}

Value beep(const CallbackInfo& info)
{
  nm_init;
  DWORD dwFreq = nm_IsNullishOr(info[0], nm_dword, 750);
  DWORD dwDuration = nm_IsNullishOr(info[1], nm_dword, 300);
  nm_ret(Beep(dwFreq, dwDuration));
}

// https://docs.microsoft.com/en-us/previous-versions/office/developer/speech-technologies/jj127460(v=msdn.10)?redirectedfrom=MSDN
Value speak(const CallbackInfo& info)
{
  nm_init;
  u16string pwcs = nm_wstr(info[0]);
  DWORD dwFlags = SPF_DEFAULT;
  ULONG* pulStreamNumber = NULL;

  CoInitialize(NULL);
  ISpVoice* pSpVoice = NULL;
  if (FAILED(CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, IID_ISpVoice, (void**)&pSpVoice))) nm_retu;


  pSpVoice->Speak((LPCWSTR)pwcs.c_str(), dwFlags, pulStreamNumber);
  pSpVoice->Release();
  CoUninitialize();
  nm_retbt;
}

Value sleep(const CallbackInfo& info)
{
  nm_init;
  DWORD dwMilliseconds = nm_dword(info[0]);
  Sleep(dwMilliseconds);
  nm_retu;
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-findwindowa
Value findWindow(const CallbackInfo& info)
{
  nm_init;
  string sClassName = nm_str(info[0]);
  string sWindowName = nm_str(info[1]);

  BOOL hasLpClassName = info[0].ToBoolean();
  BOOL hasLpWindowName = info[0].ToBoolean();

  LPCSTR lpClassName = hasLpClassName ? sClassName.c_str() : NULL;
  LPCSTR lpWindowName = hasLpWindowName ? sWindowName.c_str() : NULL;

  nm_ret((uintptr_t)FindWindowA(lpClassName, lpWindowName));
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindow
Value getWindow(const CallbackInfo& info)
{
  nm_init;
  uintptr_t  hwnd = nm_qword(info[0]);
  UINT uCmd = nm_dword(info[1]);
  nm_ret((uintptr_t)GetWindow((HWND)hwnd, uCmd));
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowtexta
Value getWindowCaption(const CallbackInfo& info)
{
  nm_init;
  uintptr_t hwnd = nm_qword(info[0]);
  char sCaption[1024];
  int r = GetWindowTextA((HWND)hwnd, sCaption, sizeof(sCaption));
  if (r == NULL) nm_retu;
  nm_rets(sCaption);
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclassname
Value getWindowClassName(const CallbackInfo& info)
{
  nm_init;
  uintptr_t hwnd = nm_qword(info[0]);
  char sClassName[1024];
  int r = GetClassNameA((HWND)hwnd, sClassName, sizeof(sClassName));
  if (r == NULL) nm_retu;
  nm_rets(sClassName);
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowthreadprocessid
Value getWindowProcessID(const CallbackInfo& info)
{
  nm_init;
  uintptr_t hwnd = nm_qword(info[0]);

  int lpdwProcessId;
  int id = GetWindowThreadProcessId((HWND)hwnd, (LPDWORD)&lpdwProcessId);

  Object r = Object::New(env);
  r.Set("pid", Number::New(env, lpdwProcessId));
  r.Set("tid", Number::New(env, id));

  return r;
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getforegroundwindow
Value getForegroundWindow(const CallbackInfo& info)
{
  nm_init;
  nm_ret((uintptr_t)GetForegroundWindow());
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendmessage
Value sendMessage(const CallbackInfo& info)
{
  nm_init;
  uintptr_t hWnd = nm_qword(info[0]);
  UINT Msg = nm_dword(info[1]);
  uint32_t wParam = nm_dword(info[2]);
  uint32_t lParam = nm_dword(info[3]);
  SendMessageA((HWND)hWnd, Msg, (WPARAM)wParam, (LPARAM)lParam);
  nm_ret((uintptr_t)GetForegroundWindow());
}