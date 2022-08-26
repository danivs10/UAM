#ifndef ALFA_H
#define ALFA_H

#include "hashTable.h"
#include "tablaSimbolos.h"
#include "generacion.h"

/*Sizes variables declarations*/
#define MAX_VECTOR_SIZE 64
#define MAX_IDENTIFICADORES 100

typedef struct
{
/*
   Structure for the atributes
*/
	char lexema[MAX_IDENTIFICADORES+1];
    int tipo;
    int valor_entero;
    int es_direccion;
    int etiqueta;
} type_atributes;
#endif 
