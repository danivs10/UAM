%{
 #include <stdio.h>
 #include <stdlib.h>
 #include "tokens.h"
 int l = 1, pos = 1;
%}

%option noyywrap

LETRA [a-zA-z]
DIGITO [0-9]
ALFANUMERICO [a-zA-Z0-9]*

%%


[\n] {l++; pos=1;}
[\t] {pos+=yyleng;}
" " {pos+=yyleng;}
"//"(.)*[\n] {l++; pos=1;}


"main" {pos+=yyleng; return TOK_MAIN;}
"int" {pos+=yyleng; return TOK_INT;}
"boolean" {pos+=yyleng; return TOK_BOOLEAN;}
"array" {pos+=yyleng; return TOK_ARRAY;}
"function" {pos+=yyleng; return TOK_FUNCTION;}
"if" {pos+=yyleng; return TOK_IF;}
"else" {pos+=yyleng; return TOK_ELSE;}
"while" {pos+=yyleng; return TOK_WHILE;}
"scanf" {pos+=yyleng; return TOK_SCANF;} 
"printf" {pos+=yyleng; return TOK_PRINTF;}
"return" {pos+=yyleng; return TOK_RETURN;}


";" {pos+=yyleng; return TOK_PUNTOYCOMA;}
"," {pos+=yyleng; return TOK_COMA;}
"(" {pos+=yyleng; return TOK_PARENTESISIZQUIERDO;}
")" {pos+=yyleng; return TOK_PARENTESISDERECHO;}
"[" {pos+=yyleng; return TOK_CORCHETEIZQUIERDO;}
"]" {pos+=yyleng; return TOK_CORCHETEDERECHO;}
"{" {pos+=yyleng; return TOK_LLAVEIZQUIERDA;}
"}" {pos+=yyleng; return TOK_LLAVEDERECHA;}


"=" {pos+=yyleng; return TOK_ASIGNACION;}
"+" {pos+=yyleng; return TOK_MAS;}
"-" {pos+=yyleng; return TOK_MENOS;}
"/" {pos+=yyleng; return TOK_DIVISION;}
"*" {pos+=yyleng; return TOK_ASTERISCO;}


"&&" {pos+=yyleng; return TOK_AND;}
"||" {pos+=yyleng; return TOK_OR;}
"!" {pos+=yyleng; return TOK_NOT;}
"==" {pos+=yyleng; return TOK_IGUAL;}
"!=" {pos+=yyleng; return TOK_DISTINTO;}
"<=" {pos+=yyleng; return TOK_MENORIGUAL;}
">=" {pos+=yyleng; return TOK_MAYORIGUAL;}
"<"  {pos+=yyleng; return TOK_MENOR;}
">" {pos+=yyleng; return TOK_MAYOR;}


"true" {pos+=yyleng; return TOK_TRUE;}
"false" {pos+=yyleng; return TOK_FALSE;}
({DIGITO})+ {pos+=yyleng; return TOK_CONSTANTE_ENTERA;}


{LETRA}{ALFANUMERICO} {pos+=yyleng; return TOK_IDENTIFICADOR;}


. {pos+=yyleng; return TOK_ERROR;}


%%
