/** 
 * @brief It defines a space
 * 
 * @file space.h
 * @author Daniel Varela and Aran Rodrigo
 * @version 1.0 
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef DIE_H
#define DIE_H

#include "types.h"

typedef struct _Die Die;

Die* die_create(Id id);
STATUS die_destroy(Die* die);
STATUS die_roll(Die* die);
STATUS die_print(Die* die);
int die_get_number(Die* die);


#endif