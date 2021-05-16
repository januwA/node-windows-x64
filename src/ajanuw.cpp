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

bool ajanuw::SSString::startWith(std::string str, const char *s2, size_t index)
{
  return str.find(s2) - index == 0;
}

bool ajanuw::SSString::endWith(std::string str, const char *s2)
{
  return str.rfind(s2) + strlen(s2) == str.size();
}

bool ajanuw::SSString::endWith(std::string str, const char *s2, size_t length)
{
  return str.rfind(s2) + strlen(s2) == length;
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
  std::vector<BYTE> byteList;
  for (size_t i = 0; i < byteStrList.size(); i++)
  {
    byteList.push_back(std::stol(byteStrList[i], nullptr, 16));
  }
  return byteList;
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
  size_t size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, NULL);
  if (size == NULL)
    return wideStr;

  wideStr.resize(size);
  MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), (LPWSTR)wideStr.data(), wideStr.length());
  return wideStr;
}

std::u16string ajanuw::SSString::strToUstr(std::string str)
{
  std::u16string wideStr;
  size_t size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, NULL);
  if (size == NULL)
    return wideStr;

  wideStr.resize(size);
  MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), (LPWSTR)wideStr.data(), wideStr.length());
  return wideStr;
}

std::string ajanuw::SSString::ustrToStr(std::u16string ustr)
{
  std::string str;
  size_t size = WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)ustr.data(), ustr.length(), NULL, NULL, 0, 0);
  if (size == NULL)
    return str;

  str.resize(size);
  WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)ustr.data(), ustr.length(), (LPSTR)str.data(), str.length(), 0, 0);
  return str;
}

std::string ajanuw::SSString::wstrToStr(std::wstring wstr)
{
  std::string str;
  size_t size = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), wstr.length(), NULL, NULL, 0, 0);
  if (size == NULL)
    return str;

  str.resize(size);
  WideCharToMultiByte(CP_UTF8, 0, wstr.data(), wstr.length(), (LPSTR)str.data(), str.length(), 0, 0);
  return str;
}

std::wstring ajanuw::SSString::ustrToWstr(std::u16string ustr)
{
  return std::wstring(ustr.begin(), ustr.end());
}

std::u16string ajanuw::SSString::wstrToUstr(std::wstring wstr)
{
  return std::u16string(wstr.begin(), wstr.end());
}

void ajanuw::SSString::toMem(void *dst, std::string str)
{
  memcpy_s(dst, str.length(), str.c_str(), str.length());
}

void ajanuw::SSString::toMem(void *dst, std::wstring str)
{
  size_t count = ajanuw::SSString::count(str);
  memcpy_s(dst, count, str.c_str(), count);
}

void ajanuw::SSString::toMem(void *dst, std::u16string str)
{
  size_t count = ajanuw::SSString::count(str);
  memcpy_s(dst, count, str.c_str(), count);
}

void ajanuw::SSString::toMemEx(HANDLE hProcess, void *dst, std::string str)
{
  WriteProcessMemory(hProcess, dst, str.c_str(), str.length(), NULL);
}

void ajanuw::SSString::toMemEx(HANDLE hProcess, void *dst, std::wstring str)
{
  size_t count = ajanuw::SSString::count(str);
  WriteProcessMemory(hProcess, dst, str.c_str(), count, NULL);
}

