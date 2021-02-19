#pragma once
#include <ostream>
#include <Windows.h>
#include <regex>
#include <fstream>
#include <map>

#include <napi.h> // Try not to use napi in it

namespace ajanuw
{

  LPVOID createCallback(void *lpAddress, size_t index);

  namespace SSString
  {
    char *setLocale(int _Category = LC_ALL, const char *_Locale = "chs");
    std::wstring strTowstr(std::string str);
    std::u16string strToustr(std::string str);
    std::string ustrTostr(std::u16string ustr);
    std::string wstrTostr(std::wstring wstr);
    std::wstring ustrTowstr(std::u16string ustr);
    std::u16string wstrToustr(std::wstring wstr);

    void strToMem(void *dst, std::string str);
    void strToMem(void *dst, std::wstring str);
    void strToMem(void *dst, std::u16string str);

    // TODO: Fix "ab��" get "ab?" when max is 3
    std::string strFormMem(void *src, uintptr_t max);
    std::wstring wstrFormMem(void *src, uintptr_t max);
    std::u16string ustrFormMem(void *src, uintptr_t max);

    bool startWith(std::string str, const char *s2);
    bool endWith(std::string str, const char *s2);
    std::vector<std::string> match(std::string str, std::regex reg);
    bool search(std::string str, std::regex reg);
    std::string trim(std::string str);
    std::string trimStart(std::string str);
    std::string trimEnd(std::string str);
    std::vector<std::string> split(std::string str, std::regex reg);
    std::vector<BYTE> toBytes(std::string byteStr);

    BOOL cmp(const char *s1, const char *s2);
    BOOL cmp(std::string s1, std::string s2);
    BOOL cmp(const wchar_t *s1, const wchar_t *s2);
    BOOL cmp(std::wstring s1, std::wstring s2);
    BOOL cmp(const char16_t *s1, const char16_t *s2);
    BOOL cmp(std::u16string s1, std::u16string s2);

    BOOL icmp(const char *s1, const char *s2);
    BOOL icmp(std::string s1, std::string s2);
    BOOL icmp(const wchar_t *s1, const wchar_t *s2);
    BOOL icmp(std::wstring s1, std::wstring s2);
    BOOL icmp(const char16_t *s1, const char16_t *s2);
    BOOL icmp(std::u16string s1, std::u16string s2);

    size_t len(const char *str);
    size_t len(const char *str, size_t maxSize);
    size_t len(const wchar_t *str);
    size_t len(const wchar_t *str, size_t maxSize);
    size_t len(std::string str);
    size_t len(std::wstring str);
    size_t len(std::u16string str);

    size_t count(const char *str);
    size_t count(const char *str, size_t maxSize);
    size_t count(const wchar_t *str);
    size_t count(const wchar_t *str, size_t maxSize);
    size_t count(std::string str);
    size_t count(std::wstring str);
    size_t count(std::u16string str);
  }

  namespace Mem
  {
    LPVOID alloc(SIZE_T dwSize, LPVOID lpAddress = 0, DWORD flAllocationType = MEM_COMMIT | MEM_RESERVE, DWORD flProtect = PAGE_EXECUTE_READWRITE);
    BOOL free(LPVOID lpAddress);

    void write_str(void *lpAddress, std::string str);
    void write_str(void *lpAddress, std::wstring str);
    void write_str(void *lpAddress, std::u16string str);
    void write_bytes(void *lpAddress, std::vector<BYTE> bytes);
    void write_word(void *lpAddress, WORD value);
    void write_dword(void *lpAddress, DWORD value);
    void write_qword(void *lpAddress, uint64_t value);
    void write_float(void *lpAddress, float value);
    void write_double(void *lpAddress, double value);
    void write_region_to_file(std::string filename, void *lpAddress, uintptr_t size);

    std::string read_str(char *lpAddress, uintptr_t max);
    std::wstring read_str(wchar_t *lpAddress, uintptr_t max);
    std::u16string read_str(char16_t *lpAddress, uintptr_t max);

    std::vector<BYTE> read_bytes(void *lpAddress, uintptr_t size);
    BYTE read_byte(void *lpAddress);
    WORD read_word(void *lpAddress);
    DWORD read_dword(void *lpAddress);
    uint64_t read_qword(void *lpAddress);
    uintptr_t read_pointer(void *lpAddress);
    float read_float(void *lpAddress);
    double read_double(void *lpAddress);
    void read_region_from_file(std::string fileame, void *lpAddress);
    void read_region_from_file(std::string fileame, void *lpAddress, size_t *fileSize);
  }

  namespace Gui
  {
    class Win32Gui
    {
    public:
      /// <summary>
      /// 主窗口句柄
      /// </summary>
      HWND hWnd_;

      std::string windowName_;
      std::string className_;
      size_t x_;
      size_t y_;
      size_t width_;
      size_t height_;
      DWORD style_;

      Napi::Env env_;
      Napi::FunctionReference cb_;

      WNDPROC messageEvent;

      Win32Gui(std::string className, std::string windowName);
      ~Win32Gui();

      /// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowa
      HWND createWindow(std::string lpClassName, std::string lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HMENU hMenu);

      /// <summary>
      /// 消息循环
      /// </summary>
      int messageLoop(Napi::Env env, Napi::Function cb);

      // 注册窗口类
      // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexw
      ATOM initRegisterClass();

      /// <summary>
      /// 窗口初始化
      /// </summary>
      /// <returns></returns>
      BOOL initWindow();

    private:
      static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

      void wndProc_(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    };
  }
}
