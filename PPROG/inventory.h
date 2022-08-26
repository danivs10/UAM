/** 
 * @brief It defines a inventory
 * 
 * @file space.h
 * @author Daniel Varela 
 * @version 1.0 
 * @date 23-03-2020
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H


#include "types.h"
#include "object.h"
#include "set.h"
typedef struct _Inventory Inventory;


Inventory* inventory_create();
STATUS inventory_destroy(Inventory* inventory);
STATUS inventory_add_object(Inventory* inventory, Id value);
STATUS inventory_del_object(Inventory* inventory, Object *object);
STATUS inventory_del_object_with_id(Inventory* inventory, Id id);
Id inventory_get_object_id_at(Inventory* inventory, int position);
Set *inventory_get_set(Inventory* inventory);
STATUS inventory_set_max(Inventory* inventory, int maxObj);
int inventory_get_max(Inventory* inventory);
STATUS inventory_print(Inventory* inventory);

#endif