void ajanuw::SSString::toMemEx(HANDLE hProcess, void *dst, std::u16string str)
{
  size_t count = ajanuw::SSString::count(str);
  WriteProcessMemory(hProcess, dst, str.c_str(), count, NULL);
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

std::string ajanuw::SSString::strFormMemEx(HANDLE hProcess, void *src, size_t max)
{
  std::string str;
  uintptr_t addr = (uintptr_t)src;
  while (true)
  {
    BYTE wc = ajanuw::Mem::rByteEx(hProcess, (BYTE *)addr);
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

void ajanuw::Mem::wStr(void *lpAddress, std::string str)
{
  ajanuw::SSString::toMem((void *)lpAddress, str);
}

void ajanuw::Mem::wWstr(void *lpAddress, std::wstring str)
{
  ajanuw::SSString::toMem((void *)lpAddress, str);
}

void ajanuw::Mem::wUstr(void *lpAddress, std::u16string str)
{
  ajanuw::SSString::toMem((void *)lpAddress, str);
}

void ajanuw::Mem::wStrEx(HANDLE hProcess, void *lpAddress, std::string str)
{
  ajanuw::SSString::toMemEx(hProcess, (void *)lpAddress, str);
}

void ajanuw::Mem::wWstrEx(HANDLE hProcess, void *lpAddress, std::wstring str)
{
  ajanuw::SSString::toMemEx(hProcess, (void *)lpAddress, str);
}

void ajanuw::Mem::wUstrEx(HANDLE hProcess, void *lpAddress, std::u16string str)
{
  ajanuw::SSString::toMemEx(hProcess, (void *)lpAddress, str);
}

void ajanuw::Mem::wByte(void *lpAddress, BYTE byte)
{
  memset(lpAddress, byte, sizeof(BYTE));
}

void ajanuw::Mem::wBytes(void *lpAddress, std::vector<BYTE> bytes)
{
  memcpy_s(lpAddress, bytes.size(), bytes.data(), bytes.size());
}

void ajanuw::Mem::wWord(void *lpAddress, WORD value)
{
  memcpy_s(lpAddress, sizeof(WORD), &value, sizeof(WORD));
}
void ajanuw::Mem::wDword(void *lpAddress, DWORD value)
{
  memcpy_s(lpAddress, sizeof(DWORD), &value, sizeof(DWORD));
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
void ajanuw::Mem::wRegionToFile(std::string filename, void *lpAddress, uintptr_t size)
{
  std::ofstream outFile;
  outFile.open(filename.c_str());
  for (int i = 0; i < size; i++)
    outFile << *(BYTE *)((uintptr_t)lpAddress + i);
  outFile.close();
}

void ajanuw::Mem::wByteEx(HANDLE hProcess, void *lpAddress, BYTE byte)
{
  WriteProcessMemory(hProcess, lpAddress, &byte, sizeof(BYTE), NULL);
}

void ajanuw::Mem::wBytesEx(HANDLE hProcess, void *lpAddress, std::vector<BYTE> bytes)
{
  WriteProcessMemory(hProcess, lpAddress, bytes.data(), bytes.size(), NULL);
}

void ajanuw::Mem::wWordEx(HANDLE hProcess, void *lpAddress, WORD value)
{
  WriteProcessMemory(hProcess, lpAddress, &value, sizeof(WORD), NULL);
}
void ajanuw::Mem::wDwordEx(HANDLE hProcess, void *lpAddress, DWORD value)
{
  WriteProcessMemory(hProcess, lpAddress, &value, sizeof(DWORD), NULL);
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
void ajanuw::Mem::wRegionToFileEx(HANDLE hProcess, std::string filename, void *lpAddress, uintptr_t size)
{
  std::ofstream outFile;
  outFile.open(filename.c_str());
  for (int i = 0; i < size; i++)
    outFile << ajanuw::Mem::rByteEx(hProcess, (BYTE *)lpAddress + i);
  outFile.close();
}

void ajanuw::Mem::wStr(std::string CEAddressString, std::string str)
{
  ajanuw::Mem::wStr(ajanuw::CEAddressString::getAddress(CEAddressString), str);
}
void ajanuw::Mem::wWstr(std::string CEAddressString, std::wstring str)
{
  ajanuw::Mem::wWstr(ajanuw::CEAddressString::getAddress(CEAddressString), str);
}
void ajanuw::Mem::wUstr(std::string CEAddressString, std::u16string str)
{
  ajanuw::Mem::wUstr(ajanuw::CEAddressString::getAddress(CEAddressString), str);
}
void ajanuw::Mem::wByte(std::string CEAddressString, BYTE byte)
{
  ajanuw::Mem::wByte(ajanuw::CEAddressString::getAddress(CEAddressString), byte);
}
void ajanuw::Mem::wBytes(std::string CEAddressString, std::vector<BYTE> bytes)
{
  ajanuw::Mem::wBytes(ajanuw::CEAddressString::getAddress(CEAddressString), bytes);
}
void ajanuw::Mem::wWord(std::string CEAddressString, WORD value)
{
  ajanuw::Mem::wWord(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}
void ajanuw::Mem::wDword(std::string CEAddressString, DWORD value)
{
  ajanuw::Mem::wDword(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}
void ajanuw::Mem::wQword(std::string CEAddressString, uint64_t value)
{
  ajanuw::Mem::wQword(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}
void ajanuw::Mem::wFloat(std::string CEAddressString, float value)
{
  ajanuw::Mem::wFloat(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}
void ajanuw::Mem::wDouble(std::string CEAddressString, double value)
{
  ajanuw::Mem::wDouble(ajanuw::CEAddressString::getAddress(CEAddressString), value);
}
void ajanuw::Mem::wRegionToFile(std::string filename, std::string CEAddressString, uintptr_t size)
{
  wRegionToFile(filename, ajanuw::CEAddressString::getAddress(CEAddressString), size);
}

void ajanuw::Mem::wStrEx(HANDLE hProcess, std::string CEAddressString, std::string str)
{
  ajanuw::Mem::wStrEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), str);
}
void ajanuw::Mem::wWstrEx(HANDLE hProcess, std::string CEAddressString, std::wstring str)
{
  ajanuw::Mem::wWstrEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), str);
}
void ajanuw::Mem::wUstrEx(HANDLE hProcess, std::string CEAddressString, std::u16string str)
{
  ajanuw::Mem::wUstrEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), str);
}
void ajanuw::Mem::wByteEx(HANDLE hProcess, std::string CEAddressString, BYTE byte)
{
  ajanuw::Mem::wByteEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), byte);
}
void ajanuw::Mem::wBytesEx(HANDLE hProcess, std::string CEAddressString, std::vector<BYTE> bytes)
{
  ajanuw::Mem::wBytesEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), bytes);
}
void ajanuw::Mem::wWordEx(HANDLE hProcess, std::string CEAddressString, WORD value)
{
  ajanuw::Mem::wWordEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), value);
}
void ajanuw::Mem::wDwordEx(HANDLE hProcess, std::string CEAddressString, DWORD value)
{
  ajanuw::Mem::wDwordEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), value);
}
void ajanuw::Mem::wQwordEx(HANDLE hProcess, std::string CEAddressString, uint64_t value)
{
  ajanuw::Mem::wQwordEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), value);
}
void ajanuw::Mem::wFloatEx(HANDLE hProcess, std::string CEAddressString, float value)
{
  ajanuw::Mem::wFloatEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), value);
}
void ajanuw::Mem::wDoubleEx(HANDLE hProcess, std::string CEAddressString, double value)
{
  ajanuw::Mem::wDoubleEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), value);
}

