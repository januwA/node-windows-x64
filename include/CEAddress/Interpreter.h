#pragma once

#include <string>
#include <map>
#include <algorithm>
#include "parser.h"
#include "error.hpp"

namespace ces {

  class PE
  {
  public:
    static uint32_t GetPID(std::wstring_view name);
    // exe module
    static MODULEINFO GetModuleBase(uint32_t pid);
    static MODULEINFO GetModuleInfo(std::wstring_view moduleName, uint32_t pid);

    static bool isX64(uint32_t pid, HMODULE hModule);
    static bool isX86(uint32_t pid, HMODULE hModule);

    // 获取模块中的函数地址
    static uint8_t* GetProcAddress(uint32_t pid, HMODULE hModule, std::string_view method);

    // user32.dll => user32
    // user32.xxx.dll => user32.xxx
    static std::wstring GetModuleName(std::wstring_view moduleName);
  };

  class Interpreter
  {
  public:
    std::map<std::string, LPVOID> symbols;
    std::string_view source;
    HANDLE hProcess;
    uint32_t pid{ NULL };
    bool isX86;
    Interpreter(HANDLE hProcess, std::string_view source, const std::map<std::string, LPVOID>& symbols);
    uintptr_t visit(ces::BaseNode* node);

  private:
    uintptr_t visitHex(ces::HexNode* node);
    uintptr_t visitIdent(ces::IdentsNode* node);
    uintptr_t visitUnary(ces::UnaryNode* node);
    uintptr_t visitPointer(ces::PointerNode* node);
    uintptr_t visitBinary(ces::BinaryNode* node);
  };

}
