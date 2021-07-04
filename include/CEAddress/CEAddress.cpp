#include "pch.h"
#include "CEAddress.h"

typedef struct yy_buffer_state* YY_BUFFER_STATE;
extern YY_BUFFER_STATE ces_scan_string(const char* str);
extern void ces_delete_buffer(YY_BUFFER_STATE buffer);

LPVOID ces::getAddress(std::string_view src, const std::map<std::string, LPVOID>& symbols, HANDLE hProcess)
{
  // text convert to ast
  YY_BUFFER_STATE state = ces_scan_string(src.data());
  ces::BaseNode* ast = nullptr;
  ces::parser parser(&ast, src);
  parser.parse();
  ces_delete_buffer(state);
  if (!ast) return 0;


  ces::Interpreter interpreter{ hProcess, src, symbols };
  auto addr = (LPVOID)interpreter.visit(ast);
  delete ast;
  return addr;
}
