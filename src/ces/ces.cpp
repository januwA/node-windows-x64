#include <iostream>
#include "parser.h"

using namespace std;

typedef struct yy_buffer_state* YY_BUFFER_STATE;
extern YY_BUFFER_STATE ces_scan_string(const char* str);
extern void ces_delete_buffer(YY_BUFFER_STATE buffer);

int main()
{
  try
  {
    string src = "中文.exe + 한글+[\"ああさっそう  と\tしている\"] + 2";
    YY_BUFFER_STATE state = ces_scan_string(src.data());
    ces::BaseNode* result = nullptr;
    ces::parser parser(&result, src);
    parser.parse();
    ces_delete_buffer(state);
    if(result) printf("node id:%d\n", result->id());
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
    return 1;
  }
}
