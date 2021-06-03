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
                 [](unsigned char c)
                 { return std::tolower(c); } // correct
  );
  return s;
}

std::string ajanuw::SSString::toupper(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c)
                 { return std::toupper(c); } // correct
  );
  return s;
}

std::wstring ajanuw::SSString::tolower(std::wstring s)
{
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c)
                 { return std::tolower(c); });
  return s;
}

std::wstring ajanuw::SSString::toupper(std::wstring s)
{
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c)
                 { return std::toupper(c); });
  return s;
}

std::string ajanuw::SSString::pad(std::string_view str, size_t size, std::string_view padStr = " ", bool isStart = true)
{
  if (str.size() >= size)
    return std::string(str.begin(), str.end());

  std::string result;
  while (true)
  {
    size_t overflowSize = padStr.size() + result.size() + str.size() - size;
    if (overflowSize > 0)
    {
      result += padStr.substr(0, padStr.size() - overflowSize);
    }
    else
    {
      result += padStr;
    }
    if (result.size() + str.size() >= size)
      return isStart ? result + str.data() : str.data() + result;
  }
}

std::string ajanuw::SSString::padStart(std::string_view str, size_t size, std::string_view padStr = " ")
{
  return ajanuw::SSString::pad(str, size, padStr);
}

std::string ajanuw::SSString::padEnd(std::string_view str, size_t size, std::string_view padStr = " ")
{
  return ajanuw::SSString::pad(str, size, padStr, false);
}

std::string ajanuw::SSString::repeat(std::string_view str, size_t len)
{
  std::string r;
  while (len--)
    r += str;
  return r;
}

std::string ajanuw::SSString::join(const std::vector<std::string> &v, std::string_view p)
{
  std::string r;
  int last = v.size() - 1;
  for (size_t i = 0, l = v.size(); i < l; i++)
  {
    r += v.at(i) + (i == last ? "" : p.data());
  }
  return r;
}

bool ajanuw::SSString::startWith(std::string_view str, std::string_view s2, size_t index)
{
  return str.find(s2) - index == 0;
}

bool ajanuw::SSString::endWith(std::string_view str, const char *s2)
{
  return str.rfind(s2) + strlen(s2) == str.size();
}

bool ajanuw::SSString::endWith(std::string_view str, const char *s2, size_t length)
{
  return str.rfind(s2) + strlen(s2) == length;
}

bool ajanuw::SSString::search(std::string_view str, const std::regex &reg)
{
  return std::regex_search(str.data(), reg);
}

bool ajanuw::SSString::search(std::wstring_view str, const std::regex &reg)
{
  return std::regex_search(std::move(ajanuw::SSString::wstrToStr(str)), reg);
}

std::string ajanuw::SSString::trim(std::string_view str)
{
  return std::regex_replace(str.data(), std::regex("^\\s+|\\s+$"), "");
}
std::string ajanuw::SSString::trimStart(std::string_view str)
{
  return std::regex_replace(str.data(), std::regex("^\\s+"), "");
}
std::string ajanuw::SSString::trimEnd(std::string_view str)
{
  return std::regex_replace(str.data(), std::regex("\\s+$"), "");
}
std::vector<std::string> ajanuw::SSString::split(const std::string &str, const std::regex &reg)
{
  std::smatch m;
  auto _start = str.begin();
  auto _end = str.end();
  std::vector<std::string> _list;

  while (std::regex_search(_start, _end, m, reg))
  {
    _list.emplace_back(_start, m[0].first);
    _start = m[0].second;
  }
  _list.emplace_back(_start, _end);
  return _list;
}
std::vector<uint8_t> ajanuw::SSString::toBytes(std::string_view byteStr)
{
  byteStr = ajanuw::SSString::trim(byteStr);
  auto byteStrList = ajanuw::SSString::split(byteStr.data(), std::regex{"[\\s\\n]+"});
  auto a = byteStrList | std::views::transform([](const std::string &s)
                                               { return std::stoi(s, nullptr, 16); });
  return std::vector<uint8_t>(a.begin(), a.end());
}
char *ajanuw::SSString::setLocale(int _Category, const char *_Locale)
{
  return setlocale(_Category, _Locale);
}

BOOL ajanuw::SSString::cmp(std::string_view s1, std::string_view s2)
{
  return strncmp(s1.data(), s2.data(), s2.size()) == 0;
}

BOOL ajanuw::SSString::cmp(std::wstring_view s1, std::wstring_view s2)
{
  return wcsncmp(s1.data(), s2.data(), s2.size()) == 0;
}

BOOL ajanuw::SSString::cmp(std::u16string_view s1, std::u16string_view s2)
{
  return wcsncmp((wchar_t *)s1.data(), (wchar_t *)s2.data(), s2.size()) == 0;
}

BOOL ajanuw::SSString::icmp(std::string_view s1, std::string_view s2)
{
  return _stricmp(s1.data(), s2.data()) == 0;
}

BOOL ajanuw::SSString::icmp(std::wstring_view s1, std::wstring_view s2)
{
  return _wcsicmp(s1.data(), s2.data()) == 0;
}

BOOL ajanuw::SSString::icmp(std::u16string_view s1, std::u16string_view s2)
{
  return _wcsicmp((wchar_t *)s1.data(), (wchar_t *)s2.data()) == 0;
}

size_t ajanuw::SSString::len(std::string_view str)
{
  return str.length();
}
size_t ajanuw::SSString::len(std::wstring_view str)
{
  return str.length();
}
size_t ajanuw::SSString::len(std::u16string_view str)
{
  return str.length();
}

size_t ajanuw::SSString::count(std::string_view str)
{
  return str.length() * sizeof(char);
}

size_t ajanuw::SSString::count(std::wstring_view str)
{
  return str.length() * sizeof(wchar_t);
}

size_t ajanuw::SSString::count(std::u16string_view str)
{
  return str.length() * sizeof(char16_t);
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

std::wstring ajanuw::SSString::strToWstr(std::string_view str)
{
  std::wstring wideStr;
  size_t size = MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), NULL, NULL);
  if (size == NULL)
    return wideStr;

  wideStr.resize(size);
  MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), (LPWSTR)wideStr.data(), wideStr.length());
  return wideStr;
}

std::u16string ajanuw::SSString::strToUstr(std::string_view str)
{
  std::u16string wideStr;
  size_t size = MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), NULL, NULL);
  if (size == NULL)
    return wideStr;

  wideStr.resize(size);
  MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), (LPWSTR)wideStr.data(), wideStr.length());
  return wideStr;
}

