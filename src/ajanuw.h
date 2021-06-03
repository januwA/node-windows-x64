#pragma once
#pragma warning(disable : 4819)

#include <ostream>
#include <algorithm>
#include <regex>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <memory>
#include <ranges>

#include <Windows.h>
#include <Windowsx.h>
#include <TlHelp32.h>
#include <psapi.h>

#include <asmjit/asmjit.h>
#include <asmtk/asmtk.h>

#include "./ces/export.h"

#define uptr_size sizeof(uintptr_t)

namespace ajanuw
{
  LPVOID createCallback(void *lpCallback, size_t index, void *vCC);

  namespace SSString
  {
    char *setLocale(int _Category = LC_ALL, const char *_Locale = "chs");
    std::wstring strToWstr(std::string_view str);
    std::u16string strToUstr(std::string_view str);
    std::string ustrToStr(std::u16string_view ustr);
    std::string wstrToStr(std::wstring_view wstr);
    std::wstring ustrToWstr(std::u16string_view ustr);
    std::u16string wstrToUstr(std::wstring_view wstr);

    // string data write to memry
    void toMem(void *dst, std::string_view str);
    void toMem(void *dst, std::wstring_view str);
    void toMem(void *dst, std::u16string_view str);

    void toMemEx(HANDLE hProcess, void *dst, std::string_view str);
    void toMemEx(HANDLE hProcess, void *dst, std::wstring_view str);
    void toMemEx(HANDLE hProcess, void *dst, std::u16string_view str);

    // TODO: 按字节读取，读中文会出问题
    std::string strFormMem(void *src, size_t max);
    std::wstring wstrFormMem(void *src, size_t max);
    std::u16string ustrFormMem(void *src, size_t max);

    std::string strFormMemEx(HANDLE hProcess, void *src, size_t max);
    std::wstring wstrFormMemEx(HANDLE hProcess, void *src, size_t max);
    std::u16string ustrFormMemEx(HANDLE hProcess, void *src, size_t max);

    /*
    * ajanuw::SSString::startWith("123", "12")   -> true
    * ajanuw::SSString::startWith("123", "2")    -> false
    * ajanuw::SSString::startWith("123", "2", 1) -> true
    */
    bool startWith(std::string_view str, std::string_view s2, size_t index = 0);

    /*
    * ajanuw::SSString::endWith("123", "23")     -> true
    * ajanuw::SSString::endWith("123", "2")      -> false
    * ajanuw::SSString::endWith("12333", "2", 2) -> true
    */
    bool endWith(std::string_view str, const char *s2);
    bool endWith(std::string_view, const char *s2, size_t length);

    bool search(std::string_view str, const std::regex &reg);
    bool search(std::wstring_view str, const std::regex &reg);

    /*
    * ajanuw::SSString::trim("  abc  ")      -> "abc"
    * ajanuw::SSString::trimStart("  abc  ") -> "abc  "
    * ajanuw::SSString::trimEnd("  abc  ")   -> "  abc"
    */
    std::string trim(std::string_view str);
    std::string trimStart(std::string_view str);
    std::string trimEnd(std::string_view str);

    /*
    * ajanuw::SSString::split("a,b-c", std::regex("[,\\-]")) -> ["a", "b", "c"]
    */
    std::vector<std::string> split(const std::string &str, const std::regex &reg);

    /*
    * ajanuw::SSString::toBytes("00 01 02") -> [1,2,3]
    */
    std::vector<uint8_t> toBytes(std::string_view byteStr);

    /*
    * ajanuw::SSString::cmp("abc", "abc") -> true
    * ajanuw::SSString::cmp("abc", "abx") -> false
    */
    BOOL cmp(std::string_view s1, std::string_view s2);
    BOOL cmp(std::wstring_view s1, std::wstring_view s2);
    BOOL cmp(std::u16string_view s1, std::u16string_view s2);

