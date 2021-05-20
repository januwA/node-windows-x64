#include "export.h"

BaseNode* ces(std::string src)
{
  YY_BUFFER_STATE state = yy_scan_string(src.c_str());
  BaseNode* result = nullptr;
  yyparse( &result ) ;
  yy_delete_buffer(state);
  return result;
}