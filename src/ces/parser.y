%skeleton "lalr1.cc"
%language "c++"
%defines "parser.h"
%define api.token.constructor
%define api.value.type variant
%locations
%define api.prefix {ces}
%parse-param { BaseNode** result }

%code requires {
	#include "BaseNode.h"
}

%code {
	#include <iostream>
	#include "BaseNode.h"

	extern ces::parser::symbol_type yylex ();
}

%token HEX "hex" IDENT "ident"
%token PLUS "+" MINUS "-" MUL "*" DIV "/" POW "**" LPAREN "(" RPAREN ")" LSQUARE "[" RSQUARE "]" DOT "."

%left PLUS MINUS
%left MUL DIV
%left POW

%type <std::string> HEX IDENT
%type <std::vector<std::string>*> identList
%type <BaseNode*> atom unaryExpr binaryExpr CEAddressString

%start CEAddressString
%%


CEAddressString: binaryExpr YYEOF { *result = $1; $$ = $1; }

binaryExpr: atom { $$ = $1; }
| unaryExpr { $$ = $1; }
| binaryExpr PLUS binaryExpr { $$ = new BinaryNode($1, token::PLUS, $3); }
| binaryExpr MINUS binaryExpr { $$ = new BinaryNode($1, token::MINUS, $3); }
| binaryExpr MUL binaryExpr { $$ = new BinaryNode($1, token::MUL, $3); }
| binaryExpr POW binaryExpr { $$ = new BinaryNode($1, token::POW, $3); }
;

unaryExpr: PLUS	atom { $$ = new UnaryNode(token::PLUS, $2); }
| MINUS atom { $$ = new UnaryNode(token::MINUS, $2); }
;

atom:	HEX	{ $$ = new HexNode($1); }
| LPAREN binaryExpr RPAREN { $$ = $2; }
| LSQUARE binaryExpr RSQUARE { $$ = new PointerNode($2); }
| identList	{ $$ = new IdentsNode($1); }
;

identList: IDENT { $$ = new std::vector<std::string>(); $$->push_back($1); }
| identList DOT IDENT	{ $$ = $1; $$->push_back($3); }
;
%%

void ces::parser::error(const location_type& loc, const std::string& msg)
{
  printf("Parser Error:%s\n%d:%d,%d:%d\n", msg.c_str(), loc.begin.line, loc.begin.column, loc.end.line, loc.end.column);
}