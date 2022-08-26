#include<stdio.h>
#include<stdlib.h>
#include"types.h"
#include"die.h"
#include"time.h"

#define MAX_NUMBER 6
#define MIN_NUMBER 1


struct _Die{
    Id id;
    int min;
    int max;
    int number;
};

Die* die_create(Id id){
    Die *newDie=NULL;
    if (!id){
        return NULL;
    }
    newDie = (Die *) malloc(sizeof (Die));
    srand(time(NULL));
    
    newDie->id=id;
    newDie->min=MIN_NUMBER;
    newDie->max=MAX_NUMBER;
    newDie->number=0;
    return newDie;
}

STATUS die_destroy(Die* die){

    if (die==NULL){
        return ERROR;
    }

    die=NULL;
    free(die);
    return OK;

}


STATUS die_roll(Die* die){
    if (die==NULL){
        return ERROR;
    }
    die->number=die->min+(rand()%die->max);
    return OK;
}


STATUS die_print(Die* die){

  if(die==NULL){
    return ERROR;
  }
  fprintf(stdout, "The die rolled to the number: %d", die->number);
  return OK;
}

int die_get_number(Die* die){
    return die->number;
}