std::string ajanuw::SSString::ustrToStr(std::u16string_view ustr)
{
  std::string str;
  size_t size = WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)ustr.data(), ustr.length(), NULL, NULL, 0, 0);
  if (size == NULL)
    return str;

  str.resize(size);
  WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)ustr.data(), ustr.length(), (LPSTR)str.data(), str.length(), 0, 0);
  return str;
}

std::string ajanuw::SSString::wstrToStr(std::wstring_view wstr)
{
  std::string str;
  size_t size = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), wstr.length(), NULL, NULL, 0, 0);
  if (size == NULL)
    return str;

  str.resize(size);
  WideCharToMultiByte(CP_UTF8, 0, wstr.data(), wstr.length(), (LPSTR)str.data(), str.length(), 0, 0);
  return str;
}

std::wstring ajanuw::SSString::ustrToWstr(std::u16string_view ustr)
{
  return std::wstring(ustr.begin(), ustr.end());
}

std::u16string ajanuw::SSString::wstrToUstr(std::wstring_view wstr)
{
  return std::u16string(wstr.begin(), wstr.end());
}

void ajanuw::SSString::toMem(void *dst, std::string_view str)
{
  memcpy_s(dst, str.length(), str.data(), str.length());
}

void ajanuw::SSString::toMem(void *dst, std::wstring_view str)
{
  size_t count = ajanuw::SSString::count(str);
  memcpy_s(dst, count, str.data(), count);
}

void ajanuw::SSString::toMem(void *dst, std::u16string_view str)
{
  size_t count = ajanuw::SSString::count(str);
  memcpy_s(dst, count, str.data(), count);
}

void ajanuw::SSString::toMemEx(HANDLE hProcess, void *dst, std::string_view str)
{
  WriteProcessMemory(hProcess, dst, str.data(), str.length(), NULL);
}

void ajanuw::SSString::toMemEx(HANDLE hProcess, void *dst, std::wstring_view str)
{
  size_t count = ajanuw::SSString::count(str);
  WriteProcessMemory(hProcess, dst, str.data(), count, NULL);
}

void ajanuw::SSString::toMemEx(HANDLE hProcess, void *dst, std::u16string_view str)
{
  size_t count = ajanuw::SSString::count(str);
  WriteProcessMemory(hProcess, dst, str.data(), count, NULL);
}

std::string ajanuw::SSString::strFormMem(void *src, size_t max)
{
  std::string str;
  uintptr_t addr = (uintptr_t)src;
  while (true)
  {
    uint8_t wc = *(uint8_t *)addr;
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

std::string ajanuw::SSString::strFormMemEx(HANDLE hProcess, void *src, size_t max)
{
  std::string str;
  uintptr_t addr = (uintptr_t)src;
  while (true)
  {
    uint8_t wc = ajanuw::Mem::rByteEx(hProcess, (uint8_t *)addr);
    if (wc == NULL || max == 0)
      break;
    str.push_back(wc);
    addr++;
    max--;
  }
  str.push_back(0);
  return str;
}

std::wstring ajanuw::SSString::wstrFormMemEx(HANDLE hProcess, void *src, size_t max)
{
  std::wstring wstr;
  uintptr_t addr = (uintptr_t)src;
  while (true)
  {
    wchar_t wc = ajanuw::Mem::rWordEx(hProcess, (wchar_t *)addr);
    if (wc == NULL || max == 0)
      break;
    wstr.push_back(wc);
    addr += sizeof(wchar_t);
    max--;
  }
  wstr.push_back(0);
  return wstr;
}

std::u16string ajanuw::SSString::ustrFormMemEx(HANDLE hProcess, void *src, size_t max)
{
  std::u16string ustr;
  uintptr_t addr = (uintptr_t)src;
  while (true)
  {
    char16_t wc = ajanuw::Mem::rWordEx(hProcess, (char16_t *)addr);
    if (wc == NULL || max == 0)
      break;
    ustr.push_back(wc);
    addr += sizeof(char16_t);
    max--;
  }
  ustr.push_back(0);
  return ustr;
}

LPVOID ajanuw::Mem::alloc(SIZE_T dwSize, LPVOID lpAddress, uint32_t flAllocationType, uint32_t flProtect)
{
  return VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
}
LPVOID ajanuw::Mem::allocEx(HANDLE hProcess, SIZE_T dwSize, LPVOID lpAddress, uint32_t flAllocationType, uint32_t flProtect)
{
  return VirtualAllocEx(hProcess, lpAddress, dwSize, flAllocationType, flProtect);
}

BOOL ajanuw::Mem::free(LPVOID lpAddress)
{
  return VirtualFree(lpAddress, 0, MEM_RELEASE);
}

BOOL ajanuw::Mem::free(std::string_view CEAddressString)
{
  return ajanuw::Mem::free(ajanuw::CEAddressString::getAddress(CEAddressString));
}

BOOL ajanuw::Mem::freeEx(HANDLE hProcess, LPVOID lpAddress)
{
  return VirtualFreeEx(hProcess, lpAddress, 0, MEM_RELEASE);
}

BOOL ajanuw::Mem::freeEx(HANDLE hProcess, std::string_view CEAddressString)
{
  return ajanuw::Mem::freeEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString));
}

void ajanuw::Mem::wStr(void *lpAddress, std::string_view str)
{
  ajanuw::SSString::toMem((void *)lpAddress, str);
}

void ajanuw::Mem::wWstr(void *lpAddress, std::wstring_view str)
{
  ajanuw::SSString::toMem((void *)lpAddress, str);
}

void ajanuw::Mem::wUstr(void *lpAddress, std::u16string_view str)
{
  ajanuw::SSString::toMem((void *)lpAddress, str);
}

void ajanuw::Mem::wStrEx(HANDLE hProcess, void *lpAddress, std::string_view str)
{
  ajanuw::SSString::toMemEx(hProcess, (void *)lpAddress, str);
}

void ajanuw::Mem::wWstrEx(HANDLE hProcess, void *lpAddress, std::wstring_view str)
{
  ajanuw::SSString::toMemEx(hProcess, (void *)lpAddress, str);
}

void ajanuw::Mem::wUstrEx(HANDLE hProcess, void *lpAddress, std::u16string_view str)
{
  ajanuw::SSString::toMemEx(hProcess, (void *)lpAddress, str);
}

void ajanuw::Mem::wByte(void *lpAddress, uint8_t byte)
{
  memset(lpAddress, byte, sizeof(uint8_t));
}

void ajanuw::Mem::wBytes(void *lpAddress, const std::vector<uint8_t> &bytes)
{
  memcpy_s(lpAddress, bytes.size(), bytes.data(), bytes.size());
}

