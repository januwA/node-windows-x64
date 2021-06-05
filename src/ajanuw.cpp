#include "ajanuw.h"

std::string ajanuw::sstr::formHex(uintptr_t _hex)
{
  std::stringstream stream;
  stream << std::hex << _hex;
  return stream.str();
}

std::string ajanuw::sstr::tolower(std::string_view s)
{
  auto r = s | std::views::transform([](unsigned char c)
                                     { return std::tolower(c); });
  return std::string(r.begin(), r.end());
}

std::string ajanuw::sstr::toupper(std::string_view s)
{
  auto r = s | std::views::transform([](unsigned char c)
                                     { return std::toupper(c); });
  return std::string(r.begin(), r.end());
}

std::wstring ajanuw::sstr::tolower(std::wstring_view s)
{
  auto r = s | std::views::transform([](unsigned char c)
                                     { return std::tolower(c); });
  return std::wstring(r.begin(), r.end());
}

std::wstring ajanuw::sstr::toupper(std::wstring_view s)
{
  auto r = s | std::views::transform([](unsigned char c)
                                     { return std::toupper(c); });
  return std::wstring(r.begin(), r.end());
}

std::string ajanuw::sstr::pad(std::string_view str, size_t size, std::string_view padStr = " ", bool isStart = true)
{
  if (str.size() >= size)
    return std::string(str);

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

std::string ajanuw::sstr::padStart(std::string_view str, size_t size, std::string_view padStr = " ")
{
  return ajanuw::sstr::pad(str, size, padStr);
}

std::string ajanuw::sstr::padEnd(std::string_view str, size_t size, std::string_view padStr = " ")
{
  return ajanuw::sstr::pad(str, size, padStr, false);
}

std::string ajanuw::sstr::repeat(std::string_view str, size_t len)
{
  std::string r;
  while (len--)
    r += str;
  return r;
}

std::string ajanuw::sstr::join(const std::vector<std::string> &v, std::string_view p)
{
  std::string r;
  int last = v.size() - 1;
  for (size_t i = 0, l = v.size(); i < l; i++)
  {
    r += v.at(i) + (i == last ? "" : p.data());
  }
  return r;
}

bool ajanuw::sstr::startWith(std::string_view str, std::string_view s2, size_t index)
{
  return str.find(s2) - index == 0;
}

bool ajanuw::sstr::endWith(std::string_view str, const char *s2)
{
  return str.rfind(s2) + strlen(s2) == str.size();
}

bool ajanuw::sstr::endWith(std::string_view str, const char *s2, size_t length)
{
  return str.rfind(s2) + strlen(s2) == length;
}

bool ajanuw::sstr::search(std::string_view str, const std::regex &reg)
{
  return std::regex_search(str.data(), reg);
}

bool ajanuw::sstr::search(std::wstring_view str, const std::regex &reg)
{
  return std::regex_search(std::move(ajanuw::sstr::wstrToStr(str)), reg);
}

std::string ajanuw::sstr::trim(std::string_view str)
{
  return std::regex_replace(str.data(), std::regex("^\\s+|\\s+$"), "");
}
std::string ajanuw::sstr::trimStart(std::string_view str)
{
  return std::regex_replace(str.data(), std::regex("^\\s+"), "");
}
std::string ajanuw::sstr::trimEnd(std::string_view str)
{
  return std::regex_replace(str.data(), std::regex("\\s+$"), "");
}
std::vector<std::string> ajanuw::sstr::split(const std::string &str, const std::regex &reg)
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
std::vector<uint8_t> ajanuw::sstr::toBytes(std::string_view byteStr)
{
  byteStr = ajanuw::sstr::trim(byteStr);
  auto byteStrList = ajanuw::sstr::split(byteStr.data(), std::regex{"[\\s\\n]+"});
  auto a = byteStrList | std::views::transform([](const std::string &s)
                                               { return std::stoi(s, nullptr, 16); });
  return std::vector<uint8_t>(a.begin(), a.end());
}
char *ajanuw::sstr::setLocale(int _Category, const char *_Locale)
{
  return setlocale(_Category, _Locale);
}

BOOL ajanuw::sstr::cmp(std::string_view s1, std::string_view s2)
{
  return strncmp(s1.data(), s2.data(), s2.size()) == 0;
}

BOOL ajanuw::sstr::cmp(std::wstring_view s1, std::wstring_view s2)
{
  return wcsncmp(s1.data(), s2.data(), s2.size()) == 0;
}

BOOL ajanuw::sstr::cmp(std::u16string_view s1, std::u16string_view s2)
{
  return wcsncmp((wchar_t *)s1.data(), (wchar_t *)s2.data(), s2.size()) == 0;
}

BOOL ajanuw::sstr::icmp(std::string_view s1, std::string_view s2)
{
  return _stricmp(s1.data(), s2.data()) == 0;
}

BOOL ajanuw::sstr::icmp(std::wstring_view s1, std::wstring_view s2)
{
  return _wcsicmp(s1.data(), s2.data()) == 0;
}

BOOL ajanuw::sstr::icmp(std::u16string_view s1, std::u16string_view s2)
{
  return _wcsicmp((wchar_t *)s1.data(), (wchar_t *)s2.data()) == 0;
}

size_t ajanuw::sstr::len(std::string_view str)
{
  return str.length();
}
size_t ajanuw::sstr::len(std::wstring_view str)
{
  return str.length();
}
size_t ajanuw::sstr::len(std::u16string_view str)
{
  return str.length();
}

size_t ajanuw::sstr::count(std::string_view str)
{
  return str.length() * sizeof(char);
}

size_t ajanuw::sstr::count(std::wstring_view str)
{
  return str.length() * sizeof(wchar_t);
}

size_t ajanuw::sstr::count(std::u16string_view str)
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

std::wstring ajanuw::sstr::strToWstr(std::string_view str)
{
  std::wstring wideStr;
  size_t size = MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), NULL, NULL);
  if (size == NULL)
    return wideStr;

  wideStr.resize(size);
  MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), (LPWSTR)wideStr.data(), wideStr.length());
  return wideStr;
}

