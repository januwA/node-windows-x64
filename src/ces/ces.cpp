#include <iostream>
#include "parser.h"

using namespace std;

typedef struct yy_buffer_state* YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char* str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

int main()
{
  YY_BUFFER_STATE state = yy_scan_string("1 + 3");
  BaseNode* result = nullptr;
  yyparse( &result ) ;
  yy_delete_buffer(state);
  if(result) printf("%d\n", result->id());
  return 0;
}
