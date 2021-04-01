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
  LPVOID createCallback(void *lpCallback, size_t index, void *vCC);

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

    void strToMemEx(HANDLE hProcess, void *dst, std::string str);
    void strToMemEx(HANDLE hProcess, void *dst, std::wstring str);
    void strToMemEx(HANDLE hProcess, void *dst, std::u16string str);

    // TODO: 按字节读取，读中文会出问题
    std::string strFormMem(void *src, size_t max);
    std::wstring wstrFormMem(void *src, size_t max);
    std::u16string ustrFormMem(void *src, size_t max);

    std::string strFormMemEx(HANDLE hProcess, void *src, size_t max);
    std::wstring wstrFormMemEx(HANDLE hProcess, void *src, size_t max);
    std::u16string ustrFormMemEx(HANDLE hProcess, void *src, size_t max);

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

    std::string tolower(std::string s);
    std::string toupper(std::string s);

    std::string pad(std::string str, size_t size, std::string padStr, bool isStart);
    std::string padStart(std::string str, size_t size, std::string padStr);
    std::string padEnd(std::string str, size_t size, std::string padStr);

    std::string repeat(std::string str, size_t len);
  }
  namespace Mem
  {
    LPVOID alloc(SIZE_T dwSize, LPVOID lpAddress = 0, DWORD flAllocationType = MEM_COMMIT | MEM_RESERVE, DWORD flProtect = PAGE_EXECUTE_READWRITE);

    LPVOID allocEx(HANDLE hProcess, SIZE_T dwSize, LPVOID lpAddress = 0, DWORD flAllocationType = MEM_COMMIT | MEM_RESERVE, DWORD flProtect = PAGE_EXECUTE_READWRITE);

    BOOL free(LPVOID lpAddress);
    BOOL free(std::string CEAddressString);

    BOOL freeEx(HANDLE hProcess, LPVOID lpAddress);
    BOOL freeEx(HANDLE hProcess, std::string CEAddressString);

    // write
    void wStr(void *lpAddress, std::string str);
    void wWstr(void *lpAddress, std::wstring str);
    void wUstr(void *lpAddress, std::u16string str);

    void wStr(std::string CEAddressString, std::string str);
    void wWstr(std::string CEAddressString, std::wstring str);
    void wUstr(std::string CEAddressString, std::u16string str);

    void wByte(void *lpAddress, BYTE byte);
    void wBytes(void *lpAddress, std::vector<BYTE> bytes);
    void wWord(void *lpAddress, WORD value);
    void wDword(void *lpAddress, DWORD value);
    void wQword(void *lpAddress, uint64_t value);
    void wFloat(void *lpAddress, float value);
    void wDouble(void *lpAddress, double value);
    void wRegionToFile(std::string filename, void *lpAddress, uintptr_t size);

    void wByte(std::string CEAddressString, BYTE byte);
    void wBytes(std::string CEAddressString, std::vector<BYTE> bytes);
    void wWord(std::string CEAddressString, WORD value);
    void wDword(std::string CEAddressString, DWORD value);
    void wQword(std::string CEAddressString, uint64_t value);
    void wFloat(std::string CEAddressString, float value);
    void wDouble(std::string CEAddressString, double value);
    void wRegionToFile(std::string filename, std::string CEAddressString, uintptr_t size);

    // write ex
    void wStrEx(HANDLE hProcess, void *lpAddress, std::string str);
    void wWstrEx(HANDLE hProcess, void *lpAddress, std::wstring str);
    void wUstrEx(HANDLE hProcess, void *lpAddress, std::u16string str);

    void wStrEx(HANDLE hProcess, std::string CEAddressString, std::string str);
    void wWstrEx(HANDLE hProcess, std::string CEAddressString, std::wstring str);
    void wUstrEx(HANDLE hProcess, std::string CEAddressString, std::u16string str);

    void wByteEx(HANDLE hProcess, void *lpAddress, BYTE byte);
    void wBytesEx(HANDLE hProcess, void *lpAddress, std::vector<BYTE> bytes);
    void wWordEx(HANDLE hProcess, void *lpAddress, WORD value);
    void wDwordEx(HANDLE hProcess, void *lpAddress, DWORD value);
    void wQwordEx(HANDLE hProcess, void *lpAddress, uint64_t value);
    void wFloatEx(HANDLE hProcess, void *lpAddress, float value);
    void wDoubleEx(HANDLE hProcess, void *lpAddress, double value);
    void wRegionToFileEx(HANDLE hProcess, std::string filename, void *lpAddress, uintptr_t size);

    void wByteEx(HANDLE hProcess, std::string CEAddressString, BYTE byte);
    void wBytesEx(HANDLE hProcess, std::string CEAddressString, std::vector<BYTE> bytes);
    void wWordEx(HANDLE hProcess, std::string CEAddressString, WORD value);
    void wDwordEx(HANDLE hProcess, std::string CEAddressString, DWORD value);
    void wQwordEx(HANDLE hProcess, std::string CEAddressString, uint64_t value);
    void wFloatEx(HANDLE hProcess, std::string CEAddressString, float value);
    void wDoubleEx(HANDLE hProcess, std::string CEAddressString, double value);
    void wRegionToFileEx(HANDLE hProcess, std::string filename, std::string CEAddressString, uintptr_t size);

    // read
    std::string rStr(char *lpAddress, uintptr_t max);
    std::wstring rWstr(wchar_t *lpAddress, uintptr_t max);
    std::u16string rUstr(char16_t *lpAddress, uintptr_t max);

    std::string rStr(std::string CEAddressString, uintptr_t max);
    std::wstring rWstr(std::string CEAddressString, uintptr_t max);
    std::u16string rUstr(std::string CEAddressString, uintptr_t max);

    std::vector<BYTE> rBytes(void *lpAddress, uintptr_t size);
    BYTE rByte(void *lpAddress);
    WORD rWord(void *lpAddress);
    DWORD rDword(void *lpAddress);
    uint64_t rQword(void *lpAddress);
    uintptr_t rPointer(void *lpAddress);
    float rFloat(void *lpAddress);
    double rDouble(void *lpAddress);
    void rRegionFromFile(std::string fileame, void *lpAddress);
    void rRegionFromFile(std::string fileame, void *lpAddress, size_t *fileSize);

    std::vector<BYTE> rBytes(std::string CEAddressString, uintptr_t size);
    BYTE rByte(std::string CEAddressString);
    WORD rWord(std::string CEAddressString);
    DWORD rDword(std::string CEAddressString);
    uint64_t rQword(std::string CEAddressString);
    uintptr_t rPointer(std::string CEAddressString);
    float rFloat(std::string CEAddressString);
    double rDouble(std::string CEAddressString);
    void rRegionFromFile(std::string fileame, std::string CEAddressString);
    void rRegionFromFile(std::string fileame, std::string CEAddressString, size_t *fileSize);

    // read ex
    std::string rStrEx(HANDLE hProcess, char *lpAddress, uintptr_t max);
    std::wstring rWstrEx(HANDLE hProcess, wchar_t *lpAddress, uintptr_t max);
    std::u16string rUstrEx(HANDLE hProcess, char16_t *lpAddress, uintptr_t max);

    std::string rStrEx(HANDLE hProcess, std::string CEAddressString, uintptr_t max);
    std::wstring rWstrEx(HANDLE hProcess, std::string CEAddressString, uintptr_t max);
    std::u16string rUstrEx(HANDLE hProcess, std::string CEAddressString, uintptr_t max);

    std::vector<BYTE> rBytesEx(HANDLE hProcess, void *lpAddress, uintptr_t size);
    BYTE rByteEx(HANDLE hProcess, void *lpAddress);
    WORD rWordEx(HANDLE hProcess, void *lpAddress);
    DWORD rDwordEx(HANDLE hProcess, void *lpAddress);
    uint64_t rQwordEx(HANDLE hProcess, void *lpAddress);
    uintptr_t rPointerEx(HANDLE hProcess, void *lpAddress);
    float rFloatEx(HANDLE hProcess, void *lpAddress);
    double rDoubleEx(HANDLE hProcess, void *lpAddress);
    void rRegionFromFileEx(HANDLE hProcess, std::string fileame, void *lpAddress);
    void rRegionFromFileEx(HANDLE hProcess, std::string fileame, void *lpAddress, size_t *fileSize);

    std::vector<BYTE> rBytesEx(HANDLE hProcess, std::string CEAddressString, uintptr_t size);
    BYTE rByteEx(HANDLE hProcess, std::string CEAddressString);
    WORD rWordEx(HANDLE hProcess, std::string CEAddressString);
    DWORD rDwordEx(HANDLE hProcess, std::string CEAddressString);
    uint64_t rQwordEx(HANDLE hProcess, std::string CEAddressString);
    uintptr_t rPointerEx(HANDLE hProcess, std::string CEAddressString);
    float rFloatEx(HANDLE hProcess, std::string CEAddressString);
    double rDoubleEx(HANDLE hProcess, std::string CEAddressString);
    void rRegionFromFileEx(HANDLE hProcess, std::string fileame, std::string CEAddressString);
    void rRegionFromFileEx(HANDLE hProcess, std::string fileame, std::string CEAddressString, size_t *fileSize);

    class VAManage
    {
    public:
      VAManage(size_t size);
      VAManage(size_t size, HANDLE hProcess);
      ~VAManage(){};
      HANDLE hProcess;
      const uintptr_t size;
      LPVOID memory;
      size_t position;

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

      Win32(std::string className, std::string windowName) : x_(CW_USEDEFAULT),
                                                             y_(CW_USEDEFAULT),
                                                             width_(CW_USEDEFAULT), height_(CW_USEDEFAULT),
                                                             style_(WS_OVERLAPPEDWINDOW),
                                                             className_(className),
                                                             windowName_(windowName),
                                                             hWnd_(NULL){};
      ~Win32() { DeleteObject(hWnd_); };

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
      AAScript(std::string script) : script_(script){};
      ~AAScript(){};

      // auto asm
      static uintptr_t aa(std::string, uintptr_t rcx);
      static std::vector<BYTE> asmBytes(std::string, bool);
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

  class PE
  {
  public:
    static DWORD GetPID(std::wstring name)
    {
      DWORD pid = NULL;
      HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
      if (hSnap != INVALID_HANDLE_VALUE)
      {
        PROCESSENTRY32W pe;
        pe.dwSize = sizeof(pe);
        if (Process32FirstW(hSnap, &pe))
        {
          do
          {
            if (!_wcsicmp(pe.szExeFile, name.c_str()))
            {
              pid = pe.th32ProcessID;
              break;
            }
          } while (Process32NextW(hSnap, &pe));
        }
      }

      CloseHandle(hSnap);
      return pid;
    }

    // exe module
    static MODULEINFO GetModuleBase(DWORD pid)
    {
      MODULEINFO mi{0};
      HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
      if (hSnap != INVALID_HANDLE_VALUE)
      {
        MODULEENTRY32W me;
        me.dwSize = sizeof(me);
        if (Module32FirstW(hSnap, &me))
        {
          mi.lpBaseOfDll = (LPVOID)me.modBaseAddr;
          mi.SizeOfImage = me.modBaseSize;
        }
      }
      CloseHandle(hSnap);
      return mi;
    }

    static MODULEINFO GetModuleInfo(std::wstring moduleName, DWORD pid)
    {
      MODULEINFO mi{0};
      HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
      if (hSnap != INVALID_HANDLE_VALUE)
      {
        MODULEENTRY32W me;
        me.dwSize = sizeof(me);
        if (Module32FirstW(hSnap, &me))
        {
          do
          {
            if (!_wcsicmp(me.szModule, moduleName.c_str()))
            {
              mi.lpBaseOfDll = (LPVOID)me.modBaseAddr;
              mi.SizeOfImage = me.modBaseSize;
              break;
            }
          } while (Module32NextW(hSnap, &me));
        }
      }
      CloseHandle(hSnap);
      return mi;
    }

    static bool isX64(DWORD pid, HMODULE hModule)
    {
      BYTE *buf = new BYTE[0x1000];
      HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
      ReadProcessMemory(hProcess, hModule, buf, 0x1000, NULL);

      PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(buf);
      PIMAGE_NT_HEADERS ntHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(buf + dosHeader->e_lfanew);
      PIMAGE_FILE_HEADER fileHeader = reinterpret_cast<PIMAGE_FILE_HEADER>(&ntHeader->FileHeader);

      // e0是32位PE，f0是64位PE
      bool isX64 = fileHeader->SizeOfOptionalHeader == 0xf0;

      CloseHandle(hProcess);
      delete[] buf;
      return isX64;
    }

    static bool isX86(DWORD pid, HMODULE hModule)
    {
      return !isX64(pid, hModule);
    }

    // 获取模块的导出表,通常一个模块会导出函数
    static std::map<std::string, uintptr_t> exports(DWORD pid, HMODULE hModule)
    {
      std::map<std::string, uintptr_t> result;
      BYTE *buf = new BYTE[0x1000];
      HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
      ReadProcessMemory(hProcess, hModule, buf, 0x1000, NULL);

      PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(buf);
      PIMAGE_NT_HEADERS ntHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(buf + dosHeader->e_lfanew);
      PIMAGE_FILE_HEADER fileHeader = reinterpret_cast<PIMAGE_FILE_HEADER>(&ntHeader->FileHeader);
      bool isX64 = fileHeader->SizeOfOptionalHeader == 0xf0;
      auto RVA2VA = [&](size_t rva) {
        return (BYTE *)hModule + rva;
      };

      IMAGE_DATA_DIRECTORY exportEntry;
      if (isX64)
      {
        PIMAGE_OPTIONAL_HEADER64 optHeader = reinterpret_cast<PIMAGE_OPTIONAL_HEADER64>(&ntHeader->OptionalHeader);
        exportEntry = optHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
      }
      else
      {
        PIMAGE_OPTIONAL_HEADER32 optHeader = reinterpret_cast<PIMAGE_OPTIONAL_HEADER32>(&ntHeader->OptionalHeader);
        exportEntry = optHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
      }

      if (exportEntry.Size == NULL)
      {
        delete hProcess;
        delete[] buf;
        return result;
      }

      BYTE *src = RVA2VA(exportEntry.VirtualAddress);
      IMAGE_EXPORT_DIRECTORY exportDes{0};
      ReadProcessMemory(hProcess, src, &exportDes, sizeof(IMAGE_EXPORT_DIRECTORY), NULL);

      // 以函数名称导出数量,指针列表
      DWORD *AddressOfNames = (DWORD *)RVA2VA(exportDes.AddressOfNames);             // 函数名称表
      DWORD *AddressOfFunctions = (DWORD *)RVA2VA(exportDes.AddressOfFunctions);     // 函数地址表
      WORD *AddressOfNameOrdinals = (WORD *)RVA2VA(exportDes.AddressOfNameOrdinals); // 函数地址index表

      size_t i = 0;
      DWORD namePtrRVA = 0;
      while (i < exportDes.NumberOfNames)
      {
        char funme[MAX_PATH] = {0};
        ReadProcessMemory(hProcess, AddressOfNames + i, &namePtrRVA, sizeof(DWORD), NULL);
        ReadProcessMemory(hProcess, RVA2VA(namePtrRVA), &funme, MAX_PATH, NULL);

        // get function address index
        WORD AddressOfFunctionsIndex = 0;
        ReadProcessMemory(hProcess, AddressOfNameOrdinals + i, &AddressOfFunctionsIndex, sizeof(WORD), NULL);

        // get function address
        DWORD funAddrRVA = 0;
        ReadProcessMemory(hProcess, AddressOfFunctions + AddressOfFunctionsIndex, &funAddrRVA, sizeof(DWORD), NULL);

        BYTE *funPtr = RVA2VA(funAddrRVA);
        result[funme] = (uintptr_t)funPtr;
        //printf("name: %s-%p\n", funme, funPtr);
        i++;
      }

      CloseHandle(hProcess);
      delete[] buf;
      return result;
    }

    static BYTE *GetProcAddress(DWORD pid, HMODULE hModule, std::string method)
    {
      BYTE *buf = new BYTE[0x1000];
      HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
      ReadProcessMemory(hProcess, hModule, buf, 0x1000, NULL);

      PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(buf);
      PIMAGE_NT_HEADERS ntHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(buf + dosHeader->e_lfanew);
      PIMAGE_FILE_HEADER fileHeader = reinterpret_cast<PIMAGE_FILE_HEADER>(&ntHeader->FileHeader);
      bool isX64 = fileHeader->SizeOfOptionalHeader == 0xf0;
      auto RVA2VA = [&](size_t rva) {
        return (BYTE *)hModule + rva;
      };

      IMAGE_DATA_DIRECTORY exportEntry;
      if (isX64)
      {
        PIMAGE_OPTIONAL_HEADER64 optHeader = reinterpret_cast<PIMAGE_OPTIONAL_HEADER64>(&ntHeader->OptionalHeader);
        exportEntry = optHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
      }
      else
      {
        PIMAGE_OPTIONAL_HEADER32 optHeader = reinterpret_cast<PIMAGE_OPTIONAL_HEADER32>(&ntHeader->OptionalHeader);
        exportEntry = optHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
      }

      if (exportEntry.Size == NULL)
      {
        delete hProcess;
        delete[] buf;
        return NULL;
      }

      BYTE *src = RVA2VA(exportEntry.VirtualAddress);
      IMAGE_EXPORT_DIRECTORY exportDes{0};
      ReadProcessMemory(hProcess, src, &exportDes, sizeof(IMAGE_EXPORT_DIRECTORY), NULL);

      // 以函数名称导出数量,指针列表
      DWORD *AddressOfNames = (DWORD *)RVA2VA(exportDes.AddressOfNames);             // 函数名称表
      DWORD *AddressOfFunctions = (DWORD *)RVA2VA(exportDes.AddressOfFunctions);     // 函数地址表
      WORD *AddressOfNameOrdinals = (WORD *)RVA2VA(exportDes.AddressOfNameOrdinals); // 函数地址index表

      size_t i = 0;
      DWORD namePtrRVA = 0;
      while (i < exportDes.NumberOfNames)
      {
        char funme[MAX_PATH] = {0};
        ReadProcessMemory(hProcess, AddressOfNames + i, &namePtrRVA, sizeof(DWORD), NULL);
        ReadProcessMemory(hProcess, RVA2VA(namePtrRVA), &funme, MAX_PATH, NULL);

        if (!_stricmp(funme, method.c_str()))
        {
          // get function address index
          WORD AddressOfFunctionsIndex = 0;
          ReadProcessMemory(hProcess, AddressOfNameOrdinals + i, &AddressOfFunctionsIndex, sizeof(WORD), NULL);

          // get function address
          DWORD funAddrRVA = 0;
          ReadProcessMemory(hProcess, AddressOfFunctions + AddressOfFunctionsIndex, &funAddrRVA, sizeof(DWORD), NULL);

          BYTE *funPtr = RVA2VA(funAddrRVA);
          return funPtr;
        }
        i++;
      }

      CloseHandle(hProcess);
      delete[] buf;
      return NULL;
    }
  };

  class CEAddressString
  {
  public:
    static LPVOID getAddress(std::string address, HANDLE hProcess = NULL);

  private:
#define TT_HEX "HEX"
#define TT_MODULE "MODULE"   // a.exe or "a b.exe" or 'a b.exe'
#define TT_MMETHOD "MMETHOD" // user32.MessageBoxA, 指定了模块的方法地址
#define TT_METHOD "METHOD"   // MessageBoxA
#define TT_SYMBOL "SYMBOL"   // s1 or s2
#define TT_PLUS "PLUS"       // +
#define TT_MINUS "MINUS"     // -
#define TT_MUL "MUL"         // *
#define TT_DIV "DIV"         // /
#define TT_POW "POW"         // **
#define TT_LPAREN "LPAREN"   // (
#define TT_RPAREN "RPAREN"   // )
#define TT_LSQUARE "LSQUARE" // [
#define TT_RSQUARE "RSQUARE" // ]
#define TT_EOF "EOF"

    class Position
    {

    public:
      size_t index;
      size_t row;
      size_t col;
      std::string text;

      Position(size_t index,
               size_t row,
               size_t col,
               std::string text)
      {
        this->index = index;
        this->row = row;
        this->col = col;
        this->text = text;
      }

      void advance(char c)
      {
        index++;
        col++;
        if (c == '\n')
        {
          col = 0;
          row++;
        }
      }

      Position *copy()
      {
        return new Position(index, row, col, text);
      }
    };

    static std::string stringsWithArrows(
        std::string text,
        Position *posStart,
        Position *posEnd)
    {
      std::string result;
      std::vector<std::string> lines = ajanuw::SSString::split(text, std::regex("\n"));
      result += lines.at(posStart->row);
      result += "\n";
      result +=
          (posStart->col ? ajanuw::SSString::padStart(" ", posStart->col, " ") : "") +
          ajanuw::SSString::repeat("^", posEnd->col - posStart->col);
      return result;
    }

    class CEAddressStringError
    {
    public:
      std::string errorName;
      Position *posStart;
      Position *posEnd;
      std::string message;

      CEAddressStringError(
          std::string errorName,
          Position *posStart,
          Position *posEnd,
          std::string message)
      {
        this->errorName = errorName;
        this->posStart = posStart;
        this->posEnd = posEnd;
        this->message = message;
      }

      virtual std::string toString()
      {
        std::string err = errorName + ": " + message + "\n";
        err += stringsWithArrows(posStart->text, posStart, posEnd);
        err += "\n";
        return err;
      };
    };

    class IllegalCharError : public CEAddressStringError
    {
    public:
      IllegalCharError(Position *posStart, Position *posEnd, std::string message) : CEAddressStringError("Illegal Char Error",
                                                                                                         posStart, posEnd, message) {}
    };

    class InvalidSyntaxError : public CEAddressStringError
    {
    public:
      InvalidSyntaxError(Position *posStart, Position *posEnd, std::string message) : CEAddressStringError("Invalid Syntax Error",
                                                                                                           posStart, posEnd, message) {}
    };

    class RuntimeError : public CEAddressStringError
    {
    public:
      RuntimeError(Position *posStart, Position *posEnd, std::string message) : CEAddressStringError("Runtime Error",
                                                                                                     posStart, posEnd, message) {}
    };

    class Token
    {
    public:
      std::string type;
      std::string value;
      Position *posStart;
      Position *posEnd;

      Token(
          std::string type,
          std::string value,
          Position *posStart,
          Position *posEnd)
      {
        this->type = type;
        this->value = value;
        this->posStart = posStart->copy();
        this->posEnd = posEnd->copy();
      }

      Token(
          std::string type,
          std::string value,
          Position *posStart)
      {
        this->type = type;
        this->value = value;
        this->posStart = posStart->copy();
        this->posEnd = posStart->copy();
        this->posEnd->advance(NULL);
      }

      ~Token()
      {
        delete posStart;
        delete posEnd;
      }

      std::string toString()
      {
        return value.empty() ? type : type + ":" + value;
      }
    };

    class Lexer
    {
    public:
      Position *pos;
      char curChar;
      std::string text;
      Lexer(std::string text)
      {
        this->text = text;
        this->pos = new Position(-1, 0, -1, this->text);
        advance();
      }

      ~Lexer()
      {
        delete pos;
      }

      void advance()
      {
        pos->advance(curChar);
        if (pos->index < text.size())
        {
          curChar = text.at(pos->index);
        }
        else
        {
          curChar = NULL;
        }
      }

      std::vector<Token *> makeTokens()
      {
        std::vector<Token *> tokens;

        while (curChar != NULL)
        {
          switch (curChar)
          {
          case ' ':
          case '\t':
            advance();
            break;

          case '+':
            tokens.push_back(new Token(TT_PLUS, "+", pos));
            advance();
            break;

          case '-':
            tokens.push_back(new Token(TT_MINUS, "-", pos));
            advance();
            break;

          case '*':
            tokens.push_back(makeMulOrPow());
            break;
          case '/':
            tokens.push_back(new Token(TT_DIV, "", pos));
            advance();
            break;
          case '(':
            tokens.push_back(new Token(TT_LPAREN, "(", pos));
            advance();
            break;
          case ')':
            tokens.push_back(new Token(TT_RPAREN, ")", pos));
            advance();
            break;
          case '[':
            tokens.push_back(new Token(TT_LSQUARE, "[", pos));
            advance();
            break;
          case ']':
            tokens.push_back(new Token(TT_RSQUARE, "]", pos));
            advance();
            break;

          case '\'':
          case '"':
            makeString(&tokens);
            break;

          case '0':
            tokens.push_back(makeHex());
            break;

          default:
            if (!std::regex_search(std::string(1, curChar), std::regex("[^\u4e00-\u9fa5\\w-.]", std::regex::icase)))
            {
              tokens.push_back(makeModuleOrSymbolOrHex());
              break;
            }
            break;
          }
        }

        tokens.push_back(new Token(TT_EOF, "", pos));
        return tokens;
      }

      bool isHex(std::string str)
      {
        return !std::regex_search(str, std::regex("[^0-9a-f]", std::regex::icase));
      };

    private:
      // 0a or 0x0a
      Token *makeHex()
      {
        std::string str;
        str.push_back(curChar);
        Position *posStart = pos->copy();

        auto getHex = [=]() {
          std::string _str;

          while (curChar != NULL && isHex(std::string(1, curChar)))
          {
            _str += curChar;
            advance();
          }
          return _str;
        };

        advance();
        if (curChar == 'x')
        {
          str.push_back(curChar);
          advance();
          str += getHex();
        }
        else
          str += getHex();

        return new Token(TT_HEX, str, posStart, pos);
      }

      Token *makeModuleOrSymbolOrHex()
      {
        std::string str;
        std::string method;
        std::string type = TT_SYMBOL;
        Position *posStart = pos->copy();

        while (curChar != NULL && !std::regex_search(std::string(1, curChar), std::regex("[^\u4e00-\u9fa5\\w-.]", std::regex::icase)))
        {
          if (type == TT_MODULE)
            method += curChar;
          if (curChar == '.')
            type = TT_MODULE;
          str += curChar;
          advance();
        }

        // 优先级: SYMBOL > HEX > METHOD
        if (type == TT_SYMBOL && !ajanuw::Symbol::has(str))
        {
          if (isHex(str))
            type = TT_HEX;
          else
            type = TT_METHOD;
        }

        // is MODULE_NAME.METHOD?
        if (type == TT_MODULE)
        {
          method = ajanuw::SSString::tolower(method);
          if (method != "dll" && method != "exe")
            type = TT_MMETHOD;
        }

        return new Token(type, str, posStart, pos);
      }

      Token *makeMulOrPow()
      {
        Position *posStart = pos->copy();
        std::string type = TT_MUL;
        std::string value = "*";

        advance();
        if (curChar == '*')
        {
          advance();
          type = TT_POW;
          value += "*";
        }
        return new Token(type, value, posStart, pos);
      }

      /**
   * "user32.dll"
   * "user32.MessageBoxA"
   * "MessageBoxA"
   * "s1" => 优先级: SYMBOL > HEX > METHOD
   * "1+1" => 2
   * "0xaa"
   * "a b.exe"
   *
   * ## error
   * "user32.dll+1"
   * "user32.MessageBoxA+1"
   * "MessageBoxA+1"
   * "s1+1"
   *
   * ## test
   * 1+'user32.MessageBoxA'-0xabc+MessageBoxA+'0x22'+'MessageboxA'
   */
      void makeString(std::vector<Token *> *tokens)
      {
        std::string str;
        std::string type = TT_MODULE;
        char s = curChar; // " or '
        Position *posStart = pos->copy();

        advance();
        while (curChar != NULL && curChar != s)
        {
          str += curChar;
          advance();
        }
        advance();

        if (ajanuw::SSString::search(str, std::regex("\\.")))
        {
          auto r = ajanuw::SSString::split(str, std::regex("\\."));
          std::string method = r.at(1);
          if (method != "exe" && method != "dll")
          {
            type = TT_MMETHOD;
          }
        }
        else
        {
          if (ajanuw::Symbol::has(str))
          {
            type = TT_SYMBOL;
          }
          else if (std::regex_search(str, std::regex("[\\+\\-\\*\\/]")))
          {
            auto lexer = ajanuw::CEAddressString::Lexer(str);
            auto _tokens = lexer.makeTokens();
            for (auto tok : _tokens)
              tokens->push_back(tok);
            return;
          }
          else if (ajanuw::SSString::startWith(str, "0x") || isHex(str))
          {
            type = TT_HEX;
          }
          else
          {
            type = TT_METHOD;
          }
        }

        tokens->push_back(new Token(type, str, posStart, pos));
      }
    };

#define CESNT_MODULE 1
#define CESNT_SYMBOL 2
#define CESNT_HEX 3
#define CESNT_MMETHOD 4
#define CESNT_METHOD 5
#define CESNT_UNARY_OP 6
#define CESNT_BIN_OP 7
#define CESNT_POINTER 8

    class CEAddressStringNode
    {
    public:
      Position *posStart;
      Position *posEnd;
      CEAddressStringNode(Position *posStart, Position *posEnd) : posStart(posStart), posEnd(posEnd) {}
      virtual size_t id() { return NULL; };
    };

    static void deleteCEAddressStringNode(CEAddressStringNode *node)
    {
      switch (node->id())
      {
      case CESNT_HEX:
        delete reinterpret_cast<HexNode *>(node);
        break;

      case CESNT_SYMBOL:
        delete reinterpret_cast<SymbolNode *>(node);
        break;

      case CESNT_MODULE:
        delete reinterpret_cast<ModuleNode *>(node);
        break;

      case CESNT_MMETHOD:
        delete reinterpret_cast<MMethodNode *>(node);
        break;

      case CESNT_METHOD:
        delete reinterpret_cast<MethodNode *>(node);
        break;

      case CESNT_UNARY_OP:
        delete reinterpret_cast<UnaryOpNode *>(node);
        break;

      case CESNT_POINTER:
        delete reinterpret_cast<PointerNode *>(node);
        break;

      case CESNT_BIN_OP:
        delete reinterpret_cast<BinOpNode *>(node);
        break;

      default:
        delete node;
        break;
      }
    }

    class ModuleNode : public CEAddressStringNode
    {
    public:
      Token *token;
      ModuleNode(Token *token) : CEAddressStringNode(token->posStart, token->posEnd), token(token) {}

      ~ModuleNode()
      {
        delete token;
      }

      size_t id()
      {
        return CESNT_MODULE;
      }
    };

    class SymbolNode : public CEAddressStringNode
    {
    public:
      Token *token;
      SymbolNode(Token *token)
          : CEAddressStringNode(token->posStart, token->posEnd), token(token) {}

      ~SymbolNode()
      {
        delete token;
      }
      size_t id()
      {
        return CESNT_SYMBOL;
      }
    };

    class HexNode : public CEAddressStringNode
    {
    public:
      Token *token;
      HexNode(Token *token)
          : CEAddressStringNode(token->posStart, token->posEnd), token(token) {}
      ~HexNode()
      {
        delete token;
      }
      size_t id()
      {
        return CESNT_HEX;
      }
    };

    class MMethodNode : public CEAddressStringNode
    {
    public:
      Token *token;
      MMethodNode(Token *token)
          : CEAddressStringNode(token->posStart, token->posEnd), token(token) {}
      ~MMethodNode()
      {
        delete token;
      }
      size_t id()
      {
        return CESNT_MMETHOD;
      }
    };

    class MethodNode : public CEAddressStringNode
    {
    public:
      Token *token;
      MethodNode(Token *token)
          : CEAddressStringNode(token->posStart, token->posEnd), token(token) {}
      ~MethodNode()
      {
        delete token;
      }

      size_t id()
      {
        return CESNT_METHOD;
      }
    };

    class UnaryOpNode : public CEAddressStringNode
    {
    public:
      Token *token;
      CEAddressStringNode *node;
      UnaryOpNode(Token *token, CEAddressStringNode *node)
          : CEAddressStringNode(token->posStart, token->posEnd), token(token), node(node) {}

      ~UnaryOpNode()
      {
        delete token;
        deleteCEAddressStringNode(node);
      }

      size_t id()
      {
        return CESNT_UNARY_OP;
      }
    };

    class BinOpNode : public CEAddressStringNode
    {
    public:
      CEAddressStringNode *leftNode;
      Token *token;
      CEAddressStringNode *rightNode;
      BinOpNode(
          CEAddressStringNode *leftNode,
          Token *token,
          CEAddressStringNode *rightNode)
          : CEAddressStringNode(leftNode->posStart, rightNode->posEnd), leftNode(leftNode), token(token), rightNode(rightNode) {}
      ~BinOpNode()
      {
        deleteCEAddressStringNode(leftNode);
        delete token;
        deleteCEAddressStringNode(rightNode);
      }

      size_t id()
      {
        return CESNT_BIN_OP;
      }
    };

    class PointerNode : public CEAddressStringNode
    {
    public:
      CEAddressStringNode *node;
      PointerNode(CEAddressStringNode *node)
          : CEAddressStringNode(node->posStart, node->posEnd), node(node) {}
      ~PointerNode()
      {
        deleteCEAddressStringNode(node);
      }
      size_t id()
      {
        return CESNT_POINTER;
      }
    };

    class Parser
    {
    public:
      size_t index = -1;
      Token *curToken = nullptr;
      std::vector<Token *> tokens;
      Parser(std::vector<Token *> tokens) : tokens(tokens)
      {
        advance();
      }

      void advance()
      {
        index++;
        if (index < tokens.size())
        {
          curToken = tokens.at(index);
        }
        else
        {
          curToken = nullptr;
        }
      }

      CEAddressStringNode *parse()
      {
        CEAddressStringNode *node = expr();

        if (curToken->type != TT_EOF)
        {
          throw std::exception(
              InvalidSyntaxError(
                  curToken->posStart,
                  curToken->posEnd,
                  "Wrong EOF")
                  .toString()
                  .c_str());
        }

        return node;
      }

      CEAddressStringNode *expr()
      {
        CEAddressStringNode *leftNode = term();

        while (curToken->type == TT_PLUS || curToken->type == TT_MINUS)
        {
          Token *token = curToken;
          advance();
          CEAddressStringNode *rightNode = term();
          leftNode = new BinOpNode(leftNode, token, rightNode);
        }

        return leftNode;
      }

      CEAddressStringNode *term()
      {
        CEAddressStringNode *leftNode = factor();

        while (curToken->type == TT_MUL || curToken->type == TT_DIV)
        {
          Token *token = curToken;
          advance();
          CEAddressStringNode *rightNode = factor();
          leftNode = new BinOpNode(leftNode, token, rightNode);
        }

        return leftNode;
      }

      CEAddressStringNode *factor()
      {
        Token *token = curToken;

        if (curToken->type == TT_PLUS || curToken->type == TT_MINUS)
        {
          advance();
          return new UnaryOpNode(token, factor());
        }

        return power();
      }

      CEAddressStringNode *power()
      {
        CEAddressStringNode *leftNode = atom();

        while (curToken->type == TT_POW)
        {
          Token *token = curToken;
          advance();
          CEAddressStringNode *rightNode = factor();
          leftNode = new BinOpNode(leftNode, token, rightNode);
        }

        return leftNode;
      }

      CEAddressStringNode *atom()
      {
        Token *token = curToken;
        if (token->type == TT_MODULE)
        {
          advance();
          return new ModuleNode(token);
        }
        else if (token->type == TT_SYMBOL)
        {
          advance();
          return new SymbolNode(token);
        }
        else if (token->type == TT_HEX)
        {
          advance();
          return new HexNode(token);
        }
        else if (token->type == TT_MMETHOD)
        {
          advance();
          return new MMethodNode(token);
        }
        else if (token->type == TT_METHOD)
        {
          advance();
          return new MethodNode(token);
        }
        else if (token->type == TT_LPAREN)
        {
          advance();
          CEAddressStringNode *_expr = expr();
          if (curToken->type == TT_RPAREN)
          {
            advance();
            return _expr;
          }
          else
          {
            throw std::exception(InvalidSyntaxError(
                                     curToken->posStart,
                                     curToken->posEnd,
                                     "Expected ')'")
                                     .toString()
                                     .c_str());
          }
        }
        else if (token->type == TT_LSQUARE)
        {
          advance();
          CEAddressStringNode *_expr = expr();
          if (curToken->type == TT_RSQUARE)
          {
            advance();
            return new PointerNode(_expr);
          }
          else
          {
            throw std::exception(InvalidSyntaxError(
                                     curToken->posStart,
                                     curToken->posEnd,
                                     "Expected ']'")
                                     .toString()
                                     .c_str());
          }
        }
        else
        {
          throw std::exception(InvalidSyntaxError(
                                   curToken->posStart,
                                   curToken->posEnd,
                                   "Expected '+', '-', '*', '/', MODULE, SYMBOL, HEX or MODULE_NAME.METHOD")
                                   .toString()
                                   .c_str());
        }
      }
    };

    class Interpreter
    {
    public:
      HANDLE hProcess;
      DWORD pid = NULL;
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
          pid = GetCurrentProcessId();
          isX86 = PE::isX86(pid, (HMODULE)(PE::GetModuleBase(pid).lpBaseOfDll));
        }
      }

      uintptr_t visit(CEAddressStringNode *node)
      {
        switch (node->id())
        {
        case CESNT_HEX:
          return std::stoull(reinterpret_cast<HexNode *>(node)->token->value, nullptr, 16);

        case CESNT_SYMBOL:
          return (uintptr_t)ajanuw::Symbol::get(reinterpret_cast<SymbolNode *>(node)->token->value);

        case CESNT_MODULE:
        {
          HMODULE hModule = NULL;
          std::string moduleName = reinterpret_cast<ModuleNode *>(node)->token->value;

          if (hProcess == NULL)
          {
            hModule = LoadLibraryA(reinterpret_cast<ModuleNode *>(node)->token->value.c_str());
          }
          else
          {
            hModule = (HMODULE)(PE::GetModuleInfo(ajanuw::SSString::strToWstr(moduleName), pid).lpBaseOfDll);
          }

          if (hModule == NULL)
          {
            throw std::exception(
                RuntimeError(
                    node->posStart,
                    node->posEnd,
                    "MODULE not module \"" + reinterpret_cast<ModuleNode *>(node)->token->value + "\"")
                    .toString()
                    .c_str());
          }

          return (uintptr_t)hModule;
        }

        case CESNT_MMETHOD:
        {
          std::vector<std::string> r = ajanuw::SSString::split(reinterpret_cast<MMethodNode *>(node)->token->value, std::regex("\\."));
          std::string mod = r.at(0);
          std::string met = r.at(1);

          HMODULE hModule = NULL;

          if (hProcess == NULL)
          {
            hModule = LoadLibraryA(mod.c_str());
          }
          else
          {
            hModule = (HMODULE)(PE::GetModuleInfo(ajanuw::SSString::strToWstr(mod), pid).lpBaseOfDll);
          }

          if (!hModule)
          {
            throw std::exception(
                RuntimeError(
                    node->posStart,
                    node->posEnd,
                    "MMETHOD not module \"" + mod + "\"")
                    .toString()
                    .c_str());
          }

          uintptr_t hMethod = NULL;
          if (hProcess == NULL)
          {
            hMethod = (uintptr_t)GetProcAddress(hModule, met.c_str());
          }
          else
          {
            hMethod = (uintptr_t)PE::GetProcAddress(pid, hModule, met);
          }

          if (hMethod == NULL)
          {
            throw std::exception(
                RuntimeError(
                    node->posStart,
                    node->posEnd,
                    "Not method \"" + met + "\"")
                    .toString()
                    .c_str());
          }
          return (uintptr_t)hMethod;
        }

        case CESNT_METHOD:
        {
          std::string met = reinterpret_cast<MethodNode *>(node)->token->value;
          uintptr_t r = NULL;
          HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
          if (hSnap != INVALID_HANDLE_VALUE)
          {
            MODULEENTRY32 me;
            me.dwSize = sizeof(me);
            if (Module32First(hSnap, &me))
            {
              do
              {
                if (hProcess == NULL)
                {
                  r = (uintptr_t)GetProcAddress((HMODULE)me.modBaseAddr, met.c_str());
                }
                else
                {
                  r = (uintptr_t)PE::GetProcAddress(pid, (HMODULE)me.modBaseAddr, met);
                }
                if (r != NULL)
                  break;
              } while (Module32Next(hSnap, &me));
            }
          }
          CloseHandle(hSnap);

          if (r == NULL)
          {
            throw std::exception(
                RuntimeError(
                    node->posStart,
                    node->posEnd,
                    "Not defined symbol \"" + met + "\"")
                    .toString()
                    .c_str());
          }

          return r;
        }

        case CESNT_UNARY_OP:
        {
          uintptr_t value = visit(reinterpret_cast<UnaryOpNode *>(node)->node);
          if (reinterpret_cast<UnaryOpNode *>(node)->token->type == TT_MINUS)
          {
            return value * -1;
          }
          return value;
        }

        case CESNT_POINTER:
        {
          uintptr_t address = visit(reinterpret_cast<PointerNode *>(node)->node);
          if (hProcess == NULL)
          {
            return *(uintptr_t *)address;
          }
          else
          {
            uintptr_t result = NULL;
            if (ReadProcessMemory(hProcess, (LPCVOID)address, (LPVOID)&result, isX86 ? 4 : 8, NULL))
            {
              return result;
            }
            else
            {
              throw std::exception(RuntimeError(
                                       node->posStart,
                                       node->posEnd,
                                       "Read Pointer Error.")
                                       .toString()
                                       .c_str());
            }
          }
        }

        case CESNT_BIN_OP:
        {
          uintptr_t left = visit(reinterpret_cast<BinOpNode *>(node)->leftNode);
          uintptr_t right = visit(reinterpret_cast<BinOpNode *>(node)->rightNode);

          std::string type = reinterpret_cast<BinOpNode *>(node)->token->type;
          if (type == TT_PLUS)
          {
            return left + right;
          }
          else if (type == TT_MINUS)
          {
            return left - right;
          }
          else if (type == TT_MUL)
          {
            return left * right;
          }
          else if (type == TT_DIV)
          {
            if (right == 0)
            {
              throw std::exception(
                  RuntimeError(
                      node->posStart,
                      node->posEnd,
                      "Division by zero")
                      .toString()
                      .c_str());
            }
            return left / right;
          }
          else if (type == TT_POW)
          {
            return pow(left, right);
          }
        }

        default:
          throw std::exception(RuntimeError(
                                   node->posStart,
                                   node->posEnd,
                                   "Unexpected CEAddressStringNode")
                                   .toString()
                                   .c_str());
          return NULL;
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
      std::vector<BYTE> origenBytes = {};

      // hook的地址
      BYTE *addr = NULL;

      // 字节大小
      size_t size = NULL;

      // 是否开启
      bool bEnable = false;

      // hook过程 是否成功
      bool bSuccess = false;

      HookBase(HANDLE hProcess, BYTE *addr, size_t size) : hProcess(hProcess), addr(addr), size(size)
      {
        origenBytes.resize(size);
        ReadProcessMemory(hProcess, addr, origenBytes.data(), size, NULL);
        bSuccess = true;
      }

      void enable()
      {
        if (!bSuccess)
          return;

        // printf("enable: hProcess(%p), addr(%p), size(%d)\n", hProcess, addr, size);

        DWORD oldProc;
        VirtualProtectEx(hProcess, addr, size, PAGE_EXECUTE_READWRITE, &oldProc);
        ajanuw::Target::memsetEx(hProcess, addr, NOP_BYTE, size);
        enableHook();
        VirtualProtectEx(hProcess, addr, size, oldProc, &oldProc);
      }

      void disable()
      {
        if (!bSuccess)
          return;
        DWORD oldProc;
        VirtualProtectEx(hProcess, addr, size, PAGE_EXECUTE_READWRITE, &oldProc);
        WriteProcessMemory(hProcess, addr, origenBytes.data(), size, 0);
        VirtualProtectEx(hProcess, addr, size, oldProc, &oldProc);
      }

      void toggle()
      {
        bEnable = !bEnable;
        if (bEnable)
          enable();
        else
          disable();
      }
      virtual void enableHook(){};
    };
    class SetNop : public HookBase
    {
    public:
      SetNop(HANDLE hProcess, BYTE *addr, size_t size) : HookBase(hProcess, addr, size)
      {
      }
    };

    class SetHook : public HookBase
    {
    public:
      BYTE *newmem = NULL;
      DWORD jmpHookBytes = NULL;

      SetHook(HANDLE hProcess, BYTE *addr, size_t size, std::vector<BYTE> hookBytes) : HookBase(hProcess, addr, size)
      {
        bSuccess = false;
        if (size < 5)
        {
          throw std::exception("SetHook Error: At least 5 bytes are required to set the Hook");
        }

        // hook code
        BYTE *returnAddr = addr + size;
        size_t newmemSize = hookBytes.size() + 100;

        newmem = (BYTE *)ajanuw::Mem::allocEx(hProcess, newmemSize);
        if (!newmem)
        {
          throw std::exception("SetHook Error: allocEx Error.");
        }
        WriteProcessMemory(hProcess, newmem, hookBytes.data(), newmemSize, NULL);

        // set return bytes
        BYTE *newmemJmpReturnAddr = newmem + hookBytes.size();
        DWORD returnBytes = (DWORD)(returnAddr - newmemJmpReturnAddr - 5);
        BYTE b = JMP_BYTE;
        WriteProcessMemory(hProcess, newmemJmpReturnAddr, (LPCVOID)&b, sizeof(BYTE), NULL);
        WriteProcessMemory(hProcess, newmemJmpReturnAddr + 1, (LPCVOID)&returnBytes, sizeof(DWORD), NULL);

        jmpHookBytes = newmem - addr - 5;
        bSuccess = true;
      }

      void enableHook()
      {
        BYTE b = JMP_BYTE;
        WriteProcessMemory(hProcess, (LPVOID)addr, (LPCVOID)&b, sizeof(BYTE), 0);
        WriteProcessMemory(hProcess, (LPVOID)(addr + 1), (LPCVOID)&jmpHookBytes, sizeof(DWORD), 0);
      }
    };

    static BYTE *memsetEx(HANDLE hProcess, BYTE *targetAddr, BYTE val, size_t size)
    {
      for (size_t i = 0; i < size; i++)
        WriteProcessMemory(hProcess, targetAddr + i, &val, sizeof(BYTE), NULL);
      return targetAddr;
    }

    std::wstring name;
    DWORD pid = NULL;
    HANDLE hProcess = NULL;
    MODULEINFO mi;

    bool isX86;
    bool isX64;

    Target(std::wstring name) : name(name)
    {
      pid = ajanuw::PE::GetPID(name);
      if (pid != NULL)
      {
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
        if (hProcess != NULL)
        {
          mi = ajanuw::PE::GetModuleInfo(name, pid);
          isX86 = ajanuw::PE::isX86(pid, (HMODULE)mi.lpBaseOfDll);
          isX64 = !isX86;
        }
      }
    }

    Target(DWORD pid) : pid(pid)
    {
      hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
      if (hProcess)
      {
        wchar_t text[1024];
        GetModuleBaseNameW(hProcess, 0, text, sizeof(text));
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

    std::vector<BYTE *> moduleScan(std::string strbytes, size_t offset = NULL)
    {
      std::vector<std::string> maskList = ajanuw::SSString::split(strbytes, std::regex("\\s+"));
      BYTE *base = (BYTE *)mi.lpBaseOfDll;
      std::vector<BYTE *> addrs;
      ;

      BYTE v = NULL;
      size_t eachSize = mi.SizeOfImage - maskList.size();
      for (size_t i = 0; i < eachSize; i++)
      {
        bool found = true;
        for (size_t j = 0; j < maskList.size(); j++)
        {
          ReadProcessMemory(hProcess, (LPCVOID)(base + i + j), (LPVOID)&v, sizeof(BYTE), 0);
          bool notEqual = maskList[j] != "?" && maskList[j] != "??" && maskList[j] != "*" && maskList[j] != "**" && (BYTE)std::stol(maskList[j], nullptr, 16) != v;
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