std::u16string ajanuw::sstr::strToUstr(std::string_view str)
{
  std::u16string wideStr;
  size_t size = MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), NULL, NULL);
  if (size == NULL)
    return wideStr;

  wideStr.resize(size);
  MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), (LPWSTR)wideStr.data(), wideStr.length());
  return wideStr;
}

std::string ajanuw::sstr::ustrToStr(std::u16string_view ustr)
{
  std::string str;
  size_t size = WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)ustr.data(), ustr.length(), NULL, NULL, 0, 0);
  if (size == NULL)
    return str;

  str.resize(size);
  WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)ustr.data(), ustr.length(), (LPSTR)str.data(), str.length(), 0, 0);
  return str;
}

std::string ajanuw::sstr::wstrToStr(std::wstring_view wstr)
{
  std::string str;
  size_t size = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), wstr.length(), NULL, NULL, 0, 0);
  if (size == NULL)
    return str;

  str.resize(size);
  WideCharToMultiByte(CP_UTF8, 0, wstr.data(), wstr.length(), (LPSTR)str.data(), str.length(), 0, 0);
  return str;
}

std::wstring ajanuw::sstr::ustrToWstr(std::u16string_view ustr)
{
  return std::wstring(ustr.begin(), ustr.end());
}

std::u16string ajanuw::sstr::wstrToUstr(std::wstring_view wstr)
{
  return std::u16string(wstr.begin(), wstr.end());
}

void ajanuw::sstr::toMem(void *dst, std::string_view str)
{
  memcpy_s(dst, str.length(), str.data(), str.length());
}

void ajanuw::sstr::toMem(void *dst, std::wstring_view str)
{
  size_t count = ajanuw::sstr::count(str);
  memcpy_s(dst, count, str.data(), count);
}

void ajanuw::sstr::toMem(void *dst, std::u16string_view str)
{
  size_t count = ajanuw::sstr::count(str);
  memcpy_s(dst, count, str.data(), count);
}

void ajanuw::sstr::toMemEx(HANDLE hProcess, void *dst, std::string_view str)
{
  WriteProcessMemory(hProcess, dst, str.data(), str.length(), NULL);
}

void ajanuw::sstr::toMemEx(HANDLE hProcess, void *dst, std::wstring_view str)
{
  size_t count = ajanuw::sstr::count(str);
  WriteProcessMemory(hProcess, dst, str.data(), count, NULL);
}

void ajanuw::sstr::toMemEx(HANDLE hProcess, void *dst, std::u16string_view str)
{
  size_t count = ajanuw::sstr::count(str);
  WriteProcessMemory(hProcess, dst, str.data(), count, NULL);
}

std::string ajanuw::sstr::strFormMem(void *src, size_t max)
{
  std::string str;
  auto addr = (uint8_t *)src;
  while (max--)
  {
    auto c = *(uint8_t *)addr;
    if (c == NULL)
      break;
    str.push_back(c);
    addr++;
  }
  str.push_back(0);
  return str;
}

std::wstring ajanuw::sstr::wstrFormMem(void *src, size_t max)
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

std::u16string ajanuw::sstr::ustrFormMem(void *src, size_t max)
{
  std::u16string ustr;
  auto addr = (uint8_t *)src;
  while (max--)
  {
    auto wc = *(char16_t *)addr;
    if (wc == NULL)
      break;
    ustr.push_back(wc);
    addr += sizeof(char16_t);
  }
  ustr.push_back(0);
  return ustr;
}

std::string ajanuw::sstr::strFormMemEx(HANDLE hProcess, void *src, size_t max)
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

std::wstring ajanuw::sstr::wstrFormMemEx(HANDLE hProcess, void *src, size_t max)
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

std::u16string ajanuw::sstr::ustrFormMemEx(HANDLE hProcess, void *src, size_t max)
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

LPVOID ajanuw::Mem::alloc(SIZE_T dwSize, LPVOID addr, uint32_t flAllocationType, uint32_t flProtect)
{
  return VirtualAlloc(addr, dwSize, flAllocationType, flProtect);
}
LPVOID ajanuw::Mem::allocEx(HANDLE hProcess, SIZE_T dwSize, LPVOID addr, uint32_t flAllocationType, uint32_t flProtect)
{
  return VirtualAllocEx(hProcess, addr, dwSize, flAllocationType, flProtect);
}

BOOL ajanuw::Mem::free(LPVOID addr)
{
  return VirtualFree(addr, 0, MEM_RELEASE);
}

BOOL ajanuw::Mem::free(std::string_view ceas)
{
  return ajanuw::Mem::free(ajanuw::CEAS::getAddress(ceas));
}

BOOL ajanuw::Mem::freeEx(HANDLE hProcess, LPVOID addr)
{
  return VirtualFreeEx(hProcess, addr, 0, MEM_RELEASE);
}

BOOL ajanuw::Mem::freeEx(HANDLE hProcess, std::string_view ceas)
{
  return ajanuw::Mem::freeEx(hProcess, ajanuw::CEAS::getAddress(ceas));
}

