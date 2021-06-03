#include "export.h"

ces::BaseNode* ces::parse(std::string_view src)
{
  YY_BUFFER_STATE state = ces_scan_string(src.data());
  ces::BaseNode* result = nullptr;
  ces::parser parser(&result, src);
  parser.parse();
  ces_delete_buffer(state);
  return result;
}