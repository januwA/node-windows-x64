#pragma once
#include "Interpreter.h"

namespace ces
{
  LPVOID __declspec(dllexport) getAddress(std::string_view src, const std::map<std::string, LPVOID>& symbols, HANDLE hProcess = nullptr);
}