void ajanuw::Mem::wStr(void *addr, std::string_view str)
{
  ajanuw::sstr::toMem((void *)addr, str);
}

void ajanuw::Mem::wWstr(void *addr, std::wstring_view str)
{
  ajanuw::sstr::toMem((void *)addr, str);
}

void ajanuw::Mem::wUstr(void *addr, std::u16string_view str)
{
  ajanuw::sstr::toMem((void *)addr, str);
}

void ajanuw::Mem::wStrEx(HANDLE hProcess, void *addr, std::string_view str)
{
  ajanuw::sstr::toMemEx(hProcess, (void *)addr, str);
}

void ajanuw::Mem::wWstrEx(HANDLE hProcess, void *addr, std::wstring_view str)
{
  ajanuw::sstr::toMemEx(hProcess, (void *)addr, str);
}

void ajanuw::Mem::wUstrEx(HANDLE hProcess, void *addr, std::u16string_view str)
{
  ajanuw::sstr::toMemEx(hProcess, (void *)addr, str);
}

void ajanuw::Mem::wByte(void *addr, uint8_t byte)
{
  memset(addr, byte, sizeof(uint8_t));
}

void ajanuw::Mem::wBytes(void *addr, const std::span<uint8_t> &bytes, intptr_t max)
{
  auto size = max >= 0 ? max : bytes.size();
  memcpy_s(addr, size, bytes.data(), size);
}

void ajanuw::Mem::wWord(void *addr, uint16_t value)
{
  memcpy_s(addr, sizeof(uint16_t), &value, sizeof(uint16_t));
}
void ajanuw::Mem::wDword(void *addr, uint32_t value)
{
  memcpy_s(addr, sizeof(uint32_t), &value, sizeof(uint32_t));
}
void ajanuw::Mem::wQword(void *addr, uint64_t value)
{
  memcpy_s(addr, sizeof(uint64_t), &value, sizeof(uint64_t));
}
void ajanuw::Mem::wFloat(void *addr, float value)
{
  memcpy_s(addr, sizeof(float), &value, sizeof(float));
}
void ajanuw::Mem::wDouble(void *addr, double value)
{
  memcpy_s(addr, sizeof(double), &value, sizeof(double));
}
void ajanuw::Mem::wRegionToFile(std::string_view filename, void *addr, uintptr_t size)
{
  std::ofstream outFile;
  outFile.open(filename.data());
  for (int i = 0; i < size; i++)
    outFile << *(uint8_t *)((uintptr_t)addr + i);
  outFile.close();
}

void ajanuw::Mem::wByteEx(HANDLE hProcess, void *addr, uint8_t byte)
{
  WriteProcessMemory(hProcess, addr, &byte, sizeof(uint8_t), NULL);
}

void ajanuw::Mem::wBytesEx(HANDLE hProcess, void *addr, const std::span<uint8_t> &bytes, intptr_t max)
{
  auto size = max >= 0 ? max : bytes.size();
  WriteProcessMemory(hProcess, addr, bytes.data(), size, NULL);
}

void ajanuw::Mem::wWordEx(HANDLE hProcess, void *addr, uint16_t value)
{
  WriteProcessMemory(hProcess, addr, &value, sizeof(uint16_t), NULL);
}
void ajanuw::Mem::wDwordEx(HANDLE hProcess, void *addr, uint32_t value)
{
  WriteProcessMemory(hProcess, addr, &value, sizeof(uint32_t), NULL);
}
void ajanuw::Mem::wQwordEx(HANDLE hProcess, void *addr, uint64_t value)
{
  WriteProcessMemory(hProcess, addr, &value, sizeof(uint64_t), NULL);
}
void ajanuw::Mem::wFloatEx(HANDLE hProcess, void *addr, float value)
{
  WriteProcessMemory(hProcess, addr, &value, sizeof(float), NULL);
}
void ajanuw::Mem::wDoubleEx(HANDLE hProcess, void *addr, double value)
{
  WriteProcessMemory(hProcess, addr, &value, sizeof(double), NULL);
}
void ajanuw::Mem::wRegionToFileEx(HANDLE hProcess, std::string_view filename, void *addr, uintptr_t size)
{
  std::ofstream outFile;
  outFile.open(filename.data());
  for (int i = 0; i < size; i++)
    outFile << ajanuw::Mem::rByteEx(hProcess, (uint8_t *)addr + i);
  outFile.close();
}

void ajanuw::Mem::wStr(std::string_view ceas, std::string_view str)
{
  ajanuw::Mem::wStr(ajanuw::CEAS::getAddress(ceas), str);
}
void ajanuw::Mem::wWstr(std::string_view ceas, std::wstring_view str)
{
  ajanuw::Mem::wWstr(ajanuw::CEAS::getAddress(ceas), str);
}
void ajanuw::Mem::wUstr(std::string_view ceas, std::u16string_view str)
{
  ajanuw::Mem::wUstr(ajanuw::CEAS::getAddress(ceas), str);
}
void ajanuw::Mem::wByte(std::string_view ceas, uint8_t byte)
{
  ajanuw::Mem::wByte(ajanuw::CEAS::getAddress(ceas), byte);
}
void ajanuw::Mem::wBytes(std::string_view ceas, const std::span<uint8_t> &bytes, intptr_t max)
{
  ajanuw::Mem::wBytes(ajanuw::CEAS::getAddress(ceas), bytes, max);
}
void ajanuw::Mem::wWord(std::string_view ceas, uint16_t value)
{
  ajanuw::Mem::wWord(ajanuw::CEAS::getAddress(ceas), value);
}
void ajanuw::Mem::wDword(std::string_view ceas, uint32_t value)
{
  ajanuw::Mem::wDword(ajanuw::CEAS::getAddress(ceas), value);
}
void ajanuw::Mem::wQword(std::string_view ceas, uint64_t value)
{
  ajanuw::Mem::wQword(ajanuw::CEAS::getAddress(ceas), value);
}
void ajanuw::Mem::wFloat(std::string_view ceas, float value)
{
  ajanuw::Mem::wFloat(ajanuw::CEAS::getAddress(ceas), value);
}
void ajanuw::Mem::wDouble(std::string_view ceas, double value)
{
  ajanuw::Mem::wDouble(ajanuw::CEAS::getAddress(ceas), value);
}
void ajanuw::Mem::wRegionToFile(std::string_view filename, std::string_view ceas, uintptr_t size)
{
  wRegionToFile(filename, ajanuw::CEAS::getAddress(ceas), size);
}