void ajanuw::Mem::wWord(void *lpAddress, uint16_t value)
{
  memcpy_s(lpAddress, sizeof(uint16_t), &value, sizeof(uint16_t));
}
void ajanuw::Mem::wDword(void *lpAddress, uint32_t value)
{
  memcpy_s(lpAddress, sizeof(uint32_t), &value, sizeof(uint32_t));
}
void ajanuw::Mem::wQword(void *lpAddress, uint64_t value)
{
  memcpy_s(lpAddress, sizeof(uint64_t), &value, sizeof(uint64_t));
}
void ajanuw::Mem::wFloat(void *lpAddress, float value)
{
  memcpy_s(lpAddress, sizeof(float), &value, sizeof(float));
}
void ajanuw::Mem::wDouble(void *lpAddress, double value)
{
  memcpy_s(lpAddress, sizeof(double), &value, sizeof(double));
}
void ajanuw::Mem::wRegionToFile(std::string_view filename, void *lpAddress, uintptr_t size)
{
  std::ofstream outFile;
  outFile.open(filename.data());
  for (int i = 0; i < size; i++)
    outFile << *(uint8_t *)((uintptr_t)lpAddress + i);
  outFile.close();
}

void ajanuw::Mem::wByteEx(HANDLE hProcess, void *lpAddress, uint8_t byte)
{
  WriteProcessMemory(hProcess, lpAddress, &byte, sizeof(uint8_t), NULL);
}

void ajanuw::Mem::wBytesEx(HANDLE hProcess, void *lpAddress, const std::vector<uint8_t> &bytes)
{
  WriteProcessMemory(hProcess, lpAddress, bytes.data(), bytes.size(), NULL);
}

void ajanuw::Mem::wWordEx(HANDLE hProcess, void *lpAddress, uint16_t value)
{
  WriteProcessMemory(hProcess, lpAddress, &value, sizeof(uint16_t), NULL);
}
void ajanuw::Mem::wDwordEx(HANDLE hProcess, void *lpAddress, uint32_t value)
{
  WriteProcessMemory(hProcess, lpAddress, &value, sizeof(uint32_t), NULL);
}
void ajanuw::Mem::wQwordEx(HANDLE hProcess, void *lpAddress, uint64_t value)
{
  WriteProcessMemory(hProcess, lpAddress, &value, sizeof(uint64_t), NULL);
}
void ajanuw::Mem::wFloatEx(HANDLE hProcess, void *lpAddress, float value)
{
  WriteProcessMemory(hProcess, lpAddress, &value, sizeof(float), NULL);
}
void ajanuw::Mem::wDoubleEx(HANDLE hProcess, void *lpAddress, double value)
{
  WriteProcessMemory(hProcess, lpAddress, &value, sizeof(double), NULL);
}
void ajanuw::Mem::wRegionToFileEx(HANDLE hProcess, std::string_view filename, void *lpAddress, uintptr_t size)
{
  std::ofstream outFile;
  outFile.open(filename.data());
  for (int i = 0; i < size; i++)
    outFile << ajanuw::Mem::rByteEx(hProcess, (uint8_t *)lpAddress + i);
  outFile.close();
}

void ajanuw::Mem::wStr(std::string_view CEAddressString, std::string_view str)
{
  ajanuw::Mem::wStr(ajanuw::CEAddressString::getAddress(CEAddressString), str);
}
void ajanuw::Mem::wWstr(std::string_view CEAddressString, std::wstring_view str)
{
  ajanuw::Mem::wWstr(ajanuw::CEAddressString::getAddress(CEAddressString), str);
}
void ajanuw::Mem::wUstr(std::string_view CEAddressString, std::u16string_view str)
{
  ajanuw::Mem::wUstr(ajanuw::CEAddressString::getAddress(CEAddressString), str);
}
void ajanuw::Mem::wByte(std::string_view CEAddressString, uint8_t byte)
{
  ajanuw::Mem::wByte(ajanuw::CEAddressString::getAddress(CEAddressString), byte);
}
void ajanuw::Mem::wBytes(std::string_view CEAddressString, const std::vector<uint8_t> &bytes)
{
  ajanuw::Mem::wBytes(ajanuw::CEAddressString::getAddress(CEAddressString), bytes);
}
void ajanuw::Mem::wWord(std::string_view CEAddressString, uint16_t value)
{
  ajanuw::Mem::wWord(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}
void ajanuw::Mem::wDword(std::string_view CEAddressString, uint32_t value)
{
  ajanuw::Mem::wDword(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}
void ajanuw::Mem::wQword(std::string_view CEAddressString, uint64_t value)
{
  ajanuw::Mem::wQword(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}
void ajanuw::Mem::wFloat(std::string_view CEAddressString, float value)
{
  ajanuw::Mem::wFloat(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}
void ajanuw::Mem::wDouble(std::string_view CEAddressString, double value)
{
  ajanuw::Mem::wDouble(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}
void ajanuw::Mem::wRegionToFile(std::string_view filename, std::string_view CEAddressString, uintptr_t size)
{
  wRegionToFile(filename, ajanuw::CEAddressString::getAddress(CEAddressString), size);
}

void ajanuw::Mem::wStrEx(HANDLE hProcess, std::string_view CEAddressString, std::string_view str)
{
  ajanuw::Mem::wStrEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), str);
}
void ajanuw::Mem::wWstrEx(HANDLE hProcess, std::string_view CEAddressString, std::wstring_view str)
{
  ajanuw::Mem::wWstrEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), str);
}
void ajanuw::Mem::wUstrEx(HANDLE hProcess, std::string_view CEAddressString, std::u16string_view str)
{
  ajanuw::Mem::wUstrEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), str);
}
void ajanuw::Mem::wByteEx(HANDLE hProcess, std::string_view CEAddressString, uint8_t byte)
{
  ajanuw::Mem::wByteEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), byte);
}
void ajanuw::Mem::wBytesEx(HANDLE hProcess, std::string_view CEAddressString, std::vector<uint8_t> bytes)
{
  ajanuw::Mem::wBytesEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), bytes);
}
void ajanuw::Mem::wWordEx(HANDLE hProcess, std::string_view CEAddressString, uint16_t value)
{
  ajanuw::Mem::wWordEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), value);
}
void ajanuw::Mem::wDwordEx(HANDLE hProcess, std::string_view CEAddressString, uint32_t value)
{
  ajanuw::Mem::wDwordEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), value);
}
void ajanuw::Mem::wQwordEx(HANDLE hProcess, std::string_view CEAddressString, uint64_t value)
{
  ajanuw::Mem::wQwordEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), value);
}
void ajanuw::Mem::wFloatEx(HANDLE hProcess, std::string_view CEAddressString, float value)
{
  ajanuw::Mem::wFloatEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), value);
}
void ajanuw::Mem::wDoubleEx(HANDLE hProcess, std::string_view CEAddressString, double value)
{
  ajanuw::Mem::wDoubleEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), value);
}

