%option noyywrap noline yylineno
%option prefix="ces"

%{
#include <iostream>
#include "parser.h"

#define YY_DECL ces::parser::symbol_type yylex ()
ces::location loc;
#define yyterminate() return ces::parser::make_CESEOF(loc)
#define _T(t) return ces::parser::make_##t(loc)
#define _ST(t) return ces::parser::make_##t(std::string(yytext, yyleng), loc)

#define YY_USER_ACTION \
    loc.step();     \
    loc.columns(yyleng);


%}

HEX	        (?i:0[0-9a-f]+)
IDENT_INSTR (?i:[\x0000-\xffffa-z0-9\-+='&\(\)\[\] ]+)
IDENT       (?i:[\x0000-\xffffa-z0-9='&]+)


%x instr
%%

"."                   { _T(DOT); };
<instr>\"             { BEGIN 0; }
<instr>{IDENT_INSTR}  { _ST(IDENT); }

[ \t\r\n]   {  }
"+" { _T(PLUS);}
"-" { _T(MINUS);}
"*" { _T(MUL);}
"/" { _T(DIV);}
"(" { _T(LPAREN);}
")" { _T(RPAREN);}
"[" { _T(RSQUARE);}
"]" { _T(RSQUARE); }
\"  { BEGIN instr; }
"**" { _T(POW); }
{HEX} { _ST(HEX); }
{IDENT} { _ST(IDENT); }

.				{ printf("Char Error:%s\n%d:%d,%d:%d\n", yytext, loc.begin.line, loc.begin.column, loc.end.line, loc.end.column ); }

%%