void ajanuw::Mem::wStrEx(HANDLE hProcess, std::string_view ceas, std::string_view str)
{
  ajanuw::Mem::wStrEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess), str);
}
void ajanuw::Mem::wWstrEx(HANDLE hProcess, std::string_view ceas, std::wstring_view str)
{
  ajanuw::Mem::wWstrEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess), str);
}
void ajanuw::Mem::wUstrEx(HANDLE hProcess, std::string_view ceas, std::u16string_view str)
{
  ajanuw::Mem::wUstrEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess), str);
}
void ajanuw::Mem::wByteEx(HANDLE hProcess, std::string_view ceas, uint8_t byte)
{
  ajanuw::Mem::wByteEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess), byte);
}
void ajanuw::Mem::wBytesEx(HANDLE hProcess, std::string_view ceas, std::span<uint8_t> bytes, intptr_t max)
{
  ajanuw::Mem::wBytesEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess), bytes, max);
}
void ajanuw::Mem::wWordEx(HANDLE hProcess, std::string_view ceas, uint16_t value)
{
  ajanuw::Mem::wWordEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess), value);
}
void ajanuw::Mem::wDwordEx(HANDLE hProcess, std::string_view ceas, uint32_t value)
{
  ajanuw::Mem::wDwordEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess), value);
}
void ajanuw::Mem::wQwordEx(HANDLE hProcess, std::string_view ceas, uint64_t value)
{
  ajanuw::Mem::wQwordEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess), value);
}
void ajanuw::Mem::wFloatEx(HANDLE hProcess, std::string_view ceas, float value)
{
  ajanuw::Mem::wFloatEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess), value);
}
void ajanuw::Mem::wDoubleEx(HANDLE hProcess, std::string_view ceas, double value)
{
  ajanuw::Mem::wDoubleEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess), value);
}

void ajanuw::Mem::wRegionToFileEx(HANDLE hProcess, std::string_view filename, std::string_view ceas, size_t size)
{
  ajanuw::Mem::wRegionToFileEx(hProcess, filename, ajanuw::CEAS::getAddress(ceas, hProcess), size);
}

std::string ajanuw::Mem::rStr(char *addr, size_t max)
{
  return ajanuw::sstr::strFormMem(addr, max);
}
std::wstring ajanuw::Mem::rWstr(wchar_t *addr, size_t max)
{
  return ajanuw::sstr::wstrFormMem(addr, max);
}
std::u16string ajanuw::Mem::rUstr(char16_t *addr, size_t max)
{
  return ajanuw::sstr::ustrFormMem(addr, max);
}

std::string ajanuw::Mem::rStrEx(HANDLE hProcess, char *addr, size_t max)
{
  return ajanuw::sstr::strFormMemEx(hProcess, addr, max);
}

std::wstring ajanuw::Mem::rWstrEx(HANDLE hProcess, wchar_t *addr, size_t max)
{
  return ajanuw::sstr::wstrFormMemEx(hProcess, addr, max);
}

std::u16string ajanuw::Mem::rUstrEx(HANDLE hProcess, char16_t *addr, size_t max)
{
  return ajanuw::sstr::ustrFormMemEx(hProcess, addr, max);
}

std::string ajanuw::Mem::rStr(std::string_view ceas, size_t max)
{
  return ajanuw::Mem::rStr((char *)ajanuw::CEAS::getAddress(ceas), max);
}
std::wstring ajanuw::Mem::rWstr(std::string_view ceas, size_t max)
{
  return ajanuw::Mem::rWstr((wchar_t *)ajanuw::CEAS::getAddress(ceas), max);
}
std::u16string ajanuw::Mem::rUstr(std::string_view ceas, size_t max)
{
  return ajanuw::Mem::rUstr((char16_t *)ajanuw::CEAS::getAddress(ceas), max);
}

std::string ajanuw::Mem::rStrEx(HANDLE hProcess, std::string_view ceas, size_t max)
{
  return ajanuw::Mem::rStrEx(hProcess, (char *)ajanuw::CEAS::getAddress(ceas, hProcess), max);
}
std::wstring ajanuw::Mem::rWstrEx(HANDLE hProcess, std::string_view ceas, size_t max)
{
  return ajanuw::Mem::rWstrEx(hProcess, (wchar_t *)ajanuw::CEAS::getAddress(ceas, hProcess), max);
}
std::u16string ajanuw::Mem::rUstrEx(HANDLE hProcess, std::string_view ceas, size_t max)
{
  return ajanuw::Mem::rUstrEx(hProcess, (char16_t *)ajanuw::CEAS::getAddress(ceas, hProcess), max);
}

