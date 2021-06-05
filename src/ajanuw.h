#pragma once
#pragma warning(disable : 4819)

#include <iostream>
#include <algorithm>
#include <regex>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <memory>
#include <ranges>
#include <format>
#include <span>

#include <Windows.h>
#include <Windowsx.h>
#include <TlHelp32.h>
#include <psapi.h>

#include <asmjit/asmjit.h>
#include <asmtk/asmtk.h>

#include "./ces/export.h"

namespace ajanuw
{
  LPVOID createCallback(void *lpCallback, size_t index, void *vCC);

  namespace sstr
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
    std::string formHex(size_t _hex);

    /*
    * ajanuw::SSString::tolower("ABC") -> "abc"
    * ajanuw::SSString::toupper("abc") -> "ABC"
    */
    std::string tolower(std::string_view s);
    std::string toupper(std::string_view s);

    std::wstring tolower(std::wstring_view s);
    std::wstring toupper(std::wstring_view s);

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
    LPVOID alloc(SIZE_T dwSize, LPVOID addr = 0, uint32_t flAllocationType = MEM_COMMIT | MEM_RESERVE, uint32_t flProtect = PAGE_EXECUTE_READWRITE);
    LPVOID allocEx(HANDLE hProcess, SIZE_T dwSize, LPVOID addr = 0, uint32_t flAllocationType = MEM_COMMIT | MEM_RESERVE, uint32_t flProtect = PAGE_EXECUTE_READWRITE);
    BOOL free(LPVOID addr);
    BOOL free(std::string_view ceas);
    BOOL freeEx(HANDLE hProcess, LPVOID addr);
    BOOL freeEx(HANDLE hProcess, std::string_view ceas);

    // write
    void wStr(void *addr, std::string_view str);
    void wWstr(void *addr, std::wstring_view str);
    void wUstr(void *addr, std::u16string_view str);

    void wStr(std::string_view ceas, std::string_view str);
    void wWstr(std::string_view ceas, std::wstring_view str);
    void wUstr(std::string_view ceas, std::u16string_view str);

    void wByte(void *addr, uint8_t byte);
    void wBytes(void *addr, const std::span<uint8_t> &bytes, intptr_t max = -1);
    void wWord(void *addr, WORD value);
    void wDword(void *addr, uint32_t value);
    void wQword(void *addr, uint64_t value);
    void wFloat(void *addr, float value);
    void wDouble(void *addr, double value);
    void wRegionToFile(std::string_view filename, void *addr, size_t size);

    void wByte(std::string_view ceas, uint8_t byte);
    void wBytes(std::string_view ceas, const std::span<uint8_t> &bytes, intptr_t max = -1);
    void wWord(std::string_view ceas, uint16_t value);
    void wDword(std::string_view ceas, uint32_t value);
    void wQword(std::string_view ceas, uint64_t value);
    void wFloat(std::string_view ceas, float value);
    void wDouble(std::string_view ceas, double value);
    void wRegionToFile(std::string_view filename, std::string_view ceas, size_t size);

    // write ex
    void wStrEx(HANDLE hProcess, void *addr, std::string_view str);
    void wWstrEx(HANDLE hProcess, void *addr, std::wstring_view str);
    void wUstrEx(HANDLE hProcess, void *addr, std::u16string_view str);

    void wStrEx(HANDLE hProcess, std::string_view ceas, std::string_view str);
    void wWstrEx(HANDLE hProcess, std::string_view ceas, std::wstring_view str);
    void wUstrEx(HANDLE hProcess, std::string_view ceas, std::u16string_view str);

    void wByteEx(HANDLE hProcess, void *addr, uint8_t byte);
    void wBytesEx(HANDLE hProcess, void *addr, const std::span<uint8_t> &bytes, intptr_t max = -1);
    void wWordEx(HANDLE hProcess, void *addr, uint16_t value);
    void wDwordEx(HANDLE hProcess, void *addr, uint32_t value);
    void wQwordEx(HANDLE hProcess, void *addr, uint64_t value);
    void wFloatEx(HANDLE hProcess, void *addr, float value);
    void wDoubleEx(HANDLE hProcess, void *addr, double value);
    void wRegionToFileEx(HANDLE hProcess, std::string_view filename, void *addr, size_t size);

