#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

extern int yylex();
extern FILE *yyin;
extern FILE *yyout;
extern char *yytext;
extern int yyleng;
extern int l;
extern int pos;


int main(int argc, char* argv[])
{
    int token = 0;
    int position = 0;

    if(argc < 3){
        fprintf(stderr, "Error in the arguments. You need ./pruebaMorfo <Name yyin file><Name yyout file>");
        return -1;
    }

    yyin = fopen(argv[1], "r");
    if(!yyin){
        fprintf(stderr, "Error while opening the yyin file");
        return -1;
    }

    yyout = fopen(argv[2], "w");
    if(!yyout){
        fprintf(stderr, "Error while opening the yyout file");
        return -1;
    }

    do{
        position = pos+1;
        token = yylex();
        if(token == TOK_MAIN){
            fprintf(yyout, "TOK_MAIN\t%d\t%s\n", TOK_MAIN, yytext);
        }
        else if(token == TOK_INT){
            fprintf(yyout, "TOK_INT\t%d\t%s\n", TOK_INT, yytext);
        }
        else if(token == TOK_BOOLEAN){
            fprintf(yyout, "TOK_BOOLEAN\t%d\t%s\n", TOK_BOOLEAN, yytext);
        }

        else if(token == TOK_ARRAY){
            fprintf(yyout, "TOK_ARRAY\t%d\t%s\n", TOK_ARRAY, yytext);
        }

        else if(token == TOK_FUNCTION){
            fprintf(yyout, "TOK_FUNCTION\t%d\t%s\n", TOK_FUNCTION, yytext);
        }

        else if(token == TOK_IF){
            fprintf(yyout, "TOK_IF\t%d\t%s\n", TOK_IF, yytext);
        }

        else if(token == TOK_ELSE){
            fprintf(yyout, "TOK_ELSE\t%d\t%s\n", TOK_ELSE, yytext);
        }

        else if(token == TOK_WHILE){
            fprintf(yyout, "TOK_WHILE\t%d\t%s\n", TOK_WHILE, yytext);
        }

        else if(token == TOK_SCANF){
            fprintf(yyout, "TOK_SCANF\t%d\t%s\n", TOK_SCANF, yytext);
        }

        else if(token == TOK_PRINTF){
            fprintf(yyout, "TOK_PRINTF\t%d\t%s\n", TOK_PRINTF, yytext);
        }

        else if(token == TOK_RETURN){
            fprintf(yyout, "TOK_RETURN\t%d\t%s\n", TOK_RETURN, yytext);
        }

        else if(token == TOK_PUNTOYCOMA){
            fprintf(yyout, "TOK_PUNTOYCOMA\t%d\t%s\n", TOK_PUNTOYCOMA, yytext);
        }

        else if(token == TOK_COMA){
            fprintf(yyout, "TOK_COMA\t%d\t%s\n", TOK_COMA, yytext);
        }

        else if(token == TOK_PARENTESISIZQUIERDO){
            fprintf(yyout, "TOK_PARENTESISIZQUIERDO\t%d\t%s\n", TOK_PARENTESISIZQUIERDO, yytext);
        }

        else if(token == TOK_PARENTESISDERECHO){
            fprintf(yyout, "TOK_PARENTESISDERECHO\t%d\t%s\n", TOK_PARENTESISDERECHO, yytext);
        }

        else if(token == TOK_CORCHETEIZQUIERDO){
            fprintf(yyout, "TOK_CORCHETEIZQUIERDO\t%d\t%s\n", TOK_CORCHETEIZQUIERDO, yytext);
        }

        else if(token == TOK_CORCHETEDERECHO){
            fprintf(yyout, "TOK_CORCHETEDERECHO\t%d\t%s\n", TOK_CORCHETEDERECHO, yytext);
        }

        else if(token == TOK_LLAVEIZQUIERDA){
            fprintf(yyout, "TOK_LLAVEIZQUIERDA\t%d\t%s\n", TOK_LLAVEIZQUIERDA, yytext);
        }

        else if(token == TOK_LLAVEDERECHA){
            fprintf(yyout, "TOK_LLAVEDERECHA\t%d\t%s\n", TOK_LLAVEDERECHA, yytext);
        }

        else if(token == TOK_ASIGNACION){
            fprintf(yyout, "TOK_ASIGNACION\t%d\t%s\n", TOK_ASIGNACION, yytext);
        }

        else if(token == TOK_MAS){
            fprintf(yyout, "TOK_MAS\t%d\t%s\n", TOK_MAS, yytext);
        }

        else if(token == TOK_MENOS){
            fprintf(yyout, "TOK_MENOS\t%d\t%s\n", TOK_MENOS, yytext);
        }

        else if(token == TOK_DIVISION){
            fprintf(yyout, "TOK_DIVISION\t%d\t%s\n", TOK_DIVISION, yytext);
        }

        else if(token == TOK_ASTERISCO){
            fprintf(yyout, "TOK_ASTERISCO\t%d\t%s\n", TOK_ASTERISCO, yytext);
        }

        else if(token == TOK_AND){
            fprintf(yyout, "TOK_AND\t%d\t%s\n", TOK_AND, yytext);
        }

        else if(token == TOK_OR){
            fprintf(yyout, "TOK_OR\t%d\t%s\n", TOK_OR, yytext);
        }

        else if(token == TOK_NOT){
            fprintf(yyout, "TOK_NOT\t%d\t%s\n", TOK_NOT, yytext);
        }

        else if(token == TOK_IGUAL){
            fprintf(yyout, "TOK_IGUAL\t%d\t%s\n", TOK_IGUAL, yytext);
        }

        else if(token == TOK_DISTINTO){
            fprintf(yyout, "TOK_DISTINTO\t%d\t%s\n", TOK_DISTINTO, yytext);
        }

        else if(token == TOK_MENORIGUAL){
            fprintf(yyout, "TOK_MENORIGUAL\t%d\t%s\n", TOK_MENORIGUAL, yytext);
        }

        else if(token == TOK_MAYORIGUAL){
            fprintf(yyout, "TOK_MAYORIGUAL\t%d\t%s\n", TOK_MAYORIGUAL, yytext);
        }

        else if(token == TOK_MENOR){
            fprintf(yyout, "TOK_MENOR\t%d\t%s\n", TOK_MENOR, yytext);
        }

        else if(token == TOK_MAYOR){
            fprintf(yyout, "TOK_MAYOR\t%d\t%s\n", TOK_MAYOR, yytext);
        }

        else if(token == TOK_IDENTIFICADOR){
            if(yyleng <= 100){
                fprintf(yyout, "TOK_IDENTIFICADOR\t%d\t%s\n", TOK_IDENTIFICADOR, yytext);
            }
            else {
                fprintf(stderr, "****Error en [lin %d, col %d]: identificador demasiado largo %s\n", l, position, yytext);
                break;
            }
        }

        else if(token == TOK_CONSTANTE_ENTERA){
            fprintf(yyout, "TOK_CONSTANTE_ENTERA\t%d\t%s\n", TOK_CONSTANTE_ENTERA, yytext);
        }

        else if(token == TOK_TRUE){
            fprintf(yyout, "TOK_TRUE\t%d\t%s\n", TOK_TRUE, yytext);
        }

        else if(token == TOK_FALSE){
            fprintf(yyout, "TOK_FALSE\t%d\t%s\n", TOK_FALSE, yytext);
        }

        else if(token == TOK_ERROR){
            fprintf(stderr, "****Error en [lin %d, col %d]: símbolo no identificado %s\n", l, position, yytext);
            break;
        }

    } while(token != 0);

    fclose(yyin);
    fclose(yyout);

    return 0;
}