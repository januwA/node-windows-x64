#include "_utils.h"

bool SSString::startWith(string str, const char* s2)
{
  return search(str, regex("$" + string(s2)));
}

bool SSString::endWith(string str, const char* s2)
{
  return search(str, regex(string(s2) + "$"));
}

vector<string> SSString::match(string str, regex reg)
{
  smatch m;
  string::const_iterator iterStart = str.begin();
  string::const_iterator iterEnd = str.end();
  vector<string> r{};
  while (regex_search(iterStart, iterEnd, m, reg))
  {
    r.emplace_back(m[0].str());
    iterStart = m[0].second;
  }
  r.emplace_back(m[0].str());
  return r;
}

bool SSString::search(string str, regex reg)
{
  return regex_search(str, reg);
}

string SSString::trim(string str)
{
  return regex_replace(str, regex("^\\s+|\\s+$"), "");
}
string SSString::trimStart(string str)
{
  return regex_replace(str, regex("^\\s+"), "");
}
string SSString::trimEnd(string str)
{
  return regex_replace(str, regex("\\s+$"), "");
}
vector<string> SSString::split(string str, regex reg)
{
  smatch m;
  string::const_iterator iterStart = str.begin();
  string::const_iterator iterEnd = str.end();

  vector<string> resultSplitList = {};

  while (regex_search(iterStart, iterEnd, m, reg))
  {
    resultSplitList.emplace_back(iterStart, m[0].first);
    iterStart = m[0].second;
  }
  resultSplitList.emplace_back(iterStart, iterEnd);
  return resultSplitList;
}
vector<BYTE> SSString::toBytes(string byteStr)
{
  byteStr = SSString::trim(byteStr);
  vector<string> byteStrList = SSString::split(byteStr, regex("[\\s\\n]+"));
  vector<BYTE> byteValList = {};
  for (size_t i = 0; i < byteStrList.size(); i++)
  {
    byteValList.push_back(stoi(byteStrList[i], nullptr, 16));
  }
  return byteValList;
}

BOOL SSString::cmp(const char* s1, const char* s2)
{
  return strncmp(s1, s2, len(s2)) == 0;
}

BOOL SSString::cmp(string s1, string s2)
{
  return strncmp(s1.c_str(), s2.c_str(), s2.size()) == 0;
}

BOOL SSString::cmp(const wchar_t* s1, const wchar_t* s2)
{
  return wcsncmp(s1, s2, len(s2)) == 0;
}

BOOL SSString::cmp(wstring s1, wstring s2)
{
  return wcsncmp(s1.c_str(), s2.c_str(), s2.size()) == 0;
}

BOOL SSString::cmp(const char16_t* s1, const char16_t* s2)
{
  return wcsncmp((wchar_t*)s1, (wchar_t*)s2, len(s2)) == 0;
}

BOOL SSString::cmp(u16string s1, u16string s2)
{
  return wcsncmp((wchar_t*)s1.c_str(), (wchar_t*)s2.c_str(), s2.size()) == 0;
}













BOOL SSString::icmp(const char* s1, const char* s2)
{
  return _stricmp(s1, s2) == 0;
}

BOOL SSString::icmp(string s1, string s2)
{
  return _stricmp(s1.c_str(), s2.c_str()) == 0;
}

BOOL SSString::icmp(const wchar_t* s1, const wchar_t* s2)
{
  return _wcsicmp(s1, s2) == 0;
}

BOOL SSString::icmp(wstring s1, wstring s2)
{
  return _wcsicmp(s1.c_str(), s2.c_str()) == 0;
}

BOOL SSString::icmp(const char16_t* s1, const char16_t* s2)
{
  return _wcsicmp((wchar_t*)s1, (wchar_t*)s2) == 0;
}

BOOL SSString::icmp(u16string s1, u16string s2)
{
  return _wcsicmp((wchar_t*)s1.c_str(), (wchar_t*)s2.c_str()) == 0;
}








size_t SSString::len(const char* str)
{
  return strlen(str);
}
size_t SSString::len(const char* str, size_t maxSize)
{
  return strnlen_s(str, maxSize);
}
size_t SSString::len(const wchar_t* str)
{
  return wcslen(str);
}
size_t SSString::len(const wchar_t* str, size_t maxSize)
{
  return wcsnlen_s(str, maxSize);
}

