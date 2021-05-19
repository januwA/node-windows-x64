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

    // string data write to memry
    void toMem(void *dst, std::string str);
    void toMem(void *dst, std::wstring str);
    void toMem(void *dst, std::u16string str);

    void toMemEx(HANDLE hProcess, void *dst, std::string str);
    void toMemEx(HANDLE hProcess, void *dst, std::wstring str);
    void toMemEx(HANDLE hProcess, void *dst, std::u16string str);

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
    bool startWith(std::string str, const char *s2, size_t index = 0);

    /*
    * ajanuw::SSString::endWith("123", "23")     -> true
    * ajanuw::SSString::endWith("123", "2")      -> false
    * ajanuw::SSString::endWith("12333", "2", 2) -> true
    */
    bool endWith(std::string str, const char *s2);
    bool endWith(std::string str, const char *s2, size_t length);

    bool search(std::string str, std::regex reg);
    bool search(std::wstring str, std::regex reg);

    /*
    * ajanuw::SSString::trim("  abc  ")      -> "abc"
    * ajanuw::SSString::trimStart("  abc  ") -> "abc  "
    * ajanuw::SSString::trimEnd("  abc  ")   -> "  abc"
    */
    std::string trim(std::string str);
    std::string trimStart(std::string str);
    std::string trimEnd(std::string str);

    /*
    * ajanuw::SSString::split("a,b-c", std::regex("[,\\-]")) -> ["a", "b", "c"]
    */
    std::vector<std::string> split(std::string str, std::regex reg);

    /*
    * ajanuw::SSString::toBytes("00 01 02") -> [1,2,3]
    */
    std::vector<BYTE> toBytes(std::string byteStr);

    /*
    * ajanuw::SSString::cmp("abc", "abc") -> true
    * ajanuw::SSString::cmp("abc", "abx") -> false
    */
    BOOL cmp(const char *s1, const char *s2);
    BOOL cmp(std::string s1, std::string s2);
    BOOL cmp(const wchar_t *s1, const wchar_t *s2);
    BOOL cmp(std::wstring s1, std::wstring s2);
    BOOL cmp(const char16_t *s1, const char16_t *s2);
    BOOL cmp(std::u16string s1, std::u16string s2);

    /*
    * ajanuw::SSString::icmp("abc", "ABc")   -> true
    * ajanuw::SSString::icmp("abc", "ABx")   -> false
    * ajanuw::SSString::icmp(L"abc", L"ABc") -> true
    * ajanuw::SSString::icmp(L"abc", L"ABx") -> false
    */
    BOOL icmp(const char *s1, const char *s2);
    BOOL icmp(std::string s1, std::string s2);
    BOOL icmp(const wchar_t *s1, const wchar_t *s2);
    BOOL icmp(std::wstring s1, std::wstring s2);
    BOOL icmp(const char16_t *s1, const char16_t *s2);
    BOOL icmp(std::u16string s1, std::u16string s2);

    /*
    * ajanuw::SSString::len("abc")  -> 3
    * ajanuw::SSString::len(L"abc") -> 3
    */
    size_t len(const char *str);
    size_t len(const char *str, size_t maxSize);
    size_t len(const wchar_t *str);
    size_t len(const wchar_t *str, size_t maxSize);
    size_t len(std::string str);
    size_t len(std::wstring str);
    size_t len(std::u16string str);

    /*
    * ajanuw::SSString::count("abc")  -> 3
    * ajanuw::SSString::count(L"abc") -> 6
    */
    size_t count(const char *str);
    size_t count(const char *str, size_t maxSize);
    size_t count(const wchar_t *str);
    size_t count(const wchar_t *str, size_t maxSize);
    size_t count(std::string str);
    size_t count(std::wstring str);
    size_t count(std::u16string str);

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

    /*
    * ajanuw::SSString::padStart("abc", 5, "^") -> "^^abc"
    * ajanuw::SSString::padEnd("abc", 5, "^")   -> "abc^^"
    */
    std::string pad(std::string str, size_t size, std::string padStr, bool isStart);
    std::string padStart(std::string str, size_t size, std::string padStr);
    std::string padEnd(std::string str, size_t size, std::string padStr);

    /*
    * ajanuw::SSString::repeat("abc", 3) -> "abcabcabc"
    */
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
      HWND hWnd;

      std::string windowName;
      std::string className;
      size_t x;
      size_t y;
      size_t width;
      size_t height;
      DWORD style;

      Win32(std::string className, std::string windowName) : x(CW_USEDEFAULT),
                                                             y(CW_USEDEFAULT),
                                                             width(CW_USEDEFAULT), height(CW_USEDEFAULT),
                                                             style(WS_OVERLAPPEDWINDOW),
                                                             className(className),
                                                             windowName(windowName),
                                                             hWnd(NULL){};
      ~Win32() { DeleteObject(hWnd); };

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
      std::string script;
      AAScript(std::string script) : script(script){};
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
    static DWORD GetPID(std::wstring name);
    // exe module
    static MODULEINFO GetModuleBase(DWORD pid);
    static MODULEINFO GetModuleInfo(std::wstring moduleName, DWORD pid);
    static bool isX64(DWORD pid, HMODULE hModule);
    static bool isX86(DWORD pid, HMODULE hModule);
    // 获取模块的导出表,通常一个模块会导出函数
    static std::map<std::string, uintptr_t> exports(DWORD pid, HMODULE hModule);
    static BYTE *GetProcAddress(DWORD pid, HMODULE hModule, std::string method);
  };

  class CEAddressString
  {
  public:
    static LPVOID getAddress(std::string address, HANDLE hProcess = NULL);

  private:
    enum class TT
    {
      HEX,
      MODULE,      // a.exe or "a b.exe" or 'a b.exe' or "a-b.exe"
      MMETHOD,     // user32.MessageBoxA, 指定了模块的方法地址
      METHOD,      // MessageBoxA
      SYMBOL,      // s1 or s2
      PLUS,        // +
      MINUS,       // -
      MUL,         // *
      DIV,         // /
      POW,         // **
      LPAREN,      // (
      RPAREN,      // )
      LSQUARE,     // [
      RSQUARE,     // ]
      END_OF_FILE, // \0
    };

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
          : index(index), row(row), col(col), text(text)
      {
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
          : errorName(errorName), posStart(posStart), posEnd(posEnd), message(message)
      {
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
      IllegalCharError(Position *posStart, Position *posEnd, std::string message) : CEAddressStringError("Illegal Char Error", posStart, posEnd, message) {}
    };

    class InvalidSyntaxError : public CEAddressStringError
    {
    public:
      InvalidSyntaxError(Position *posStart, Position *posEnd, std::string message) : CEAddressStringError("Invalid Syntax Error", posStart, posEnd, message) {}
    };

    class RuntimeError : public CEAddressStringError
    {
    public:
      RuntimeError(Position *posStart, Position *posEnd, std::string message) : CEAddressStringError("Runtime Error", posStart, posEnd, message) {}
    };

    class Token
    {
    public:
      TT type;
      std::string value;
      Position *posStart;
      Position *posEnd;

      Token(
          TT type,
          std::string value,
          Position *posStart,
          Position *posEnd)
          : type(type), value(value), posStart(posStart), posEnd(posEnd->copy())
      {
      }

      Token(
          TT type,
          std::string value,
          Position *posStart) : type(type), value(value), posStart(posStart->copy()), posEnd(posStart->copy())
      {
        this->posEnd->advance(NULL);
      }

      ~Token()
      {
        delete posStart;
        delete posEnd;
      }

      std::string toString()
      {
        return value + ":" + std::to_string((int)type);
      }
    };

    class Lexer
    {
    public:
      Position *pos;
      char c;
      std::string text;
      Lexer(std::string text) : text(text), pos(new Position(-1, 0, -1, text))
      {
        advance();
      }

      ~Lexer()
      {
        delete pos;
      }

      void advance()
      {
        pos->advance(c);
        c = pos->index < text.size() ? text.at(pos->index) : '\0';
      }

      void makeTokens(std::vector<Token *> *tokens)
      {
        while (c != '\0')
        {
          switch (c)
          {
          case ' ':
          case '\t':
          case '\r':
          case '\n':
            advance();
            break;

          case '+':
            tokens->push_back(new Token(TT::PLUS, "+", pos));
            advance();
            break;

          case '-':
            tokens->push_back(new Token(TT::MINUS, "-", pos));
            advance();
            break;

          case '*':
            tokens->push_back(makeMulOrPow());
            break;

          case '/':
            tokens->push_back(new Token(TT::DIV, "/", pos));
            advance();
            break;

          case '(':
            tokens->push_back(new Token(TT::LPAREN, "(", pos));
            advance();
            break;

          case ')':
            tokens->push_back(new Token(TT::RPAREN, ")", pos));
            advance();
            break;

          case '[':
            tokens->push_back(new Token(TT::LSQUARE, "[", pos));
            advance();
            break;

          case ']':
            tokens->push_back(new Token(TT::RSQUARE, "]", pos));
            advance();
            break;

          case '\'':
          case '"':
            makeString(tokens);
            break;

          case '0':
            tokens->push_back(makeHex());
            break;

          default:
            if (isSymbol(c))
            {
              tokens->push_back(makeModuleOrSymbolOrHex());
              break;
            }
            break;
          }
        }

        tokens->push_back(new Token(TT::END_OF_FILE, "EOF", pos));
      }

      bool isHex(char c)
      {
        return isHex(std::string(1, c));
      };

      bool isHex(std::string str)
      {
        return !std::regex_search(str, std::regex("[^0-9a-f]", std::regex::icase));
      };

      bool isSymbol(char c)
      {
        return !std::regex_search(std::string(1, c), std::regex("[^\u4e00-\u9fa5\\w-.]", std::regex::icase));
      }

    private:
      // 0a or 0x0a
      Token *makeHex()
      {
        std::string str;
        str.push_back(c);
        Position *posStart = pos->copy();

        auto getHex = [=](std::string *s)
        {
          while (c != '\0' && isHex(c))
          {
            *s += c;
            advance();
          }
        };

        advance();
        if (c == 'x')
        {
          str.push_back(c);
          advance();
          getHex(&str);
        }
        else
          getHex(&str);

        return new Token(TT::HEX, str, posStart, pos);
      }

      Token *makeModuleOrSymbolOrHex()
      {
        std::string str;
        std::string method;
        TT type = TT::SYMBOL;
        Position *posStart = pos->copy();

        while (c != '\0' && isSymbol(c))
        {
          if (type == TT::MODULE)
            method += c;
          if (c == '.')
            type = TT::MODULE;
          str += c;
          advance();
        }

        // 优先级: SYMBOL > HEX > METHOD
        if (type == TT::SYMBOL && !ajanuw::Symbol::has(str))
        {
          if (isHex(str))
            type = TT::HEX;
          else
            type = TT::METHOD;
        }

        // is MODULE_NAME.METHOD?
        if (type == TT::MODULE)
        {
          method = ajanuw::SSString::tolower(method);
          if (method != "dll" && method != "exe")
            type = TT::MMETHOD;
        }

        return new Token(type, str, posStart, pos);
      }

      Token *makeMulOrPow()
      {
        Position *posStart = pos->copy();
        TT type = TT::MUL;
        std::string value = "*";

        advance();
        if (c == '*')
        {
          advance();
          type = TT::POW;
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
      void makeString(std::vector<ajanuw::CEAddressString::Token *> *tokens)
      {
        std::string str;
        TT type = TT::MODULE;
        char s = c; // " or '
        Position *posStart = pos->copy();

        advance();
        while (c != '\0' && c != s)
        {
          str += c;
          advance();
        }
        advance();

        if (ajanuw::SSString::search(str, std::regex("\\.")))
        {
          auto r = ajanuw::SSString::split(str, std::regex("\\."));
          std::string method = r.at(1);
          if (method != "exe" && method != "dll")
          {
            type = TT::MMETHOD;
          }
        }
        else
        {
          if (ajanuw::Symbol::has(str))
          {
            type = TT::SYMBOL;
          }
          else if (std::regex_search(str, std::regex("[\\+\\-\\*\\/]")))
          {
            auto lexer = ajanuw::CEAddressString::Lexer(str);
            lexer.makeTokens(tokens);
            tokens->pop_back(); // remove last EOF token
            return;
          }
          else if (ajanuw::SSString::startWith(str, "0x") || isHex(str))
          {
            type = TT::HEX;
          }
          else
          {
            type = TT::METHOD;
          }
        }

        tokens->push_back(new Token(type, str, posStart, pos));
      }
    };

    enum class NT
    {
      MODULE,
      SYMBOL,
      HEX,
      MMETHOD,
      METHOD,
      UNARY,
      BINARY,
      POINTER
    };
    class BaseNode
    {
    public:
      Position *posStart;
      Position *posEnd;
      BaseNode(Position *posStart, Position *posEnd) : posStart(posStart), posEnd(posEnd) {}
      virtual ~BaseNode() {}
      virtual NT id() = 0;
    };

    class ModuleNode : public BaseNode
    {
    public:
      Token *token;
      ModuleNode(Token *token) : BaseNode(token->posStart, token->posEnd), token(token) {}

      ~ModuleNode()
      {
        delete token;
      }

      NT id()
      {
        return NT::MODULE;
      }
    };

    class SymbolNode : public BaseNode
    {
    public:
      Token *token;
      SymbolNode(Token *token)
          : BaseNode(token->posStart, token->posEnd), token(token) {}

      ~SymbolNode()
      {
        delete token;
      }
      NT id()
      {
        return NT::SYMBOL;
      }
    };

    class HexNode : public BaseNode
    {
    public:
      Token *token;
      HexNode(Token *token)
          : BaseNode(token->posStart, token->posEnd), token(token) {}
      ~HexNode()
      {
        delete token;
      }
      NT id()
      {
        return NT::HEX;
      }
    };

    class MMethodNode : public BaseNode
    {
    public:
      Token *token;
      MMethodNode(Token *token)
          : BaseNode(token->posStart, token->posEnd), token(token) {}
      ~MMethodNode()
      {
        delete token;
      }
      NT id()
      {
        return NT::MMETHOD;
      }
    };

    class MethodNode : public BaseNode
    {
    public:
      Token *token;
      MethodNode(Token *token)
          : BaseNode(token->posStart, token->posEnd), token(token) {}
      ~MethodNode()
      {
        delete token;
      }

      NT id()
      {
        return NT::METHOD;
      }
    };

    class UnaryNode : public BaseNode
    {
    public:
      Token *op;
      BaseNode *node;
      UnaryNode(Token *op, BaseNode *node)
          : BaseNode(op->posStart, op->posEnd), op(op), node(node) {}

      ~UnaryNode()
      {
        delete op;
        delete node;
      }

      NT id()
      {
        return NT::UNARY;
      }
    };

    class BinaryNode : public BaseNode
    {
    public:
      BaseNode *left;
      Token *op;
      BaseNode *right;
      BinaryNode(BaseNode *left, Token *op, BaseNode *right)
          : BaseNode(left->posStart, right->posEnd), left(left), op(op), right(right) {}
      ~BinaryNode()
      {
        delete left;
        delete op;
        delete right;
      }

      NT id()
      {
        return NT::BINARY;
      }
    };

    class PointerNode : public BaseNode
    {
    public:
      BaseNode *node;
      PointerNode(BaseNode *node)
          : BaseNode(node->posStart, node->posEnd), node(node) {}
      ~PointerNode()
      {
        delete node;
      }
      NT id()
      {
        return NT::POINTER;
      }
    };

    class Parser
    {
    public:
      size_t index = -1;
      Token *curToken = nullptr;
      std::vector<Token *> *tokens;
      Parser(std::vector<Token *> *tokens) : tokens(tokens)
      {
        advance();
      }

      void advance()
      {
        index++;
        curToken = index < tokens->size() ? tokens->at(index) : nullptr;
      }

      uint8_t getUnaryOperatorPrecedence(ajanuw::CEAddressString::Token *token)
      {
        if (token->type == TT::PLUS || token->type == TT::MINUS)
        {
          return 17;
        }
        return 0;
      }

      uint8_t getBinaryOperatorPrecedence(ajanuw::CEAddressString::Token *token)
      {
        if (token->type == TT::POW)
        {
          return 16;
        }

        if (token->type == TT::MUL || token->type == TT::DIV)
        {
          return 15;
        }

        if (token->type == TT::PLUS || token->type == TT::MINUS)
        {
          return 14;
        }

        return 0;
      }

      BaseNode *parse()
      {
        BaseNode *node = binaryExpr();

        if (curToken->type != TT::END_OF_FILE)
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

      BaseNode *binaryExpr(uint8_t parentPrecedence = 0)
      {
        BaseNode *left;

        uint8_t unaryPrecedence = getUnaryOperatorPrecedence(curToken);
        if (unaryPrecedence != 0 && unaryPrecedence >= parentPrecedence)
        {
          left = unaryExpr();
        }
        else
        {
          left = atom();
        }

        while (true)
        {
          uint8_t precedence = getBinaryOperatorPrecedence(curToken);
          if (precedence == 0 || precedence <= parentPrecedence)
            break;

          auto *op = curToken;
          advance();
          BaseNode *right = binaryExpr(precedence);
          left = new BinaryNode(left, op, right);
        }

        return left;
      }

      BaseNode *unaryExpr()
      {
        auto op = curToken;
        advance();
        auto _node = atom();
        return new UnaryNode(op, _node);
      }

      BaseNode *atom()
      {
        Token *token = curToken;
        if (token->type == TT::MODULE)
        {
          advance();
          return new ModuleNode(token);
        }
        else if (token->type == TT::SYMBOL)
        {
          advance();
          return new SymbolNode(token);
        }
        else if (token->type == TT::HEX)
        {
          advance();
          return new HexNode(token);
        }
        else if (token->type == TT::MMETHOD)
        {
          advance();
          return new MMethodNode(token);
        }
        else if (token->type == TT::METHOD)
        {
          advance();
          return new MethodNode(token);
        }
        else if (token->type == TT::LPAREN)
        {
          advance();
          BaseNode *_expr = binaryExpr();
          if (curToken->type == TT::RPAREN)
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
        else if (token->type == TT::LSQUARE)
        {
          advance();
          BaseNode *_expr = binaryExpr();
          if (curToken->type == TT::RSQUARE)
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
          hProcess = GetCurrentProcess();
          pid = GetCurrentProcessId();
          isX86 = PE::isX86(pid, (HMODULE)(PE::GetModuleBase(pid).lpBaseOfDll));
        }
      }

      uintptr_t visit(BaseNode *node)
      {
        switch (node->id())
        {
        case NT::HEX:
          return std::stoull(reinterpret_cast<HexNode *>(node)->token->value, nullptr, 16);

        case NT::SYMBOL:
          return (uintptr_t)ajanuw::Symbol::get(reinterpret_cast<SymbolNode *>(node)->token->value);

        case NT::MODULE:
        {
          std::string modName = reinterpret_cast<ModuleNode *>(node)->token->value;
          HMODULE hModule = (HMODULE)(PE::GetModuleInfo(ajanuw::SSString::strToWstr(modName), pid).lpBaseOfDll);
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

        case NT::MMETHOD:
        {
          std::vector<std::string> r = ajanuw::SSString::split(reinterpret_cast<MMethodNode *>(node)->token->value, std::regex("\\."));
          std::string mod = r.at(0) + ".dll";
          std::string met = r.at(1);
          HMODULE hModule = (HMODULE)(PE::GetModuleInfo(ajanuw::SSString::strToWstr(mod), pid).lpBaseOfDll);
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

          uintptr_t hMethod = (uintptr_t)PE::GetProcAddress(pid, hModule, met);

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

        case NT::METHOD:
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
                r = (uintptr_t)PE::GetProcAddress(pid, (HMODULE)me.modBaseAddr, met);
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

        case NT::UNARY:
        {
          uintptr_t value = visit(reinterpret_cast<UnaryNode *>(node)->node);
          if (reinterpret_cast<UnaryNode *>(node)->op->type == TT::MINUS)
          {
            return value * -1;
          }
          return value;
        }

        case NT::POINTER:
        {
          uintptr_t address = visit(reinterpret_cast<PointerNode *>(node)->node);
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

        case NT::BINARY:
        {
          auto n = reinterpret_cast<BinaryNode *>(node);
          uintptr_t left = visit(n->left);
          uintptr_t right = visit(n->right);

          switch (n->op->type)
          {
          case TT::PLUS:
            return left + right;
          case TT::MINUS:
            return left - right;
          case TT::MUL:
            return left * right;
          case TT::DIV:
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
          case TT::POW:
            return pow(left, right);

          default:
            throw std::exception(RuntimeError(
                                     node->posStart,
                                     node->posEnd,
                                     "Unexpected Binary Node")
                                     .toString()
                                     .c_str());
            break;
          }
        };
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
        bSuccess = ReadProcessMemory(hProcess, addr, origenBytes.data(), size, NULL);
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
      virtual void enableHook() = 0;
    };
    class SetNop : public HookBase
    {
    public:
      SetNop(HANDLE hProcess, BYTE *addr, size_t size) : HookBase(hProcess, addr, size)
      {
      }
      void enableHook(){};
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