    void wByteEx(HANDLE hProcess, std::string_view ceas, uint8_t byte);
    void wBytesEx(HANDLE hProcess, std::string_view ceas, std::span<uint8_t> bytes, intptr_t max = -1);
    void wWordEx(HANDLE hProcess, std::string_view ceas, uint16_t value);
    void wDwordEx(HANDLE hProcess, std::string_view ceas, uint32_t value);
    void wQwordEx(HANDLE hProcess, std::string_view ceas, uint64_t value);
    void wFloatEx(HANDLE hProcess, std::string_view ceas, float value);
    void wDoubleEx(HANDLE hProcess, std::string_view ceas, double value);
    void wRegionToFileEx(HANDLE hProcess, std::string_view filename, std::string_view ceas, size_t size);

    // read
    std::string rStr(char *addr, size_t max);
    std::wstring rWstr(wchar_t *addr, size_t max);
    std::u16string rUstr(char16_t *addr, size_t max);

    std::string rStr(std::string_view ceas, size_t max);
    std::wstring rWstr(std::string_view ceas, size_t max);
    std::u16string rUstr(std::string_view ceas, size_t max);

    std::vector<uint8_t> rBytes(void *addr, size_t size);
    uint8_t rByte(void *addr);
    uint16_t rWord(void *addr);
    uint32_t rDword(void *addr);
    uint64_t rQword(void *addr);
    uintptr_t rPointer(void *addr);
    float rFloat(void *addr);
    double rDouble(void *addr);
    void rRegionFromFile(std::string_view fileame, void *addr);
    void rRegionFromFile(std::string_view fileame, void *addr, size_t *fileSize);

    std::vector<uint8_t> rBytes(std::string_view ceas, size_t size);
    uint8_t rByte(std::string_view ceas);
    uint16_t rWord(std::string_view ceas);
    uint32_t rDword(std::string_view ceas);
    uint64_t rQword(std::string_view ceas);
    uintptr_t rPointer(std::string_view ceas);
    float rFloat(std::string_view ceas);
    double rDouble(std::string_view ceas);
    void rRegionFromFile(std::string_view fileame, std::string_view ceas);
    void rRegionFromFile(std::string_view fileame, std::string_view ceas, size_t *fileSize);

    // read ex
    std::string rStrEx(HANDLE hProcess, char *addr, size_t max);
    std::wstring rWstrEx(HANDLE hProcess, wchar_t *addr, size_t max);
    std::u16string rUstrEx(HANDLE hProcess, char16_t *addr, size_t max);

    std::string rStrEx(HANDLE hProcess, std::string_view ceas, size_t max);
    std::wstring rWstrEx(HANDLE hProcess, std::string_view ceas, size_t max);
    std::u16string rUstrEx(HANDLE hProcess, std::string_view ceas, size_t max);