void ajanuw::Mem::wRegionToFileEx(HANDLE hProcess, std::string_view filename, std::string_view CEAddressString, uintptr_t size)
{
  ajanuw::Mem::wRegionToFileEx(hProcess, filename, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), size);
}

std::string ajanuw::Mem::rStr(char *lpAddress, uintptr_t max)
{
  return ajanuw::SSString::strFormMem(lpAddress, max);
}
std::wstring ajanuw::Mem::rWstr(wchar_t *lpAddress, uintptr_t max)
{
  return ajanuw::SSString::wstrFormMem(lpAddress, max);
}
std::u16string ajanuw::Mem::rUstr(char16_t *lpAddress, uintptr_t max)
{
  return ajanuw::SSString::ustrFormMem(lpAddress, max);
}

std::string ajanuw::Mem::rStrEx(HANDLE hProcess, char *lpAddress, uintptr_t max)
{
  return ajanuw::SSString::strFormMemEx(hProcess, lpAddress, max);
}

std::wstring ajanuw::Mem::rWstrEx(HANDLE hProcess, wchar_t *lpAddress, uintptr_t max)
{
  return ajanuw::SSString::wstrFormMemEx(hProcess, lpAddress, max);
}

std::u16string ajanuw::Mem::rUstrEx(HANDLE hProcess, char16_t *lpAddress, uintptr_t max)
{
  return ajanuw::SSString::ustrFormMemEx(hProcess, lpAddress, max);
}

std::string ajanuw::Mem::rStr(std::string_view CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::rStr((char *)ajanuw::CEAddressString::getAddress(CEAddressString), max);
}
std::wstring ajanuw::Mem::rWstr(std::string_view CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::rWstr((wchar_t *)ajanuw::CEAddressString::getAddress(CEAddressString), max);
}
std::u16string ajanuw::Mem::rUstr(std::string_view CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::rUstr((char16_t *)ajanuw::CEAddressString::getAddress(CEAddressString), max);
}

std::string ajanuw::Mem::rStrEx(HANDLE hProcess, std::string_view CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::rStrEx(hProcess, (char *)ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), max);
}
std::wstring ajanuw::Mem::rWstrEx(HANDLE hProcess, std::string_view CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::rWstrEx(hProcess, (wchar_t *)ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), max);
}
std::u16string ajanuw::Mem::rUstrEx(HANDLE hProcess, std::string_view CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::rUstrEx(hProcess, (char16_t *)ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), max);
}

std::vector<uint8_t> ajanuw::Mem::rBytes(void *lpAddress, uintptr_t size)
{
  std::vector<uint8_t> bytes(size);
  memcpy_s(bytes.data(), size, lpAddress, size);
  return bytes;
}

uint8_t ajanuw::Mem::rByte(void *lpAddress)
{
  return *(uint8_t *)lpAddress;
}

uint16_t ajanuw::Mem::rWord(void *lpAddress)
{
  return *(uint16_t *)lpAddress;
}
uint32_t ajanuw::Mem::rDword(void *lpAddress)
{
  return *(uint32_t *)lpAddress;
}
uint64_t ajanuw::Mem::rQword(void *lpAddress)
{
  return *(uint64_t *)lpAddress;
}

uintptr_t ajanuw::Mem::rPointer(void *lpAddress)
{
  return *(uintptr_t *)lpAddress;
}

float ajanuw::Mem::rFloat(void *lpAddress)
{
  return *(float *)lpAddress;
}

double ajanuw::Mem::rDouble(void *lpAddress)
{
  return *(double *)lpAddress;
}

void ajanuw::Mem::rRegionFromFile(std::string_view fileame, void *lpAddress)
{
  rRegionFromFile(fileame, lpAddress, NULL);
}

void ajanuw::Mem::rRegionFromFile(std::string_view fileame, void *lpAddress, size_t *fileSize)
{
  std::ifstream inFile;
  inFile.open(fileame.data());
  uintptr_t offset = (uintptr_t)lpAddress;
  while (inFile.good())
  {
    char r = inFile.get();
    if (inFile.eof())
      break;
    memset((void *)offset, r, sizeof(uint8_t));
    offset += sizeof(uint8_t);
    if (fileSize)
      (*fileSize)++;
  }
  inFile.close();
}

std::vector<uint8_t> ajanuw::Mem::rBytesEx(HANDLE hProcess, void *lpAddress, uintptr_t size)
{
  std::vector<uint8_t> bytes(size);
  ReadProcessMemory(hProcess, lpAddress, bytes.data(), size, NULL);
  return bytes;
}

uint8_t ajanuw::Mem::rByteEx(HANDLE hProcess, void *lpAddress)
{
  uint8_t r;
  ReadProcessMemory(hProcess, lpAddress, &r, sizeof(uint8_t), NULL);
  return r;
}

uint16_t ajanuw::Mem::rWordEx(HANDLE hProcess, void *lpAddress)
{
  uint16_t r;
  ReadProcessMemory(hProcess, lpAddress, &r, sizeof(uint16_t), NULL);
  return r;
}
uint32_t ajanuw::Mem::rDwordEx(HANDLE hProcess, void *lpAddress)
{
  uint32_t r;
  ReadProcessMemory(hProcess, lpAddress, &r, sizeof(uint32_t), NULL);
  return r;
}
uint64_t ajanuw::Mem::rQwordEx(HANDLE hProcess, void *lpAddress)
{
  uint64_t r;
  ReadProcessMemory(hProcess, lpAddress, &r, sizeof(uint64_t), NULL);
  return r;
}

uintptr_t ajanuw::Mem::rPointerEx(HANDLE hProcess, void *lpAddress)
{
  uint32_t pid = GetProcessId(hProcess);

  bool isx64 = ajanuw::PE::isX64(pid, (HMODULE)ajanuw::PE::GetModuleBase(pid).lpBaseOfDll);

  if (isx64)
  {
    uint64_t r;
    ReadProcessMemory(hProcess, lpAddress, &r, sizeof(uint64_t), NULL);
    return r;
  }
  else
  {
    uint32_t r;
    ReadProcessMemory(hProcess, lpAddress, &r, sizeof(uint32_t), NULL);
    return r;
  }
}

