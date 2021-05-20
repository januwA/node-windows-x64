%option noyywrap noline yylineno
%{
#include <iostream>
#include "parser.h"

using namespace std;
#define SAVE_STR yylval.text = new std::string(yytext, yyleng)

int yycolumn = 1;

#define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng; \
%}

HEX	        (?i:0[0-9a-f]+)
IDENT_INSTR (?i:[\x0000-\xffff-z0-9\-+='&\(\)\[\] ]+)
IDENT       (?i:[\x0000-\xffff-z0-9='&]+)


%x instr
%%


"."                   { return DOT; };
<instr>\"             { BEGIN 0; }
<instr>{IDENT_INSTR}  { SAVE_STR; return IDENT; }

[ \t\r\n]   {  }
"+" { return PLUS;}
"-" { return MINUS;}
"*" { return MUL;}
"/" { return DIV;}
"(" { return LPAREN;}
")" { return RPAREN;}
"[" { return LSQUARE;}
"]" { return RSQUARE;}
\"  { BEGIN instr; }
"**" { return POW;}
{HEX} { SAVE_STR; return HEX; }
{IDENT} { SAVE_STR; return  IDENT; }

.				{ printf("Char Error: %s\n%d:%d,%d:%d\n", yytext, yylloc.first_line, yylloc.first_column, yylloc.last_line, yylloc.last_column ); }

%%

void yyerror(BaseNode** result, const char* msg)
{
  cout << "YYError: " << msg << endl;
}