    std::vector<uint8_t> rBytesEx(HANDLE hProcess, void *addr, size_t size);
    uint8_t rByteEx(HANDLE hProcess, void *addr);
    uint16_t rWordEx(HANDLE hProcess, void *addr);
    uint32_t rDwordEx(HANDLE hProcess, void *addr);
    uint64_t rQwordEx(HANDLE hProcess, void *addr);
    uintptr_t rPointerEx(HANDLE hProcess, void *addr);
    float rFloatEx(HANDLE hProcess, void *addr);
    double rDoubleEx(HANDLE hProcess, void *addr);
    void rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, void *addr);
    void rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, void *addr, size_t *fileSize);

    std::vector<uint8_t> rBytesEx(HANDLE hProcess, std::string_view ceas, size_t size);
    uint8_t rByteEx(HANDLE hProcess, std::string_view ceas);
    uint16_t rWordEx(HANDLE hProcess, std::string_view ceas);
    uint32_t rDwordEx(HANDLE hProcess, std::string_view ceas);
    uint64_t rQwordEx(HANDLE hProcess, std::string_view ceas);
    uintptr_t rPointerEx(HANDLE hProcess, std::string_view ceas);
    float rFloatEx(HANDLE hProcess, std::string_view ceas);
    double rDoubleEx(HANDLE hProcess, std::string_view ceas);
    void rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, std::string_view ceas);
    void rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, std::string_view ceas, size_t *fileSize);

    class VAManage
    {
    public:
      HANDLE hProcess{NULL};
      size_t size{1024};
      LPVOID memory{nullptr};
      size_t position{0};
      VAManage(size_t size);
      VAManage(size_t size, HANDLE hProcess);
      ~VAManage(){};

      // memory +  position
      uint8_t *ptr() const {
        return (uint8_t *)memory + position;
      }

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
      void write(const std::span<uint8_t> &table, intptr_t max = -1);
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
    };

    class Win32
    {
    public:
      // 0: HIWORD, 1: LOWORD
      static std::vector<uint16_t> getHLMessage(uint32_t message);
      static bool getCheck(HWND hWnd);
      static uint32_t rgb(uint32_t r, uint32_t g, uint32_t b);

      // 主窗口句柄
      HWND _hWnd{NULL};
      std::string windowName;
      std::string className;
      int x{CW_USEDEFAULT};
      int y{CW_USEDEFAULT};
      int width{CW_USEDEFAULT};
      int height{CW_USEDEFAULT};
      uint32_t style{WS_OVERLAPPEDWINDOW};

      Win32(std::string className, std::string windowName) : className(className),
                                                             windowName(windowName){};
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
    static std::map<std::string, LPVOID> symbols;
  };

  class PE
  {
  public:
    static uint32_t GetPID(std::string_view name);
    static uint32_t GetPID(std::wstring_view name);
    // exe module
    static MODULEINFO GetModuleBase(uint32_t pid);
    static MODULEINFO GetModuleInfo(std::wstring_view moduleName, uint32_t pid);
    static MODULEINFO GetModuleInfo(std::string_view moduleName, uint32_t pid);

    static bool isX64(uint32_t pid, HMODULE hModule);
    static bool isX86(uint32_t pid, HMODULE hModule);
    // 获取模块的导出表,通常一个模块会导出大量函数
    static std::map<std::string, uintptr_t> exports(uint32_t pid, HMODULE hModule);

    // 获取模块中的函数地址
    static uint8_t *GetProcAddress(uint32_t pid, HMODULE hModule, std::string_view method);
    static uint8_t *GetProcAddress(uint32_t pid, HMODULE hModule, std::wstring_view method);

    // user32.dll => user32
    // user32.xxx.dll => user32.xxx
    static std::wstring GetModuleName(std::wstring_view moduleName);
    static std::string GetModuleName(std::string_view moduleName);
  };

  class CEAS
  {
  public:
    static LPVOID getAddress(std::string_view address, HANDLE hProcess = NULL);

  private:
    class Interpreter
    {
    public:
      std::string_view source;
      HANDLE hProcess;
      uint32_t pid{NULL};
      bool isX86;
      Interpreter(HANDLE hProcess, std::string_view source);
      uintptr_t visit(ces::BaseNode *node);

    private:
      uintptr_t visitHex(ces::HexNode *node);
      uintptr_t visitIdent(ces::IdentsNode *node);
      uintptr_t visitUnary(ces::UnaryNode *node);
      uintptr_t visitPointer(ces::PointerNode *node);
      uintptr_t visitBinary(ces::BinaryNode *node);
    };
  };

  class Target
  {
#define JMP_BYTE 0xE9
#define CALL_BYTE 0xE8
#define NOP_BYTE 0x90

  public:
    class HookBase
    {
    public:
      HANDLE hProcess{NULL};

      // 拷贝的原始字节
      std::vector<uint8_t> oldBytes{};

      // hook的地址
      uint8_t *addr{NULL};

      // 字节大小
      size_t size{NULL};

      // 是否开启
      bool bEnable{false};

      // hook过程 是否成功
      bool bSuccess{false};

      HookBase(HANDLE hProcess, uint8_t *addr, size_t size)
          : hProcess(hProcess), addr(addr), size(size)
      {
        oldBytes.resize(size);
        bSuccess = ReadProcessMemory(hProcess, addr, oldBytes.data(), size, NULL);
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
        WriteProcessMemory(hProcess, addr, oldBytes.data(), size, 0);
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
      else
      {
        throw std::exception(std::format("GetPID error: {}", GetLastError()).data());
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
        throw std::exception(std::format("OpenProcess error: {}", GetLastError()).data());
      }
    }

    ~Target()
    {
      if (hProcess)
        CloseHandle(hProcess);
    }

    std::vector<uint8_t *> moduleScan(const std::string &strbytes, size_t offset = NULL)
    {
      auto maskList = ajanuw::sstr::split(strbytes, std::regex("\\s+"));
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
