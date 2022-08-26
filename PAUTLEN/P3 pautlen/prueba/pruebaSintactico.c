#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
extern FILE *yyin;
extern FILE *yyout;

int main(int argc, char **argv){

    if (argc != 3){
        printf("\n Error en el numero de parametros:\t./pruebaSintactico <ficheroEntrada> <ficheroSalida>\n");
        return 0;
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL){
        printf("Error al abrir el fichero de entrada.\n");
        return 0;
    }

    yyout = fopen(argv[2], "w");
    if (yyout == NULL){
        printf("Error al abrir el fichero de salida.\n");
        fclose(yyin);
        return 0;
    }

    if (yyparse() != 0)
        printf("Error en el analisis sintactico.\n");
    else
        printf("El analisis sintactico a terminado con exito.\n");

    fclose(yyout);
    fclose(yyin);
    return 0;
}