#pragma once
#include <ostream>
#include <Windows.h>
#include <regex>
#include <fstream>

using namespace std;

LPVOID createCallback(void* lpAddress, size_t index);

namespace SSString
{
  wstring strTowstr(string str);
  u16string strToustr(string str);
  string ustrTostr(u16string ustr);
  string wstrTostr(wstring wstr);

  void strToMem(void* dst, string str);
  void strToMem(void* dst, wstring str);
  void strToMem(void* dst, u16string str);

  // TODO: Fix "ab��" get "ab?" when max is 3
  string strFormMem(void* src, uintptr_t max);
  wstring wstrFormMem(void* src, uintptr_t max);
  u16string ustrFormMem(void* src, uintptr_t max);

  bool startWith(string str, const char* s2);
  bool endWith(string str, const char* s2);
  vector<string> match(string str, regex reg);
  bool search(string str, regex reg);
  string trim(string str);
  string trimStart(string str);
  string trimEnd(string str);
  vector<string> split(string str, regex reg);
  vector<BYTE> toBytes(string byteStr);

  BOOL cmp(const char* s1, const char* s2);
  BOOL cmp(string s1, string s2);
  BOOL cmp(const wchar_t* s1, const wchar_t* s2);
  BOOL cmp(wstring s1, wstring s2);
  BOOL cmp(const char16_t* s1, const char16_t* s2);
  BOOL cmp(u16string s1, u16string s2);

  BOOL icmp(const char* s1, const char* s2);
  BOOL icmp(string s1, string s2);
  BOOL icmp(const wchar_t* s1, const wchar_t* s2);
  BOOL icmp(wstring s1, wstring s2);
  BOOL icmp(const char16_t* s1, const char16_t* s2);
  BOOL icmp(u16string s1, u16string s2);

  size_t len(const char* str);
  size_t len(const char* str, size_t maxSize);
  size_t len(const wchar_t* str);
  size_t len(const wchar_t* str, size_t maxSize);
  size_t len(string str);
  size_t len(wstring str);
  size_t len(u16string str);

  size_t count(const char* str);
  size_t count(const char* str, size_t maxSize);
  size_t count(const wchar_t* str);
  size_t count(const wchar_t* str, size_t maxSize);
  size_t count(string str);
  size_t count(wstring str);
  size_t count(u16string str);
}

namespace Mem
{
  LPVOID alloc(SIZE_T dwSize, LPVOID lpAddress = 0, DWORD flAllocationType = MEM_COMMIT | MEM_RESERVE, DWORD flProtect = PAGE_EXECUTE_READWRITE);
  BOOL free(LPVOID lpAddress);

  void write_str(void* lpAddress, string str);
  void write_str(void* lpAddress, wstring str);
  void write_str(void* lpAddress, u16string str);
  void write_bytes(void* lpAddress, vector<BYTE> bytes);
  void write_word(void* lpAddress, WORD value);
  void write_dword(void* lpAddress, DWORD value);
  void write_qword(void* lpAddress, uint64_t value);
  void write_float(void* lpAddress, float value);
  void write_double(void* lpAddress, double value);
  void write_region_to_file(string filename, void* lpAddress, uintptr_t size);

  string read_str(char* lpAddress, uintptr_t max);
  wstring read_str(wchar_t* lpAddress, uintptr_t max);
  u16string read_str(char16_t* lpAddress, uintptr_t max);

  vector<BYTE> read_bytes(void* lpAddress, uintptr_t size);
  BYTE read_byte(void* lpAddress);
  WORD read_word(void* lpAddress);
  DWORD read_dword(void* lpAddress);
  uint64_t read_qword(void* lpAddress);
  uintptr_t read_pointer(void* lpAddress);
  float read_float(void* lpAddress);
  double read_double(void* lpAddress);
  void read_region_from_file(string fileame, void* lpAddress);
  void read_region_from_file(string fileame, void* lpAddress, size_t* fileSize);
}