float ajanuw::Mem::rFloatEx(HANDLE hProcess, void *lpAddress)
{
  float r;
  ReadProcessMemory(hProcess, lpAddress, &r, sizeof(float), NULL);
  return r;
}

double ajanuw::Mem::rDoubleEx(HANDLE hProcess, void *lpAddress)
{
  double r;
  ReadProcessMemory(hProcess, lpAddress, &r, sizeof(float), NULL);
  return r;
}

void ajanuw::Mem::rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, void *lpAddress)
{
  rRegionFromFileEx(hProcess, fileame, lpAddress, NULL);
}

void ajanuw::Mem::rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, void *lpAddress, size_t *fileSize)
{
  std::ifstream inFile;
  inFile.open(fileame.data());
  uintptr_t offset = (uintptr_t)lpAddress;
  while (inFile.good())
  {
    char r = inFile.get();
    if (inFile.eof())
      break;
    ajanuw::Mem::wByteEx(hProcess, (void *)offset, r);
    offset += sizeof(uint8_t);
    if (fileSize)
      (*fileSize)++;
  }
  inFile.close();
}

std::vector<uint8_t> ajanuw::Mem::rBytes(std::string_view CEAddressString, uintptr_t size)
{
  return ajanuw::Mem::rBytes(ajanuw::CEAddressString::getAddress(CEAddressString), size);
}

uint8_t ajanuw::Mem::rByte(std::string_view CEAddressString)
{
  return ajanuw::Mem::rByte(ajanuw::CEAddressString::getAddress(CEAddressString));
}

uint16_t ajanuw::Mem::rWord(std::string_view CEAddressString)
{
  return ajanuw::Mem::rWord(ajanuw::CEAddressString::getAddress(CEAddressString));
}

uint32_t ajanuw::Mem::rDword(std::string_view CEAddressString)
{
  return ajanuw::Mem::rDword(ajanuw::CEAddressString::getAddress(CEAddressString));
}

uint64_t ajanuw::Mem::rQword(std::string_view CEAddressString)
{
  return ajanuw::Mem::rQword(ajanuw::CEAddressString::getAddress(CEAddressString));
}

uintptr_t ajanuw::Mem::rPointer(std::string_view CEAddressString)
{
  return ajanuw::Mem::rPointer(ajanuw::CEAddressString::getAddress(CEAddressString));
}

float ajanuw::Mem::rFloat(std::string_view CEAddressString)
{
  return ajanuw::Mem::rFloat(ajanuw::CEAddressString::getAddress(CEAddressString));
}

double ajanuw::Mem::rDouble(std::string_view CEAddressString)
{
  return ajanuw::Mem::rDouble(ajanuw::CEAddressString::getAddress(CEAddressString));
}

void ajanuw::Mem::rRegionFromFile(std::string_view fileame, std::string_view CEAddressString)
{
  ajanuw::Mem::rRegionFromFile(fileame, ajanuw::CEAddressString::getAddress(CEAddressString));
}

void ajanuw::Mem::rRegionFromFile(std::string_view fileame, std::string_view CEAddressString, size_t *fileSize)
{
  ajanuw::Mem::rRegionFromFile(fileame, ajanuw::CEAddressString::getAddress(CEAddressString), fileSize);
}

std::vector<uint8_t> ajanuw::Mem::rBytesEx(HANDLE hProcess, std::string_view CEAddressString, uintptr_t size)
{
  return ajanuw::Mem::rBytesEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), size);
}

