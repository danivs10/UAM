#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "set.h"
#include "link.h"

struct _Space {
  Id id;
  BOOL illuminated;
  char name[WORD_SIZE + 1];
  Link *north;
  Link *south;
  Link *east;
  Link *west;
  Link *up;
  Link *down;
  Set *object;
  char gdesc[3][21];
  char desc[MAX_DESC];
};


Space* space_create(Id id) {

  Space *newSpace = NULL;

  if (id == NO_ID)
    return NULL;

  newSpace = (Space *) malloc(sizeof (Space));

  if (newSpace == NULL) {
    return NULL;
  }
  newSpace->id = id;

  newSpace->name[0] = '\0';

  newSpace->north = NULL;
  newSpace->south = NULL;
  newSpace->east = NULL;
  newSpace->west = NULL;
  newSpace->up = NULL;
  newSpace->down = NULL;
  newSpace->illuminated=TRUE;
  strcpy(newSpace->desc, "This space has no description");

  newSpace->object = set_create();



  return newSpace;
}

STATUS space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  free(space);
  space = NULL;

  return OK;
}

STATUS space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }

  return OK;
}

STATUS space_set_north(Space* space, Link *link) {
  if (!space || !link) {
    return ERROR;
  }
  space->north = link;
  return OK;
}

STATUS space_set_south(Space* space, Link *link) {
  if (!space || !link) {
    return ERROR;
  }
  space->south = link;
  return OK;
}

STATUS space_set_east(Space* space, Link *link) {
  if (!space || !link) {
    return ERROR;
  }
  space->east = link;
  return OK;
}

STATUS space_set_west(Space* space, Link *link) {
  if (!space || !link) {
    return ERROR;
  }
  space->west = link;
  return OK;
}
STATUS space_set_up(Space* space, Link *link) {
  if (!space || !link) {
    return ERROR;
  }
  space->up = link;
  return OK;
}
STATUS space_set_down(Space* space, Link *link) {
  if (!space || !link) {
    return ERROR;
  }
  space->down = link;
  return OK;
}

STATUS space_add_object(Space* space, Id value) {
  if (!space) {
    return ERROR;
  }
  
  
  return set_add_id(space->object, value);
}

const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

Id space_get_north(Space* space) {
  if (!space ||space->north==NULL) {
    return NO_ID;
  }
  return link_get_source(space->north);
}

Id space_get_south(Space* space) {
  if (!space ||space->south==NULL) {
    return NO_ID;
  }
  return link_get_destiny(space->south);
}

Id space_get_east(Space* space) {
  if (!space ||space->east==NULL) {
    return NO_ID;
  }
  return link_get_destiny(space->east);
}

Id space_get_west(Space* space) {
  if (!space ||space->west==NULL) {
    return NO_ID;
  }
  return link_get_source(space->west);
}
Id space_get_up(Space* space) {
  if (!space ||space->up==NULL) {
    return NO_ID;
  }
  return link_get_source(space->up);
}
Id space_get_down(Space* space) {
  if (!space ||space->down==NULL) {
    return NO_ID;
  }
  return link_get_destiny(space->down);
}


Id space_get_object_at(Space* space, int position) {
  if (!space) {
    return NO_ID;
  }

    return set_get_id(space->object, position);
}

