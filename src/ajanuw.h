#pragma once
#pragma warning(disable : 4819)

#include <ostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <psapi.h>
#include <regex>
#include <fstream>
#include <map>
#include <sstream>
#include <asmjit/asmjit.h>
#include <asmtk/asmtk.h>

#define uptr_size sizeof(uintptr_t)

typedef uintptr_t(CALLBACK *callback_t)(void *_, void *index, uintptr_t *lpRcx, uintptr_t *lpP5);

namespace ajanuw
{
  LPVOID createCallback(callback_t lpCallback, size_t index);

  namespace SSString
  {
    char *setLocale(int _Category = LC_ALL, const char *_Locale = "chs");
    std::wstring strToWstr(std::string str);
    std::u16string strToUstr(std::string str);
    std::string ustrToStr(std::u16string ustr);
    std::string wstrToStr(std::wstring wstr);
    std::wstring ustrToWstr(std::u16string ustr);
    std::u16string wstrToUstr(std::wstring wstr);

    void strToMem(void *dst, std::string str);
    void strToMem(void *dst, std::wstring str);
    void strToMem(void *dst, std::u16string str);

    // TODO: Fix "ab��" get "ab?" when max is 3
    std::string strFormMem(void *src, uintptr_t max);
    std::wstring wstrFormMem(void *src, uintptr_t max);
    std::u16string ustrFormMem(void *src, uintptr_t max);

    bool startWith(std::string str, const char *s2);
    bool endWith(std::string str, const char *s2);
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

    std::string strFormNumber(uintptr_t number, bool isHex = false);
  }

  namespace Mem
  {
    LPVOID alloc(SIZE_T dwSize, LPVOID lpAddress = 0, DWORD flAllocationType = MEM_COMMIT | MEM_RESERVE, DWORD flProtect = PAGE_EXECUTE_READWRITE);
    BOOL free(LPVOID lpAddress);
    BOOL free(std::string CEAddtrssString);

    void write_str(void *lpAddress, std::string str);
    void write_wstr(void *lpAddress, std::wstring str);
    void write_ustr(void *lpAddress, std::u16string str);
    void write_byte(void *lpAddress, BYTE byte);
    void write_bytes(void *lpAddress, std::vector<BYTE> bytes);
    void write_word(void *lpAddress, WORD value);
    void write_dword(void *lpAddress, DWORD value);
    void write_qword(void *lpAddress, uint64_t value);
    void write_float(void *lpAddress, float value);
    void write_double(void *lpAddress, double value);
    void write_region_to_file(std::string filename, void *lpAddress, uintptr_t size);
  
    void write_str(std::string CEAddtrssString, std::string str);
    void write_wstr(std::string CEAddtrssString, std::wstring str);
    void write_ustr(std::string CEAddtrssString, std::u16string str);
    void write_byte(std::string CEAddtrssString, BYTE byte);
    void write_bytes(std::string CEAddtrssString, std::vector<BYTE> bytes);
    void write_word(std::string CEAddtrssString, WORD value);
    void write_dword(std::string CEAddtrssString, DWORD value);
    void write_qword(std::string CEAddtrssString, uint64_t value);
    void write_float(std::string CEAddtrssString, float value);
    void write_double(std::string CEAddtrssString, double value);
    void write_region_to_file(std::string filename, std::string CEAddtrssString, uintptr_t size);

    std::string read_str(char *lpAddress, uintptr_t max);
    std::wstring read_wstr(wchar_t *lpAddress, uintptr_t max);
    std::u16string read_ustr(char16_t *lpAddress, uintptr_t max);

    std::string read_str(std::string CEAddtrssString, uintptr_t max);
    std::wstring read_wstr(std::string CEAddtrssString, uintptr_t max);
    std::u16string read_ustr(std::string CEAddtrssString, uintptr_t max);

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

    std::vector<BYTE> read_bytes(std::string CEAddtrssString, uintptr_t size);
    BYTE read_byte(std::string CEAddtrssString);
    WORD read_word(std::string CEAddtrssString);
    DWORD read_dword(std::string CEAddtrssString);
    uint64_t read_qword(std::string CEAddtrssString);
    uintptr_t read_pointer(std::string CEAddtrssString);
    float read_float(std::string CEAddtrssString);
    double read_double(std::string CEAddtrssString);
    void read_region_from_file(std::string fileame, std::string CEAddtrssString);
    void read_region_from_file(std::string fileame, std::string CEAddtrssString, size_t *fileSize);

    class VAManage
    {
    public:
      VAManage(size_t size);
      ~VAManage();
      const uintptr_t size_;
      LPVOID memory_;
      size_t position_;

      // memory_ +  position_
      uint8_t *ptr_();

      // read bytes
      std::vector<uint8_t> read(size_t size);
      uint8_t readByte();
      uint16_t readWord();
      uint32_t readDword();
      uint64_t readQword();
      float readFloat();
      double readDouble();
      std::string readStr(size_t maxSize);
      std::wstring readWstr(size_t maxSize);
      std::u16string readUstr(size_t maxSize);

      // write bytes
      void write(std::vector<uint8_t> table, size_t count);
      void writeByte(uint8_t v);
      void writeWord(uint16_t v);
      void writeDword(uint32_t v);
      void writeQword(uintptr_t v);
      void writeFloat(float v);
      void writeDouble(double v);
      void writeStr(std::string str);
      void writeWstr(std::wstring wstr);
      void writeUstr(std::u16string ustr);

      void loadFromFile(std::string filename);
      void saveToFile(std::string filename);
      BOOL destroy();

    private:
    };
  }

  namespace Gui
  {
    class Win32
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

      Win32(std::string className, std::string windowName);
      ~Win32();

      /// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowa
      HWND createWindow(std::string lpClassName, std::string lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HMENU hMenu);

      /// <summary>
      /// 消息循环
      /// </summary>
      int messageLoop();

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

      virtual void wndProc_(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    };
  }

  namespace Asm
  {
    class AutoAsm
    {
    private:
    public:
      std::string script_;
      AutoAsm(std::string script);
      ~AutoAsm();
    };
  }

  class Symbol
  {
  public:
    static void registerSymbol(std::string symbolname, LPVOID address);
    static void unregisterSymbol(std::string symbolname);
    static LPVOID get(std::string symbolname);
    static bool has(std::string symbolname);

  private:
    static std::map<std::string, LPVOID> _symbolMap;
  };

  namespace CEStringe
  {
    struct SplitListItem
    {
      std::string key;
      std::string value;
    };

    /* example

struct _TestData
{
  DWORD hp = 10;
  DWORD mp = 2;
  char* name = "abc";
} TestData;

  ajanuw::Symbol::registerSymbol("ttt", &TestData);
  LPVOID addr = ajanuw::CEStringe::getAddress("[ttt+8]+2");
  printf("%p\n", addr);
  printf("%c\n", *(char*)addr); // c



  LPVOID addr = ajanuw::CEStringe::getAddress("user32.MessageBoxA");
  printf("%p\n", addr);
  printf("%p\n", MessageBoxA);



  LPVOID addr = ajanuw::CEStringe::getAddress("MessageBoxA");
  printf("%p\n", addr);
  printf("%p\n", MessageBoxA);


    */
    LPVOID getAddress(std::string address, LPVOID nextValue = NULL);
    std::string replaceString(std::string origenString, std::string replaceString, std::string newValue);
    std::vector<SplitListItem> splitString(std::string origenString);
    LPVOID getData(std::string str);
  }

}
