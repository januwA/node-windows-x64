#include "ajanuw.h"

#define uptr_size sizeof(uintptr_t)

bool ajanuw::SSString::startWith(std::string str, const char *s2)
{
  return search(str, std::regex("$" + std::string(s2)));
}

bool ajanuw::SSString::endWith(std::string str, const char *s2)
{
  return search(str, std::regex(std::string(s2) + "$"));
}

std::vector<std::string> ajanuw::SSString::match(std::string str, std::regex reg)
{
  std::smatch m;
  std::string::const_iterator iterStart = str.begin();
  std::string::const_iterator iterEnd = str.end();
  std::vector<std::string> r{};
  while (std::regex_search(iterStart, iterEnd, m, reg))
  {
    r.emplace_back(m[0].str());
    iterStart = m[0].second;
  }
  r.emplace_back(m[0].str());
  return r;
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

LPVOID ajanuw::createCallback(void *lpAddress, size_t index)
{
  std::string code_str = "55 48 8B EC 48 81 EC 90 01 00 00\n"
                         "48 89 4C 24 08 48 89 54 24 10 4C 89 44 24 18 4C 89 4C 24 20\n"
                         "48 B9 00 00 00 00 00 00 00 00 48 BA 00 00 00 00 00 00 00 00 4C 8D 44 24 08 4C 8D 4D 30\n"
                         "48 B8 F0 AC AB 14 FE 7F 00 00 FF D0\n"
                         "48 81 C4 90 01 00 00 48 8B E5 5D C3";

  std::vector<BYTE> code_bytes = ajanuw::SSString::toBytes(code_str);

  //memcpy_s(code_bytes.data() + 0x21, uptr_size, &lpCB, uptr_size); // 备用
  memcpy_s(code_bytes.data() + 0x2B, uptr_size, &index, uptr_size);
  memcpy_s(code_bytes.data() + 0x3E, uptr_size, &lpAddress, uptr_size);
  auto newmem = ajanuw::Mem::alloc(code_bytes.size() + uptr_size);
  memcpy_s(newmem, code_bytes.size(), code_bytes.data(), code_bytes.size());
  return newmem;
}

std::wstring ajanuw::SSString::strTowstr(std::string str)
{
  std::wstring wideStr;
  wideStr.resize(str.length());
  MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), (LPWSTR)wideStr.data(), wideStr.length());
  return wideStr;
}

std::u16string ajanuw::SSString::strToustr(std::string str)
{
  std::u16string wideStr{0};
  wideStr.resize(str.length());
  MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), (LPWSTR)wideStr.data(), wideStr.length());
  return wideStr;
}

std::string ajanuw::SSString::ustrTostr(std::u16string ustr)
{
  std::string str{0};
  str.resize(ustr.length() * 2);
  WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)ustr.data(), ustr.length(), (LPSTR)str.data(), str.length(), 0, 0);
  return str;
}

std::wstring ajanuw::SSString::ustrTowstr(std::u16string ustr)
{
  std::wstring str;
  str.resize(ustr.length());
  std::memcpy((BYTE *)str.data(), (BYTE *)ustr.data(), str.length());
  return str;
}

std::u16string ajanuw::SSString::wstrToustr(std::wstring wstr)
{
  std::u16string ustr;
  ustr.resize(wstr.length());
  std::memcpy((BYTE *)ustr.data(), (BYTE *)wstr.data(), ustr.length());
  return ustr;
}

std::string ajanuw::SSString::wstrTostr(std::wstring wstr)
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

std::string ajanuw::SSString::strFormMem(void *src, uintptr_t max)
{
  std::string str{0};
  uintptr_t addr = (uintptr_t)src;
  while (true)
  {
    char wc = *(char *)addr;
    if (wc == NULL || max == 0)
      break;
    str.push_back(wc);
    addr += sizeof(char);
    max--;
  }
  return str;
}

std::wstring ajanuw::SSString::wstrFormMem(void *src, uintptr_t max)
{
  std::wstring wstr{0};
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
  return wstr;
}

std::u16string ajanuw::SSString::ustrFormMem(void *src, uintptr_t max)
{
  std::u16string ustr{0};
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
  return ustr;
}

