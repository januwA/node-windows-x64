#include "ajanuw.h"

std::string ajanuw::SSString::strFormNumber(uintptr_t number, bool isHex)
{
  std::stringstream stream;
  if (isHex)
  {
    stream << std::hex << number;
  }
  else
  {
    stream << number;
  }
  return stream.str();
}

std::string ajanuw::SSString::tolower(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(),
                 // static_cast<int(*)(int)>(std::tolower)         // wrong
                 // [](int c){ return std::tolower(c); }           // wrong
                 // [](char c){ return std::tolower(c); }          // wrong
                 [](unsigned char c) { return std::tolower(c); } // correct
  );
  return s;
}

std::string ajanuw::SSString::toupper(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(),
                 // static_cast<int(*)(int)>(std::tolower)         // wrong
                 // [](int c){ return std::tolower(c); }           // wrong
                 // [](char c){ return std::tolower(c); }          // wrong
                 [](unsigned char c) { return std::toupper(c); } // correct
  );
  return s;
}

std::string ajanuw::SSString::pad(std::string str, size_t size, std::string padStr = " ", bool isStart = true)
{
  if (str.size() >= size)
    return std::string(str.begin(), str.end());

  std::string pad = "";
  while (true)
  {
    size_t overflowSize = padStr.size() + pad.size() + str.size() - size;
    if (overflowSize > 0)
    {
      pad += padStr.substr(0, padStr.size() - overflowSize);
    }
    else
    {
      pad += padStr;
    }
    if (pad.size() + str.size() >= size)
      return isStart ? pad + str : str + pad;
  }
}

std::string ajanuw::SSString::padStart(std::string str, size_t size, std::string padStr = " ")
{
  return ajanuw::SSString::pad(str, size, padStr);
}

std::string ajanuw::SSString::padEnd(std::string str, size_t size, std::string padStr = " ")
{
  return ajanuw::SSString::pad(str, size, padStr, false);
}

std::string ajanuw::SSString::repeat(std::string str, size_t len)
{
  std::string r;

  while (len > 0)
  {
    r += str;
    len--;
  }

  return r;
}

bool ajanuw::SSString::startWith(std::string str, const char *s2)
{
  return ajanuw::SSString::search(str, std::regex("^" + std::string(s2)));
}

bool ajanuw::SSString::endWith(std::string str, const char *s2)
{
  return ajanuw::SSString::search(str, std::regex(std::string(s2) + "$"));
}

bool ajanuw::SSString::search(std::string str, std::regex reg)
{
  return std::regex_search(str, reg);
}

std::string ajanuw::SSString::trim(std::string str)
{
  return std::regex_replace(str, std::regex("^\\s+|\\s+$"), "");
}
std::string ajanuw::SSString::trimStart(std::string str)
{
  return std::regex_replace(str, std::regex("^\\s+"), "");
}
std::string ajanuw::SSString::trimEnd(std::string str)
{
  return std::regex_replace(str, std::regex("\\s+$"), "");
}
std::vector<std::string> ajanuw::SSString::split(std::string str, std::regex reg)
{
  std::smatch m;
  std::string::const_iterator iterStart = str.begin();
  std::string::const_iterator iterEnd = str.end();

  std::vector<std::string> resultSplitList = {};

  while (std::regex_search(iterStart, iterEnd, m, reg))
  {
    resultSplitList.emplace_back(iterStart, m[0].first);
    iterStart = m[0].second;
  }
  resultSplitList.emplace_back(iterStart, iterEnd);
  return resultSplitList;
}
std::vector<BYTE> ajanuw::SSString::toBytes(std::string byteStr)
{
  byteStr = ajanuw::SSString::trim(byteStr);
  std::vector<std::string> byteStrList = ajanuw::SSString::split(byteStr, std::regex("[\\s\\n]+"));
  std::vector<BYTE> byteValList = {};
  for (size_t i = 0; i < byteStrList.size(); i++)
  {
    byteValList.push_back(std::stoi(byteStrList[i], nullptr, 16));
  }
  return byteValList;
}
char *ajanuw::SSString::setLocale(int _Category, const char *_Locale)
{
  return setlocale(_Category, _Locale);
}
BOOL ajanuw::SSString::cmp(const char *s1, const char *s2)
{
  return strncmp(s1, s2, len(s2)) == 0;
}