size_t SSString::len(string str)
{
  return str.length();
}
size_t SSString::len(wstring str)
{
  return str.length();
}
size_t SSString::len(u16string str)
{
  return str.length();
}

size_t SSString::count(const char* str)
{
  return len(str);
}

size_t SSString::count(const char* str, size_t maxSize)
{
  return len(str, maxSize);
}

size_t SSString::count(const wchar_t* str)
{
  return len(str) * 2;
}

size_t SSString::count(const wchar_t* str, size_t maxSize)
{
  return len(str, maxSize) * 2;
}

size_t SSString::count(string str)
{
  return len(str);
}

size_t SSString::count(wstring str)
{
  return len(str) * 2;
}

size_t SSString::count(u16string str)
{
  return len(str) * 2;
}

LPVOID createCallback(void* lpAddress, size_t index)
{
  string code_str = "55 48 8B EC 48 81 EC 90 01 00 00\n"
    "48 89 4C 24 08 48 89 54 24 10 4C 89 44 24 18 4C 89 4C 24 20\n"
    "48 B9 00 00 00 00 00 00 00 00 48 BA 00 00 00 00 00 00 00 00 4C 8D 44 24 08 4C 8D 4D 30\n"
    "48 B8 F0 AC AB 14 FE 7F 00 00 FF D0\n"
    "48 81 C4 90 01 00 00 48 8B E5 5D C3";

  vector<BYTE> code_bytes = SSString::toBytes(code_str);

  //memcpy_s(code_bytes.data() + 0x21, sizeof(uintptr_t), &lpCB, sizeof(uintptr_t)); // 备用
  memcpy_s(code_bytes.data() + 0x2B, sizeof(uintptr_t), &index, sizeof(uintptr_t));
  memcpy_s(code_bytes.data() + 0x3E, sizeof(uintptr_t), &lpAddress, sizeof(uintptr_t));
  auto newmem = VirtualAlloc(0, code_bytes.size() + sizeof(uintptr_t), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
  memcpy_s(newmem, code_bytes.size(), code_bytes.data(), code_bytes.size());
  return newmem;
}

wstring SSString::strTowstr(string str)
{
  wstring wideStr{ 0 };
  wideStr.resize(str.length());
  MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), (LPWSTR)wideStr.data(), wideStr.length());
  return wideStr;

}

u16string SSString::strToustr(string str)
{
  u16string wideStr{ 0 };
  wideStr.resize(str.length());
  MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), (LPWSTR)wideStr.data(), wideStr.length());
  return wideStr;
}

string SSString::ustrTostr(u16string ustr)
{
  string str{ 0 };
  str.resize(ustr.length() * 2);
  WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)ustr.data(), ustr.length(), (LPSTR)str.data(), str.length(), 0, 0);
  return str;
}

string SSString::wstrTostr(wstring wstr)
{
  string str{ 0 };
  str.resize(wstr.length() * 2);
  WideCharToMultiByte(CP_UTF8, 0, wstr.data(), wstr.length(), (LPSTR)str.data(), str.length(), 0, 0);
  return str;
}

void SSString::strToMem(void* dst, string str)
{
  memcpy_s(dst, str.length(), str.c_str(), str.length());
}

void SSString::strToMem(void* dst, wstring str)
{
  memcpy_s(dst, str.length() * 2, str.c_str(), str.length() * 2);
}

void SSString::strToMem(void* dst, u16string str)
{
  memcpy_s(dst, str.length() * 2, str.c_str(), str.length() * 2);
}

string SSString::strFormMem(void* src, uintptr_t max)
{
  string str{ 0 };
  uintptr_t addr = (uintptr_t)src;
  while (true)
  {
    char wc = *(char*)addr;
    if (wc == NULL || max == 0)
      break;
    str.push_back(wc);
    addr += sizeof(char);
    max--;
  }
  return str;

}

wstring SSString::wstrFormMem(void* src, uintptr_t max)
{
  wstring wstr{ 0 };
  uintptr_t addr = (uintptr_t)src;
  while (true)
  {
    wchar_t wc = *(wchar_t*)addr;
    if (wc == NULL || max == 0)
      break;
    wstr.push_back(wc);
    addr += sizeof(wchar_t);
    max--;
  }
  return wstr;

}

