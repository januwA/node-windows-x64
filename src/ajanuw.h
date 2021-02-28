#pragma once
#pragma warning(disable : 4819)

#include <ostream>
#include <Windows.h>
#include <Windowsx.h>
#include <TlHelp32.h>
#include <psapi.h>
#include <regex>
#include <fstream>
#include <map>
#include <sstream>
#include <asmjit/asmjit.h>
#include <asmtk/asmtk.h>

#define uptr_size sizeof(uintptr_t)

namespace ajanuw
{
  LPVOID createCallback(void*  lpCallback, size_t index, void* vCC);

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

    // TODO: 按字节读取，读中会出问题
    std::string strFormMem(void *src, size_t max);
    std::wstring wstrFormMem(void *src, size_t max);
    std::u16string ustrFormMem(void *src, size_t max);

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
    BOOL free(std::string CEAddressString);

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

    void write_str(std::string CEAddressString, std::string str);
    void write_wstr(std::string CEAddressString, std::wstring str);
    void write_ustr(std::string CEAddressString, std::u16string str);
    void write_byte(std::string CEAddressString, BYTE byte);
    void write_bytes(std::string CEAddressString, std::vector<BYTE> bytes);
    void write_word(std::string CEAddressString, WORD value);
    void write_dword(std::string CEAddressString, DWORD value);
    void write_qword(std::string CEAddressString, uint64_t value);
    void write_float(std::string CEAddressString, float value);
    void write_double(std::string CEAddressString, double value);
    void write_region_to_file(std::string filename, std::string CEAddressString, uintptr_t size);

    std::string read_str(char *lpAddress, uintptr_t max);
    std::wstring read_wstr(wchar_t *lpAddress, uintptr_t max);
    std::u16string read_ustr(char16_t *lpAddress, uintptr_t max);

    std::string read_str(std::string CEAddressString, uintptr_t max);
    std::wstring read_wstr(std::string CEAddressString, uintptr_t max);
    std::u16string read_ustr(std::string CEAddressString, uintptr_t max);

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

    std::vector<BYTE> read_bytes(std::string CEAddressString, uintptr_t size);
    BYTE read_byte(std::string CEAddressString);
    WORD read_word(std::string CEAddressString);
    DWORD read_dword(std::string CEAddressString);
    uint64_t read_qword(std::string CEAddressString);
    uintptr_t read_pointer(std::string CEAddressString);
    float read_float(std::string CEAddressString);
    double read_double(std::string CEAddressString);
    void read_region_from_file(std::string fileame, std::string CEAddressString);
    void read_region_from_file(std::string fileame, std::string CEAddressString, size_t *fileSize);

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

    struct Win32CreateOption
    {
      std::string className;
      std::string windowName;
      DWORD style;
      int x;
      int y;
      int width;
      int height;
      HMENU id;
      HWND parent;
    };

    class Win32
    {
    public:
      // 0: HIWORD, 1: LOWORD
      static std::vector<WORD> getHLMessage(DWORD message);
      static bool getCheck(HWND hWnd);
      static DWORD rgb(DWORD r, DWORD g, DWORD b);

      // 主窗口句柄
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

      // 消息循环
      int messageLoop();

      // 注册窗口类
      // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexw
      ATOM initRegisterClass();

      // 窗口初始化
      BOOL initWindow();

      /// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowa
      HWND createWindow(Win32CreateOption opt);
      HWND button(Win32CreateOption opt);
      HWND checkbox(Win32CreateOption opt);
      HWND radio(Win32CreateOption opt);
      HWND groupbox(Win32CreateOption opt);
      HWND text(Win32CreateOption opt);
      HWND input(Win32CreateOption opt);
      HWND textarea(Win32CreateOption opt);
      HWND listbox(Win32CreateOption opt);
      HWND select(Win32CreateOption opt);

    protected:
      static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
      virtual LRESULT OnReceiveMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    private:
      static std::map<HWND, uintptr_t> hwndMap;
    };
  }

  namespace Asm
  {
    using namespace asmjit;
    using namespace asmtk;
    using namespace asmjit::x86;
    
    typedef uintptr_t (*Func)(uintptr_t lpParam);

    class AAScript
    {
    private:
    public:
      std::string script_;
      AAScript(std::string script);
      ~AAScript();

      // auto asm
      static uintptr_t aa(std::string, uintptr_t rcx);
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

  namespace CEString
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