std::vector<uint8_t> ajanuw::Mem::rBytes(void *addr, size_t size)
{
  std::vector<uint8_t> bytes(size);
  memcpy_s(bytes.data(), size, addr, size);
  return bytes;
}

uint8_t ajanuw::Mem::rByte(void *addr)
{
  return *(uint8_t *)addr;
}

uint16_t ajanuw::Mem::rWord(void *addr)
{
  return *(uint16_t *)addr;
}
uint32_t ajanuw::Mem::rDword(void *addr)
{
  return *(uint32_t *)addr;
}
uint64_t ajanuw::Mem::rQword(void *addr)
{
  return *(uint64_t *)addr;
}

uintptr_t ajanuw::Mem::rPointer(void *addr)
{
  return *(uintptr_t *)addr;
}

float ajanuw::Mem::rFloat(void *addr)
{
  return *(float *)addr;
}

double ajanuw::Mem::rDouble(void *addr)
{
  return *(double *)addr;
}

void ajanuw::Mem::rRegionFromFile(std::string_view fileame, void *addr)
{
  rRegionFromFile(fileame, addr, NULL);
}

void ajanuw::Mem::rRegionFromFile(std::string_view fileame, void *addr, size_t *fileSize)
{
  std::ifstream inFile;
  inFile.open(fileame.data());
  uintptr_t offset = (uintptr_t)addr;
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

std::vector<uint8_t> ajanuw::Mem::rBytesEx(HANDLE hProcess, void *addr, uintptr_t size)
{
  std::vector<uint8_t> bytes(size);
  ReadProcessMemory(hProcess, addr, bytes.data(), size, NULL);
  return bytes;
}

uint8_t ajanuw::Mem::rByteEx(HANDLE hProcess, void *addr)
{
  uint8_t r;
  ReadProcessMemory(hProcess, addr, &r, sizeof(uint8_t), NULL);
  return r;
}

uint16_t ajanuw::Mem::rWordEx(HANDLE hProcess, void *addr)
{
  uint16_t r;
  ReadProcessMemory(hProcess, addr, &r, sizeof(uint16_t), NULL);
  return r;
}
uint32_t ajanuw::Mem::rDwordEx(HANDLE hProcess, void *addr)
{
  uint32_t r;
  ReadProcessMemory(hProcess, addr, &r, sizeof(uint32_t), NULL);
  return r;
}
uint64_t ajanuw::Mem::rQwordEx(HANDLE hProcess, void *addr)
{
  uint64_t r;
  ReadProcessMemory(hProcess, addr, &r, sizeof(uint64_t), NULL);
  return r;
}

uintptr_t ajanuw::Mem::rPointerEx(HANDLE hProcess, void *addr)
{
  uint32_t pid = GetProcessId(hProcess);
  bool isx64 = ajanuw::PE::isX64(pid, (HMODULE)ajanuw::PE::GetModuleBase(pid).lpBaseOfDll);
  if (isx64)
  {
    uint64_t r;
    ReadProcessMemory(hProcess, addr, &r, sizeof(uint64_t), NULL);
    return r;
  }
  else
  {
    uint32_t r;
    ReadProcessMemory(hProcess, addr, &r, sizeof(uint32_t), NULL);
    return r;
  }
}

float ajanuw::Mem::rFloatEx(HANDLE hProcess, void *addr)
{
  float r;
  ReadProcessMemory(hProcess, addr, &r, sizeof(float), NULL);
  return r;
}

double ajanuw::Mem::rDoubleEx(HANDLE hProcess, void *addr)
{
  double r;
  ReadProcessMemory(hProcess, addr, &r, sizeof(float), NULL);
  return r;
}

void ajanuw::Mem::rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, void *addr)
{
  rRegionFromFileEx(hProcess, fileame, addr, NULL);
}

void ajanuw::Mem::rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, void *addr, size_t *fileSize)
{
  std::ifstream inFile;
  inFile.open(fileame.data());
  uintptr_t offset = (uintptr_t)addr;
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

std::vector<uint8_t> ajanuw::Mem::rBytes(std::string_view ceas, uintptr_t size)
{
  return ajanuw::Mem::rBytes(ajanuw::CEAS::getAddress(ceas), size);
}

uint8_t ajanuw::Mem::rByte(std::string_view ceas)
{
  return ajanuw::Mem::rByte(ajanuw::CEAS::getAddress(ceas));
}

uint16_t ajanuw::Mem::rWord(std::string_view ceas)
{
  return ajanuw::Mem::rWord(ajanuw::CEAS::getAddress(ceas));
}

uint32_t ajanuw::Mem::rDword(std::string_view ceas)
{
  return ajanuw::Mem::rDword(ajanuw::CEAS::getAddress(ceas));
}

uint64_t ajanuw::Mem::rQword(std::string_view ceas)
{
  return ajanuw::Mem::rQword(ajanuw::CEAS::getAddress(ceas));
}

uintptr_t ajanuw::Mem::rPointer(std::string_view ceas)
{
  return ajanuw::Mem::rPointer(ajanuw::CEAS::getAddress(ceas));
}

float ajanuw::Mem::rFloat(std::string_view ceas)
{
  return ajanuw::Mem::rFloat(ajanuw::CEAS::getAddress(ceas));
}

double ajanuw::Mem::rDouble(std::string_view ceas)
{
  return ajanuw::Mem::rDouble(ajanuw::CEAS::getAddress(ceas));
}

void ajanuw::Mem::rRegionFromFile(std::string_view fileame, std::string_view ceas)
{
  ajanuw::Mem::rRegionFromFile(fileame, ajanuw::CEAS::getAddress(ceas));
}

void ajanuw::Mem::rRegionFromFile(std::string_view fileame, std::string_view ceas, size_t *fileSize)
{
  ajanuw::Mem::rRegionFromFile(fileame, ajanuw::CEAS::getAddress(ceas), fileSize);
}

std::vector<uint8_t> ajanuw::Mem::rBytesEx(HANDLE hProcess, std::string_view ceas, uintptr_t size)
{
  return ajanuw::Mem::rBytesEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess), size);
}

