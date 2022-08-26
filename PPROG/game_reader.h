
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

#ifndef GAME_READER_H
#define GAME_READER_H

#include "types.h"
#include "command.h"
#include "space.h"
#include "player.h"
#include "die.h"
#include "object.h"
#include "game.h"
#include "link.h"


/***@brief Load a game from a file
*
* game_load_spaces initializes all variables inside a space
*
*@date 16/01/20
*@author Daniel Varela and Aran Rodrigo
*
* @param game structure
* @param file name 
* @return status
*/

STATUS game_load_spaces(Game* game, char* filename);
STATUS game_load_objects(Game* game, char* filename);
STATUS game_load_players(Game* game, char* filename);
STATUS game_load_links(Game* game, char* filename);
STATUS game_management_save(Game* game, char* filename);
STATUS game_management_load(Game* game, char* filename);
STATUS game_update_objects(Game* game, char* filename);
STATUS game_update_player(Game* game, char* filename);

#endif