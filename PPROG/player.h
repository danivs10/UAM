/** 
 * @brief It defines a player
 * 
 * @file player.h
 * @author Daniel Varela and Aran Rodrigo
 * @version 1.0 
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "inventory.h"
#include "set.h"
/*
*
*@brief elements of a player
* Defines the ids and name of a player
*
*/
typedef struct _Player Player;

#define MAX_PLAYERS 100
#define FIRST_PLAYER 1
/***@brief It creates a new player
*
* player_create reserves memory for
* new player if it is created
*
*@date 16/02/20
*@author Daniel Varela and Aran Rodrigo
*
* @param the identification of the player
* @return the player created
*/
Player* player_create(Id id);
/***@brief It destroys a player
*
* player_destroy deletes the player 
* and frees the memory
*
*@date 16/02/20
*@author Daniel Varela and Aran Rodrigo
*
* @param existing player
* @return status check
*/
STATUS player_destroy(Player* player);
/***@brief Searches the id 
*
* player_get_id searches the id of the player
*
*@date 16/02/20
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure player
* @return the id
*/
Id player_get_id(Player* player);
/***@brief It changes the name
*
* player_set_name changes the name of the player
*
*@date 16/02/20
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure
* @param name to change
* @return status 
*/
STATUS player_set_name(Player* player, char* name);
/***@brief Searches the name
*
* player_get_name searches the name of the player
*
*@date 16/02/20
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure player
* @return the name
*/
const char* player_get_name(Player* player);
/***@brief It sets the player location
*
* player_set_name changes the position of
* north in the structure
*
*@date 16/02/20
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure
* @param id to change
* @return status check
*/
STATUS player_set_location(Player* player, Id id);
/***@brief Searches the location value
*
* player_get_location searches the player location
*
*@date 16/02/20
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure player
* @return the id
*/
Id player_get_location(Player* player);
/***@brief It changes position
*
* player_set_name changes the position 
* of the object66
*
*@date 16/02/20
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure
* @param value of the id
* @return status check
*/
STATUS player_add_object(Player* player, Id newObject);
STATUS player_del_object(Player* player, Id object);
/***@brief Searches the id object
*
* player_get_object searches the object id
*
*@date 16/02/20
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure player
* @return the id
*/
Inventory *player_get_object(Player* player);
/***@brief Gives information of the players
*
* player_print checks if it is possible to print
*
*@date 16/02/20
*@author Daniel Varela and Aran Rodrigo
*
* @param pointer to the structure player
* @return status check
*/
STATUS player_set_max_obj(Player *player, int max);
STATUS player_print(Player* player);

#endif