void ajanuw::Mem::wRegionToFileEx(HANDLE hProcess, std::string filename, std::string CEAddressString, uintptr_t size)
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

std::string ajanuw::Mem::rStr(std::string CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::rStr((char *)ajanuw::CEAddressString::getAddress(CEAddressString), max);
}
std::wstring ajanuw::Mem::rWstr(std::string CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::rWstr((wchar_t *)ajanuw::CEAddressString::getAddress(CEAddressString), max);
}
std::u16string ajanuw::Mem::rUstr(std::string CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::rUstr((char16_t *)ajanuw::CEAddressString::getAddress(CEAddressString), max);
}

std::string ajanuw::Mem::rStrEx(HANDLE hProcess, std::string CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::rStrEx(hProcess, (char *)ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), max);
}
std::wstring ajanuw::Mem::rWstrEx(HANDLE hProcess, std::string CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::rWstrEx(hProcess, (wchar_t *)ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), max);
}
std::u16string ajanuw::Mem::rUstrEx(HANDLE hProcess, std::string CEAddressString, uintptr_t max)
{
  return ajanuw::Mem::rUstrEx(hProcess, (char16_t *)ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), max);
}

std::vector<BYTE> ajanuw::Mem::rBytes(void *lpAddress, uintptr_t size)
{
  std::vector<BYTE> bytes(size);
  memcpy_s(bytes.data(), size, lpAddress, size);
  return bytes;
}

BYTE ajanuw::Mem::rByte(void *lpAddress)
{
  return *(BYTE *)lpAddress;
}