    /*
    * ajanuw::SSString::icmp("abc", "ABc")   -> true
    * ajanuw::SSString::icmp("abc", "ABx")   -> false
    * ajanuw::SSString::icmp(L"abc", L"ABc") -> true
    * ajanuw::SSString::icmp(L"abc", L"ABx") -> false
    */
    BOOL icmp(std::string_view s1, std::string_view s2);
    BOOL icmp(std::wstring_view s1, std::wstring_view s2);
    BOOL icmp(std::u16string_view s1, std::u16string_view s2);

    /*
    * ignore \0
    * ajanuw::SSString::len("abc")  -> 3
    * ajanuw::SSString::len(L"abc") -> 3
    */
    size_t len(std::string_view str);
    size_t len(std::wstring_view str);
    size_t len(std::u16string_view str);

    /*
    * ignore \0
    * ajanuw::SSString::count("abc")  -> 3
    * ajanuw::SSString::count(L"abc") -> 6
    */
    size_t count(std::string_view str);
    size_t count(std::wstring_view str);
    size_t count(std::u16string_view str);

    /*
    * ajanuw::SSString::strFormNumber(255)       -> "255"
    * ajanuw::SSString::strFormNumber(255, true) -> "ff"
    */
    std::string strFormNumber(uintptr_t number, bool isHex = false);

    /*
    * ajanuw::SSString::tolower("ABC") -> "abc"
    * ajanuw::SSString::toupper("abc") -> "ABC"
    */
    std::string tolower(std::string s);
    std::string toupper(std::string s);

    std::wstring tolower(std::wstring s);
    std::wstring toupper(std::wstring s);

    /*
    * ajanuw::SSString::padStart("abc", 5, "^") -> "^^abc"
    * ajanuw::SSString::padEnd("abc", 5, "^")   -> "abc^^"
    */
    std::string pad(std::string_view str, size_t size, std::string_view padStr, bool isStart);
    std::string padStart(std::string_view str, size_t size, std::string_view padStr);
    std::string padEnd(std::string_view str, size_t size, std::string_view padStr);

    /*
    * ajanuw::SSString::repeat("abc", 3) -> "abcabcabc"
    */
    std::string repeat(std::string_view str, size_t len);

    /*
    * join<MyStruct*>(vct, "--", [](MyStruct* item) { return item->name; })
    */
    std::string join(const std::vector<std::string> &v, std::string_view p);

    template <class T>
    std::string join(const std::vector<T> &v, std::string_view p, std::string (*t)(T item))
    {
      std::string r;
      int last = v.size() - 1;
      for (size_t i = 0; i < v.size(); i++)
      {
        r += t(v.at(i)) + (i == last ? "" : p.data());
      }
      return r;
    };
  }
  
  namespace Mem
  {
    LPVOID alloc(SIZE_T dwSize, LPVOID lpAddress = 0, uint32_t flAllocationType = MEM_COMMIT | MEM_RESERVE, uint32_t flProtect = PAGE_EXECUTE_READWRITE);

    LPVOID allocEx(HANDLE hProcess, SIZE_T dwSize, LPVOID lpAddress = 0, uint32_t flAllocationType = MEM_COMMIT | MEM_RESERVE, uint32_t flProtect = PAGE_EXECUTE_READWRITE);

    BOOL free(LPVOID lpAddress);
    BOOL free(std::string_view CEAddressString);

    BOOL freeEx(HANDLE hProcess, LPVOID lpAddress);
    BOOL freeEx(HANDLE hProcess, std::string_view CEAddressString);

    // write
    void wStr(void *lpAddress, std::string_view str);
    void wWstr(void *lpAddress, std::wstring_view str);
    void wUstr(void *lpAddress, std::u16string_view str);

    void wStr(std::string_view CEAddressString, std::string_view str);
    void wWstr(std::string_view CEAddressString, std::wstring_view str);
    void wUstr(std::string_view CEAddressString, std::u16string_view str);

