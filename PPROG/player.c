#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "player.h"
#include "object.h"
#include "inventory.h"
#include "set.h"

struct _Player {
  Id id;
  char name[WORD_SIZE + 1];
  Id location;
  Inventory* bacpack;
};

/*Creates a new player*/
Player* player_create(Id id) {

  Player *newPlayer = NULL;

  if (id == NO_ID)
    return NULL;

  newPlayer = (Player *) malloc(sizeof (Player));

  if (newPlayer == NULL) {
    return NULL;
  }
  newPlayer->id = id;

  newPlayer->name[0] = '\0';

  newPlayer->location = NO_ID;

  newPlayer->bacpack = inventory_create();

  inventory_set_max(newPlayer->bacpack, 2);
  
  return newPlayer;
}

/*Destroys the given player*/
STATUS player_destroy(Player* player) {
  if (!player) {
    return ERROR;
  }

  free(player);
  player = NULL;

  return OK;
}

/*Changes the name of a given player*/
STATUS player_set_name(Player* player, char* name) {
  if (!player || !name) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }

  return OK;
}

/*Returns the name of an specific player*/
const char * player_get_name(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}

/*Returns the id of a player*/
Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}


/*Changes the id of a player*/
STATUS player_set_Id(Player* player, Id newId) {
  if (!player || !newId) {
    return ERROR;
  }
  player->id = newId;
  return OK;
}

/*Prints all the player's information*/
STATUS player_print(Player* player) {
  if (!player) {
    return ERROR;
  }

  fprintf(stdout, "--> Player (Id: %ld; Name: %s Location. %ld)\n", player->id, player->name, player->location);

  if (player_get_object(player)) {
    fprintf(stdout, "---> Object in the player.\n");
  } else {
    fprintf(stdout, "---> No object in the player.\n");
  }

  return OK;
}


/*Returns the location of a player*/
Id player_get_location(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->location;
}

/*Changes the locationof a player*/
STATUS player_set_location(Player* player, Id newLocation) {
  if (!player || !newLocation) {
    return ERROR;
  }
  player->location = newLocation;
  return OK;
}

/*Returns the id o the object that the player is carrying (if he isnt carrying one it returns -1)*/
Inventory *player_get_object(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->bacpack;
}

/*Changes the player's object id*/
STATUS player_add_object(Player* player, Id newObject) {
  if (!player) {
    return ERROR;
  }
  
  return inventory_add_object(player->bacpack, newObject);
}

/*Changes the player's object id*/
STATUS player_del_object(Player* player, Id object) {
  if (!player) {
    return ERROR;
  }
  
  return inventory_del_object_with_id(player->bacpack, object);
}


STATUS player_set_max_obj(Player *player, int max){
  inventory_set_max(player->bacpack, max);
  return OK;
}