WORD ajanuw::Mem::rWord(void *lpAddress)
{
  return *(WORD *)lpAddress;
}
DWORD ajanuw::Mem::rDword(void *lpAddress)
{
  return *(DWORD *)lpAddress;
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

void ajanuw::Mem::rRegionFromFile(std::string fileame, void *lpAddress)
{
  rRegionFromFile(fileame, lpAddress, NULL);
}

void ajanuw::Mem::rRegionFromFile(std::string fileame, void *lpAddress, size_t *fileSize)
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

std::vector<BYTE> ajanuw::Mem::rBytesEx(HANDLE hProcess, void *lpAddress, uintptr_t size)
{
  std::vector<BYTE> bytes(size);
  ReadProcessMemory(hProcess, lpAddress, bytes.data(), size, NULL);
  return bytes;
}

BYTE ajanuw::Mem::rByteEx(HANDLE hProcess, void *lpAddress)
{
  BYTE r;
  ReadProcessMemory(hProcess, lpAddress, &r, sizeof(BYTE), NULL);
  return r;
}

WORD ajanuw::Mem::rWordEx(HANDLE hProcess, void *lpAddress)
{
  WORD r;
  ReadProcessMemory(hProcess, lpAddress, &r, sizeof(WORD), NULL);
  return r;
}
DWORD ajanuw::Mem::rDwordEx(HANDLE hProcess, void *lpAddress)
{
  DWORD r;
  ReadProcessMemory(hProcess, lpAddress, &r, sizeof(DWORD), NULL);
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
  DWORD pid = GetProcessId(hProcess);

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

void ajanuw::Mem::rRegionFromFileEx(HANDLE hProcess, std::string fileame, void *lpAddress)
{
  rRegionFromFileEx(hProcess, fileame, lpAddress, NULL);
}

void ajanuw::Mem::rRegionFromFileEx(HANDLE hProcess, std::string fileame, void *lpAddress, size_t *fileSize)
{
  std::ifstream inFile;
  inFile.open(fileame);
  uintptr_t offset = (uintptr_t)lpAddress;
  while (inFile.good())
  {
    char r = inFile.get();
    if (inFile.eof())
      break;
    ajanuw::Mem::wByteEx(hProcess, (void *)offset, r);
    offset += sizeof(BYTE);
    if (fileSize)
      (*fileSize)++;
  }
  inFile.close();
}

std::vector<BYTE> ajanuw::Mem::rBytes(std::string CEAddressString, uintptr_t size)
{
  return ajanuw::Mem::rBytes(ajanuw::CEAddressString::getAddress(CEAddressString), size);
}

BYTE ajanuw::Mem::rByte(std::string CEAddressString)
{
  return ajanuw::Mem::rByte(ajanuw::CEAddressString::getAddress(CEAddressString));
}

WORD ajanuw::Mem::rWord(std::string CEAddressString)
{
  return ajanuw::Mem::rWord(ajanuw::CEAddressString::getAddress(CEAddressString));
}

DWORD ajanuw::Mem::rDword(std::string CEAddressString)
{
  return ajanuw::Mem::rDword(ajanuw::CEAddressString::getAddress(CEAddressString));
}

uint64_t ajanuw::Mem::rQword(std::string CEAddressString)
{
  return ajanuw::Mem::rQword(ajanuw::CEAddressString::getAddress(CEAddressString));
}

uintptr_t ajanuw::Mem::rPointer(std::string CEAddressString)
{
  return ajanuw::Mem::rPointer(ajanuw::CEAddressString::getAddress(CEAddressString));
}

float ajanuw::Mem::rFloat(std::string CEAddressString)
{
  return ajanuw::Mem::rFloat(ajanuw::CEAddressString::getAddress(CEAddressString));
}

double ajanuw::Mem::rDouble(std::string CEAddressString)
{
  return ajanuw::Mem::rDouble(ajanuw::CEAddressString::getAddress(CEAddressString));
}

void ajanuw::Mem::rRegionFromFile(std::string fileame, std::string CEAddressString)
{
  ajanuw::Mem::rRegionFromFile(fileame, ajanuw::CEAddressString::getAddress(CEAddressString));
}

void ajanuw::Mem::rRegionFromFile(std::string fileame, std::string CEAddressString, size_t *fileSize)
{
  ajanuw::Mem::rRegionFromFile(fileame, ajanuw::CEAddressString::getAddress(CEAddressString), fileSize);
}

std::vector<BYTE> ajanuw::Mem::rBytesEx(HANDLE hProcess, std::string CEAddressString, uintptr_t size)
{
  return ajanuw::Mem::rBytesEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess), size);
}

