/********************************************************/
/* Nombre: common.c                                     */
/*                                                      */
/* Fecha: 09/05/2021                                    */
/* Autores: Javier Lopez & Daniel Varela                */
/*                                                      */
/* @Brief: Este programa se encarga de definir las      */
/* funciones comunes entre monitor y minero para asi    */
/* utilizarlas en ambos procesos de forma sumultanea    */
/********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <fcntl.h>
#include "miner.h"

/********************************************************/
/* Funcion: print_blocks                                */
/*                                                      */
/* Fecha: 09/05/2021                                    */
/* Autores: Javier Lopez & Daniel Varela                */
/*                                                      */
/* @brief: imprime en el archivo con nombre file toda   */
/* la lista de bloques del minado                       */
/*                                                      */
/* @param: *plast_block primer bloque creado            */
/* @param: num_wallets numero de carteras a printear    */
/* @param: *file nombre del archivo donde printear      */
/********************************************************/
void print_blocks(Block *plast_block, int num_wallets, char * file)
{
    Block *block = NULL;
    int i, j;
    FILE *f;

    if(plast_block==NULL || num_wallets<0 || file==NULL) {
        printf("Soy un error reloco");
        return;
    }

    if ((f = fopen(file, "w")) == NULL)
    {
        printf("Error opening file");
        return;
    }
    
    for (i = 0, block = plast_block; block != NULL; block = block->prev, i++)
    {
        fprintf(f, "Block number: %d; Target: %ld;    Solution: %ld\n", block->id, block->target, block->solution);
        for (j = 0; j < num_wallets; j++)
        {
            fprintf(f, "%d: %d;         ", j, block->wallets[j]);
        }
        fprintf(f, "\n\n\n");
    }
    fprintf(f, "A total of %d blocks were printed\n", i);
}
