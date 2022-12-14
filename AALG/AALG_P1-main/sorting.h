/**
 *
 * Descripcion: Header file for sorting functions 
 *
 * Fichero: sorting.h
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#ifndef ORDENACION_H
#define ORDENACION_H

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

/* type definitions */
typedef int (* pfunc_ordena)(int*, int, int);

/* Functions */

int InsertSort(int* table, int ip, int iu);
int InsertSortInv(int* table, int ip, int iu);

int MergeSort(int* table, int ip, int iu);
int Merge(int* table, int ip, int iu, int imiddle);

int quicksort(int *table, int ip, int iu);
int split(int *table, int ip, int iu, int *pos);


#endif