uint8_t ajanuw::Mem::rByteEx(HANDLE hProcess, std::string_view CEAddressString)
{
  return ajanuw::Mem::rByteEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

uint16_t ajanuw::Mem::rWordEx(HANDLE hProcess, std::string_view CEAddressString)
{
  return ajanuw::Mem::rWordEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

uint32_t ajanuw::Mem::rDwordEx(HANDLE hProcess, std::string_view CEAddressString)
{
  return ajanuw::Mem::rDwordEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

uint64_t ajanuw::Mem::rQwordEx(HANDLE hProcess, std::string_view CEAddressString)
{
  return ajanuw::Mem::rQwordEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

uintptr_t ajanuw::Mem::rPointerEx(HANDLE hProcess, std::string_view CEAddressString)
{
  return ajanuw::Mem::rPointerEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

float ajanuw::Mem::rFloatEx(HANDLE hProcess, std::string_view CEAddressString)
{
  return ajanuw::Mem::rFloatEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

double ajanuw::Mem::rDoubleEx(HANDLE hProcess, std::string_view CEAddressString)
{
  return ajanuw::Mem::rDoubleEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

void ajanuw::Mem::rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, std::string_view CEAddressString)
{
  ajanuw::Mem::rRegionFromFileEx(hProcess, fileame, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

void ajanuw::Mem::rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, std::string_view CEAddressString, size_t *fileSize)
{
  ajanuw::Mem::rRegionFromFileEx(hProcess, fileame, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), fileSize);
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
  wcex.lpszClassName = className.c_str();
  return RegisterClassExA(&wcex);
}

BOOL ajanuw::Gui::Win32::initWindow()
{
  _hWnd = CreateWindowA(
      className.c_str(),
      windowName.c_str(),
      style,
      x, y,
      width, height,
      NULL, NULL, NULL, NULL);

  if (!_hWnd)
    return FALSE;
  std::wstring ws = ajanuw::SSString::strToWstr(windowName);
  SetWindowTextW(_hWnd, ws.c_str());
  hwndMap.insert(std::pair<HWND, uintptr_t>(_hWnd, (uintptr_t)this));
  ShowWindow(_hWnd, SW_RESTORE);
  UpdateWindow(_hWnd);
  return TRUE;
}

std::vector<uint16_t> ajanuw::Gui::Win32::getHLMessage(uint32_t message)
{
  return {HIWORD(message), LOWORD(message)};
}

bool ajanuw::Gui::Win32::getCheck(HWND hWnd)
{
  return Button_GetCheck(hWnd);
}

uint32_t ajanuw::Gui::Win32::rgb(uint32_t r, uint32_t g, uint32_t b)
{
  return RGB(r, g, b);
}

HWND ajanuw::Gui::Win32::createWindow(std::unique_ptr<Win32CreateOption> opt)
{
  HWND hWnd = CreateWindowA(opt->className.c_str(), opt->windowName.c_str(),
                            opt->style,
                            opt->x, opt->y,
                            opt->width, opt->height,
                            opt->parent ? opt->parent : _hWnd,
                            opt->id,
                            NULL, NULL);
  auto ws = ajanuw::SSString::strToWstr(opt->windowName);
  SetWindowTextW(hWnd, ws.data());
  return hWnd;
}

HWND ajanuw::Gui::Win32::button(std::unique_ptr<Win32CreateOption> opt)
{
  opt->className = "button";
  opt->style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_MULTILINE | opt->style;
  return ajanuw::Gui::Win32::createWindow(std::move(opt));
}

HWND ajanuw::Gui::Win32::checkbox(std::unique_ptr<Win32CreateOption> opt)
{
  opt->className = "button";
  opt->style = WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_CENTER | BS_MULTILINE | opt->style;
  return ajanuw::Gui::Win32::createWindow(std::move(opt));
}

HWND ajanuw::Gui::Win32::radio(std::unique_ptr<Win32CreateOption> opt)
{
  opt->className = "button";
  opt->style = WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_CENTER | BS_MULTILINE | opt->style;
  return ajanuw::Gui::Win32::createWindow(std::move(opt));
}
HWND ajanuw::Gui::Win32::groupbox(std::unique_ptr<Win32CreateOption> opt)
{
  opt->className = "button";
  opt->style = WS_CHILD | WS_VISIBLE | BS_GROUPBOX | BS_MULTILINE | opt->style;
  return ajanuw::Gui::Win32::createWindow(std::move(opt));
}

HWND ajanuw::Gui::Win32::text(std::unique_ptr<Win32CreateOption> opt)
{
  opt->className = "static";
  opt->style = WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOTIFY | SS_SIMPLE | opt->style;
  return ajanuw::Gui::Win32::createWindow(std::move(opt));
}

HWND ajanuw::Gui::Win32::input(std::unique_ptr<Win32CreateOption> opt)
{
  opt->className = "edit";
  opt->style = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | opt->style;
  return ajanuw::Gui::Win32::createWindow(std::move(opt));
}

HWND ajanuw::Gui::Win32::textarea(std::unique_ptr<Win32CreateOption> opt)
{
  opt->className = "edit";
  opt->style = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | opt->style;
  return ajanuw::Gui::Win32::createWindow(std::move(opt));
}
HWND ajanuw::Gui::Win32::listbox(std::unique_ptr<Win32CreateOption> opt)
{
  opt->className = "LISTBOX";
  opt->style = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY | opt->style;
  return ajanuw::Gui::Win32::createWindow(std::move(opt));
}
HWND ajanuw::Gui::Win32::select(std::unique_ptr<Win32CreateOption> opt)
{
  opt->className = "combobox";
  opt->style = WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | opt->style;
  return ajanuw::Gui::Win32::createWindow(std::move(opt));
}

ajanuw::Mem::VAManage::VAManage(size_t size)
    : size(size),
      position(0),
      memory(ajanuw::Mem::alloc(size)),
      hProcess(NULL)
{
  if (memory == NULL)
  {
    throw std::exception("VAManage alloc fail.");
  }
}

ajanuw::Mem::VAManage::VAManage(size_t size, HANDLE hProcess)
    : size(size),
      position(0),
      memory(ajanuw::Mem::allocEx(hProcess, size)),
      hProcess(hProcess)
{
  if (memory == NULL)
  {
    throw std::exception("VAManage alloc fail.");
  }
}

uint8_t *ajanuw::Mem::VAManage::ptr()
{
  return (uint8_t *)memory + position;
}

std::vector<uint8_t> ajanuw::Mem::VAManage::read(size_t _size)
{
  if (hProcess == NULL)
  {
    return ajanuw::Mem::rBytes(ptr(), _size);
  }
  else
  {
    return ajanuw::Mem::rBytesEx(hProcess, ptr(), _size);
  }
}

uint8_t ajanuw::Mem::VAManage::readByte()
{
  return hProcess == NULL ? ajanuw::Mem::rByte(ptr()) : ajanuw::Mem::rByteEx(hProcess, ptr());
}

uint16_t ajanuw::Mem::VAManage::readWord()
{
  return hProcess == NULL ? ajanuw::Mem::rWord(ptr()) : ajanuw::Mem::rWordEx(hProcess, ptr());
}

uint32_t ajanuw::Mem::VAManage::readDword()
{
  return hProcess == NULL ? ajanuw::Mem::rDword(ptr()) : ajanuw::Mem::rDwordEx(hProcess, ptr());
}

uint64_t ajanuw::Mem::VAManage::readQword()
{
  return hProcess == NULL ? ajanuw::Mem::rQword(ptr()) : ajanuw::Mem::rQwordEx(hProcess, ptr());
}

float ajanuw::Mem::VAManage::readFloat()
{
  return hProcess == NULL ? ajanuw::Mem::rFloat(ptr()) : ajanuw::Mem::rFloatEx(hProcess, ptr());
}

double ajanuw::Mem::VAManage::readDouble()
{
  return hProcess == NULL ? ajanuw::Mem::rDouble(ptr()) : ajanuw::Mem::rDoubleEx(hProcess, ptr());
}

std::string ajanuw::Mem::VAManage::readStr(size_t maxSize)
{
  return hProcess == NULL ? ajanuw::Mem::rStr((char *)ptr(), maxSize) : ajanuw::Mem::rStrEx(hProcess, (char *)ptr(), maxSize);
}

std::wstring ajanuw::Mem::VAManage::readWstr(size_t maxSize)
{
  return hProcess == NULL ? ajanuw::Mem::rWstr((wchar_t *)ptr(), maxSize) : ajanuw::Mem::rWstrEx(hProcess, (wchar_t *)ptr(), maxSize);
}

std::u16string ajanuw::Mem::VAManage::readUstr(size_t maxSize)
{
  return hProcess == NULL ? ajanuw::Mem::rUstr((char16_t *)ptr(), maxSize) : ajanuw::Mem::rUstrEx(hProcess, (char16_t *)ptr(), maxSize);
}

void ajanuw::Mem::VAManage::write(std::vector<uint8_t> &table, size_t count)
{
  if (count < table.size())
  {
    table.resize(count);
  }
  if (hProcess == NULL)
  {
    ajanuw::Mem::wBytes(ptr(), table);
  }
  else
  {
    ajanuw::Mem::wBytesEx(hProcess, ptr(), table);
  }
  position += table.size();
}

void ajanuw::Mem::VAManage::writeByte(uint8_t v)
{
  if (hProcess == NULL)
  {
    ajanuw::Mem::wByte(ptr(), v);
  }
  else
  {
    ajanuw::Mem::wByteEx(hProcess, ptr(), v);
  }
  position++;
}

void ajanuw::Mem::VAManage::writeWord(uint16_t v)
{
  if (hProcess == NULL)
  {
    ajanuw::Mem::wWord(ptr(), v);
  }
  else
  {
    ajanuw::Mem::wWordEx(hProcess, ptr(), v);
  }
  position += sizeof(uint16_t);
}

void ajanuw::Mem::VAManage::writeDword(uint32_t v)
{
  if (hProcess == NULL)
  {
    ajanuw::Mem::wDword(ptr(), v);
  }
  else
  {
    ajanuw::Mem::wDwordEx(hProcess, ptr(), v);
  }
  position += sizeof(uint32_t);
}

void ajanuw::Mem::VAManage::writeQword(uintptr_t v)
{
  if (hProcess == NULL)
  {
    ajanuw::Mem::wQword(ptr(), v);
  }
  else
  {
    ajanuw::Mem::wQwordEx(hProcess, ptr(), v);
  }

  position += sizeof(uint64_t);
}

void ajanuw::Mem::VAManage::writeFloat(float v)
{
  if (hProcess == NULL)
  {
    ajanuw::Mem::wFloat(ptr(), v);
  }
  else
  {
    ajanuw::Mem::wFloatEx(hProcess, ptr(), v);
  }

  position += sizeof(float);
}

void ajanuw::Mem::VAManage::writeDouble(double v)
{
  if (hProcess == NULL)
  {
    ajanuw::Mem::wDouble(ptr(), v);
  }
  else
  {
    ajanuw::Mem::wDoubleEx(hProcess, ptr(), v);
  }

  position += sizeof(double);
}

void ajanuw::Mem::VAManage::writeStr(std::string_view str)
{
  if (hProcess == NULL)
  {
    ajanuw::Mem::wStr(ptr(), str);
  }
  else
  {
    ajanuw::Mem::wStrEx(hProcess, ptr(), str);
  }

  position += ajanuw::SSString::count(str);
}

void ajanuw::Mem::VAManage::writeWstr(std::wstring_view wstr)
{
  if (hProcess == NULL)
  {
    ajanuw::Mem::wWstr(ptr(), wstr);
  }
  else
  {
    ajanuw::Mem::wWstrEx(hProcess, ptr(), wstr);
  }
  position += ajanuw::SSString::count(wstr);
}

void ajanuw::Mem::VAManage::writeUstr(std::u16string_view ustr)
{
  if (hProcess == NULL)
  {
    ajanuw::Mem::wUstr(ptr(), ustr);
  }
  else
  {
    ajanuw::Mem::wUstrEx(hProcess, ptr(), ustr);
  }
  position += ajanuw::SSString::count(ustr);
}

void ajanuw::Mem::VAManage::loadFromFile(std::string_view filename)
{
  if (hProcess == NULL)
  {
    ajanuw::Mem::rRegionFromFile(filename, ptr(), &position);
  }
  else
  {
    ajanuw::Mem::rRegionFromFileEx(hProcess, filename, ptr(), &position);
  }
}

void ajanuw::Mem::VAManage::saveToFile(std::string_view filename)
{
  if (hProcess == NULL)
  {
    ajanuw::Mem::wRegionToFile(filename, ptr(), size);
  }
  else
  {
    ajanuw::Mem::wRegionToFileEx(hProcess, filename, ptr(), size);
  }
}

BOOL ajanuw::Mem::VAManage::destroy()
{
  if (memory)
  {
    if (hProcess == NULL)
    {
      return ajanuw::Mem::free(memory);
    }
    else
    {
      return ajanuw::Mem::freeEx(hProcess, memory);
    }
  }
  else
    return FALSE;
}

uintptr_t ajanuw::Asm::AAScript::aa(std::string_view asmString, uintptr_t rcx = 0)
{
  JitRuntime rt;
  CodeHolder code;
  code.init(rt.environment());

  x86::Assembler a(&code);
  AsmParser p(&a);

  asmjit::Error err = p.parse(asmString.data());
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

std::vector<uint8_t> ajanuw::Asm::AAScript::asmBytes(std::string_view asmString, bool isX64)
{
  CodeHolder code;
  Environment env = hostEnvironment();
  env.setArch(isX64 ? Environment::kArchX64 : Environment::kArchX86);
  code.init(env);

  x86::Assembler a(&code);
  AsmParser p(&a);
  asmjit::Error err = p.parse(asmString.data());
  if (err)
  {
    char msg[100];
    sprintf(msg, "AsmParser ERROR: %08x (%s)\n", err, DebugUtils::errorAsString(err));
    throw std::exception(msg);
  }

  std::vector<uint8_t> r(a.offset());
  memcpy_s(r.data(), r.size(), a.bufferData(), r.size());
  return r;
}

std::map<std::string, LPVOID> ajanuw::Symbol::_symbolMap;
void ajanuw::Symbol::registerSymbol(std::string symbolname, LPVOID address)
{
  ajanuw::Symbol::_symbolMap[symbolname] = address;
}

void ajanuw::Symbol::unregisterSymbol(std::string_view symbolname)
{
  ajanuw::Symbol::_symbolMap.erase(symbolname.data());
}

LPVOID ajanuw::Symbol::get(std::string_view symbolname)
{
  if (ajanuw::Symbol::_symbolMap.count(symbolname.data()) == NULL)
    return NULL;
  return ajanuw::Symbol::_symbolMap.at(symbolname.data());
}

bool ajanuw::Symbol::has(std::string_view symbolname)
{
  return ajanuw::Symbol::_symbolMap.count(symbolname.data()) != NULL;
}

LPVOID ajanuw::CEAddressString::getAddress(std::string_view CEAddressString, HANDLE hProcess)
{
  try
  {
    auto node = ces::parse(CEAddressString.data());
    if (!node)
    {
      throw std::exception("parser error.\n");
    }
    // printf("id:%d\n", node->id());

    Interpreter interpreter{hProcess};
    auto addr = (LPVOID)interpreter.visit(node);
    delete node;
    return addr;
  }
  catch (const std::exception &e)
  {
    throw e;
  }
}
uint32_t ajanuw::PE::GetPID(std::string_view name)
{
  return ajanuw::PE::GetPID(ajanuw::SSString::strToWstr(name));
}
uint32_t ajanuw::PE::GetPID(std::wstring_view name)
{
  uint32_t pid = NULL;
  HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (hSnap != INVALID_HANDLE_VALUE)
  {
    PROCESSENTRY32W pe;
    pe.dwSize = sizeof(pe);
    if (Process32FirstW(hSnap, &pe))
    {
      do
      {
        if (!_wcsicmp(pe.szExeFile, name.data()))
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

MODULEINFO ajanuw::PE::GetModuleBase(uint32_t pid)
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

std::wstring ajanuw::PE::GetModuleName(std::wstring_view moduleName)
{
  auto index = moduleName.rfind(L".");
  return std::wstring(moduleName.substr(0, index));
}
std::string ajanuw::PE::GetModuleName(std::string_view moduleName)
{
  auto index = moduleName.rfind(".");
  return std::string(moduleName.substr(0, index));
}

// 忽略大小写判断
// user32.dll
// user32
MODULEINFO ajanuw::PE::GetModuleInfo(std::wstring_view moduleName, uint32_t pid)
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
        // me.szModule 带有模块后缀 .dll .exe .node
        if (
            ajanuw::SSString::icmp(ajanuw::PE::GetModuleName(me.szModule), moduleName) ||
            ajanuw::SSString::icmp(me.szModule, moduleName))
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

bool ajanuw::PE::isX64(uint32_t pid, HMODULE hModule)
{
  uint8_t *buf = new uint8_t[0x1000];
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

bool ajanuw::PE::isX86(uint32_t pid, HMODULE hModule)
{
  return !isX64(pid, hModule);
}

std::map<std::string, uintptr_t> ajanuw::PE::exports(uint32_t pid, HMODULE hModule)
{
  std::map<std::string, uintptr_t> result;
  uint8_t *buf = new uint8_t[0x1000];
  HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
  ReadProcessMemory(hProcess, hModule, buf, 0x1000, NULL);

  PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(buf);
  PIMAGE_NT_HEADERS ntHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(buf + dosHeader->e_lfanew);
  PIMAGE_FILE_HEADER fileHeader = reinterpret_cast<PIMAGE_FILE_HEADER>(&ntHeader->FileHeader);
  bool isX64 = fileHeader->SizeOfOptionalHeader == 0xf0;
  auto RVA2VA = [&](size_t rva)
  {
    return (uint8_t *)hModule + rva;
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

  uint8_t *src = RVA2VA(exportEntry.VirtualAddress);
  IMAGE_EXPORT_DIRECTORY exportDes{0};
  ReadProcessMemory(hProcess, src, &exportDes, sizeof(IMAGE_EXPORT_DIRECTORY), NULL);

  // 以函数名称导出数量,指针列表
  uint32_t *AddressOfNames = (uint32_t *)RVA2VA(exportDes.AddressOfNames);               // 函数名称表
  uint32_t *AddressOfFunctions = (uint32_t *)RVA2VA(exportDes.AddressOfFunctions);       // 函数地址表
  uint16_t *AddressOfNameOrdinals = (uint16_t *)RVA2VA(exportDes.AddressOfNameOrdinals); // 函数地址index表

  size_t i = 0;
  uint32_t namePtrRVA = 0;
  while (i < exportDes.NumberOfNames)
  {
    char funme[MAX_PATH] = {0};
    ReadProcessMemory(hProcess, AddressOfNames + i, &namePtrRVA, sizeof(uint32_t), NULL);
    ReadProcessMemory(hProcess, RVA2VA(namePtrRVA), &funme, MAX_PATH, NULL);

    // get function address index
    uint16_t AddressOfFunctionsIndex = 0;
    ReadProcessMemory(hProcess, AddressOfNameOrdinals + i, &AddressOfFunctionsIndex, sizeof(uint16_t), NULL);

    // get function address
    uint32_t funAddrRVA = 0;
    ReadProcessMemory(hProcess, AddressOfFunctions + AddressOfFunctionsIndex, &funAddrRVA, sizeof(uint32_t), NULL);

    uint8_t *funPtr = RVA2VA(funAddrRVA);
    result[funme] = (uintptr_t)funPtr;
    //printf("name: %s-%p\n", funme, funPtr);
    i++;
  }

  CloseHandle(hProcess);
  delete[] buf;
  return result;
}

uint8_t *ajanuw::PE::GetProcAddress(uint32_t pid, HMODULE hModule, std::string_view method)
{
  uint8_t *result = NULL;
  uint8_t *buf = new uint8_t[0x1000];
  HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
  ReadProcessMemory(hProcess, hModule, buf, 0x1000, NULL);

  PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(buf);
  PIMAGE_NT_HEADERS ntHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(buf + dosHeader->e_lfanew);
  PIMAGE_FILE_HEADER fileHeader = reinterpret_cast<PIMAGE_FILE_HEADER>(&ntHeader->FileHeader);
  bool isX64 = fileHeader->SizeOfOptionalHeader == 0xf0;
  auto RVA2VA = [&](size_t rva)
  {
    return (uint8_t *)hModule + rva;
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
    CloseHandle(hProcess);
    delete[] buf;
    return result;
  }

  uint8_t *src = RVA2VA(exportEntry.VirtualAddress);
  IMAGE_EXPORT_DIRECTORY exportDes{0};
  ReadProcessMemory(hProcess, src, &exportDes, sizeof(IMAGE_EXPORT_DIRECTORY), NULL);

  // 以函数名称导出数量,指针列表
  uint32_t *AddressOfNames = (uint32_t *)RVA2VA(exportDes.AddressOfNames);               // 函数名称表
  uint32_t *AddressOfFunctions = (uint32_t *)RVA2VA(exportDes.AddressOfFunctions);       // 函数地址表
  uint16_t *AddressOfNameOrdinals = (uint16_t *)RVA2VA(exportDes.AddressOfNameOrdinals); // 函数地址index表

  size_t i = 0;
  uint32_t namePtrRVA = 0;
  while (i < exportDes.NumberOfNames)
  {
    char funme[MAX_PATH] = {0};
    ReadProcessMemory(hProcess, AddressOfNames + i, &namePtrRVA, sizeof(uint32_t), NULL);
    ReadProcessMemory(hProcess, RVA2VA(namePtrRVA), &funme, MAX_PATH, NULL);

    if (ajanuw::SSString::icmp(funme, method))
    {
      // get function address index
      uint16_t AddressOfFunctionsIndex = 0;
      ReadProcessMemory(hProcess, AddressOfNameOrdinals + i, &AddressOfFunctionsIndex, sizeof(uint16_t), NULL);

      // get function address
      uint32_t funAddrRVA = 0;
      ReadProcessMemory(hProcess, AddressOfFunctions + AddressOfFunctionsIndex, &funAddrRVA, sizeof(uint32_t), NULL);

      result = RVA2VA(funAddrRVA);
      break;
    }
    i++;
  }

  CloseHandle(hProcess);
  delete[] buf;
  return result;
}