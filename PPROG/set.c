#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

struct _Set {
  Id id[MAX_IDS];
  int nIds;
};

Set* set_create() {
  int i=0;
  Set *newSet = NULL;
  newSet = (Set *) malloc(sizeof (Set));

  if (newSet == NULL) {
    return NULL;
  }
  for (i=0; i<MAX_IDS;i++){
    newSet->id[i] = NO_ID;
  }
  newSet->nIds=0;
  return newSet;
}

STATUS set_destroy(Set* set) {
  if (set==NULL) {
    return ERROR;
  }

  free(set);
  set = NULL;

  return OK;
}

Id set_get_id(Set* set, int position){
  if(!set ){
    return NO_ID;
  }
  return set->id[position];
  }



STATUS set_add_id(Set* set, Id id){
  int i=0;
  if (!set || id == NO_ID) return ERROR;
  if (set->nIds>= MAX_IDS) return ERROR;
  for(i=0; i<MAX_IDS; i++){
    if (set_get_id(set, i)==NO_ID){
      set->id[i]=id;
      set->nIds++;
      return OK;
    }
  }
  return ERROR;
}


STATUS set_del_id(Set* set, Id id){
  int i=0;
  if(!set || id==NO_ID) return ERROR;
  if (set->nIds<=0) return ERROR;

  for(i=0; i<MAX_IDS; i++){
    if(set->id[i]==id){
        set->id[i]=NO_ID;
        set->nIds--;
        return OK;
    }
  }
  return ERROR;
}


STATUS set_print(Set* set){
  int i;
  if(!set){
    return ERROR;
  }

  
  for(i=0; i<MAX_IDS; i++){
    if(set->id[i]!=NO_ID){
      fprintf(stdout, "ID(%d)=%ld", i, set->id[i]);
    }
  }
  fprintf(stdout, "%d", set->nIds);
  return OK;
}