#pragma once
#include <windows.h>
#include <string>
#include <map>

namespace ces
{
  LPVOID __declspec(dllexport) getAddress(std::string_view src, const std::map<std::string, LPVOID>& symbols, HANDLE hProcess = nullptr);
}