uint8_t ajanuw::Mem::rByteEx(HANDLE hProcess, std::string_view ceas)
{
  return ajanuw::Mem::rByteEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess));
}

uint16_t ajanuw::Mem::rWordEx(HANDLE hProcess, std::string_view ceas)
{
  return ajanuw::Mem::rWordEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess));
}

uint32_t ajanuw::Mem::rDwordEx(HANDLE hProcess, std::string_view ceas)
{
  return ajanuw::Mem::rDwordEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess));
}

uint64_t ajanuw::Mem::rQwordEx(HANDLE hProcess, std::string_view ceas)
{
  return ajanuw::Mem::rQwordEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess));
}

uintptr_t ajanuw::Mem::rPointerEx(HANDLE hProcess, std::string_view ceas)
{
  return ajanuw::Mem::rPointerEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess));
}

float ajanuw::Mem::rFloatEx(HANDLE hProcess, std::string_view ceas)
{
  return ajanuw::Mem::rFloatEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess));
}

double ajanuw::Mem::rDoubleEx(HANDLE hProcess, std::string_view ceas)
{
  return ajanuw::Mem::rDoubleEx(hProcess, ajanuw::CEAS::getAddress(ceas, hProcess));
}

void ajanuw::Mem::rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, std::string_view ceas)
{
  ajanuw::Mem::rRegionFromFileEx(hProcess, fileame, ajanuw::CEAS::getAddress(ceas, hProcess));
}

