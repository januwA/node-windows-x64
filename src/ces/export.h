#pragma once

#include <iostream>
#include "parser.h"

typedef struct yy_buffer_state* YY_BUFFER_STATE;
extern YY_BUFFER_STATE ces_scan_string(const char* str);
extern void ces_delete_buffer(YY_BUFFER_STATE buffer);

namespace ces
{
  BaseNode* parse(std::string_view src);
}