    void wByte(void *lpAddress, uint8_t byte);
    void wBytes(void *lpAddress, const std::vector<uint8_t> &bytes);
    void wWord(void *lpAddress, WORD value);
    void wDword(void *lpAddress, uint32_t value);
    void wQword(void *lpAddress, uint64_t value);
    void wFloat(void *lpAddress, float value);
    void wDouble(void *lpAddress, double value);
    void wRegionToFile(std::string_view filename, void *lpAddress, uintptr_t size);

    void wByte(std::string_view CEAddressString, uint8_t byte);
    void wBytes(std::string_view CEAddressString, const std::vector<uint8_t> &bytes);
    void wWord(std::string_view CEAddressString, uint16_t value);
    void wDword(std::string_view CEAddressString, uint32_t value);
    void wQword(std::string_view CEAddressString, uint64_t value);
    void wFloat(std::string_view CEAddressString, float value);
    void wDouble(std::string_view CEAddressString, double value);
    void wRegionToFile(std::string_view filename, std::string_view CEAddressString, uintptr_t size);

    // write ex
    void wStrEx(HANDLE hProcess, void *lpAddress, std::string_view str);
    void wWstrEx(HANDLE hProcess, void *lpAddress, std::wstring_view str);
    void wUstrEx(HANDLE hProcess, void *lpAddress, std::u16string_view str);

    void wStrEx(HANDLE hProcess, std::string_view CEAddressString, std::string_view str);
    void wWstrEx(HANDLE hProcess, std::string_view CEAddressString, std::wstring_view str);
    void wUstrEx(HANDLE hProcess, std::string_view CEAddressString, std::u16string_view str);

    void wByteEx(HANDLE hProcess, void *lpAddress, uint8_t byte);
    void wBytesEx(HANDLE hProcess, void *lpAddress, const std::vector<uint8_t> &bytes);
    void wWordEx(HANDLE hProcess, void *lpAddress, uint16_t value);
    void wDwordEx(HANDLE hProcess, void *lpAddress, uint32_t value);
    void wQwordEx(HANDLE hProcess, void *lpAddress, uint64_t value);
    void wFloatEx(HANDLE hProcess, void *lpAddress, float value);
    void wDoubleEx(HANDLE hProcess, void *lpAddress, double value);
    void wRegionToFileEx(HANDLE hProcess, std::string_view filename, void *lpAddress, uintptr_t size);

    void wByteEx(HANDLE hProcess, std::string_view CEAddressString, uint8_t byte);
    void wBytesEx(HANDLE hProcess, std::string_view CEAddressString, std::vector<uint8_t> bytes);
    void wWordEx(HANDLE hProcess, std::string_view CEAddressString, uint16_t value);
    void wDwordEx(HANDLE hProcess, std::string_view CEAddressString, uint32_t value);
    void wQwordEx(HANDLE hProcess, std::string_view CEAddressString, uint64_t value);
    void wFloatEx(HANDLE hProcess, std::string_view CEAddressString, float value);
    void wDoubleEx(HANDLE hProcess, std::string_view CEAddressString, double value);
    void wRegionToFileEx(HANDLE hProcess, std::string_view filename, std::string_view CEAddressString, uintptr_t size);

    // read
    std::string rStr(char *lpAddress, uintptr_t max);
    std::wstring rWstr(wchar_t *lpAddress, uintptr_t max);
    std::u16string rUstr(char16_t *lpAddress, uintptr_t max);

    std::string rStr(std::string_view CEAddressString, uintptr_t max);
    std::wstring rWstr(std::string_view CEAddressString, uintptr_t max);
    std::u16string rUstr(std::string_view CEAddressString, uintptr_t max);

    std::vector<uint8_t> rBytes(void *lpAddress, uintptr_t size);
    uint8_t rByte(void *lpAddress);
    uint16_t rWord(void *lpAddress);
    uint32_t rDword(void *lpAddress);
    uint64_t rQword(void *lpAddress);
    uintptr_t rPointer(void *lpAddress);
    float rFloat(void *lpAddress);
    double rDouble(void *lpAddress);
    void rRegionFromFile(std::string_view fileame, void *lpAddress);
    void rRegionFromFile(std::string_view fileame, void *lpAddress, size_t *fileSize);

