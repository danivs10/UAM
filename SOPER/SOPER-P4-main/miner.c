/********************************************************/
/* Nombre: miner.c                                      */
/*                                                      */
/* Fecha: 09/05/2021                                    */
/* Autores: Javier Lopez & Daniel Varela                */
/*                                                      */
/* @Brief: Este programa implementa una red de mineros  */
/* que buscan simultaneamente una solucion a un problema*/
/* matematico(POW)                                      */
/********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <fcntl.h>
#include "miner.h"
#include "common.h"

#define PRIME 99997669
#define BIG_X 435679812
#define BIG_Y 100001819

/*Nombre de la cola de mensajes y de los segmentos de memoria compartida*/
#define MQ_NAME "/MsgQueue"
#define SHM_NET "/red_mineros"
#define SHM_BLOCK "/bloque"

static volatile int solucionado = -1;
static volatile sig_atomic_t sigusr2 = 0;

/********************************************************/
/* Funcion: *manejador_SIGUSR2                          */
/*                                                      */
/* Fecha: 09/05/2021                                    */
/* Autores: Javier Lopez & Daniel Varela                */
/*                                                      */
/* @brief: pone la variable global sigusr2 a 1 cuando   */
/* la función es llamada                                */
/*                                                      */
/* @param: sig este parametro indica el numero de la    */
/* señal recibida                                       */
/********************************************************/
void manejador_SIGUSR2(int sig)
{
    sigusr2 = 1;
}

/********************************************************/
/* Funcion: *buscarSolucion                            */
/*                                                      */
/* Fecha: 09/05/2021                                    */
/* Autores: Javier Lopez & Daniel Varela                */
/*                                                      */
/* @brief: busca una solucion a un problema matematico  */
/* previamente establecido y lo guarda en un bloque     */
/*                                                      */
/* @param: *b estructura de tipo bloque donde se guarda */
/* la solucion                                          */
/********************************************************/
void *buscarSolucion(void *b)
{
    long int i = 0;
    Block *block = b;
    for (i = 0; i < PRIME; i++)
    {
        if (block->target == simple_hash(i))
        {
            fprintf(stdout, "\nSolution: %ld\n", i);
            block->solution = i;
            solucionado = i;
            return NULL;
        }
        if (solucionado != -1)
        {
            //comprobar solucion y votar en consecuencia
            return NULL;
        }
    }
}

/********************************************************/
/* Funcion: simple_hash                                 */
/*                                                      */
/* Fecha: 09/05/2021                                    */
/* Autores: Javier Lopez & Daniel Varela                */
/*                                                      */
/* @brief: resuelve el problema maatematico dado en     */
/* base al parametro introducido                        */
/*                                                      */
/* @param: number el cual se utilizara para buscar la   */
/* solucion                                             */ 
/*                                                      */
/* @return int con el resultado obtenido                */
/********************************************************/
long int simple_hash(long int number)
{
    long int result = (number * BIG_X + BIG_Y) % PRIME;
    return result;
}

