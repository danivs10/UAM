#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
extern FILE *yyin;
extern FILE *yyout;

int main(int argc, char **argv){

    if (argc != 3){
        printf("Incorrect parametres. Input: pruebaSintactico <input file name> <output file name>\n");
        return -1;
    }

    if(!(yyin = fopen(argv[1], "r"))){
        printf("Error while opening input file\n");
        return -1;
    }

    if(!(yyout = fopen(argv[2], "w"))){
        printf("Error while opening output file\n");
        fclose(yyin);
        return -1;
    }

    if(yyparse() != 0){
        printf("Error while executing the parser\n");
    }

    else{
        printf("Executing parser was successful\n");
    }

    fclose(yyin);
    fclose(yyout);
    return 0;

}