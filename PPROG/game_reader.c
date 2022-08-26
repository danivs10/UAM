#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_reader.h"
#include "game.h"
#include "types.h"


/*This function loads the game spaces*/
STATUS game_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  char gdesc1[7];
  char gdesc2[7];
  char gdesc3[7];
  BOOL illuminated=FALSE;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID, up=NO_ID, down=NO_ID;
  Space* space = NULL;
  STATUS status = OK;
  
  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
      toks = strtok(NULL, "|");
      up = atol(toks);
      toks = strtok(NULL, "|");
      down = atol(toks);
      toks = strtok(NULL, "|");
      illuminated = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(gdesc1, toks);
      toks = strtok(NULL, "|");
      strcpy(gdesc2, toks);
      toks = strtok(NULL, "|");
      strcpy(gdesc3, toks);

#ifdef DEBUG 
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%s|%s|%s|\n", id, name, north, east, south, west, gdesc1, gdesc2, gdesc3);
#endif
      space = space_create(id);
      if (space != NULL) {
	space_set_name(space, name);
	space_set_north(space, game_get_link_with_id(game, north));
  space_set_east(space, game_get_link_with_id(game, east));
  space_set_south(space, game_get_link_with_id(game, south));
  space_set_west(space, game_get_link_with_id(game, west));
  space_set_up(space, game_get_link_with_id(game, up));
  space_set_down(space, game_get_link_with_id(game, down));
  space_set_illuminated(space, illuminated);
	game_add_space(game, space);
  space_set_gdesc1(space, gdesc1);
  space_set_gdesc2(space, gdesc2);
  space_set_gdesc3(space, gdesc3);
      }
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  return status;
}
/*This function loads the game objects*/
STATUS game_load_objects(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, location = NO_ID, open=NO_ID, incompatible=NO_ID, dependency=NO_ID;
  BOOL movable=FALSE, hidden=FALSE, illuminate=FALSE, turnedOn=FALSE; 
  Object *object = NULL;
  STATUS status = OK;
  
  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      movable = atol(toks);
      toks = strtok(NULL, "|");
      hidden = atol(toks);
      toks = strtok(NULL, "|");
      open = atol(toks);
      toks = strtok(NULL, "|");
      illuminate = atol(toks);
      toks = strtok(NULL, "|");
      turnedOn = atol(toks);
      toks = strtok(NULL, "|");
      dependency = atol(toks);
      toks = strtok(NULL, "|");
      incompatible = atol(toks);
#ifdef DEBUG 
      printf("Leido: %ld|%s|%ld\n", id, name, location);
#endif
      object = object_create(id);
      if (object != NULL) {
        object_set_name(object, name);
        object_set_movable(object, movable);
        object_set_hidden(object, hidden);
        object_set_open(object, open);
        object_set_illuminate(object, illuminate);
        object_set_turnedOn(object, turnedOn);
        object_set_dependency(object, dependency);
        object_set_incompatible(object, incompatible);
        game_set_object_location(game, location, id);
        game_add_object(game, object);
      }
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  return status;
}



/*This function loads the game objects*/
STATUS game_load_players(Game* game, char* filename) {
  FILE* file = NULL;
  int max=0;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, location = NO_ID;
  STATUS status = OK;
  
  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#p:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      max = atol(toks);
#ifdef DEBUG 
      printf("Leido: %ld|%s|%ld|%d\n", id, name, location, max);
#endif
        player_set_name(game_get_player(game), name);
        player_set_max_obj(game_get_player(game), max);
        game_set_player_location(game, location);
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  return status;
}

STATUS game_load_links(Game* game, char* filename){
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, source = NO_ID, destiny = NO_ID;
  Link *link=NULL;
  STATUS status = OK;
  openStatus st = OPEN;

  
  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#l:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      source = atol(toks);
      toks = strtok(NULL, "|");
      destiny = atol(toks);
      toks = strtok(NULL, "|");
      st = atol(toks);
#ifdef DEBUG 
      printf("Leido: %ld|%s|%ld|%ld|%d\n", id, name, source, destiny, status);
#endif
      link = link_create(id);
      if (link != NULL) {
	link_set_name(link, name);
	link_set_source(link, source);
	link_set_destiny(link, destiny);
	link_set_status(link, st);
  game_add_link(game,link);
      }
        status = OK;
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  return status;
}




STATUS game_management_save(Game* game, char* filename) {
  FILE* file = NULL;
  Object *currentObject=NULL;
  Id arrayId[MAX_OBJECT];
  int i=0;

  
  if (!filename) {
    return ERROR;
  }
  file = fopen(filename, "w");
  if (file == NULL) {
    return ERROR;
  }

  fprintf(file, "#p:%ld|\n", player_get_location(game_get_player(game)));
    for(i=0; i<MAX_OBJECT; i++){
      currentObject = game_get_object(game, inventory_get_object_id_at(player_get_object(game_get_player(game)), i));
      if(object_get_id(currentObject)!=-1){
        fprintf(file, "#o:%ld|%d|%d\n", object_get_id(currentObject), object_get_turnedOn(currentObject), object_get_oppened(currentObject));
      }
    }
  
  fclose(file);
  return OK;

}


STATUS game_management_load(Game* game, char* filename) {
  game_update_player(game, filename);
  game_update_objects(game, filename);
  return OK;
}

STATUS game_update_objects(Game* game, char* filename){
  STATUS status=OK;
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char* toks = NULL;
  Id objectId=NO_ID;
  BOOL turnedOn=FALSE, oppened=FALSE;
  Object *currentObject;

  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }


  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      objectId = atol(toks);
      toks = strtok(NULL, "|");
      turnedOn = atol(toks);
      toks = strtok(NULL, "|");
      oppened = atol(toks);
#ifdef DEBUG 
      printf("Leido: %ld, %d, %d", objectId, turnedOn, oppened);
#endif
      currentObject = game_get_object(game, objectId);
      object_set_turnedOn(currentObject, turnedOn);
      if(oppened==TRUE){
        object_set_turnedOn(currentObject, oppened);
        game_object_open_link(game, currentObject);
      }
          if( player_add_object(game_get_player(game), object_get_id(currentObject))==OK){
          space_del_object(game_get_space(game, game_get_object_location(game, object_get_id(currentObject))), currentObject);
          }


    }
  }
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  return status;
}



STATUS game_update_player(Game* game, char* filename){
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char* toks = NULL;
  Id playerLocation = NO_ID;
  STATUS status = OK;
  
  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#p:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      playerLocation = atol(toks);
#ifdef DEBUG 
      printf("Leido: %ld", playerLocation);
#endif
        game_set_player_location(game, playerLocation);
    }
  }

  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  return status;

}