int main(int argc, char *argv[])
{ 
    long int i, target, j;
    long int numTrabajadores;
    long int rondasMinado = 0;
    int red, bloque,error;
    Block *b, *bloqueComp;
    Block *auxb;
    NetData *redMineros;
    pid_t pid;
    bool notRondas = false;
    struct sigaction act;
    pthread_t hilo[numTrabajadores];
    struct mq_attr attributes = {
        . mq_flags = 0 ,
        . mq_maxmsg =  10,
        . mq_curmsgs = 0 ,
        . mq_msgsize = sizeof ( Block )
    };
    
    /*Creamos y/o abrimos la cola de mensajes*/
    mqd_t mq = mq_open(MQ_NAME, O_CREAT | O_WRONLY | O_NONBLOCK, S_IRUSR | S_IWUSR, &attributes);
    if (mq == (mqd_t)-1)
        {
            perror(" mq_open ");
            exit(EXIT_FAILURE);
        }
/*
    red = shm_open ( SHM_NET , O_RDWR | O_CREAT | O_EXCL , S_IRUSR | S_IWUSR ) ;
    if ( red == -1) {
    if ( errno == EEXIST ) {
        red = shm_open ( SHM_NET , O_RDWR , 0) ;
        if ( red == -1) {
            perror (" Error opening the shared memory segment ") ;
            exit ( EXIT_FAILURE ) ;
        }
    }
    else {
        perror (" Error creating the shared memory segment \n") ;
        exit ( EXIT_FAILURE ) ;
    }
    if ( ftruncate ( red , sizeof ( NetData ) ) == -1) {
        perror (" ftruncate ") ;
        shm_unlink ( SHM_NET ) ;
        exit ( EXIT_FAILURE ) ;
    }

    redMineros = mmap ( NULL , sizeof ( NetData ) , PROT_READ | PROT_WRITE , MAP_SHARED , red , 0) ;
    close ( red ) ;

    bloque = shm_open ( SHM_BLOCK , O_RDWR | O_CREAT | O_EXCL , S_IRUSR | S_IWUSR ) ;
    if ( bloque == -1) {
    if ( errno == EEXIST ) {
        bloque = shm_open ( SHM_BLOCK , O_RDWR , 0);
        if ( bloque == -1) {
            perror (" Error opening the shared memory segment ");
            exit ( EXIT_FAILURE ) ;
        }
    }
    else {
        perror (" Error creating the shared memory segment \n");
        exit ( EXIT_FAILURE ) ;
    }
    if ( ftruncate ( bloque , sizeof ( Block ) ) == -1){
        perror (" ftruncate ") ;
        shm_unlink ( SHM_BLOCK ) ;
        exit ( EXIT_FAILURE ) ;
    }

    bloqueComp = mmap ( NULL , sizeof ( Block ) , PROT_READ | PROT_WRITE , MAP_SHARED , bloque , 0) ;
    close (bloque);
}
*/
    /*Configuramos la estructura del sigaction para capturar la señal sigusr2*/
    act.sa_handler = manejador_SIGUSR2;
    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;
    
    /*Llamada a sigaction*/
    if (sigaction(SIGUSR2, &act, NULL) < 0)
    {
        perror(" sigaction ");
        exit(EXIT_FAILURE);
    }

    /*Declaracion del numbero primo con el que trabajaremos*/
    srand(time(NULL));
    target = rand() % PRIME;

    /*Control de errores para el numero de argumnetos*/
    if (argc < 2 || argc > 3)
    {
        fprintf(stderr, "Usage: %s <TRABAJADORES> <RONDAS>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid = getpid();

    /*Cogemos los valores que han entrado como argumentos*/
    numTrabajadores = atol(argv[1]);
    if (argv[2] != NULL)
    {
        rondasMinado = atol(argv[2]);
    }
    if (!(rondasMinado > 0))
    {
        notRondas = true;
    }

    /*Bucle principal del minado*/
    for (j = 1; j <= rondasMinado || notRondas; j++)
    {
        /*Comprobamos si hemos capturado la señal*/
        if (sigusr2)
        {
            sigusr2 = 0;
            notRondas = false;
            mq_close(mq);
            exit(EXIT_SUCCESS);
        }

        auxb = b;
        b = (Block *)malloc(sizeof(Block));
        if (b == NULL)
            exit(EXIT_FAILURE);
        b->target = target;
        b->id = j;
        if (j > 1)
        {
            b->prev = auxb;
            b->prev->next = b;
        }
        /*Bucle de creacion de todos los hilos*/
        for (i = 0; i < numTrabajadores; i++)
        {
            error=pthread_create(&hilo[i], NULL, buscarSolucion, b);
            if(error != 0){
                fprintf ( stderr , " pthread_create : %s\n", strerror ( error ) ) ;
                exit ( EXIT_FAILURE ) ;
            }
        }

        /*Bucle para esperar a todos los hilos creados*/
        for (i = 0; i < numTrabajadores; i++)
        {
            error=pthread_join(hilo[i], NULL);
            if(error != 0){
                fprintf ( stderr , " pthread_join : %s\n", strerror ( error ) ) ;
                
                exit ( EXIT_FAILURE ) ;
            }
        }
        /*Envio del mensaje al monitor*/
        error = mq_send(mq, (const char*)b, sizeof(Block), 1);
        
        printf("bloque : %ld\n", j );
        
        /*Asignamos la solucion al sigiente bucle de minado*/
        solucionado = -1;
        target = b->solution;
    }
    /*Una vez terminado el minado, printeamos todos los bloques y cerramos los recursos*/
    print_blocks(b, 1, "Ex1");
    mq_close(mq);
    wait(NULL);
    exit(EXIT_SUCCESS);
}
