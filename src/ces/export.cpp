#include "export.h"

ces::BaseNode* ces::parse(std::string src)
{
  YY_BUFFER_STATE state = ces_scan_string(src.c_str());
  ces::BaseNode* result = nullptr;
  ces::parser parser(&result);
  parser.parse();
  ces_delete_buffer(state);
  return result;
}