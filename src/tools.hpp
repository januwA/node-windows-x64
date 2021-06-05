#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <Windows.h>
#include <napi.h>
#include <sphelper.h>
#include "_napi_macro.h"

nm_api(getProcessID)
{
  nm_init;
  nm_ret(info.Length() ? ajanuw::PE::GetPID(nmi_s(0)) : GetCurrentProcessId());
}

nm_api(getCurrentProcess)
{
  nm_init;
  nm_ret((uintptr_t)GetCurrentProcess());
}

nm_api(openProcess)
{
  nm_init;
  uint32_t dwDesiredAccess = nmi_is_und(0, ui, PROCESS_ALL_ACCESS);
  BOOL bInheritHandle = nmi_b(1);
  uint32_t dwProcessId = nmi_is_und(2, ui, GetCurrentProcessId());
  nm_ret((uintptr_t)OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId));
}

nm_api(closeHandle)
{
  nm_init_cal(1);
  nm_retb(CloseHandle((HANDLE)nmi_ull(0)));
}

nm_api(getMousePos)
{
  nm_init;
  POINT pos{0};
  if (!GetCursorPos(&pos))
    nm_retu;
  auto r = Napi::Object::New(env);
  r.Set("x", pos.x);
  r.Set("y", pos.y);
  return r;
}

nm_api(setMousePos)
{
  nm_init_cal(2);
  nm_retb(SetCursorPos(nmi_i(0), nmi_i(1)));
}

nm_api(isKeyPressed)
{
  nm_init_cal(1);
  nm_retb(GetKeyState(nmi_i(0)));
}

nm_api(keyDown)
{
  nm_init_cal(1);
  keybd_event(nmi_ui(0), 0, 0, 0);
  nm_retu;
}

nm_api(keyUp)
{
  nm_init_cal(1);
  keybd_event(nmi_ui(0), 0, KEYEVENTF_KEYUP, 0);
  nm_retu;
}

nm_api(doKeyPress)
{
  nm_init_cal(1);
  auto bVK = (uint8_t)nmi_ui(0);
  keybd_event(bVK, 0, 0, 0);
  keybd_event(bVK, 0, KEYEVENTF_KEYUP, 0);
  nm_retu;
}

nm_api(e_mouse_event)
{
  nm_init_cal(1);
  auto dwFlags = nmi_ui(0);
  auto dx = nmi_is_und(1, i, 0);
  auto dy = nmi_is_und(2, i, 0);
  auto dwData = nmi_is_und(3, ui, 0);
  ULONG_PTR dwExtraInf = nmi_is_und(4, ui, 0);

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
nm_api(readFromClipboard)
{
  nm_init;
  if (!OpenClipboard(nullptr))
    nm_retbf;

  auto hglb = GetClipboardData(CF_TEXT);
  if (!hglb)
    nm_retbf;

  auto lptstr = (LPTSTR)GlobalLock(hglb);
  if (!lptstr)
    nm_retbf;

  GlobalUnlock(hglb);
  CloseClipboard();
  nm_rets((char *)lptstr);
}

// https://docs.microsoft.com/en-us/windows/win32/dataxchg/using-the-clipboard
nm_api(writeToClipboard)
{
  nm_init_cal(1);

  if (!OpenClipboard(nullptr))
    nm_retbf;
  EmptyClipboard();

  auto output = nmi_s(0);
  auto hMem = GlobalAlloc(GMEM_MOVEABLE, output.size());
  if (!hMem)
    nm_retbf;

  memcpy_s(GlobalLock(hMem), output.size(), output.c_str(), output.size());
  GlobalUnlock(hMem);

  SetClipboardData(CF_TEXT, hMem);

  CloseClipboard();
  nm_retbt;
}

nm_api(getScreenHeight)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CYSCREEN));
}

nm_api(getScreenWidth)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CXSCREEN));
}

nm_api(getWorkAreaWidth)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CXFULLSCREEN));
}

nm_api(getWorkAreaHeight)
{
  nm_init;
  nm_ret(GetSystemMetrics(SM_CYFULLSCREEN));
}

nm_api(getPixel)
{
  nm_init_cal(2);
  int x = nmi_i(0);
  int y = nmi_i(1);

  auto dc = GetDC(NULL);
  auto rgbColor = GetPixel(dc, x, y);
  auto r = Napi::Object::New(env);
  r.Set("r", GetRValue(rgbColor));
  r.Set("g", GetGValue(rgbColor));
  r.Set("b", GetBValue(rgbColor));
  r.Set("rgb", rgbColor);
  ReleaseDC(NULL, dc);
  return r;
}

nm_api(beep)
{
  nm_init;
  uint32_t dwFreq = nmi_is_und(0, ui, 750);
  uint32_t dwDuration = nmi_is_und(1, ui, 300);
  nm_retb(Beep(dwFreq, dwDuration));
}

