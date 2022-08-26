/** 
 * @brief It creates links between different spaces
 * @file game.h
 * @author Daniel Varela
 * @version 1.0 
 * @date 23-03-2020
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "link.h"
#include "types.h"

struct _Link {
  Id id;
  char name[WORD_SIZE + 1];
  Id field1;
  Id field2;
  openStatus status;
};


Link *link_create(Id id){
    Link *newLink=NULL;

    if (id==NO_ID){
        return NULL;
    }

    newLink = (Link *) malloc(sizeof (Link));

    if (newLink == NULL) {
       return NULL;
    }

    newLink->id = id;
    newLink->name[0] = '\0';
    newLink->field1 = NO_ID;
    newLink->field2 = NO_ID;
    newLink->status = CLOSED;

  return newLink;
}


STATUS link_destroy(Link* link) {
  if (!link) {
    return ERROR;
  }

  free(link);
  link = NULL;

  return OK;
}

STATUS link_set_name(Link *link, char* name) {
  if (!link || !name) {
    return ERROR;
  }

  if (!strcpy(link->name, name)) {
    return ERROR;
  }

  return OK;
}

STATUS link_set_source(Link *link, Id source){
  if (!link) {
    return ERROR;
  }

  link->field1 = source;

  return OK;
}

STATUS link_set_destiny(Link *link, Id destiny){
  if (!link) {
    return ERROR;
  }

  link->field2 = destiny;
  return OK;
}


STATUS link_set_status(Link *link, openStatus status){
  if(link == NULL){
     return ERROR;
   }

    link->status = status;
    return OK;
}


Id link_get_id(Link *link){
  if(link == NULL){
     return NO_ID;
   }

    return link->id;
}

const char *link_get_name(Link *link){
   if(link == NULL){
     return NULL;
   }
   
    return link->name;
}

Id link_get_source(Link *link){
  if(!link){
     return NO_ID;
   }

    return link->field1;
}


Id link_get_destiny(Link *link){
  if(!link){
     return NO_ID;
   }

    return link->field2;
}

openStatus link_get_status(Link *link){
    if(!link){
     return ERROR;
   }

    return link->status;
}

STATUS link_print(Link *link){
  if (!link) {
    return ERROR;
  }

  fprintf(stdout, "Link (Id: %ld Name: %s)\n", link->id, link->name);
  fprintf(stdout, "Link (source: %ld destination: %ld;)\n", link->field1, link->field2);
  fprintf(stdout, "Link (Status: %d )\n", link->status);


  if(link_get_id(link) == link->field1){
      if (link->status == OPEN){

        fprintf(stdout, "--> %ld", link->field2);

      }else if(link->status == CLOSED){

        fprintf(stdout, "%ld <--", link->field1);
      }
  }
  
  return OK;
}

