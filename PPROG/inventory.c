/** 
 * @brief It implements a new way of storaging the objects that the player is carrying
 * @file game.h
 * @author Daniel Varela
 * @version 1.0 
 * @date 23-03-2020
 * @copyright GNU Public License
 */


#include<stdio.h>
#include<stdlib.h>
#include"types.h"
#include"inventory.h"


struct _Inventory {
    int max;
    Set *objects;
};

Inventory* inventory_create(){


  Inventory *newInventory = NULL;

  newInventory = (Inventory *) malloc(sizeof (Inventory));

  if (newInventory == NULL) {
    return NULL;
  }
  
  newInventory->objects = set_create();
  newInventory->max=4;

  return newInventory;
}


STATUS inventory_destroy(Inventory* inventory){
  if (!inventory) {
    return ERROR;
  }

  free(inventory);
  inventory = NULL;

  return OK;
}


STATUS inventory_add_object(Inventory* inventory, Id value){
    int i=0;
    if (value==NO_ID){
        return ERROR;
    }
    for(i=0; i<inventory_get_max(inventory); i++){
    if (inventory_get_object_id_at(inventory, i)==NO_ID){
        set_add_id(inventory->objects, value);
        return OK;
    }
    }
    return ERROR;
}


STATUS inventory_del_object(Inventory* inventory, Object *object){
    int i=0;
    if(object==NULL){
        return ERROR;
    }
    for (i=0; i<inventory_get_max(inventory); i++){
        if(object_get_id(object)==inventory_get_object_id_at(inventory, i)){
            set_del_id(inventory->objects, object_get_id(object));
            return OK;
        }
    }
    return ERROR;
}

STATUS inventory_del_object_with_id(Inventory* inventory, Id id){
    int i=0;
    if(id==NO_ID){
        return ERROR;
    }
    for (i=0; i<inventory_get_max(inventory); i++){
        if(id==inventory_get_object_id_at(inventory, i)){
            return set_del_id(inventory->objects, id);
        }
    }
    return ERROR;
}

Id inventory_get_object_id_at(Inventory* inventory, int position){
    if (position>inventory_get_max(inventory) || position<0 ){
        return NO_ID;
    }
    return set_get_id(inventory->objects, position);
}

Set *inventory_get_set(Inventory* inventory){
    if(inventory==NULL){
        return NULL;
    }
    return inventory->objects;
}

STATUS inventory_set_max(Inventory* inventory, int maxObj){
    if (maxObj<=0){
        return ERROR;
    }
    inventory->max = maxObj;
    return OK;
}
int inventory_get_max(Inventory* inventory){
    if(!inventory){
        return -1;
    }
    
    return inventory->max;
}


STATUS inventory_print(Inventory* inventory){
    int i=0;

    if(inventory==NULL || inventory->max<=0){
        return ERROR;
    }
    fprintf(stdout, "Max objects: %d\n", inventory_get_max(inventory));
    fprintf(stdout, "Objects in the backpack:\n");

    for (i=0; i<inventory_get_max(inventory); i++){
        if(inventory_get_object_id_at(inventory, i)!=NO_ID){    
            fprintf(stdout, "%ld\n", inventory_get_object_id_at(inventory, i));
        }
    }
    return OK;

}
