/** 
 * @brief It defines a space
 * 
 * @file space.h
 * @author Daniel Varela and Aran Rodrigo
 * @version 1.0 
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "player.h"
#include "object.h"
#include "set.h"
#include "link.h"

/* 
*@brief elements of a space
* Defines the ids and name of a space
*/
typedef struct _Space Space;

#define MAX_SPACES 100
#define FIRST_SPACE 1


/***@brief It creates a new space
*
* space_create reserves memory for
* new space if it is created
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param the identification of the space
* @return the space created
*/
Space* space_create(Id id);
/***@brief It destroys a space
*
* space_destroy deletes the space 
* and frees the memory
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param existing space
* @return status check
*/
STATUS space_destroy(Space* space);
/***@brief Searches the id 
*
* space_get_id searches the id of the space
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure space
* @return the id
*/
Id space_get_id(Space* space);
/***@brief It changes the name
*
* space_set_name changes the name of the space
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure
* @param name to change
* @return status check
*/
STATUS space_set_name(Space* space, char* name);
/***@brief Searches the name
*
* space_get_name searches the name of the space
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure space
* @return the name
*/
const char* space_get_name(Space* space);
/***@brief It changes position
*
* space_set_name changes the position of
* north in the structure
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure
* @param id to change
* @return status check
*/
STATUS space_set_north(Space* space, Link *link);
/***@brief Searches the north value 
*
* space_get_north searches in the north
* of the player position
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure space
* @return the id
*/
Id space_get_north(Space* space);
/***@brief It changes position
*
* space_set_name changes the position of 
* south in the strcuture
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure
* @param id to change
* @return status check
*/
STATUS space_set_south(Space* space, Link *link);
/***@brief Searches the south value 
*
* space_get_south searches in the south
* of the player position
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure space
* @return the id
*/
Id space_get_south(Space* space);
/***@brief It changes position
*
* space_set_name changes the position of
* east in the structure
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure
* @param id to change
* @return status check
*/
STATUS space_set_east(Space* space, Link *link);
/***@brief Searches the east value 
*
* space_get_east searches in the east
* of the player position
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure space
* @return the id
*/
Id space_get_east(Space* space);
/***@brief It changes position
*
* space_set_name changes the position of
* west in the structure
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure
* @param id to change
* @return status check
*/
STATUS space_set_west(Space* space, Link *link);
/***@brief Searches the west value 
*
* space_get_west searches in the west
* of the player position
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure space
* @return the id
*/
Id space_get_west(Space* space);
/***@brief It changes position
*
* space_set_name changes the position 
* of the object66
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure
* @param value of the id
* @return status check
*/
STATUS space_add_object(Space* space, Id value);
/***@brief Searches the id object
*
* space_get_object_at searches the object id at an specific position
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure space
* @return the id
*/
Id space_get_object_at(Space* space, int position);

/***@brief Gives information of the spaces
*
* space_print checks if it is possible to print
*
*@date 13/01/15
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure space
* @return status check
*/
STATUS space_print(Space* space);
Set *space_get_set(Space* space);
STATUS space_del_object(Space *space, Object *object);



STATUS space_set_gdesc1(Space* space, char* gdesc);

STATUS space_set_gdesc2(Space* space, char* gdesc);

STATUS space_set_gdesc3(Space* space, char* gdesc);

const char * space_get_gdesc1(Space* space);

const char * space_get_gdesc2(Space* space);

const char * space_get_gdesc3(Space* space);

STATUS space_set_description(Space *space, char desc[MAX_DESC]);
char *space_get_description(Space *space);


BOOL is_north_available(Space *space);
BOOL is_south_available(Space *space);
BOOL is_east_available(Space *space);
BOOL is_west_available(Space *space);
BOOL is_up_available(Space *space);
BOOL is_down_available(Space *space);
STATUS space_set_up(Space* space, Link *link);
STATUS space_set_down(Space* space, Link *link); 
Id space_get_up(Space* space);
Id space_get_down(Space* space);
Link *space_get_link_north(Space *space);
Link *space_get_link_east(Space *space);
Link *space_get_link_south(Space *space);
Link *space_get_link_west(Space *space);
BOOL space_get_illuminated(Space *space);
STATUS space_set_illuminated(Space *space, BOOL illuminated);
#endif