    std::vector<uint8_t> rBytes(std::string_view CEAddressString, uintptr_t size);
    uint8_t rByte(std::string_view CEAddressString);
    uint16_t rWord(std::string_view CEAddressString);
    uint32_t rDword(std::string_view CEAddressString);
    uint64_t rQword(std::string_view CEAddressString);
    uintptr_t rPointer(std::string_view CEAddressString);
    float rFloat(std::string_view CEAddressString);
    double rDouble(std::string_view CEAddressString);
    void rRegionFromFile(std::string_view fileame, std::string_view CEAddressString);
    void rRegionFromFile(std::string_view fileame, std::string_view CEAddressString, size_t *fileSize);

    // read ex
    std::string rStrEx(HANDLE hProcess, char *lpAddress, uintptr_t max);
    std::wstring rWstrEx(HANDLE hProcess, wchar_t *lpAddress, uintptr_t max);
    std::u16string rUstrEx(HANDLE hProcess, char16_t *lpAddress, uintptr_t max);

    std::string rStrEx(HANDLE hProcess, std::string_view CEAddressString, uintptr_t max);
    std::wstring rWstrEx(HANDLE hProcess, std::string_view CEAddressString, uintptr_t max);
    std::u16string rUstrEx(HANDLE hProcess, std::string_view CEAddressString, uintptr_t max);

