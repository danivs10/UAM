/** 
 * @brief It defines a space
 * 
 * @file space.h
 * @author Daniel Varela and Aran Rodrigo
 * @version 1.0 
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef SETS_H
#define SETS_H

#include "types.h"

typedef struct _Set Set;

#define MAX_IDS 1000

Set* set_create();
STATUS set_destroy(Set* set);
Id set_get_id(Set* set, int position);
STATUS set_add_id(Set* set, Id id);
STATUS set_del_id(Set* set, Id id);
STATUS set_print(Set* set);

#endif