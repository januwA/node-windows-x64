%option noyywrap noline
%option prefix="ces"

%{
#include <iostream>
#include "parser.h"
#include "error.hpp"

#define YY_DECL ces::parser::symbol_type yylex (std::string_view source)
ces::location loc;
#define yyterminate() return ces::parser::make_CESEOF(loc)
#define _T(t) return ces::parser::make_##t(loc)
#define _ST(t) return ces::parser::make_##t(std::string(yytext, yyleng), loc)

#define YY_USER_ACTION \
    loc.step();     \
    loc.columns(yyleng);


%}

IDENT_FIRST [^0-9 \.\+\-\*\/\[\]\\"]
IDENT_BODY  [^ \.\+\-\*\/\[\]\\"]

HEX	        (?i:[0-9]+[0-9a-f]*)
IDENT_INSTR (?i:[^\."]+)
IDENT       (?i:{IDENT_FIRST}{IDENT_BODY}*)


%x instr
%%

"."                   { _T(DOT); };
<instr>\"             { BEGIN 0; }
<instr>{IDENT_INSTR}  { /* std::cout << yytext << std::endl; */ _ST(IDENT); }

[ \t\r\n]   {  }
"+" { _T(PLUS);}
"-" { _T(MINUS);}
"*" { _T(MUL);}
"/" { _T(DIV);}
"[" { _T(LSQUARE);}
"]" { _T(RSQUARE); }
\"  { BEGIN instr; }
"**" { _T(POW); }
{HEX} { _ST(HEX);  }
{IDENT} { /* std::cout << yytext << std::endl; */ _ST(IDENT); }

.				{  throw ces::lexer_error(source, loc); }

%%