// https://docs.microsoft.com/en-us/previous-versions/office/developer/speech-technologies/jj127460(v=msdn.10)?redirectedfrom=MSDN
nm_api(speak)
{
  nm_init_cal(1);
  auto pwcs = nmi_us(0);
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

nm_api(sleep)
{
  nm_init_cal(1);
  Sleep(nmi_ui(0));
  nm_retu;
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-findwindowa
nm_api(findWindow)
{
  nm_init;
  auto classname = nmi_s(0);
  auto windowname = nmi_s(1);
  LPCSTR lpClassName = nmi_b(0) ? classname.data() : NULL;
  LPCSTR lpWindowName = nmi_b(1) ? windowname.data() : NULL;
  nm_ret((uintptr_t)FindWindowA(lpClassName, lpWindowName));
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindow
nm_api(getWindow)
{
  nm_init_cal(2);
  nm_ret((uintptr_t)GetWindow((HWND)nmi_ull(0), (UINT)nmi_ui(1)));
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowtexta
nm_api(getWindowCaption)
{
  nm_init_cal(1);
  std::u16string uCaption;
  uCaption.resize(MAX_CLASS_NAME);
  if (!GetWindowTextW((HWND)nmi_ull(0), (LPWSTR)uCaption.data(), MAX_CLASS_NAME))
    nm_retu;
  nm_rets(uCaption);
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclassname
nm_api(getWindowClassName)
{
  nm_init_cal(1);
  std::u16string uClassName;
  uClassName.resize(MAX_CLASS_NAME);
  if (!GetClassNameW((HWND)nmi_ull(0), (LPWSTR)uClassName.data(), MAX_CLASS_NAME))
    nm_retu;
  nm_rets(uClassName);
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowthreadprocessid
nm_api(getWindowProcessID)
{
  nm_init_cal(1);
  auto hWnd = nmi_ull(0);
  int lpdwProcessId;
  int threadId = GetWindowThreadProcessId((HWND)hWnd, (LPDWORD)&lpdwProcessId);
  auto r = Napi::Object::New(env);
  r.Set("pid", lpdwProcessId);
  r.Set("tid", threadId);

  return r;
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getforegroundwindow
nm_api(getForegroundWindow)
{
  nm_init;
  nm_ret((uintptr_t)GetForegroundWindow());
}

// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendmessage
nm_api(sendMessage)
{
  nm_init_cal(4);
  auto hWnd = nmi_ull(0);
  UINT Msg = nmi_ui(1);
  auto wParam = nmi_ull(2);
  auto lParam = nmi_ull(3);

  if (nmi_is_s(2) && nmi_is_n(3))
  {
    nm_ret((uintptr_t)SendMessageA((HWND)hWnd, Msg, (WPARAM)nmi_s(2).c_str(), (LPARAM)lParam));
  }
  else if (nmi_is_n(2) && nmi_is_s(3))
  {
    nm_ret((uintptr_t)SendMessageA((HWND)hWnd, Msg, (WPARAM)wParam, (LPARAM)nmi_s(3).c_str()));
  }
  else if (nmi_is_s(2) && nmi_is_s(3))
  {
    nm_ret((uintptr_t)SendMessageA((HWND)hWnd, Msg, (WPARAM)nmi_s(2).c_str(), (LPARAM)nmi_s(3).c_str()));
  }
  else
  {
    nm_ret((uintptr_t)SendMessageA((HWND)hWnd, Msg, (WPARAM)wParam, (LPARAM)lParam));
  }
}

// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/setlocale-wsetlocale?view=msvc-160&viewFallbackFrom=vs-2019
nm_api(e_setlocale)
{
  nm_init;
  int _Category = nmi_is_und(0, ui, LC_ALL);
  auto _Locale = nmi_is_und(1, s, "chs");
  nm_rets(ajanuw::sstr::setLocale(_Category, _Locale.c_str()));
}

nm_api(registerSymbol)
{
  nm_init_cal(2);
  ajanuw::Symbol::registerSymbol(nmi_s(0), (LPVOID)nmi_ull(1));
  nm_retu;
}

nm_api(unregisterSymbol)
{
  nm_init_cal(1);
  ajanuw::Symbol::unregisterSymbol(nmi_s(0));
  nm_retu;
}

nm_api(getAddress)
{
  nm_init_cal(1);
  try
  {
    auto r = info.Length() == 1 ? ajanuw::CEAS::getAddress(nmi_s(0)) : ajanuw::CEAS::getAddress(nmi_s(0), (HANDLE)nmi_ull(1));
    nm_ret((uintptr_t)r);
  }
  catch (const std::exception &e)
  {
    nm_err(e.what());
    nm_retu;
  }
}

nm_api(aa)
{
  nm_init_cal(1);
  try
  {
    nm_ret(ajanuw::Asm::AAScript::aa(nmi_s(0), nmi_is_und(1, ull, NULL)));
  }
  catch (const std::exception &e)
  {
    nm_err(e.what());
    nm_retu;
  }
}

nm_api(asmBytes)
{
  nm_init_cal(1);
  try
  {
    auto isX64 = nmi_is_und(1, b, true);
    auto r = ajanuw::Asm::AAScript::asmBytes(nmi_s(0), isX64);
    auto buf = Napi::ArrayBuffer::New(env, r.size());
    memcpy_s((BYTE *)buf.Data(), buf.ByteLength(), r.data(), buf.ByteLength());
    return buf;
  }
  catch (const std::exception &e)
  {
    nm_err(e.what());
    nm_retu;
  }
}