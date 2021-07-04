#include "pch.h"
#include "Interpreter.h"

namespace ces
{

  uint32_t  PE::GetPID(std::wstring_view name)
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

  MODULEINFO  PE::GetModuleBase(uint32_t pid)
  {
    MODULEINFO mi{ 0 };
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

  std::wstring  PE::GetModuleName(std::wstring_view moduleName)
  {
    auto index = moduleName.rfind(L".");
    return std::wstring(moduleName.substr(0, index));
  }

  // 忽略大小写判断
  // user32.dll
  // user32
  MODULEINFO  PE::GetModuleInfo(std::wstring_view moduleName, uint32_t pid)
  {
    MODULEINFO mi{ 0 };
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
            _wcsicmp(PE::GetModuleName(me.szModule).data(), moduleName.data()) == 0
            ||
            _wcsicmp(me.szModule, moduleName.data()) == 0
            )
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

  bool  PE::isX64(uint32_t pid, HMODULE hModule)
  {
    uint8_t* buf = new uint8_t[0x1000];
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

  bool  PE::isX86(uint32_t pid, HMODULE hModule)
  {
    return !isX64(pid, hModule);
  }

  uint8_t* PE::GetProcAddress(uint32_t pid, HMODULE hModule, std::string_view method)
  {
    uint8_t* result = NULL;
    uint8_t* buf = new uint8_t[0x1000];
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    ReadProcessMemory(hProcess, hModule, buf, 0x1000, NULL);

    PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(buf);
    PIMAGE_NT_HEADERS ntHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(buf + dosHeader->e_lfanew);
    PIMAGE_FILE_HEADER fileHeader = reinterpret_cast<PIMAGE_FILE_HEADER>(&ntHeader->FileHeader);
    bool isX64 = fileHeader->SizeOfOptionalHeader == 0xf0;
    auto RVA2VA = [&](size_t rva)
    {
      return (uint8_t*)hModule + rva;
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

    uint8_t* src = RVA2VA(exportEntry.VirtualAddress);
    IMAGE_EXPORT_DIRECTORY exportDes{ 0 };
    ReadProcessMemory(hProcess, src, &exportDes, sizeof(IMAGE_EXPORT_DIRECTORY), NULL);

    // 以函数名称导出数量,指针列表
    uint32_t* AddressOfNames = (uint32_t*)RVA2VA(exportDes.AddressOfNames);               // 函数名称表
    uint32_t* AddressOfFunctions = (uint32_t*)RVA2VA(exportDes.AddressOfFunctions);       // 函数地址表
    uint16_t* AddressOfNameOrdinals = (uint16_t*)RVA2VA(exportDes.AddressOfNameOrdinals); // 函数地址index表

    size_t i = 0;
    uint32_t namePtrRVA = 0;
    while (i < exportDes.NumberOfNames)
    {
      char funme[MAX_PATH] = { 0 };
      ReadProcessMemory(hProcess, AddressOfNames + i, &namePtrRVA, sizeof(uint32_t), NULL);
      ReadProcessMemory(hProcess, RVA2VA(namePtrRVA), &funme, MAX_PATH, NULL);

      if (_stricmp(funme, method.data()) == 0)
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


  Interpreter::Interpreter(HANDLE hProcess, std::string_view source, const std::map<std::string, LPVOID>& symbols)
    : source(source), hProcess(hProcess), symbols(symbols)
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

  uintptr_t   Interpreter::visit(ces::BaseNode* node)
  {
    switch (node->id())
    {
    case ces::NT::HEX:
      return visitHex(reinterpret_cast<ces::HexNode*>(node));
    case ces::NT::IDENTS:
      return visitIdent(reinterpret_cast<ces::IdentsNode*>(node));
    case ces::NT::UNARY:
      return visitUnary(reinterpret_cast<ces::UnaryNode*>(node));
    case ces::NT::POINTER:
      return visitPointer(reinterpret_cast<ces::PointerNode*>(node));
    case ces::NT::BINARY:
      return visitBinary(reinterpret_cast<ces::BinaryNode*>(node));
    default:
      throw ces::runtime_error(source, node->loc, "Unexpected Node");
    }
  }

  uintptr_t   Interpreter::visitHex(ces::HexNode* node)
  {
    return std::stoull(node->value, nullptr, 16);
  }

  uintptr_t   Interpreter::visitIdent(ces::IdentsNode* node)
  {
    // 优先级 SYMBOL -> HEX -> MODULE
    if (node->idents->size() == 1)
    {
      auto val = *node->idents->begin();
      if (symbols.count(val))
        return (uintptr_t)symbols[val];
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
              r = (uintptr_t)PE::GetProcAddress(pid, (HMODULE)me.modBaseAddr, val);
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
      std::string first;
      for (auto& s : *node->idents)
      {
        first += s;
        first.push_back('.');
      }
      first.pop_back();
      // user32.messageboxa
      // user32.dll
      // node.exe
      if (last == "dll" || last == "exe")
      {
        auto hModule = (HMODULE)(PE::GetModuleInfo(std::wstring(first.begin(), first.end()), pid).lpBaseOfDll);
        if (!hModule)
          throw ces::runtime_error(source, node->loc, std::format("Module not found '{}'", first));
        return (uintptr_t)hModule;
      }

      auto hModule = (HMODULE)(PE::GetModuleInfo(std::wstring(first.begin(), first.end()), pid).lpBaseOfDll);
      if (!hModule)
        throw ces::runtime_error(source, node->loc, std::format("Module not found '{}'", first));

      auto hMethod = (uintptr_t)PE::GetProcAddress(pid, hModule, last);
      if (!hMethod)
        throw ces::runtime_error(source, node->loc, std::format("Symbol not found '{}'", last));
      return (uintptr_t)hMethod;
    }
  }

  uintptr_t   Interpreter::visitUnary(ces::UnaryNode* node)
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

  uintptr_t   Interpreter::visitPointer(ces::PointerNode* node)
  {
    auto address = visit(node->node);
    uintptr_t result = NULL;
    if (ReadProcessMemory(!hProcess ? GetCurrentProcess() : hProcess, (LPCVOID)address, (LPVOID)&result, isX86 ? 4 : 8, NULL))
      return result;
    throw ces::runtime_error(source, node->loc, "Failed to read pointer");
  }

  uintptr_t   Interpreter::visitBinary(ces::BinaryNode* node)
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
}
