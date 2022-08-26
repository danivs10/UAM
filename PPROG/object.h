/** 
 * @brief It defines a object
 * 
 * @file object.h
 * @author Daniel Varela and Aran Rodrigo
 * @version 1.0 
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"
/*
*
*@brief elements of an object
* Defines the id and name of a space
*
*/
typedef struct _Object Object;

#define MAX_OBJECT 30
#define MAX_DESC 200
#define FIRST_OBJECT 1
/***@brief It creates a new object
*
* object_create reserves memory for
* new object if it is created
*
*@date 16/01/20
*@author Daniel Varela and Aran Rodrigo
*
* @param the identification of the object
* @return the object created
*/
Object* object_create(Id id);
/***@brief It destroys an object
*
* object_destroy deletes the object 
* and frees the memory
*
*@date 16/01/20
*@author Daniel Varela and Aran Rodrigo
*
* @param existing object
* @return status check
*/
STATUS object_destroy(Object* object);
/***@brief Searches the object
*
* object_get_id searches the id of the object
*
*@date 16/01/20
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure object
* @return the id
*/
Id object_get_id(Object* object);
/***@brief It changes the name
*
* object_set_name changes the name of the object
*
*@date 16/01/20
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure object
* @param name to change
* @return status check
*/
STATUS object_set_name(Object* object, char* name);
/***@brief Searches the name
*
* object_get_name searches the name of the object
*
*@date 16/01/20
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure object
* @return the name
*/
const char* object_get_name(Object* object);
/***@brief Gives information of the object
*
* object_print checks if it is possible to print
*
*@date 16/01/20
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure object
* @return status check
*/
STATUS object_print(Object* object);
/***@brief Searches the position
*
* object_get_location searches for the position of the object
*
*@date 16/01/20
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure object
* @return the id
*/


char *object_get_description(Object *object);
STATUS object_set_description(Object *object, char desc[MAX_DESC]);


BOOL object_get_turnedOn(Object *object);
STATUS object_set_turnedOn(Object *object, BOOL turnedOn);
BOOL object_get_hidden(Object *object);
STATUS object_set_hidden(Object *object, BOOL hidden);
BOOL object_get_movable(Object *object);
STATUS object_set_movable(Object *object, BOOL movable);
BOOL object_get_illuminate(Object *object);
STATUS object_set_illuminate(Object *object, BOOL illuminate);
Id object_get_open(Object *object);
STATUS object_set_open(Object *object, Id open);
Id object_get_dependency(Object *object);
STATUS object_set_dependency(Object *object, Id dependency);
Id object_get_incompatible(Object *object);
STATUS object_set_incompatible(Object *object, Id incompatible);
BOOL object_get_oppened(Object *object);
STATUS object_set_oppened(Object *object, BOOL oppened);

#endif