LPVOID ajanuw::Mem::alloc(SIZE_T dwSize, LPVOID lpAddress, DWORD flAllocationType, DWORD flProtect)
{
  return VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
}

BOOL ajanuw::Mem::free(LPVOID lpAddress)
{
  return VirtualFree(lpAddress, 0, MEM_RELEASE);
}

void ajanuw::Mem::write_str(void *lpAddress, std::string str)
{
  ajanuw::SSString::strToMem((void *)lpAddress, str);
}

void ajanuw::Mem::write_str(void *lpAddress, std::wstring str)
{
  ajanuw::SSString::strToMem((void *)lpAddress, str);
}
void ajanuw::Mem::write_str(void *lpAddress, std::u16string str)
{
  ajanuw::SSString::strToMem((void *)lpAddress, str);
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

std::string ajanuw::Mem::read_str(char *lpAddress, uintptr_t max)
{
  return ajanuw::SSString::strFormMem(lpAddress, max);
}
std::wstring ajanuw::Mem::read_str(wchar_t *lpAddress, uintptr_t max)
{
  return ajanuw::SSString::wstrFormMem(lpAddress, max);
}
std::u16string ajanuw::Mem::read_str(char16_t *lpAddress, uintptr_t max)
{
  return ajanuw::SSString::ustrFormMem(lpAddress, max);
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

std::map<HWND, uintptr_t> mapHwnd;

ajanuw::Gui::Win32Gui::Win32Gui(std::string className, std::string windowName)
    : x_(0), y_(0),
      width_(600), height_(400),
      style_(WS_OVERLAPPEDWINDOW),
      className_(className),
      windowName_(windowName),
      hWnd_(NULL),
      messageEvent(NULL),
      env_(NULL)
{
}

ajanuw::Gui::Win32Gui::~Win32Gui()
{
  DeleteObject(this->hWnd_);
}

int ajanuw::Gui::Win32Gui::messageLoop(Napi::Env env, Napi::Function cb)
{
  env_ = env;
  cb_ = Napi::Persistent(cb);
  MSG msg;
  while (GetMessage(&msg, nullptr, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return (int)msg.wParam;
}

LRESULT ajanuw::Gui::Win32Gui::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  if (mapHwnd.size())
  {
    auto self = (Gui::Win32Gui *)mapHwnd.at(hWnd);
    self->wndProc_(hWnd, message, wParam, lParam);
  }
  switch (message)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

void ajanuw::Gui::Win32Gui::wndProc_(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  if (this->messageEvent)
    this->messageEvent(hWnd, message, wParam, lParam);

  if (cb_)
  {
    std::vector<napi_value> args;
    args.push_back(Napi::Number::New(env_, (uintptr_t)hWnd));
    args.push_back(Napi::Number::New(env_, (uintptr_t)message));
    args.push_back(Napi::Number::New(env_, (uintptr_t)wParam));
    args.push_back(Napi::Number::New(env_, (uintptr_t)lParam));
    cb_.Call(args);
  }
}

ATOM ajanuw::Gui::Win32Gui::initRegisterClass()
{
  WNDCLASSEXA wcex{0};
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = this->WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = NULL;
  wcex.hIcon = NULL;
  wcex.lpszMenuName = NULL;
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszClassName = this->className_.c_str();
  return RegisterClassExA(&wcex);
}

BOOL ajanuw::Gui::Win32Gui::initWindow()
{
  this->hWnd_ = CreateWindowA(
      this->className_.c_str(),
      this->windowName_.c_str(),
      this->style_,
      this->x_, this->y_,
      this->width_, this->height_,
      NULL, NULL, NULL, NULL);

  if (!this->hWnd_)
    return FALSE;
  mapHwnd.insert(std::pair<HWND, uintptr_t>(this->hWnd_, (uintptr_t)this));
  ShowWindow(this->hWnd_, SW_RESTORE);
  UpdateWindow(this->hWnd_);
  return TRUE;
}

HWND ajanuw::Gui::Win32Gui::createWindow(std::string lpClassName, std::string lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HMENU hMenu)
{
  return CreateWindowA(lpClassName.c_str(), lpWindowName.c_str(),
                       dwStyle,
                       x, y,
                       nWidth, nHeight,
                       this->hWnd_,
                       hMenu,
                       NULL, NULL);
}