BOOL ajanuw::SSString::cmp(std::string s1, std::string s2)
{
  return strncmp(s1.c_str(), s2.c_str(), s2.size()) == 0;
}

BOOL ajanuw::SSString::cmp(const wchar_t *s1, const wchar_t *s2)
{
  return wcsncmp(s1, s2, len(s2)) == 0;
}

BOOL ajanuw::SSString::cmp(std::wstring s1, std::wstring s2)
{
  return wcsncmp(s1.c_str(), s2.c_str(), s2.size()) == 0;
}

BOOL ajanuw::SSString::cmp(const char16_t *s1, const char16_t *s2)
{
  return wcsncmp((wchar_t *)s1, (wchar_t *)s2, len(s2)) == 0;
}

BOOL ajanuw::SSString::cmp(std::u16string s1, std::u16string s2)
{
  return wcsncmp((wchar_t *)s1.c_str(), (wchar_t *)s2.c_str(), s2.size()) == 0;
}

BOOL ajanuw::SSString::icmp(const char *s1, const char *s2)
{
  return _stricmp(s1, s2) == 0;
}

BOOL ajanuw::SSString::icmp(std::string s1, std::string s2)
{
  return _stricmp(s1.c_str(), s2.c_str()) == 0;
}

BOOL ajanuw::SSString::icmp(const wchar_t *s1, const wchar_t *s2)
{
  return _wcsicmp(s1, s2) == 0;
}

BOOL ajanuw::SSString::icmp(std::wstring s1, std::wstring s2)
{
  return _wcsicmp(s1.c_str(), s2.c_str()) == 0;
}

BOOL ajanuw::SSString::icmp(const char16_t *s1, const char16_t *s2)
{
  return _wcsicmp((wchar_t *)s1, (wchar_t *)s2) == 0;
}

BOOL ajanuw::SSString::icmp(std::u16string s1, std::u16string s2)
{
  return _wcsicmp((wchar_t *)s1.c_str(), (wchar_t *)s2.c_str()) == 0;
}

size_t ajanuw::SSString::len(const char *str)
{
  return strlen(str);
}
size_t ajanuw::SSString::len(const char *str, size_t maxSize)
{
  return strnlen_s(str, maxSize);
}
size_t ajanuw::SSString::len(const wchar_t *str)
{
  return wcslen(str);
}
size_t ajanuw::SSString::len(const wchar_t *str, size_t maxSize)
{
  return wcsnlen_s(str, maxSize);
}

size_t ajanuw::SSString::len(std::string str)
{
  return str.length();
}
size_t ajanuw::SSString::len(std::wstring str)
{
  return str.length();
}
size_t ajanuw::SSString::len(std::u16string str)
{
  return str.length();
}

size_t ajanuw::SSString::count(const char *str)
{
  return len(str);
}

size_t ajanuw::SSString::count(const char *str, size_t maxSize)
{
  return len(str, maxSize);
}

size_t ajanuw::SSString::count(const wchar_t *str)
{
  return len(str) * 2;
}

size_t ajanuw::SSString::count(const wchar_t *str, size_t maxSize)
{
  return len(str, maxSize) * 2;
}

size_t ajanuw::SSString::count(std::string str)
{
  return len(str);
}

size_t ajanuw::SSString::count(std::wstring str)
{
  return len(str) * 2;
}

size_t ajanuw::SSString::count(std::u16string str)
{
  return len(str) * 2;
}

LPVOID ajanuw::createCallback(void *lpCallback, size_t index, void *vCC)
{
  using namespace asmjit;
  using namespace asmjit::x86;

  Environment env = hostEnvironment();
  CodeHolder code;
  code.init(env);
  x86::Assembler a(&code);

  a.push(rbp);
  a.mov(rbp, rsp);
  a.sub(rsp, 32);

  a.mov(ptr(rsp), rcx);
  a.mov(ptr(rsp, 8), rdx);
  a.mov(ptr(rsp, 0x10), r8);
  a.mov(ptr(rsp, 0x18), r9);

  a.sub(rsp, 32);

  a.mov(rcx, vCC);           // callback 列表
  a.mov(rdx, imm(index));    // callback index
  a.lea(r8, ptr(rsp, 32));   // 前4个参数指针
  a.lea(r9, ptr(rbp, 0x30)); // 之后的参数指针
  a.mov(rax, lpCallback);
  a.call(rax);

  a.add(rsp, 32 * 2);
  a.mov(rsp, rbp);
  a.pop(rbp);
  a.ret();

  size_t codeSize = code.codeSize();
  LPVOID p = ajanuw::Mem::alloc(codeSize);
  code.relocateToBase((uint64_t)p);
  code.copyFlattenedData(p, codeSize, CodeHolder::kCopyPadSectionBuffer);
  return p;
}

