/** 
 * @brief It defines the game interface
 * for each command
 * 
 * @file game.h
 * @author Daniel Varela and Aran Rodrigo
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H
#include "types.h"
#include "command.h"
#include "space.h"
#include "player.h"
#include "die.h"
#include "set.h"
#include "object.h"
#include "inventory.h"
#include "link.h"

/**
* 
* @brief The Game structure
*
* It stores information of the different parts of the game
*/
typedef struct _Game Game;

/**
* @brief Initialize game 
*
* game_create initializes all the variables inside a game
* function is changed due to the opaque structure
*
* @date 16/04/2019
* @author: Beatriz Sainz
*
* @param game intended to be initialized
* @return the game
*/
Game *game_create();

/**
 * *@brief Load a game from a file
*
* game_create_from_file initializes a game from a saved file
* pointer is added to game due to the games opaque structure
*
*@date 15/01/2019
*@author: Instructors and Beatriz Sainz
*
* @param game intended to be initialized
* @param file name
* @return a Status check
*/
STATUS game_create_from_file(Game **game, char* filename);

/**
* @brief Updates the game
*
* game_update updates the game with the last command
*
*@date 15/01/2019
*@author: Instructors
*
* @param game 
* @param command used
* @return a Status check
*/
STATUS game_update(Game *game, T_Command cmd, char* arg, char *arg2, char* arg3);

/**
*@brief Eliminates a game
*
* game_destroy calls other functions to free the used memory
*
*@date 14/02/20
*@author: Daniel Varela and Aran Rodrigo
*
* @param game intended to be eliminated
* @return a Status check
*/
STATUS game_destroy(Game* game);

/**
 * @brief Indicates if a game is over
*
* game_is_over checks if the game is over
*
*@date 15/01/2019
*@author: Instructors
*
* @param game
* @return a BOOL state
*/
BOOL   game_is_over(Game* game);

/**
 * @brief Prints player and object location and spaces
*
* game_print_data show the player and object location and spaces
*
*@date 15/01/2019
*@author: Instructors
*
* @param game 
* @return printed data
*/
void   game_print_data(Game* game);

/**
* @brief Returns space asked
*
* game_get_space returns the space pointer of the given id
*
*@date 15/01/2019
*@author: Instructors
*
* @param game
* @param space id
* @return the space pointer
*/
Space* game_get_space(Game* game, Id id);

/**
 * *@brief shows the positions id
*
*@date 11/02/2019
*@author: Daniel Varela and Aran Rodrigo
*
* @param game
* @return a position id
*/
Id game_get_space_id_at(Game *game, int position);

/**
 * *@brief shows player location
*
* game_get_player_location calls other functions to return the player location
*
*@date 11/02/2019
*@author: Daniel Varela and Aran Rodrigo
*
* @param game
* @return a player location
*/
Id     game_get_player_location(Game* game);

/**
 * *@brief shows object location
*
* game_get_player_location calls other functions to return the object location
*
*@date 11/02/2019
*@author: Daniel Varela and Aran Rodrigo
*
* @param game 
* @return object location id
*/
Id game_get_object_location(Game* game, Id id);

const char * game_get_object_name(Game* game, Id id);

/**
 * *@brief gets last input command
*
* game_get_last_command receives a game and sends the last command used
*
*@date 15/02/2019
*@author: Instructors
*
* @param game intended to bi initialized
* @param file name
* @return a Status check
*/
T_Command game_get_last_command(Game* game);

char* game_get_last_execution (Game *game);

/***@brief Adds an space
*
* game_add_space initializes a new space
*
*@date 15/01/2019
*@author: Instructors
*
* @param game where the space is going to be initialized
* @param new space
* @return a Status check
*/
STATUS game_add_space(Game* game, Space* space);
STATUS game_add_object(Game* game, Object* object);
STATUS game_add_player(Game *game, Player *player);

/***@brief Adds an space
*
* game_add_space initializes a new link
*
*@date 15/04/2020
*@author: Beatriz Sainz
*
* @param game where the link is going to be initialized
* @param new link
* @return a Status check
*/
STATUS game_add_link(Game *game, Link *link);

/***@brief Changes the player location
*
* game_set_player_location changes player location with a new one
*
*@date 11/02/20
*@author: Daniel Varela and Aran Rodrigo
*
* @param game
* @param new location id
* @return status
*/
STATUS game_set_player_location(Game* game, Id id);

/**
* @brief Changes the player location
*
* game_set_player_location changes player location with a new one
*
*@date 11/02/20
*@author: Daniel Varela and Aran Rodrigo
*
* @param game
* @param new location id
* @return status
*/
STATUS game_set_object_location(Game *game, Id location, Id objectId);
Object *game_get_object(Game *game, Id id);
Link *game_get_link_with_id(Game *game, Id id);

/**
* @brief Sets a player (primitive made due to opaque struct)
*
* game_set_player changes player location with a new one
*
*@date 16/04/20
*@author: Beatriz Sainz
*
* @param game
* @param player
* @return OK or ERROR in case of error
*/
STATUS game_set_player(Game *game, Player *player);

/**
* @brief Gets a player (primitive made due to opaque struct)
*
* game_get_player recieves the player pointed by the game struct
*
*@date 16/04/20
*@author: Beatriz Sainz
*
* @param game
* @return player
*/
Player *game_get_player(Game *game);

/**
* @brief Sets a die (primitive made due to opaque struct)
*
* game_set_player changes die location with a new one
*
*@date 16/04/20
*@author: Beatriz Sainz
*
* @param game
* @param die
* @return OK or ERROR in case of error
*/
STATUS game_set_die(Game *game, Die *die);

/**
* @brief Gets a die (primitive made due to opaque struct)
*
* game_get_die recieves the die pointed by the game struct
*
*@date 16/04/20
*@author: Beatriz Sainz
*
* @param game
* @return die
*/
Die *game_get_die(Game *game);


char *game_get_desc(Game *game);
STATUS game_set_desc(Game *game, char *desc);
STATUS game_add_to_desc(Game *game, char *desc);
STATUS game_object_open_link(Game *game, Object *object);
STATUS game_object_close_link(Game *game, Object *object);
BOOL player_is_illuminating(Game *game);
BOOL game_can_get_object (Game *game, Object *object);
#endif