u16string SSString::ustrFormMem(void* src, uintptr_t max)
{
  u16string ustr{ 0 };
  uintptr_t addr = (uintptr_t)src;
  while (true)
  {
    char16_t wc = *(char16_t*)addr;
    if (wc == NULL || max == 0)
      break;
    ustr.push_back(wc);
    addr += sizeof(char16_t);
    max--;
  }
  return ustr;

}

LPVOID Mem::alloc(SIZE_T dwSize, LPVOID lpAddress, DWORD flAllocationType, DWORD flProtect)
{
  return VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
}

BOOL Mem::free(LPVOID lpAddress)
{
  return VirtualFree(lpAddress, 0, MEM_RELEASE);
}

void Mem::write_str(void* lpAddress, string str)
{
  SSString::strToMem((void*)lpAddress, str);
}

void Mem::write_str(void* lpAddress, wstring str)
{
  SSString::strToMem((void*)lpAddress, str);
}
void Mem::write_str(void* lpAddress, u16string str)
{
  SSString::strToMem((void*)lpAddress, str);
}

void Mem::write_bytes(void* lpAddress, vector<BYTE> bytes)
{
  memcpy_s(lpAddress, bytes.size(), bytes.data(), bytes.size());
}

void Mem::write_word(void* lpAddress, WORD value)
{
  memcpy_s(lpAddress, sizeof(WORD), &value, sizeof(WORD));
}
void Mem::write_dword(void* lpAddress, DWORD value)
{
  memcpy_s(lpAddress, sizeof(DWORD), &value, sizeof(DWORD));
}
void Mem::write_qword(void* lpAddress, uint64_t value)
{
  memcpy_s(lpAddress, sizeof(uint64_t), &value, sizeof(uint64_t));
}
void Mem::write_float(void* lpAddress, float value)
{
  memcpy_s(lpAddress, sizeof(float), &value, sizeof(float));
}
void Mem::write_double(void* lpAddress, double value)
{
  memcpy_s(lpAddress, sizeof(double), &value, sizeof(double));
}
void Mem::write_region_to_file(string filename, void* lpAddress, uintptr_t size)
{
  ofstream outFile;
  outFile.open(filename.c_str());
  for (int i = 0; i < size; i++)
    outFile << *(BYTE*)((uintptr_t)lpAddress + i);
  outFile.close();
}

string Mem::read_str(char* lpAddress, uintptr_t max)
{
  return SSString::strFormMem(lpAddress, max);
}
wstring Mem::read_str(wchar_t* lpAddress, uintptr_t max)
{
  return SSString::wstrFormMem(lpAddress, max);
}
u16string Mem::read_str(char16_t* lpAddress, uintptr_t max)
{
  return SSString::ustrFormMem(lpAddress, max);
}
vector<BYTE> Mem::read_bytes(void* lpAddress, uintptr_t size)
{
  vector<BYTE> bytes(size);
  memcpy_s(bytes.data(), size, lpAddress, size);
  return bytes;
}

BYTE Mem::read_byte(void* lpAddress)
{
  return *(BYTE*)lpAddress;
}

WORD Mem::read_word(void* lpAddress)
{
  return *(WORD*)lpAddress;
}
DWORD Mem::read_dword(void* lpAddress)
{
  return *(DWORD*)lpAddress;
}
uint64_t Mem::read_qword(void* lpAddress)
{
  return *(uint64_t*)lpAddress;
}

uintptr_t Mem::read_pointer(void* lpAddress)
{
  return *(uintptr_t*)lpAddress;
}

float Mem::read_float(void* lpAddress)
{
  return *(float*)lpAddress;
}

double Mem::read_double(void* lpAddress)
{
  return *(double*)lpAddress;
}

void Mem::read_region_from_file(string fileame, void* lpAddress)
{
  read_region_from_file(fileame, lpAddress, NULL);
}

void Mem::read_region_from_file(string fileame, void* lpAddress, size_t* fileSize)
{
  ifstream inFile;
  inFile.open(fileame);
  uintptr_t offset = (uintptr_t)lpAddress;
  while (inFile.good())
  {
    char r = inFile.get();
    if (inFile.eof())
      break;
    memset((void*)offset, r, sizeof(BYTE));
    offset += sizeof(BYTE);
    if (fileSize) (*fileSize)++;
  }
  inFile.close();
}
