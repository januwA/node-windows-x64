%defines "parser.h"
%locations

%code requires {
	#include "BaseNode.h"
}

%{
	#include <cmath>
	#include <cstdio>
	#include <iostream>
	#include "BaseNode.h"

	extern int yylex();
	extern void yyerror(BaseNode** result, const char*);
%}

%parse-param { BaseNode** result }
%union {
	std::string* text;
	std::vector<std::string*>* idents;
	BaseNode* node;
}

%token HEX "hex" IDENT "ident"
%token PLUS "+" MINUS "-" MUL "*" DIV "/" POW "**" LPAREN "(" RPAREN ")" LSQUARE "[" RSQUARE "]" DOT "."

%left PLUS MINUS
%left MUL DIV
%left POW

%type <text> HEX IDENT
%type <idents> identList
%type <node> atom unaryExpr binaryExpr CEAddressString

%start CEAddressString
%%


CEAddressString: binaryExpr YYEOF { *result = $1; $$ = $1; }

binaryExpr: atom { $$ = $1; }
| unaryExpr { $$ = $1; }
| binaryExpr PLUS binaryExpr { $$ = new BinaryNode($1, PLUS, $3); }
| binaryExpr MINUS binaryExpr { $$ = new BinaryNode($1, MINUS, $3); }
| binaryExpr MUL binaryExpr { $$ = new BinaryNode($1, MUL, $3); }
| binaryExpr POW binaryExpr { $$ = new BinaryNode($1, POW, $3); }
;

unaryExpr: PLUS	atom { $$ = new UnaryNode(PLUS, $2); }
| MINUS atom { $$ = new UnaryNode(MINUS, $2); }
;

atom:	HEX	{ $$ = new HexNode($1); }
| LPAREN binaryExpr RPAREN { $$ = $2; }
| LSQUARE binaryExpr RSQUARE { $$ = new PointerNode($2); }
| identList	{ $$ = new IdentsNode($1); }
;

identList: IDENT { $$ = new std::vector<std::string*>(); $$->push_back($1); }
| identList DOT IDENT	{ $$ = $1; $$->push_back($3); }
;
%%