std::wstring ajanuw::SSString::strToWstr(std::string str)
{
  std::wstring wideStr;
  wideStr.resize(str.length());
  MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), (LPWSTR)wideStr.data(), wideStr.length());
  return wideStr;
}

std::u16string ajanuw::SSString::strToUstr(std::string str)
{
  std::u16string wideStr{0};
  wideStr.resize(str.length());
  MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), (LPWSTR)wideStr.data(), wideStr.length());
  return wideStr;
}

std::string ajanuw::SSString::ustrToStr(std::u16string ustr)
{
  std::string str{0};
  str.resize(ustr.length() * 2);
  WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)ustr.data(), ustr.length(), (LPSTR)str.data(), str.length(), 0, 0);
  return str;
}

std::wstring ajanuw::SSString::ustrToWstr(std::u16string ustr)
{
  std::wstring str;
  str.resize(ustr.length());
  std::memcpy((BYTE *)str.data(), (BYTE *)ustr.data(), str.length());
  return str;
}

std::u16string ajanuw::SSString::wstrToUstr(std::wstring wstr)
{
  std::u16string ustr;
  ustr.resize(wstr.length());
  std::memcpy((BYTE *)ustr.data(), (BYTE *)wstr.data(), ustr.length());
  return ustr;
}

std::string ajanuw::SSString::wstrToStr(std::wstring wstr)
{
  std::string str{0};
  str.resize(wstr.length() * 2);
  WideCharToMultiByte(CP_UTF8, 0, wstr.data(), wstr.length(), (LPSTR)str.data(), str.length(), 0, 0);
  return str;
}

void ajanuw::SSString::strToMem(void *dst, std::string str)
{
  memcpy_s(dst, str.length(), str.c_str(), str.length());
}

void ajanuw::SSString::strToMem(void *dst, std::wstring str)
{
  memcpy_s(dst, str.length() * 2, str.c_str(), str.length() * 2);
}

void ajanuw::SSString::strToMem(void *dst, std::u16string str)
{
  memcpy_s(dst, str.length() * 2, str.c_str(), str.length() * 2);
}

std::string ajanuw::SSString::strFormMem(void *src, size_t max)
{
  std::string str;
  uintptr_t addr = (uintptr_t)src;
  while (true)
  {
    BYTE wc = *(BYTE *)addr;
    if (wc == NULL || max == 0)
      break;
    str.push_back(wc);
    addr++;
    max--;
  }
  str.push_back(0);
  return str;
}

std::wstring ajanuw::SSString::wstrFormMem(void *src, size_t max)
{
  std::wstring wstr;
  uintptr_t addr = (uintptr_t)src;
  while (true)
  {
    wchar_t wc = *(wchar_t *)addr;
    if (wc == NULL || max == 0)
      break;
    wstr.push_back(wc);
    addr += sizeof(wchar_t);
    max--;
  }
  wstr.push_back(0);
  return wstr;
}

std::u16string ajanuw::SSString::ustrFormMem(void *src, size_t max)
{
  std::u16string ustr;
  uintptr_t addr = (uintptr_t)src;
  while (true)
  {
    char16_t wc = *(char16_t *)addr;
    if (wc == NULL || max == 0)
      break;
    ustr.push_back(wc);
    addr += sizeof(char16_t);
    max--;
  }
  ustr.push_back(0);
  return ustr;
}

LPVOID ajanuw::Mem::alloc(SIZE_T dwSize, LPVOID lpAddress, DWORD flAllocationType, DWORD flProtect)
{
  return VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
}
LPVOID ajanuw::Mem::allocEx(HANDLE hProcess, SIZE_T dwSize, LPVOID lpAddress, DWORD flAllocationType, DWORD flProtect)
{
  return VirtualAllocEx(hProcess, lpAddress, dwSize, flAllocationType, flProtect);
}

BOOL ajanuw::Mem::free(LPVOID lpAddress)
{
  return VirtualFree(lpAddress, 0, MEM_RELEASE);
}