STATUS space_print(Space* space) {
  int nObj=0;
  int i=0;
  Id idaux = NO_ID;

  if (!space) {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_north(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }

  idaux = space_get_south(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }

  idaux = space_get_east(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }

  idaux = space_get_west(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  idaux = space_get_up(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Up link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No up link.\n");
  }

  idaux = space_get_down(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Down link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No down link.\n");
  }
  for (i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(space, i)!=NO_ID){
      nObj++;
    }
  }
  if (nObj>0) {
    fprintf(stdout, "---> Object in the space.\n");
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}

Set *space_get_set(Space* space){
  if(!space)return ERROR;
  return space->object;
}

STATUS space_del_object(Space *space, Object *object){
  if(space==NULL || object==NULL){
    return ERROR;
  }
  set_del_id(space->object, object_get_id(object));
  return OK;
}


STATUS space_set_gdesc1(Space* space, char* gdesc){

  if (!space || !gdesc) {
    return ERROR;
  }

  if (!strcpy(space->gdesc[0], gdesc)) {
    return ERROR;
  }
  
  return OK;
}
STATUS space_set_gdesc2(Space* space, char* gdesc){
 
  if (!space || !gdesc) {
    return ERROR;
  }

  if (!strcpy(space->gdesc[1], gdesc)) {
    return ERROR;
  }
  
  return OK;
}

STATUS space_set_gdesc3(Space* space, char* gdesc){
 
  if (!space || !gdesc) {
    return ERROR;
  }

  if (!strcpy(space->gdesc[2], gdesc)) {
    return ERROR;
  }
  
  return OK;
}

const char * space_get_gdesc1(Space* space){
  char* gdesc1 = NULL;

  if (!space) {
    return NULL;
  }

gdesc1 = (char*)malloc(sizeof(char)*7);

  strncpy(gdesc1, space->gdesc[0], 7);

  return gdesc1;
}

const char * space_get_gdesc2(Space* space){
  char* gdesc2 = NULL;

  if (!space) {
    return NULL;
  }

gdesc2 = (char*)malloc(sizeof(char)*7);

  strncpy(gdesc2, space->gdesc[1], 7);

  return gdesc2;
}

const char * space_get_gdesc3(Space* space){
  if (!space) {
    return NULL;
  }
  return space->gdesc[2];
}


STATUS space_set_description(Space *space, char desc[MAX_DESC]){
  if (!space){
    return ERROR;
  }
  strcpy(space->desc, desc);
  return OK;
}

char *space_get_description(Space *space){
  if (!space){
    return NULL;
  }

  return space->desc;
}


BOOL is_west_available(Space *space){
  if(!space){
    return FALSE;
  }
  if (space->west!=NULL && link_get_status(space->west)==OPEN){
    return TRUE;
  }
  return FALSE;
}

BOOL is_up_available(Space *space){
  if(!space){
    return FALSE;
  }
  if (space->up!=NULL && link_get_status(space->up)==OPEN){
    return TRUE;
  }
  return FALSE;
}

BOOL is_down_available(Space *space){
  if(!space){
    return FALSE;
  }
  if (space->down!=NULL && link_get_status(space->down)==OPEN){
    return TRUE;
  }
  return FALSE;
}
BOOL is_east_available(Space *space){
  if(!space){
    return FALSE;
  }
  if (space->east!=NULL && link_get_status(space->east)==OPEN){
    return TRUE;
  }
  return FALSE;
}
BOOL is_north_available(Space *space){
  if(!space){
    return FALSE;
  }
  if (space->north!=NULL && link_get_status(space->north)==OPEN){
    return TRUE;
  }
  return FALSE;
}
BOOL is_south_available(Space *space){
  if(!space){
    return FALSE;
  }
  if (space->south!=NULL && link_get_status(space->south)==OPEN){
    return TRUE;
  }
  return FALSE;
}

Link *space_get_link_north(Space *space){
  if(!space){
    return NULL;
  }
  return space->north;
}

Link *space_get_link_east(Space *space){
  if(!space){
    return NULL;
  }
  return space->east;
}

Link *space_get_link_south(Space *space){
  if(!space){
    return NULL;
  }
  return space->south;
}

Link *space_get_link_west(Space *space){
  if(!space){
    return NULL;
  }
  return space->west;
}

BOOL space_get_illuminated(Space *space){
  if(!space){
    return FALSE;
  }
  return space->illuminated;
}
STATUS space_set_illuminated(Space *space, BOOL illuminated){
  if(!space){
    return FALSE;
  }
  space->illuminated=illuminated;
  return OK;
}