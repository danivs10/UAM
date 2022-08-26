/** 
 * @brief It defines a link
 * 
 * @file space.h
 * @author Daniel Varela 
 * @version 1.0 
 * @date 23-03-2020
 * @copyright GNU Public License
 */

#ifndef LINKS_H
#define LINKS_H


#include "types.h"

typedef struct _Link Link;

#define MAX_LINKS 200

Link *link_create(Id id);
STATUS link_destroy(Link *link);
STATUS link_set_name(Link *link, char *name);
STATUS link_set_destiny(Link *link, Id destiny);
STATUS link_set_source(Link *link, Id source);
STATUS link_set_status(Link *link, openStatus status);
Id link_get_id(Link *link);
const char *link_get_name(Link *link);
Id link_get_source(Link *link);
Id link_get_destiny(Link *link);
openStatus link_get_status(Link *link);
STATUS link_print(Link *link);

#endif