BOOL ajanuw::Mem::free(std::string CEAddressString)
{
  return ajanuw::Mem::free(ajanuw::CEAddressString::getAddress(CEAddressString));
}

BOOL ajanuw::Mem::freeEx(HANDLE hProcess, LPVOID lpAddress)
{
  return VirtualFreeEx(hProcess, lpAddress, 0, MEM_RELEASE);
}

BOOL ajanuw::Mem::freeEx(HANDLE hProcess, std::string CEAddressString)
{
  return ajanuw::Mem::freeEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString));
}

void ajanuw::Mem::write_str(void *lpAddress, std::string str)
{
  ajanuw::SSString::strToMem((void *)lpAddress, str);
}

void ajanuw::Mem::write_wstr(void *lpAddress, std::wstring str)
{
  ajanuw::SSString::strToMem((void *)lpAddress, str);
}
void ajanuw::Mem::write_ustr(void *lpAddress, std::u16string str)
{
  ajanuw::SSString::strToMem((void *)lpAddress, str);
}

void ajanuw::Mem::write_byte(void *lpAddress, BYTE byte)
{
  memset(lpAddress, byte, sizeof(BYTE));
}

void ajanuw::Mem::write_bytes(void *lpAddress, std::vector<BYTE> bytes)
{
  memcpy_s(lpAddress, bytes.size(), bytes.data(), bytes.size());
}

void ajanuw::Mem::write_word(void *lpAddress, WORD value)
{
  memcpy_s(lpAddress, sizeof(WORD), &value, sizeof(WORD));
}
void ajanuw::Mem::write_dword(void *lpAddress, DWORD value)
{
  memcpy_s(lpAddress, sizeof(DWORD), &value, sizeof(DWORD));
}
void ajanuw::Mem::write_qword(void *lpAddress, uint64_t value)
{
  memcpy_s(lpAddress, sizeof(uint64_t), &value, sizeof(uint64_t));
}
void ajanuw::Mem::write_float(void *lpAddress, float value)
{
  memcpy_s(lpAddress, sizeof(float), &value, sizeof(float));
}
void ajanuw::Mem::write_double(void *lpAddress, double value)
{
  memcpy_s(lpAddress, sizeof(double), &value, sizeof(double));
}
void ajanuw::Mem::write_region_to_file(std::string filename, void *lpAddress, uintptr_t size)
{
  std::ofstream outFile;
  outFile.open(filename.c_str());
  for (int i = 0; i < size; i++)
    outFile << *(BYTE *)((uintptr_t)lpAddress + i);
  outFile.close();
}

void ajanuw::Mem::write_str(std::string CEAddressString, std::string str)
{
  ajanuw::Mem::write_str(ajanuw::CEAddressString::getAddress(CEAddressString), str);
}

void ajanuw::Mem::write_wstr(std::string CEAddressString, std::wstring str)
{
  ajanuw::Mem::write_wstr(ajanuw::CEAddressString::getAddress(CEAddressString), str);
}

void ajanuw::Mem::write_ustr(std::string CEAddressString, std::u16string str)
{
  ajanuw::Mem::write_ustr(ajanuw::CEAddressString::getAddress(CEAddressString), str);
}

void ajanuw::Mem::write_byte(std::string CEAddressString, BYTE byte)
{
  ajanuw::Mem::write_byte(ajanuw::CEAddressString::getAddress(CEAddressString), byte);
}

void ajanuw::Mem::write_bytes(std::string CEAddressString, std::vector<BYTE> bytes)
{
  ajanuw::Mem::write_bytes(ajanuw::CEAddressString::getAddress(CEAddressString), bytes);
}

