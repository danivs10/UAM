%{
 #include <stdio.h>
 #include <stdlib.h>
 #include "y.tab.h"
 int l = 1, pos = 1, e=0;
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


"main" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MAIN;}
"int" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_INT;}
"boolean" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_BOOLEAN;}
"array" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_ARRAY;}
"function" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_FUNCTION;}
"if" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_IF;}
"else" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_ELSE;}
"while" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_WHILE;}
"scanf" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_SCANF;} 
"printf" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_PRINTF;}
"return" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_RETURN;}


";" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_PUNTOYCOMA;}
"," {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_COMA;}
"(" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_PARENTESISIZQUIERDO;}
")" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_PARENTESISDERECHO;}
"[" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_CORCHETEIZQUIERDO;}
"]" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_CORCHETEDERECHO;}
"{" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_LLAVEIZQUIERDA;}
"}" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_LLAVEDERECHA;}


"=" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_ASIGNACION;}
"+" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MAS;}
"-" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MENOS;}
"/" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_DIVISION;}
"*" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_ASTERISCO;}


"&&" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_AND;}
"||" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_OR;}
"!" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_NOT;}
"==" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_IGUAL;}
"!=" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_DISTINTO;}
"<=" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MENORIGUAL;}
">=" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MAYORIGUAL;}
"<"  {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MENOR;}
">" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MAYOR;}


"true" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_TRUE;}
"false" {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_FALSE;}
({DIGITO})+ {pos+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_CONSTANTE_ENTERA;}


{LETRA}{ALFANUMERICO} {pos+=yyleng; if (yyleng<=100){; fprintf(yyout, ";D:\t%s\n", yytext);} else {fprintf(stdout, "****Error en [lin %d, col %d]: identificador demasiado largo %s\n", l, pos, yytext); e=1; return TOK_ERROR;} return TOK_IDENTIFICADOR;}


. {pos+=yyleng; e=1; fprintf(stdout, "****Error en [lin %d, col %d]: simbolo no permitido (%s)\n", l, pos, yytext); e=1; return TOK_ERROR;}


%%