void ajanuw::Mem::rRegionFromFileEx(HANDLE hProcess, std::string_view fileame, std::string_view ceas, size_t *fileSize)
{
  ajanuw::Mem::rRegionFromFileEx(hProcess, fileame, ajanuw::CEAS::getAddress(ceas, hProcess), fileSize);
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
  auto self = reinterpret_cast<Gui::Win32 *>(Gui::Win32::Win32::hwndMap[hWnd]);
  if (self)
    r = self->OnReceiveMessage(hWnd, message, wParam, lParam);

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
  if (_hWnd)
    return 0;
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
  if (_hWnd)
    return 0;
  _hWnd = CreateWindowA(
      className.c_str(),
      windowName.c_str(),
      style,
      x, y,
      width, height,
      NULL, NULL, NULL, NULL);

  if (!_hWnd)
    return FALSE;
  std::wstring ws = ajanuw::sstr::strToWstr(windowName);
  SetWindowTextW(_hWnd, ws.c_str());
  hwndMap[_hWnd] = (uintptr_t)this;
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
  auto ws = ajanuw::sstr::strToWstr(opt->windowName);
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
      memory(ajanuw::Mem::alloc(size))
{
  if (!memory)
    throw std::exception("VAManage alloc fail.");
}

ajanuw::Mem::VAManage::VAManage(size_t size, HANDLE hProcess)
    : size(size),
      hProcess(hProcess),
      memory(!hProcess ? ajanuw::Mem::alloc(size) : ajanuw::Mem::allocEx(hProcess, size))
{
  if (!memory)
    throw std::exception("VAManage alloc fail.");
}

std::vector<uint8_t> ajanuw::Mem::VAManage::read(size_t _size)
{
  return !hProcess ? ajanuw::Mem::rBytes(ptr(), _size) : ajanuw::Mem::rBytesEx(hProcess, ptr(), _size);
}

uint8_t ajanuw::Mem::VAManage::readByte()
{
  return !hProcess ? ajanuw::Mem::rByte(ptr()) : ajanuw::Mem::rByteEx(hProcess, ptr());
}

uint16_t ajanuw::Mem::VAManage::readWord()
{
  return !hProcess ? ajanuw::Mem::rWord(ptr()) : ajanuw::Mem::rWordEx(hProcess, ptr());
}

uint32_t ajanuw::Mem::VAManage::readDword()
{
  return !hProcess ? ajanuw::Mem::rDword(ptr()) : ajanuw::Mem::rDwordEx(hProcess, ptr());
}

uint64_t ajanuw::Mem::VAManage::readQword()
{
  return !hProcess ? ajanuw::Mem::rQword(ptr()) : ajanuw::Mem::rQwordEx(hProcess, ptr());
}

float ajanuw::Mem::VAManage::readFloat()
{
  return !hProcess ? ajanuw::Mem::rFloat(ptr()) : ajanuw::Mem::rFloatEx(hProcess, ptr());
}

double ajanuw::Mem::VAManage::readDouble()
{
  return !hProcess ? ajanuw::Mem::rDouble(ptr()) : ajanuw::Mem::rDoubleEx(hProcess, ptr());
}

std::string ajanuw::Mem::VAManage::readStr(size_t maxSize)
{
  return !hProcess ? ajanuw::Mem::rStr((char *)ptr(), maxSize) : ajanuw::Mem::rStrEx(hProcess, (char *)ptr(), maxSize);
}

std::wstring ajanuw::Mem::VAManage::readWstr(size_t maxSize)
{
  return !hProcess ? ajanuw::Mem::rWstr((wchar_t *)ptr(), maxSize) : ajanuw::Mem::rWstrEx(hProcess, (wchar_t *)ptr(), maxSize);
}

std::u16string ajanuw::Mem::VAManage::readUstr(size_t maxSize)
{
  return !hProcess ? ajanuw::Mem::rUstr((char16_t *)ptr(), maxSize) : ajanuw::Mem::rUstrEx(hProcess, (char16_t *)ptr(), maxSize);
}

void ajanuw::Mem::VAManage::write(const std::span<uint8_t> &table, intptr_t max)
{
  !hProcess ? ajanuw::Mem::wBytes(ptr(), table, max) : ajanuw::Mem::wBytesEx(hProcess, ptr(), table, max);
  position += max >= 0 ? max : table.size();
}

void ajanuw::Mem::VAManage::writeByte(uint8_t v)
{
  !hProcess ? ajanuw::Mem::wByte(ptr(), v) : ajanuw::Mem::wByteEx(hProcess, ptr(), v);
  position++;
}

void ajanuw::Mem::VAManage::writeWord(uint16_t v)
{
  !hProcess ? ajanuw::Mem::wWord(ptr(), v) : ajanuw::Mem::wWordEx(hProcess, ptr(), v);
  position += sizeof(uint16_t);
}

void ajanuw::Mem::VAManage::writeDword(uint32_t v)
{
  !hProcess ? ajanuw::Mem::wDword(ptr(), v) : ajanuw::Mem::wDwordEx(hProcess, ptr(), v);
  position += sizeof(uint32_t);
}

void ajanuw::Mem::VAManage::writeQword(uintptr_t v)
{
  !hProcess ? ajanuw::Mem::wQword(ptr(), v) : ajanuw::Mem::wQwordEx(hProcess, ptr(), v);
  position += sizeof(uint64_t);
}

void ajanuw::Mem::VAManage::writeFloat(float v)
{
  !hProcess ? ajanuw::Mem::wFloat(ptr(), v) : ajanuw::Mem::wFloatEx(hProcess, ptr(), v);
  position += sizeof(float);
}

void ajanuw::Mem::VAManage::writeDouble(double v)
{
  !hProcess ? ajanuw::Mem::wDouble(ptr(), v) : ajanuw::Mem::wDoubleEx(hProcess, ptr(), v);
  position += sizeof(double);
}

void ajanuw::Mem::VAManage::writeStr(std::string_view str)
{
  !hProcess ? ajanuw::Mem::wStr(ptr(), str) : ajanuw::Mem::wStrEx(hProcess, ptr(), str);
  position += ajanuw::sstr::count(str);
}

void ajanuw::Mem::VAManage::writeWstr(std::wstring_view wstr)
{
  !hProcess ? ajanuw::Mem::wWstr(ptr(), wstr) : ajanuw::Mem::wWstrEx(hProcess, ptr(), wstr);
  position += ajanuw::sstr::count(wstr);
}

void ajanuw::Mem::VAManage::writeUstr(std::u16string_view ustr)
{
  !hProcess ? ajanuw::Mem::wUstr(ptr(), ustr) : ajanuw::Mem::wUstrEx(hProcess, ptr(), ustr);
  position += ajanuw::sstr::count(ustr);
}

void ajanuw::Mem::VAManage::loadFromFile(std::string_view filename)
{
  !hProcess ? ajanuw::Mem::rRegionFromFile(filename, ptr(), &position) : ajanuw::Mem::rRegionFromFileEx(hProcess, filename, ptr(), &position);
}

void ajanuw::Mem::VAManage::saveToFile(std::string_view filename)
{
  !hProcess ? ajanuw::Mem::wRegionToFile(filename, ptr(), size) : ajanuw::Mem::wRegionToFileEx(hProcess, filename, ptr(), size);
}

BOOL ajanuw::Mem::VAManage::destroy()
{
  return memory ? !hProcess ? ajanuw::Mem::free(memory) : ajanuw::Mem::freeEx(hProcess, memory) : FALSE;
}

#define EXCE_CODE(code) \
  err = code;           \
  if (err)              \
    throw std::exception(std::format("AsmParser ERROR: {:08x} ({})", err, DebugUtils::errorAsString(err)).data());

uintptr_t ajanuw::Asm::AAScript::aa(std::string_view asmString, uintptr_t rcx = 0)
{
  asmjit::Error err;
  JitRuntime rt;
  CodeHolder code;
  EXCE_CODE(code.init(rt.environment()));

  x86::Assembler a(&code);
  AsmParser p(&a);

  EXCE_CODE(p.parse(asmString.data()));

  Func fn;
  EXCE_CODE(rt.add(&fn, &code));

  uintptr_t r = fn(rcx);
  EXCE_CODE(rt.release(fn));

  return r;
}

std::vector<uint8_t> ajanuw::Asm::AAScript::asmBytes(std::string_view asmString, bool isX64)
{
  CodeHolder code;
  asmjit::Error err;
  Environment env = hostEnvironment();
  env.setArch(isX64 ? Environment::kArchX64 : Environment::kArchX86);
  EXCE_CODE(code.init(env));

  x86::Assembler a(&code);
  AsmParser p(&a);
  EXCE_CODE(p.parse(asmString.data()));

  std::vector<uint8_t> r(a.offset());
  memcpy_s(r.data(), r.size(), a.bufferData(), r.size());
  return r;
}

std::map<std::string, LPVOID> ajanuw::Symbol::symbols;
void ajanuw::Symbol::registerSymbol(std::string symbolname, LPVOID address)
{
  ajanuw::Symbol::symbols[symbolname] = address;
}

void ajanuw::Symbol::unregisterSymbol(std::string_view symbolname)
{
  ajanuw::Symbol::symbols.erase(symbolname.data());
}

LPVOID ajanuw::Symbol::get(std::string_view symbolname)
{
  if (ajanuw::Symbol::symbols.count(symbolname.data()) == NULL)
    return NULL;
  return ajanuw::Symbol::symbols.at(symbolname.data());
}

bool ajanuw::Symbol::has(std::string_view symbolname)
{
  return ajanuw::Symbol::symbols.count(symbolname.data()) != NULL;
}

LPVOID ajanuw::CEAS::getAddress(std::string_view ceas, HANDLE hProcess)
{
  auto node = ces::parse(ceas.data());
  if (!node)
    return NULL;
  // printf("id:%d\n", node->id());

  Interpreter interpreter{hProcess, ceas};
  auto addr = (LPVOID)interpreter.visit(node);
  delete node;
  return addr;
}
uint32_t ajanuw::PE::GetPID(std::string_view name)
{
  return ajanuw::PE::GetPID(ajanuw::sstr::strToWstr(name));
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
            ajanuw::sstr::icmp(ajanuw::PE::GetModuleName(me.szModule), moduleName) ||
            ajanuw::sstr::icmp(me.szModule, moduleName))
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

MODULEINFO ajanuw::PE::GetModuleInfo(std::string_view moduleName, uint32_t pid)
{
  return ajanuw::PE::GetModuleInfo(ajanuw::sstr::strToWstr(moduleName), pid);
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

    if (ajanuw::sstr::icmp(funme, method))
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

uint8_t *ajanuw::PE::GetProcAddress(uint32_t pid, HMODULE hModule, std::wstring_view method)
{
  return ajanuw::PE::GetProcAddress(pid, hModule, ajanuw::sstr::wstrToStr(method));
}
ajanuw::CEAS::Interpreter::Interpreter(HANDLE hProcess, std::string_view source)
    : source(source), hProcess(hProcess)
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

uintptr_t ajanuw::CEAS::Interpreter::visit(ces::BaseNode *node)
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
    throw ces::runtime_error(source, node->loc, "Unexpected Node");
  }
}