void ajanuw::Mem::write_word(std::string CEAddressString, WORD value)
{
  ajanuw::Mem::write_word(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}

void ajanuw::Mem::write_dword(std::string CEAddressString, DWORD value)
{
  ajanuw::Mem::write_dword(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}

void ajanuw::Mem::write_qword(std::string CEAddressString, uint64_t value)
{
  ajanuw::Mem::write_qword(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}

void ajanuw::Mem::write_float(std::string CEAddressString, float value)
{
  ajanuw::Mem::write_float(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}

void ajanuw::Mem::write_double(std::string CEAddressString, double value)
{
  ajanuw::Mem::write_double(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}

void ajanuw::Mem::write_region_to_file(std::string filename, std::string CEAddressString, uintptr_t size)
{
  ajanuw::Mem::write_region_to_file(filename, ajanuw::CEAddressString::getAddress(CEAddressString), size);
}

std::string ajanuw::Mem::read_str(char *lpAddress, uintptr_t max)
{
  return ajanuw::SSString::strFormMem(lpAddress, max);
}
std::wstring ajanuw::Mem::read_wstr(wchar_t *lpAddress, uintptr_t max)
{
  return ajanuw::SSString::wstrFormMem(lpAddress, max);
}
std::u16string ajanuw::Mem::read_ustr(char16_t *lpAddress, uintptr_t max)
{
  return ajanuw::SSString::ustrFormMem(lpAddress, max);
}
std::string ajanuw::Mem::read_str(std::string CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::read_str((char *)ajanuw::CEAddressString::getAddress(CEAddressString), max);
}
std::wstring ajanuw::Mem::read_wstr(std::string CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::read_wstr((wchar_t *)ajanuw::CEAddressString::getAddress(CEAddressString), max);
}
std::u16string ajanuw::Mem::read_ustr(std::string CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::read_ustr((char16_t *)ajanuw::CEAddressString::getAddress(CEAddressString), max);
}
std::vector<BYTE> ajanuw::Mem::read_bytes(void *lpAddress, uintptr_t size)
{
  std::vector<BYTE> bytes(size);
  memcpy_s(bytes.data(), size, lpAddress, size);
  return bytes;
}

BYTE ajanuw::Mem::read_byte(void *lpAddress)
{
  return *(BYTE *)lpAddress;
}

WORD ajanuw::Mem::read_word(void *lpAddress)
{
  return *(WORD *)lpAddress;
}
DWORD ajanuw::Mem::read_dword(void *lpAddress)
{
  return *(DWORD *)lpAddress;
}
uint64_t ajanuw::Mem::read_qword(void *lpAddress)
{
  return *(uint64_t *)lpAddress;
}

uintptr_t ajanuw::Mem::read_pointer(void *lpAddress)
{
  return *(uintptr_t *)lpAddress;
}

float ajanuw::Mem::read_float(void *lpAddress)
{
  return *(float *)lpAddress;
}

double ajanuw::Mem::read_double(void *lpAddress)
{
  return *(double *)lpAddress;
}

void ajanuw::Mem::read_region_from_file(std::string fileame, void *lpAddress)
{
  read_region_from_file(fileame, lpAddress, NULL);
}

void ajanuw::Mem::read_region_from_file(std::string fileame, void *lpAddress, size_t *fileSize)
{
  std::ifstream inFile;
  inFile.open(fileame);
  uintptr_t offset = (uintptr_t)lpAddress;
  while (inFile.good())
  {
    char r = inFile.get();
    if (inFile.eof())
      break;
    memset((void *)offset, r, sizeof(BYTE));
    offset += sizeof(BYTE);
    if (fileSize)
      (*fileSize)++;
  }
  inFile.close();
}

std::vector<BYTE> ajanuw::Mem::read_bytes(std::string CEAddressString, uintptr_t size)
{
  return ajanuw::Mem::read_bytes(ajanuw::CEAddressString::getAddress(CEAddressString), size);
}

BYTE ajanuw::Mem::read_byte(std::string CEAddressString)
{
  return ajanuw::Mem::read_byte(ajanuw::CEAddressString::getAddress(CEAddressString));
}

WORD ajanuw::Mem::read_word(std::string CEAddressString)
{
  return ajanuw::Mem::read_word(ajanuw::CEAddressString::getAddress(CEAddressString));
}

DWORD ajanuw::Mem::read_dword(std::string CEAddressString)
{
  return ajanuw::Mem::read_dword(ajanuw::CEAddressString::getAddress(CEAddressString));
}

uint64_t ajanuw::Mem::read_qword(std::string CEAddressString)
{
  return ajanuw::Mem::read_qword(ajanuw::CEAddressString::getAddress(CEAddressString));
}

uintptr_t ajanuw::Mem::read_pointer(std::string CEAddressString)
{
  return ajanuw::Mem::read_pointer(ajanuw::CEAddressString::getAddress(CEAddressString));
}

float ajanuw::Mem::read_float(std::string CEAddressString)
{
  return ajanuw::Mem::read_float(ajanuw::CEAddressString::getAddress(CEAddressString));
}

double ajanuw::Mem::read_double(std::string CEAddressString)
{
  return ajanuw::Mem::read_double(ajanuw::CEAddressString::getAddress(CEAddressString));
}

void ajanuw::Mem::read_region_from_file(std::string fileame, std::string CEAddressString)
{
  ajanuw::Mem::read_region_from_file(fileame, ajanuw::CEAddressString::getAddress(CEAddressString));
}

void ajanuw::Mem::read_region_from_file(std::string fileame, std::string CEAddressString, size_t *fileSize)
{
  ajanuw::Mem::read_region_from_file(fileame, ajanuw::CEAddressString::getAddress(CEAddressString), fileSize);
}

std::map<HWND, uintptr_t> ajanuw::Gui::Win32::Win32::hwndMap;

int ajanuw::Gui::Win32::messageLoop()
{
  MSG msg;
  while (GetMessage(&msg, nullptr, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return (int)msg.wParam;
}

LRESULT ajanuw::Gui::Win32::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT r = 0;
  if (Gui::Win32::Win32::hwndMap.size())
  {
    auto self = (Gui::Win32 *)Gui::Win32::Win32::hwndMap.at(hWnd);
    r = self->OnReceiveMessage(hWnd, message, wParam, lParam);
  }

  // 自动处理一些默认事件
  if (r == 0)
  {
    switch (message)
    {
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }
  }
  return r;
}

LRESULT ajanuw::Gui::Win32::OnReceiveMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  return 0;
}

ATOM ajanuw::Gui::Win32::initRegisterClass()
{
  WNDCLASSEXA wcex{0};
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = NULL;
  wcex.hIcon = NULL;
  wcex.lpszMenuName = NULL;
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszClassName = className_.c_str();
  return RegisterClassExA(&wcex);
}

BOOL ajanuw::Gui::Win32::initWindow()
{
  hWnd_ = CreateWindowA(
      className_.c_str(),
      windowName_.c_str(),
      style_,
      x_, y_,
      width_, height_,
      NULL, NULL, NULL, NULL);

  if (!hWnd_)
    return FALSE;
  std::wstring ws = ajanuw::SSString::strToWstr(windowName_);
  SetWindowTextW(hWnd_, ws.c_str());
  hwndMap.insert(std::pair<HWND, uintptr_t>(hWnd_, (uintptr_t)this));
  ShowWindow(hWnd_, SW_RESTORE);
  UpdateWindow(hWnd_);
  return TRUE;
}

std::vector<WORD> ajanuw::Gui::Win32::getHLMessage(DWORD message)
{
  return std::vector<WORD>{HIWORD(message), LOWORD(message)};
}

bool ajanuw::Gui::Win32::getCheck(HWND hWnd)
{
  return Button_GetCheck(hWnd);
}

DWORD ajanuw::Gui::Win32::rgb(DWORD r, DWORD g, DWORD b)
{
  return RGB(r, g, b);
}

HWND ajanuw::Gui::Win32::createWindow(Win32CreateOption opt)
{
  HWND hWnd = CreateWindowA(opt.className.c_str(), opt.windowName.c_str(),
                            opt.style,
                            opt.x, opt.y,
                            opt.width, opt.height,
                            opt.parent ? opt.parent : hWnd_,
                            opt.id,
                            NULL, NULL);
  std::wstring ws = ajanuw::SSString::strToWstr(opt.windowName);
  SetWindowTextW(hWnd, ws.c_str());
  return hWnd;
}

HWND ajanuw::Gui::Win32::button(Win32CreateOption opt)
{
  opt.className = "button";
  opt.style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_MULTILINE | opt.style;
  return ajanuw::Gui::Win32::createWindow(opt);
}

HWND ajanuw::Gui::Win32::checkbox(Win32CreateOption opt)
{
  opt.className = "button";
  opt.style = WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_CENTER | BS_MULTILINE | opt.style;
  return ajanuw::Gui::Win32::createWindow(opt);
}

HWND ajanuw::Gui::Win32::radio(Win32CreateOption opt)
{
  opt.className = "button";
  opt.style = WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_CENTER | BS_MULTILINE | opt.style;
  return ajanuw::Gui::Win32::createWindow(opt);
}
HWND ajanuw::Gui::Win32::groupbox(Win32CreateOption opt)
{
  opt.className = "button";
  opt.style = WS_CHILD | WS_VISIBLE | BS_GROUPBOX | BS_MULTILINE | opt.style;
  return ajanuw::Gui::Win32::createWindow(opt);
}

HWND ajanuw::Gui::Win32::text(Win32CreateOption opt)
{
  opt.className = "static";
  opt.style = WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOTIFY | SS_SIMPLE | opt.style;
  return ajanuw::Gui::Win32::createWindow(opt);
}

HWND ajanuw::Gui::Win32::input(Win32CreateOption opt)
{
  opt.className = "edit";
  opt.style = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | opt.style;
  return ajanuw::Gui::Win32::createWindow(opt);
}

HWND ajanuw::Gui::Win32::textarea(Win32CreateOption opt)
{
  opt.className = "edit";
  opt.style = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | opt.style;
  return ajanuw::Gui::Win32::createWindow(opt);
}
HWND ajanuw::Gui::Win32::listbox(Win32CreateOption opt)
{
  opt.className = "LISTBOX";
  opt.style = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY | opt.style;
  return ajanuw::Gui::Win32::createWindow(opt);
}
HWND ajanuw::Gui::Win32::select(Win32CreateOption opt)
{
  opt.className = "combobox";
  opt.style = WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | opt.style;
  return ajanuw::Gui::Win32::createWindow(opt);
}

ajanuw::Mem::VAManage::VAManage(size_t size) : size_(size),
                                               position_(0),
                                               memory_(ajanuw::Mem::alloc(size))
{
  if (memory_ == NULL)
  {
    printf("VAManage alloc fail.");
    throw 1;
  }
}

uint8_t *ajanuw::Mem::VAManage::ptr_()
{
  return (BYTE *)memory_ + position_;
}

std::vector<uint8_t> ajanuw::Mem::VAManage::read(size_t size)
{
  std::vector<uint8_t> table;
  for (size_t i = 0; i < size; i++)
    table.push_back(ajanuw::Mem::read_byte(ptr_() + i));
  return table;
}

uint8_t ajanuw::Mem::VAManage::readByte()
{
  return ajanuw::Mem::read_byte(ptr_());
}

uint16_t ajanuw::Mem::VAManage::readWord()
{
  return ajanuw::Mem::read_word(ptr_());
}

uint32_t ajanuw::Mem::VAManage::readDword()
{
  return ajanuw::Mem::read_dword(ptr_());
}

uint64_t ajanuw::Mem::VAManage::readQword()
{
  return ajanuw::Mem::read_qword(ptr_());
}

float ajanuw::Mem::VAManage::readFloat()
{
  return ajanuw::Mem::read_float(ptr_());
}

double ajanuw::Mem::VAManage::readDouble()
{
  return ajanuw::Mem::read_double(ptr_());
}

std::string ajanuw::Mem::VAManage::readStr(size_t maxSize)
{
  return ajanuw::Mem::read_str((char *)ptr_(), maxSize);
}

std::wstring ajanuw::Mem::VAManage::readWstr(size_t maxSize)
{
  return ajanuw::Mem::read_wstr((wchar_t *)ptr_(), maxSize);
}

std::u16string ajanuw::Mem::VAManage::readUstr(size_t maxSize)
{
  return ajanuw::Mem::read_ustr((char16_t *)ptr_(), maxSize);
}

void ajanuw::Mem::VAManage::write(std::vector<uint8_t> table, size_t count)
{
  if (count < table.size())
  {
    table.resize(count);
  }
  ajanuw::Mem::write_bytes(ptr_(), table);
  position_ += table.size();
}

void ajanuw::Mem::VAManage::writeByte(uint8_t v)
{
  ajanuw::Mem::write_byte(ptr_(), v);
  position_++;
}

void ajanuw::Mem::VAManage::writeWord(uint16_t v)
{
  ajanuw::Mem::write_word(ptr_(), v);
  position_ += sizeof(uint16_t);
}

void ajanuw::Mem::VAManage::writeDword(uint32_t v)
{
  ajanuw::Mem::write_dword(ptr_(), v);
  position_ += sizeof(uint32_t);
}

void ajanuw::Mem::VAManage::writeQword(uintptr_t v)
{
  ajanuw::Mem::write_qword(ptr_(), v);
  position_ += sizeof(uint64_t);
}

void ajanuw::Mem::VAManage::writeFloat(float v)
{
  ajanuw::Mem::write_float(ptr_(), v);
  position_ += sizeof(float);
}

void ajanuw::Mem::VAManage::writeDouble(double v)
{
  ajanuw::Mem::write_double(ptr_(), v);
  position_ += sizeof(double);
}

void ajanuw::Mem::VAManage::writeStr(std::string str)
{
  ajanuw::Mem::write_str(ptr_(), str);
  position_ += ajanuw::SSString::count(str);
}

void ajanuw::Mem::VAManage::writeWstr(std::wstring wstr)
{
  ajanuw::Mem::write_wstr(ptr_(), wstr);
  position_ += ajanuw::SSString::count(wstr);
}

void ajanuw::Mem::VAManage::writeUstr(std::u16string ustr)
{
  ajanuw::Mem::write_ustr(ptr_(), ustr);
  position_ += ajanuw::SSString::count(ustr);
}

void ajanuw::Mem::VAManage::loadFromFile(std::string filename)
{
  ajanuw::Mem::read_region_from_file(filename, ptr_(), &position_);
}

void ajanuw::Mem::VAManage::saveToFile(std::string filename)
{
  ajanuw::Mem::write_region_to_file(filename, ptr_(), size_);
}

BOOL ajanuw::Mem::VAManage::destroy()
{
  if (memory_)
    return ajanuw::Mem::free(memory_);
  else
    return FALSE;
}

uintptr_t ajanuw::Asm::AAScript::aa(std::string asmString, uintptr_t rcx = 0)
{
  JitRuntime rt;
  CodeHolder code;
  code.init(rt.environment());

  x86::Assembler a(&code);
  AsmParser p(&a);

  asmjit::Error err = p.parse(asmString.c_str());
  if (err)
  {
    char msg[100];
    sprintf(msg, "AsmParser ERROR: %08x (%s)\n", err, DebugUtils::errorAsString(err));
    throw std::exception(msg);
  }

  Func fn;
  rt.add(&fn, &code);

  uintptr_t r = fn(rcx);
  rt.release(fn);
  return r;
}

std::vector<BYTE> ajanuw::Asm::AAScript::asmBytes(std::string asmString, bool isX64)
{

  CodeHolder code;
  Environment env = hostEnvironment();
  if (isX64)
  {
    env.setArch(Environment::kArchX64);
  }
  else
  {
    env.setArch(Environment::kArchX86);
  }
  code.init(env);

  x86::Assembler a(&code);
  AsmParser p(&a);
  asmjit::Error err = p.parse(asmString.c_str());
  if (err)
  {
    char msg[100];
    sprintf(msg, "AsmParser ERROR: %08x (%s)\n", err, DebugUtils::errorAsString(err));
    throw std::exception(msg);
  }

  std::vector<BYTE> r(a.offset());
  memcpy_s(r.data(), r.size(), a.bufferData(), r.size());
  return r;
}

std::map<std::string, LPVOID> ajanuw::Symbol::_symbolMap;
void ajanuw::Symbol::registerSymbol(std::string symbolname, LPVOID address)
{
  ajanuw::Symbol::_symbolMap[symbolname] = address;
}

void ajanuw::Symbol::unregisterSymbol(std::string symbolname)
{
  ajanuw::Symbol::_symbolMap.erase(symbolname);
}

LPVOID ajanuw::Symbol::get(std::string symbolname)
{
  if (ajanuw::Symbol::_symbolMap.count(symbolname) == NULL)
    return NULL;
  return ajanuw::Symbol::_symbolMap.at(symbolname);
}

bool ajanuw::Symbol::has(std::string symbolname)
{
  return ajanuw::Symbol::_symbolMap.count(symbolname) != NULL;
}

LPVOID ajanuw::CEAddressString::getAddress(std::string CEAddressString, HANDLE hProcess)
{
  try
  {
    Lexer lexer = ajanuw::CEAddressString::Lexer(CEAddressString);
    std::vector<Token *> tokens = lexer.makeTokens();

    /*
     for (auto token : tokens)
       printf("%s ", token->toString().c_str());
     printf("\n");
    */

    Parser parser = Parser(tokens);
    CEAddressStringNode *node = parser.parse();
    // printf("node id: %d\n", node->id());

    Interpreter interpreter{hProcess};
    LPVOID addr = (LPVOID)interpreter.visit(node);

    deleteCEAddressStringNode(node);

    return addr;
  }
  catch (const std::exception &e)
  {
    throw e;
  }
}