    std::vector<uint8_t> rBytesEx(HANDLE hProcess, void *lpAddress, uintptr_t size);
    uint8_t rByteEx(HANDLE hProcess, void *lpAddress);
    uint16_t rWordEx(HANDLE hProcess, void *lpAddress);
    uint32_t rDwordEx(HANDLE hProcess, void *lpAddress);
    uint64_t rQwordEx(HANDLE hProcess, void *lpAddress);
    uintptr_t rPointerEx(HANDLE hProcess, void *lpAddress);
    float rFloatEx(HANDLE hProcess, void *lpAddress);
    double rDoubleEx(HANDLE hProcess, void *lpAddress);
    void rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, void *lpAddress);
    void rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, void *lpAddress, size_t *fileSize);

    std::vector<uint8_t> rBytesEx(HANDLE hProcess, std::string_view CEAddressString, uintptr_t size);
    uint8_t rByteEx(HANDLE hProcess, std::string_view CEAddressString);
    uint16_t rWordEx(HANDLE hProcess, std::string_view CEAddressString);
    uint32_t rDwordEx(HANDLE hProcess, std::string_view CEAddressString);
    uint64_t rQwordEx(HANDLE hProcess, std::string_view CEAddressString);
    uintptr_t rPointerEx(HANDLE hProcess, std::string_view CEAddressString);
    float rFloatEx(HANDLE hProcess, std::string_view CEAddressString);
    double rDoubleEx(HANDLE hProcess, std::string_view CEAddressString);
    void rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, std::string_view CEAddressString);
    void rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, std::string_view CEAddressString, size_t *fileSize);

    class VAManage
    {
    public:
      HANDLE hProcess;
      const uintptr_t size;
      LPVOID memory;
      size_t position;
      VAManage(size_t size);
      VAManage(size_t size, HANDLE hProcess);
      ~VAManage(){};

      // memory +  position
      uint8_t *ptr();

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
      void write(std::vector<uint8_t> &table, size_t count);
      void writeByte(uint8_t v);
      void writeWord(uint16_t v);
      void writeDword(uint32_t v);
      void writeQword(uintptr_t v);
      void writeFloat(float v);
      void writeDouble(double v);
      void writeStr(std::string_view str);
      void writeWstr(std::wstring_view wstr);
      void writeUstr(std::u16string_view ustr);

      void loadFromFile(std::string_view filename);
      void saveToFile(std::string_view filename);
      BOOL destroy();
    };
  }

  namespace Gui
  {
    struct Win32CreateOption
    {
      std::string className;
      std::string windowName;
      uint32_t style;
      int x;
      int y;
      int width;
      int height;
      HMENU id;
      HWND parent;
      Win32CreateOption(std::string className,
                        std::string windowName,
                        uint32_t style,
                        int x,
                        int y,
                        int width,
                        int height,
                        HMENU id,
                        HWND parent) : className(className),
                                       windowName(windowName),
                                       style(style),
                                       x(x),
                                       y(y),
                                       width(width),
                                       height(height),
                                       id(id),
                                       parent(parent)
      {
      }
    };

    class Win32
    {
    public:
      // 0: HIWORD, 1: LOWORD
      static std::vector<uint16_t> getHLMessage(uint32_t message);
      static bool getCheck(HWND hWnd);
      static uint32_t rgb(uint32_t r, uint32_t g, uint32_t b);

      // 主窗口句柄
      HWND _hWnd;

      std::string windowName;
      std::string className;
      size_t x;
      size_t y;
      size_t width;
      size_t height;
      uint32_t style;

      Win32(std::string className, std::string windowName) : x(CW_USEDEFAULT),
                                                             y(CW_USEDEFAULT),
                                                             width(CW_USEDEFAULT), height(CW_USEDEFAULT),
                                                             style(WS_OVERLAPPEDWINDOW),
                                                             className(className),
                                                             windowName(windowName),
                                                             _hWnd(NULL){};
      ~Win32() { DeleteObject(_hWnd); };

      // 消息循环
      int messageLoop();

      // 注册窗口类
      // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexw
      ATOM initRegisterClass();

      // 窗口初始化
      BOOL initWindow();

      /// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowa
      HWND createWindow(std::unique_ptr<Win32CreateOption> opt);
      HWND button(std::unique_ptr<Win32CreateOption> opt);
      HWND checkbox(std::unique_ptr<Win32CreateOption> opt);
      HWND radio(std::unique_ptr<Win32CreateOption> opt);
      HWND groupbox(std::unique_ptr<Win32CreateOption> opt);
      HWND text(std::unique_ptr<Win32CreateOption> opt);
      HWND input(std::unique_ptr<Win32CreateOption> opt);
      HWND textarea(std::unique_ptr<Win32CreateOption> opt);
      HWND listbox(std::unique_ptr<Win32CreateOption> opt);
      HWND select(std::unique_ptr<Win32CreateOption> opt);

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
      std::string_view script;
      AAScript(std::string_view script) : script(script){};
      ~AAScript(){};

      // auto asm
      static uintptr_t aa(std::string_view asmString, uintptr_t rcx);
      static std::vector<uint8_t> asmBytes(std::string_view asmString, bool isX64);
    };
  }

  class Symbol
  {
  public:
    static void registerSymbol(std::string symbolname, LPVOID address);
    static void unregisterSymbol(std::string_view symbolname);
    static LPVOID get(std::string_view symbolname);
    static bool has(std::string_view symbolname);

  private:
    static std::map<std::string, LPVOID> _symbolMap;
  };

  class PE
  {
  public:
    static uint32_t GetPID(std::string_view name);
    static uint32_t GetPID(std::wstring_view name);
    // exe module
    static MODULEINFO GetModuleBase(uint32_t pid);
    static MODULEINFO GetModuleInfo(std::wstring_view moduleName, uint32_t pid);
    static bool isX64(uint32_t pid, HMODULE hModule);
    static bool isX86(uint32_t pid, HMODULE hModule);
    // 获取模块的导出表,通常一个模块会导出函数
    static std::map<std::string, uintptr_t> exports(uint32_t pid, HMODULE hModule);
    static uint8_t *GetProcAddress(uint32_t pid, HMODULE hModule, std::string_view method);

    // user32.dll => user32
    // user32.xxx.dll => user32.xxx
    static std::wstring GetModuleName(std::wstring_view moduleName);
    static std::string GetModuleName(std::string_view moduleName);
  };

  class CEAddressString
  {
  public:
    static LPVOID getAddress(std::string_view address, HANDLE hProcess = NULL);

  private:
    class Interpreter
    {
    public:
      HANDLE hProcess;
      uint32_t pid = NULL;
      bool isX86;
      Interpreter(HANDLE hProcess) : hProcess(hProcess)
      {
        if (hProcess != NULL)
        {
          pid = GetProcessId(hProcess);
          isX86 = PE::isX86(pid, (HMODULE)(PE::GetModuleBase(pid).lpBaseOfDll));
        }
        else
        {
          hProcess = GetCurrentProcess();
          pid = GetCurrentProcessId();
          isX86 = PE::isX86(pid, (HMODULE)(PE::GetModuleBase(pid).lpBaseOfDll));
        }
      }

      uintptr_t visit(ces::BaseNode *node)
      {
        switch (node->id())
        {
        case ces::NT::HEX:
          return visitHex(reinterpret_cast<ces::HexNode *>(node));
        case ces::NT::IDENTS:
          return visitIdent(reinterpret_cast<ces::IdentsNode *>(node));
        case ces::NT::UNARY:
          return visitUnary(reinterpret_cast<ces::UnaryNode *>(node));
        case ces::NT::POINTER:
          return visitPointer(reinterpret_cast<ces::PointerNode *>(node));
        case ces::NT::BINARY:
          return visitBinary(reinterpret_cast<ces::BinaryNode *>(node));
        default:
          throw std::exception("Unexpected CEAddressString Node");
        }
      }

      uintptr_t visitHex(ces::HexNode *node)
      {
        return std::stoull(node->value, nullptr, 16);
      }

      uintptr_t visitIdent(ces::IdentsNode *node)
      {
        // 优先级 SYMBOL -> HEX -> MODULE
        auto idents = *node->idents;
        if (idents.size() == 1)
        {
          // symbol -> hex -> method
          auto val = idents.at(0);
          if (ajanuw::Symbol::has(val))
          {
            return (uintptr_t)ajanuw::Symbol::get(val);
          }
          else if (std::all_of(val.begin(), val.end(), ::isxdigit))
          {
            return std::stoull(val, nullptr, 16);
          }
          else
          {
            // 遍历所有模块中的方法，直到找到为止
            uintptr_t r = NULL;
            auto hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
            if (hSnap != INVALID_HANDLE_VALUE)
            {
              MODULEENTRY32 me;
              me.dwSize = sizeof(me);
              if (Module32First(hSnap, &me))
              {
                do
                {
                  r = (uintptr_t)PE::GetProcAddress(pid, (HMODULE)me.modBaseAddr, val);
                  if (r != NULL)
                    break;
                } while (Module32Next(hSnap, &me));
              }
            }
            CloseHandle(hSnap);

            if (r == NULL)
            {
              throw std::exception(("Not defined symbol \"" + val + "\"").c_str());
            }

            return r;
          }
        }
        else
        {
          auto last = idents.back();
          idents.pop_back();
          auto first = ajanuw::SSString::join(idents, ".");

          // printf("first:%s\nlast:%s\n", first.c_str(), last.c_str());

          // user32.messageboxa
          // user32.dll
          // node.exe
          if (last == "dll" || last == "exe")
          {
            auto hModule = (HMODULE)(PE::GetModuleInfo(ajanuw::SSString::strToWstr(first), pid).lpBaseOfDll);
            if (hModule == NULL)
            {
              throw std::exception(("MODULE not module \"" + first + "\"").c_str());
            }
            return (uintptr_t)hModule;
          }

          auto hModule = (HMODULE)(PE::GetModuleInfo(ajanuw::SSString::strToWstr(first), pid).lpBaseOfDll);
          if (hModule == NULL)
          {
            throw std::exception(("not find module \"" + first + "\"").c_str());
          }

          auto hMethod = (uintptr_t)PE::GetProcAddress(pid, hModule, last);
          if (hMethod == NULL)
          {
            throw std::exception(("not find method \"" + last + "\"").c_str());
          }
          return (uintptr_t)hMethod;
        }
      }

      uintptr_t visitUnary(ces::UnaryNode *node)
      {
        auto value = visit(node->node);
        if (node->op == ces::parser::token::MINUS)
        {
          return value * -1;
        }
        return value;
      }

      uintptr_t visitPointer(ces::PointerNode *node)
      {
        auto address = visit(node->node);
        uintptr_t result = NULL;
        if (ReadProcessMemory(hProcess == NULL ? GetCurrentProcess() : hProcess, (LPCVOID)address, (LPVOID)&result, isX86 ? 4 : 8, NULL))
        {
          return result;
        }
        else
        {
          throw std::exception("Read Pointer Error.");
        }
      }

      uintptr_t visitBinary(ces::BinaryNode *node)
      {
        auto left = visit(node->left);
        auto right = visit(node->right);
        switch (node->op)
        {
        case ces::parser::token::PLUS:
          return left + right;
        case ces::parser::token::MINUS:
          return left - right;
        case ces::parser::token::MUL:
          return left * right;
        case ces::parser::token::DIV:
        {
          if (right == 0)
          {
            throw std::exception("Division by zero");
          }
          return left / right;
        }
        case ces::parser::token::POW:
          return pow(left, right);

        default:
          throw std::exception("Unexpected Binary Node");
        }
      }
    };
  };

  class Target
  {
#define JMP_BYTE 0xE9
#define CALL_BYTE 0xE9
#define NOP_BYTE 0x90

  public:
    class HookBase
    {
    public:
      HANDLE hProcess = NULL;

      // 拷贝的原始字节
      std::vector<uint8_t> origenBytes = {};

      // hook的地址
      uint8_t *addr = NULL;

      // 字节大小
      size_t size = NULL;

      // 是否开启
      bool bEnable = false;

      // hook过程 是否成功
      bool bSuccess = false;

      HookBase(HANDLE hProcess, uint8_t *addr, size_t size)
          : hProcess(hProcess), addr(addr), size(size)
      {
        origenBytes.resize(size);
        bSuccess = ReadProcessMemory(hProcess, addr, origenBytes.data(), size, NULL);
      }

      void enable()
      {
        if (!bSuccess)
          return;

        // printf("enable: hProcess(%p), addr(%p), size(%d)\n", hProcess, addr, size);

        uint32_t oldProc;
        VirtualProtectEx(hProcess, addr, size, PAGE_EXECUTE_READWRITE, reinterpret_cast<PDWORD>(&oldProc));
        ajanuw::Target::memsetEx(hProcess, addr, NOP_BYTE, size);
        enableHook();
        VirtualProtectEx(hProcess, addr, size, oldProc, reinterpret_cast<PDWORD>(&oldProc));
      }

      void disable()
      {
        if (!bSuccess)
          return;
        uint32_t oldProc;
        VirtualProtectEx(hProcess, addr, size, PAGE_EXECUTE_READWRITE, reinterpret_cast<PDWORD>(&oldProc));
        WriteProcessMemory(hProcess, addr, origenBytes.data(), size, 0);
        VirtualProtectEx(hProcess, addr, size, oldProc, reinterpret_cast<PDWORD>(&oldProc));
      }

      void toggle()
      {
        bEnable = !bEnable;
        if (bEnable)
          enable();
        else
          disable();
      }
      virtual void enableHook() = 0;
    };
    class SetNop : public HookBase
    {
    public:
      SetNop(HANDLE hProcess, uint8_t *addr, size_t size) : HookBase(hProcess, addr, size)
      {
      }
      void enableHook(){};
    };

    class SetHook : public HookBase
    {
    public:
      uint8_t *newmem = NULL;
      uint32_t jmpHookBytes = NULL;

      SetHook(HANDLE hProcess, uint8_t *addr, size_t size, const std::vector<uint8_t> &hookBytes)
          : HookBase(hProcess, addr, size)
      {
        bSuccess = false;
        if (size < 5)
        {
          throw std::exception("SetHook Error: At least 5 bytes are required to set the Hook");
        }

        // hook code
        auto returnAddr = addr + size;
        auto newmemSize = hookBytes.size() + 100;

        newmem = (uint8_t *)ajanuw::Mem::allocEx(hProcess, newmemSize);
        if (!newmem)
        {
          throw std::exception("SetHook Error: allocEx Error.");
        }
        WriteProcessMemory(hProcess, newmem, hookBytes.data(), newmemSize, NULL);

        // set return bytes
        auto newmemJmpReturnAddr = newmem + hookBytes.size();
        auto retByteCode = (uint32_t)(returnAddr - newmemJmpReturnAddr - 5);
        uint8_t b = JMP_BYTE;
        WriteProcessMemory(hProcess, newmemJmpReturnAddr, (LPCVOID)&b, sizeof(uint8_t), NULL);
        WriteProcessMemory(hProcess, newmemJmpReturnAddr + 1, (LPCVOID)&retByteCode, sizeof(uint32_t), NULL);

        jmpHookBytes = newmem - addr - 5;
        bSuccess = true;
      }

      void enableHook()
      {
        uint8_t b = JMP_BYTE;
        WriteProcessMemory(hProcess, (LPVOID)addr, (LPCVOID)&b, sizeof(uint8_t), 0);
        WriteProcessMemory(hProcess, (LPVOID)(addr + 1), (LPCVOID)&jmpHookBytes, sizeof(uint32_t), 0);
      }
    };

    static uint8_t *memsetEx(HANDLE hProcess, uint8_t *targetAddr, uint8_t val, size_t size)
    {
      for (size_t i = 0; i < size; i++)
        WriteProcessMemory(hProcess, targetAddr + i, &val, sizeof(uint8_t), NULL);
      return targetAddr;
    }

    std::wstring name;
    uint32_t pid = NULL;
    HANDLE hProcess = NULL;
    MODULEINFO mi;

    bool isX86;
    bool isX64;

    Target(const std::wstring &name) : name(name)
    {
      pid = ajanuw::PE::GetPID(name);
      if (pid)
      {
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
        if (hProcess)
        {
          mi = ajanuw::PE::GetModuleInfo(name, pid);
          isX86 = ajanuw::PE::isX86(pid, (HMODULE)mi.lpBaseOfDll);
          isX64 = !isX86;
        }
      }
    }

    Target(uint32_t pid) : pid(pid)
    {
      hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
      if (hProcess)
      {
        wchar_t text[MAX_PATH];
        GetModuleBaseNameW(hProcess, 0, text, MAX_PATH);
        name = std::wstring(text);
        mi = ajanuw::PE::GetModuleInfo(name, pid);
        isX86 = ajanuw::PE::isX86(pid, (HMODULE)mi.lpBaseOfDll);
        isX64 = !isX86;
      }
      else
      {
        printf("OpenProcess error: %d\n", GetLastError());
      }
    }

    ~Target()
    {
      if (hProcess)
        CloseHandle(hProcess);
    }

    std::vector<uint8_t *> moduleScan(const std::string &strbytes, size_t offset = NULL)
    {
      auto maskList = ajanuw::SSString::split(strbytes, std::regex("\\s+"));
      auto base = (uint8_t *)mi.lpBaseOfDll;
      std::vector<uint8_t *> addrs;
      uint8_t v = NULL;
      size_t eachSize = mi.SizeOfImage - maskList.size();
      for (size_t i = 0; i < eachSize; i++)
      {
        bool found = true;
        for (size_t j = 0; j < maskList.size(); j++)
        {
          ReadProcessMemory(hProcess, (LPCVOID)(base + i + j), (LPVOID)&v, sizeof(uint8_t), 0);
          bool notEqual = maskList[j] != "?" && maskList[j] != "??" && maskList[j] != "*" && maskList[j] != "**" && (uint8_t)std::stol(maskList[j], nullptr, 16) != v;
          if (notEqual)
          {
            found = false;
            break;
          }
        }
        if (found)
          addrs.push_back(base + i + offset);
      }
      return addrs;
    }
  };
}