uintptr_t ajanuw::CEAS::Interpreter::visitHex(ces::HexNode *node)
{
  return std::stoull(node->value, nullptr, 16);
}

uintptr_t ajanuw::CEAS::Interpreter::visitIdent(ces::IdentsNode *node)
{
  // 优先级 SYMBOL -> HEX -> MODULE
  if (node->idents->size() == 1)
  {
    auto val = *node->idents->begin();
    if (ajanuw::Symbol::has(val))
      return (uintptr_t)ajanuw::Symbol::get(val);
    else if (std::all_of(val.begin(), val.end(), ::isxdigit))
      return std::stoull(val, nullptr, 16);
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
            r = (uintptr_t)ajanuw::PE::GetProcAddress(pid, (HMODULE)me.modBaseAddr, val);
            if (r != NULL)
              break;
          } while (Module32Next(hSnap, &me));
        }
      }
      CloseHandle(hSnap);
      if (!r)
        throw ces::runtime_error(source, node->loc, std::format("Symbol not found '{}'", val));
      return r;
    }
  }
  else
  {
    auto last = node->idents->back();
    node->idents->pop_back();
    auto first = ajanuw::sstr::join(*node->idents, ".");
    // user32.messageboxa
    // user32.dll
    // node.exe
    if (last == "dll" || last == "exe")
    {
      auto hModule = (HMODULE)(PE::GetModuleInfo(ajanuw::sstr::strToWstr(first), pid).lpBaseOfDll);
      if (!hModule)
        throw ces::runtime_error(source, node->loc, std::format("Module not found '{}'", first));
      return (uintptr_t)hModule;
    }

    auto hModule = (HMODULE)(PE::GetModuleInfo(ajanuw::sstr::strToWstr(first), pid).lpBaseOfDll);
    if (!hModule)
      throw ces::runtime_error(source, node->loc, std::format("Module not found '{}'", first));

    auto hMethod = (uintptr_t)PE::GetProcAddress(pid, hModule, last);
    if (!hMethod)
      throw ces::runtime_error(source, node->loc, std::format("Symbol not found '{}'", last));
    return (uintptr_t)hMethod;
  }
}

uintptr_t ajanuw::CEAS::Interpreter::visitUnary(ces::UnaryNode *node)
{
  auto value = visit(node->node);
  switch (node->op)
  {
  case ces::parser::token::MINUS:
    return value * -1;
  case ces::parser::token::PLUS:
    return value;
  default:
    throw ces::runtime_error(source, node->loc, "Unexpected unary expression");
  }
  return value;
}

uintptr_t ajanuw::CEAS::Interpreter::visitPointer(ces::PointerNode *node)
{
  auto address = visit(node->node);
  uintptr_t result = NULL;
  if (ReadProcessMemory(!hProcess ? GetCurrentProcess() : hProcess, (LPCVOID)address, (LPVOID)&result, isX86 ? 4 : 8, NULL))
    return result;
  throw ces::runtime_error(source, node->loc, "Failed to read pointer");
}

uintptr_t ajanuw::CEAS::Interpreter::visitBinary(ces::BinaryNode *node)
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
      throw ces::runtime_error(source, node->loc, "Infinity");
    return left / right;
  }
  case ces::parser::token::POW:
    return pow(left, right);

  default:
    throw ces::runtime_error(source, node->loc, "Unexpected binary expression");
  }
}
