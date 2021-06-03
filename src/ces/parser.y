%require "3.7"
%skeleton "lalr1.cc"
%language "c++"
%defines "parser.h"
%define api.token.constructor
%define api.value.type variant
%locations
%define api.prefix {ces}
%parse-param { BaseNode** result } {std::string_view source}
%lex-param {std::string_view source}

%code requires {
	#include "BaseNode.h"
  #include "error.hpp"
}

%code {
	#include <iostream>
	#include "BaseNode.h"

	extern ces::parser::symbol_type yylex (std::string_view source);
}

%token HEX "hex" IDENT "ident"
%token PLUS "+" MINUS "-" MUL "*" DIV "/" POW "**" LSQUARE "[" RSQUARE "]" DOT "."

%left PLUS MINUS
%left MUL DIV
%left POW

%type <std::string> HEX IDENT
%type <std::vector<std::string>*> identList
%type <BaseNode*> atom unaryExpr binaryExpr CEAddressString

%start CEAddressString
%%


CEAddressString: binaryExpr YYEOF { *result = $1; $$ = $1; }
;

binaryExpr: atom { $$ = $1; }
| unaryExpr { $$ = $1; }
| binaryExpr PLUS binaryExpr { $$ = new BinaryNode($1, token::PLUS, $3, @1 += @3); }
| binaryExpr MINUS binaryExpr { $$ = new BinaryNode($1, token::MINUS, $3,@1 += @3); }
| binaryExpr MUL binaryExpr { $$ = new BinaryNode($1, token::MUL, $3, @1 += @3); }
| binaryExpr DIV binaryExpr { $$ = new BinaryNode($1, token::DIV, $3, @1 += @3); }
| binaryExpr POW binaryExpr { $$ = new BinaryNode($1, token::POW, $3, @1 += @3); }
;

unaryExpr: PLUS	atom { $$ = new UnaryNode(token::PLUS, $2, @1+@2); }
| MINUS atom { $$ = new UnaryNode(token::MINUS, $2, @1+@2); }
;

atom:	HEX	{ $$ = new HexNode($1, @1); }
| "[" binaryExpr "]" { $$ = new PointerNode($2, @1+@3); }
| identList	{ $$ = new IdentsNode($1, @1);}
;

identList: IDENT { $$ = new std::vector<std::string>{$1}; }
| identList DOT IDENT	{ $$ = $1; $$->push_back($3); }
;
%%

void ces::parser::error(const location_type& loc, const std::string& msg)
{
  throw ces::parser_error(source, loc);
}