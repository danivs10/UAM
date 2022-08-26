#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "object.h"

struct _Object {
  BOOL movable;
  BOOL hidden;
  Id open;
  BOOL illuminate;
  BOOL turnedOn;
  Id id;
  Id dependency;
  Id incompatible;
  BOOL oppened;
  char name[WORD_SIZE + 1];
  char desc[MAX_DESC];
};


/*Creates a new obect with the given Id*/
Object* object_create(Id id) {

  Object *newObject = NULL;

  if (id == NO_ID)
    return NULL;

  newObject = (Object *) malloc(sizeof (Object));

  if (newObject == NULL) {
    return NULL;
  }
  newObject->id = id;
  object_set_description(newObject, "there is no description yet");
  newObject->name[0] = '\0';
  newObject->movable=FALSE;
  newObject->hidden=FALSE;
  newObject->open=NO_ID;
  newObject->incompatible=NO_ID;
  newObject->dependency=NO_ID;
  newObject->illuminate=FALSE;
  newObject->turnedOn=FALSE;
  newObject->oppened=FALSE;

  return newObject;
}

/*Destroys the obect given as parameter*/
STATUS object_destroy(Object* object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  object = NULL;

  return OK;
}

/*Changes the name of a given obect*/
STATUS object_set_name(Object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }

  return OK;
}

/*Returns the name of an object*/
const char * object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}

/*Returns the Id of an specific object*/
Id object_get_id(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}


/*Prints the requested object*/
STATUS object_print(Object* object) {

  if (!object) {
    return ERROR;
  }

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}


char *object_get_description(Object *object){
  if (!object) {
    return NULL;
  }
  return object->desc;
}

STATUS object_set_description(Object *object, char desc[MAX_DESC]){
  if (!object) {
    return ERROR;
  }
  strcpy(object->desc, desc);
  return OK;
}

BOOL object_get_movable(Object *object){
  if (!object){
    return FALSE;
  }
  return object->movable;
}

STATUS object_set_movable(Object *object, BOOL movable){
  if (!object){
    return ERROR;
  }
  object->movable=movable;
  return OK;
}

BOOL object_get_hidden(Object *object){
  if (!object){
    return TRUE;
  }
  return object->hidden;
}

STATUS object_set_hidden(Object *object, BOOL hidden){
  if (!object){
    return ERROR;
  }
  object->hidden=hidden;
  return OK;
}
Id object_get_open(Object *object){
  if (!object){
    return NO_ID;
  }
  return object->open;
}

STATUS object_set_open(Object *object, Id open){
  if (!object){
    return ERROR;
  }
  object->open=open;
  return OK;
}

BOOL object_get_illuminate(Object *object){
  if (!object){
    return FALSE;
  }
  return object->illuminate;
}

STATUS object_set_illuminate(Object *object, BOOL illuminate){
  if (!object){
    return ERROR;
  }
  object->illuminate=illuminate;
  return OK;
}
BOOL object_get_turnedOn(Object *object){
  if (!object){
    return FALSE;
  }
  return object->turnedOn;
}

STATUS object_set_turnedOn(Object *object, BOOL turnedOn){
  if (!object){
    return ERROR;
  }
  object->turnedOn=turnedOn;
  return OK;
}

Id object_get_dependency(Object *object){
  if (!object){
    return NO_ID;
  }
  return object->dependency;
}

STATUS object_set_dependency(Object *object, Id dependency){
  if (!object){
    return ERROR;
  }
  object->dependency=dependency;
  return OK;
}
Id object_get_incompatible(Object *object){
  if (!object){
    return NO_ID;
  }
  return object->incompatible;
}

STATUS object_set_incompatible(Object *object, Id incompatible){
  if (!object){
    return ERROR;
  }
  object->incompatible=incompatible;
  return OK;
}


BOOL object_get_oppened(Object *object){
  if (!object){
    return FALSE;
  }
  return object->oppened;
}

STATUS object_set_oppened(Object *object, BOOL oppened){
  if (!object){
    return ERROR;
  }
  object->oppened=oppened;
  return OK;
}