BYTE ajanuw::Mem::rByteEx(HANDLE hProcess, std::string CEAddressString)
{
  return ajanuw::Mem::rByteEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

WORD ajanuw::Mem::rWordEx(HANDLE hProcess, std::string CEAddressString)
{
  return ajanuw::Mem::rWordEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

DWORD ajanuw::Mem::rDwordEx(HANDLE hProcess, std::string CEAddressString)
{
  return ajanuw::Mem::rDwordEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

uint64_t ajanuw::Mem::rQwordEx(HANDLE hProcess, std::string CEAddressString)
{
  return ajanuw::Mem::rQwordEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

uintptr_t ajanuw::Mem::rPointerEx(HANDLE hProcess, std::string CEAddressString)
{
  return ajanuw::Mem::rPointerEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

float ajanuw::Mem::rFloatEx(HANDLE hProcess, std::string CEAddressString)
{
  return ajanuw::Mem::rFloatEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

double ajanuw::Mem::rDoubleEx(HANDLE hProcess, std::string CEAddressString)
{
  return ajanuw::Mem::rDoubleEx(hProcess, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

void ajanuw::Mem::rRegionFromFileEx(HANDLE hProcess, std::string fileame, std::string CEAddressString)
{
  ajanuw::Mem::rRegionFromFileEx(hProcess, fileame, ajanuw::CEAddressString::getAddress(CEAddressString, hProcess));
}

void ajanuw::Mem::rRegionFromFileEx(HANDLE hProcess, std::string fileame, std::string CEAddressString, size_t *fileSize)
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
  hWnd = CreateWindowA(
      className.c_str(),
      windowName.c_str(),
      style,
      x, y,
      width, height,
      NULL, NULL, NULL, NULL);

  if (!hWnd)
    return FALSE;
  std::wstring ws = ajanuw::SSString::strToWstr(windowName);
  SetWindowTextW(hWnd, ws.c_str());
  hwndMap.insert(std::pair<HWND, uintptr_t>(hWnd, (uintptr_t)this));
  ShowWindow(hWnd, SW_RESTORE);
  UpdateWindow(hWnd);
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
  HWND _hWnd = CreateWindowA(opt.className.c_str(), opt.windowName.c_str(),
                             opt.style,
                             opt.x, opt.y,
                             opt.width, opt.height,
                             opt.parent ? opt.parent : this->hWnd,
                             opt.id,
                             NULL, NULL);
  std::wstring ws = ajanuw::SSString::strToWstr(opt.windowName);
  SetWindowTextW(_hWnd, ws.c_str());
  return _hWnd;
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
  return (BYTE *)memory + position;
}

std::vector<uint8_t> ajanuw::Mem::VAManage::read(size_t size)
{
  if (hProcess == NULL)
  {
    return ajanuw::Mem::rBytes(ptr(), size);
  }
  else
  {
    return ajanuw::Mem::rBytesEx(hProcess, ptr(), size);
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

void ajanuw::Mem::VAManage::write(std::vector<uint8_t> table, size_t count)
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

void ajanuw::Mem::VAManage::writeStr(std::string str)
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

void ajanuw::Mem::VAManage::writeWstr(std::wstring wstr)
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

void ajanuw::Mem::VAManage::writeUstr(std::u16string ustr)
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

void ajanuw::Mem::VAManage::loadFromFile(std::string filename)
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

void ajanuw::Mem::VAManage::saveToFile(std::string filename)
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

    delete node;

    return addr;
  }
  catch (const std::exception &e)
  {
    throw e;
  }
}

DWORD ajanuw::PE::GetPID(std::wstring name)
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

MODULEINFO ajanuw::PE::GetModuleBase(DWORD pid)
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

MODULEINFO ajanuw::PE::GetModuleInfo(std::wstring moduleName, DWORD pid)
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

bool ajanuw::PE::isX64(DWORD pid, HMODULE hModule)
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

bool ajanuw::PE::isX86(DWORD pid, HMODULE hModule)
{
  return !isX64(pid, hModule);
}

std::map<std::string, uintptr_t> ajanuw::PE::exports(DWORD pid, HMODULE hModule)
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

BYTE *ajanuw::PE::GetProcAddress(DWORD pid, HMODULE hModule, std::string method)
{
  BYTE *result = NULL;
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

    if (!_stricmp(funme, method.c_str()))
    {
      // get function address index
      WORD AddressOfFunctionsIndex = 0;
      ReadProcessMemory(hProcess, AddressOfNameOrdinals + i, &AddressOfFunctionsIndex, sizeof(WORD), NULL);

      // get function address
      DWORD funAddrRVA = 0;
      ReadProcessMemory(hProcess, AddressOfFunctions + AddressOfFunctionsIndex, &funAddrRVA, sizeof(DWORD), NULL);

      result = RVA2VA(funAddrRVA);
      break;
    }
    i++;
  }

  CloseHandle(hProcess);
  delete[] buf;
  return result;
}