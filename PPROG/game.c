/** 
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 * 
 * @file game.c
 * @author Daniel Varela and Aran Rodrigo
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_reader.h"
#include "game.h"
#include "link.h"

#define N_CALLBACK 18

struct _Game{
  Player* player;
  Die* die;
  Object* object[MAX_OBJECT + 1];
  Space* spaces[MAX_SPACES + 1];
  Link *link[MAX_LINKS+1];
  T_Command last_cmd;
  char last_exc[MAX_DESC];
  char last_arg[WORD_SIZE +1];
  char desc[MAX_DESC];
  char linkName[WORD_SIZE +1], with[5];
};


/**
   Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game *game);

/**
   List of callbacks for each command in the game 
*/
void game_callback_unknown(Game *game);
void game_callback_exit(Game *game);
void game_callback_next(Game *game);
void game_callback_back(Game *game);
void game_callback_take(Game *game);
void game_callback_drop(Game *game);
void game_callback_roll(Game *game);
void game_callback_left(Game *game);
void game_callback_right(Game *game);
void game_callback_up(Game *game);
void game_callback_down(Game *game);
void game_callback_move(Game *game);
void game_callback_inspect(Game *game);
void game_callback_turnon(Game *game);
void game_callback_turnoff(Game *game);
void game_callback_open(Game *game);
void game_callback_save(Game *game);
void game_callback_load(Game *game);

static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_exit,
    game_callback_next,
    game_callback_back,
    game_callback_take,
    game_callback_drop,
    game_callback_roll,
    game_callback_left,
    game_callback_right,
    game_callback_up,
    game_callback_down,
    game_callback_move,
    game_callback_inspect,
    game_callback_turnon,
    game_callback_turnoff,
    game_callback_open,
    game_callback_save,
    game_callback_load};

/**
   Game interface implementation
*/


/*Creates the game initializing necessary items such as the spaces the player and the object*/
Game *game_create(){
  Game *game = NULL;
  int i;
 
  game = (Game *) malloc(sizeof (Game));

  if (game == NULL) {
    return NULL;
  }

  for (i = 0; i <= MAX_SPACES; i++){
    game->spaces[i] = NULL;
  }

  for (i = 0; i <= MAX_LINKS; i++){
    game->link[i] = NULL;
  }

  game->die = die_create(1);
  game->player=player_create(1);

  for(i=0; i<MAX_OBJECT; i++){
    game->object[i] = NULL;
  }
  game->last_cmd = NO_CMD;
  strcpy(game->desc, " ");
  strcpy(game->linkName, "\0");
  strcpy(game->with, "\0");
  return game;
}

/*it generates the map according to data.dat*/
STATUS game_create_from_file(Game **game, char *filename)
{
  
  *game = game_create();
  if (*game == ERROR){
    return ERROR;
  }
  if (game_load_links(*game, filename) == ERROR){
    return ERROR;
}
  if (game_load_spaces(*game, filename) == ERROR){
    return ERROR;
}
  if (game_load_objects(*game, filename) == ERROR){
    return ERROR;
  }

  if (game_load_players(*game, filename) == ERROR){
    return ERROR;
  }
  return OK;
}

/*Destroys the whole game*/
STATUS game_destroy(Game *game)
{
  int i = 0;

  for (i = 0; game->spaces[i] != NULL; i++){
    space_destroy(game->spaces[i]);
  }

  for (i = 0; game->link[i] != NULL; i++){
    link_destroy(game->link[i]);
  }

  for (i = 0; game->object[i] != NULL; i++){
    object_destroy(game->object[i]);
  }

  player_destroy(game->player);

  free(game);
  game = NULL;
  
  return OK;
}

/*Adds a new space to the game*/
STATUS game_add_space(Game *game, Space *space)
{
  int i = 0;

  if (space == NULL)
  {
    return ERROR;
  }

  while (game->spaces[i] != NULL)
  {
    i++;
  }

  if (i >= MAX_SPACES)
  {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}

/*Returns the id at an specific position*/
Id game_get_space_id_at(Game *game, int position)
{

  if (position < 0 || position >= MAX_SPACES)
  {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

/*Returns a concrete space matching the Id given as a parameter*/
Space *game_get_space(Game *game, Id id)
{
  int i = 0;

  if (id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i<MAX_SPACES; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}
/*Returns a concrete space matching the Id given as a parameter*/
Object *game_get_object(Game *game, Id id)
{
  int i = 0;

  if (id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; game->object[i] != NULL; i++)
  {
    if (id == object_get_id(game->object[i]))
    {
      return game->object[i];
    }
  }

  return NULL;
}

const char * game_get_object_name(Game* game, Id id) {

  if (id == NO_ID||!game)
  {
    return NULL;
  }

  return object_get_name(game_get_object(game, game_get_object_location(game, id)));
}

/*Changes the player's location*/
STATUS game_set_player_location(Game *game, Id id)
{

  if (id == NO_ID)
  {
    return ERROR;
  }


  player_set_location(game->player, id);

  return OK;
}

/*Changes the given object's location*/
STATUS game_set_object_location(Game *game, Id location, Id objectId)
{
  if(objectId == NO_ID || location==NO_ID || !game){
    return ERROR;
  }

  return space_add_object(game->spaces[location-1], objectId);
  
}

/*Returns the player's current location*/
Id game_get_player_location(Game *game)
{
  return player_get_location(game->player);
}

/*Returns the object's location*/
Id game_get_object_location(Game *game, Id id)
{
  int i=0, j=0;

  for (i=0; i < MAX_SPACES; i++)
  {
    for (j = 0; j < MAX_OBJECT; j++)
    {
      if (space_get_object_at(game->spaces[i], j) == id)
      {
        return space_get_id(game->spaces[i]);
      }
    }
  }
  return NO_ID;
}

/*It updates the whole game*/
STATUS game_update(Game *game, T_Command cmd, char* arg, char *arg2, char* arg3)
{
  if(!game || !cmd || !arg ||!arg2 || !arg3){
    return ERROR;
  }

  game->last_cmd = cmd;
  strcpy(game->last_arg, arg);
  strcpy(game->with, arg2);
  strcpy(game->linkName, arg3);
  (*game_callback_fn_list[cmd])(game);
  return OK;
}
/*This function returns the last command intruded*/
T_Command game_get_last_command(Game *game)
{
  return game->last_cmd;
}

char *game_get_last_execution (Game *game){
  return game->last_exc;
}



/*Prints the data of the game on the right side*/
void game_print_data(Game *game)
{
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; game->spaces[i] != NULL; i++)
  {
    space_print(game->spaces[i]);
  }

  for (i = 0; game->object[i] != NULL; i++)
  {
    object_print(game->object[i]);
  }

  printf("=> Player location: %d\n", (int)game_get_player_location(game));
  printf("prompt:> ");
}

/*True or false function that returns whether or not the game is over*/
BOOL game_is_over(Game *game)
{
  return FALSE;
}

/**
   Callbacks implementation for each action 
*/
/*Callback when you input a non registered instruction*/
void game_callback_unknown(Game *game)
{
}

/*Callback for when you input e to exit the game*/
void game_callback_exit(Game *game)
{
}

/*Callback for the necessary procedure when you give the instruction next*/
void game_callback_next(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID || is_south_available(game_get_space(game, space_id))==FALSE)
  {
    strcpy(game->last_exc, "ERROR" );
    return;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
    strcpy(game->last_exc, "OK");
      return;
    }
  }
    strcpy(game->last_exc, "ERROR");
  return;
}

/*Callback for the necessary procedure when you give the instruction back*/
void game_callback_back(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id || is_north_available(game_get_space(game, space_id))==FALSE)
  {
    strcpy(game->last_exc, "ERROR");
    return;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
    strcpy(game->last_exc, "OK");
      return;
    }
  }
}

/*Callback for when given the instruction take*/
void game_callback_take(Game *game)
{
  int i=0;
  Object *currentObject=NULL;
  char objectName[10];
  strcpy(objectName, game->last_arg);

  for(i=0; i<MAX_OBJECT; i++){
    currentObject = game_get_object(game, space_get_object_at(game_get_space(game, game_get_player_location(game)), i));
    if (currentObject!=NULL){
    if (strcmp(objectName, object_get_name(currentObject))==0 && game_can_get_object(game, currentObject)==TRUE){
      if(player_add_object(game->player, space_get_object_at(game_get_space(game, game_get_player_location(game)), i))==OK){
        space_del_object(game_get_space(game, game_get_player_location(game)), currentObject);
        if(object_get_hidden(currentObject)==TRUE){
          object_set_hidden(currentObject, 0);
        }
        strcpy(game->last_exc, "OK");
        return;
      }
  }
  }
}
    fprintf(stdout, "You can't take that object");
    strcpy(game->last_exc, "ERROR");
    return;
}


/*Callback for when given the instruction drop*/

void game_callback_drop(Game *game)
{
  int i=0;
  Object *currentObject=NULL;
  char objectName[10];
  strcpy(objectName, game->last_arg);

  for(i=0; i<MAX_OBJECT; i++){
    
    currentObject = game_get_object(game, inventory_get_object_id_at(player_get_object(game->player), i));
    if(currentObject!=NULL){
    if (strcmp(objectName, object_get_name(currentObject))==0)
    {
      game_object_close_link(game, currentObject);
      if(space_add_object(game_get_space(game, game_get_player_location(game)), object_get_id(currentObject))==OK){
      player_del_object(game->player, object_get_id(currentObject));
      strcpy(game->last_exc, "OK");
      return;
    }
  }
  }
  }
    strcpy(game->last_exc, "ERROR");
  return;
}




void game_callback_roll(Game *game)
{
  int i=0;
  die_roll(game->die);
  for(i=0; i<die_get_number(game->die); i++){
    game_callback_next(game);
  }
    strcpy(game->last_exc, "OK");

  return ;
  
}

void game_callback_left(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID || is_west_available(game_get_space(game, space_id))==FALSE)
  {
    strcpy(game->last_exc, "ERROR");
    return;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_west(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      }
    strcpy(game->last_exc, "OK");
      return;
    }
  }
    strcpy(game->last_exc, "ERROR");
  return;
}

void game_callback_right(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID || is_east_available(game_get_space(game, space_id))==FALSE)
  {
    strcpy(game->last_exc, "ERROR");
    return;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_east(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      strcpy(game->last_exc, "OK");
      return;
      }
    }
  }
}


void game_callback_up(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID || is_up_available(game_get_space(game, space_id))==FALSE)
  {
    strcpy(game->last_exc, "ERROR");
    return;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_up(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      strcpy(game->last_exc, "OK");
      return;
      }
    }
  }
}


void game_callback_down(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID || is_down_available(game_get_space(game, space_id))==FALSE)
  {
    strcpy(game->last_exc, "ERROR");
    return;
  }

  for (i = 0; game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_down(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
      strcpy(game->last_exc, "OK");
      return;
      }
    }
  }
}


STATUS game_add_object(Game *game, Object *object)
{
  int i = 0;

  if (object == NULL)
  {
    return ERROR;
  }

  while (game->object[i] != NULL)
  {
    i++;
  }

  if (i >= MAX_OBJECT)
  {
    return ERROR;
  }

  game->object[i] = object;

  return OK;
}
STATUS game_add_player(Game *game, Player *player)
{

  if (player == NULL)
  {
    return ERROR;
  }



  game->player = player;
  return OK;
}

STATUS game_add_link(Game *game, Link *link){
    int i = 0;

  if (link == NULL){
    return ERROR;
  }

  while (game->link[i] != NULL){
    i++;
  }

  if (i >= MAX_SPACES){
    return ERROR;
  }

    game->link[i] = link;

    return OK;
}




Link *game_get_link_with_id(Game *game, Id id){
  int i=0;
  if (!game || id==NO_ID){
    return NULL;
  }
  for(i=0; i<MAX_LINKS;i++){
    if(game->link[i]!=NULL){
      if(link_get_id(game->link[i])==id ){
      return game->link[i];
    }
    }
  }
  return NULL;
}




/*Callback for when given the instruction move*/
void game_callback_move(Game *game){
  char direction[6];
  strcpy(direction, game->last_arg);

  if (strcmp(direction, "n")==0 || strcmp(direction, "north")==0){
    game_callback_back(game);
    return;
  }
  else if (strcmp(direction, "s")==0 || strcmp(direction, "south")==0){
    game_callback_next(game);
    return;
  }
  else if (strcmp(direction, "e")==0 || strcmp(direction, "east")==0){
    game_callback_right(game);
    return;
  }
  else if (strcmp(direction, "w")==0 || strcmp(direction, "west")==0){
    game_callback_left(game);
    return;
  }
  else if (strcmp(direction, "u")==0 || strcmp(direction, "up")==0){
    game_callback_up(game);
    return;
  }
  else if (strcmp(direction, "d")==0 || strcmp(direction, "down")==0){
    game_callback_down(game);
    return;
  }
  else{
    fprintf(stdout, "You can't go in that direction");
    strcpy(game->last_exc, "ERROR");
    return;
  }
}



/*Callback for when given the instruction inspect*/
void game_callback_inspect(Game *game){
  int i=0;
  Object *currentObject=NULL;
  char element[10];
  strcpy(element, game->last_arg);
  if ((strcmp(element, "s")==0 || strcmp(element, "space")==0) && (space_get_illuminated(game_get_space(game, player_get_location(game->player)))==TRUE || player_is_illuminating(game)==TRUE)){
      game_set_desc(game, space_get_name(game_get_space(game, player_get_location(game->player))));
      game_add_to_desc(game, " - ");
      game_add_to_desc(game, space_get_description(game_get_space(game, player_get_location(game->player))));
      strcpy(game->last_exc, "OK");
      return;
  }

  for(i=0; i<MAX_OBJECT; i++){
    currentObject = game_get_object(game, inventory_get_object_id_at(player_get_object(game->player), i));
    if(currentObject!=NULL){
      if (strcmp(element, object_get_name(currentObject))==0 && object_get_hidden(currentObject)==FALSE && space_get_illuminated(game_get_space(game, player_get_location(game->player)))) {
      game_set_desc(game, object_get_name(currentObject));
      game_add_to_desc(game, " - ");
      game_add_to_desc(game, object_get_description(currentObject));
      strcpy(game->last_exc, "OK");
      return;
      }
    }
    currentObject = game_get_object(game, space_get_object_at(game_get_space(game, game_get_player_location(game)), i));
    if (currentObject!=NULL){
     if (strcmp(element, object_get_name(currentObject))==0){
      game_set_desc(game, object_get_name(currentObject));
      game_add_to_desc(game, " - ");
      game_add_to_desc(game, object_get_description(currentObject));
      strcpy(game->last_exc, "OK");
      return;
      }
    }
  }
  
  game_set_desc(game, " ");
  strcpy(game->last_exc, "ERROR");
  return;
}

STATUS game_set_player(Game *game, Player *player){
    if(!player){
      return ERROR;
    }

  game->player = player;

  return OK;
}

Player *game_get_player(Game *game){
  if (!game){
    return NULL;
  }

  return game->player;
}

STATUS game_set_die(Game *game, Die *die){
    if(!die){
      return ERROR;
    }

  game->die = die;

  return OK;
}

Die *game_get_die(Game *game){
  if(!game){
    return NULL;
  }

  return game->die;
}


char *game_get_desc(Game *game){
  if(!game){
    return NULL;
  }
  return game->desc;
}

STATUS game_set_desc(Game *game, char *desc){
  if (!game){
    return ERROR;
  }
  strcpy(game->desc, desc);
  return OK;
}
STATUS game_add_to_desc(Game *game, char *desc){
  if (!game){
    return ERROR;
  }
  strcat(game->desc, desc);
  return OK;
}


STATUS game_object_open_link(Game *game, Object *object){
  if (object_get_open(object)==NO_ID){
    return ERROR;
  }
  object_set_oppened(object, TRUE);
  link_set_status(game_get_link_with_id(game, object_get_open(object)), OPEN);
  return OK;
}

STATUS game_object_close_link(Game *game, Object *object){
  if (object_get_open(object)==NO_ID){
    return ERROR;
  }
  object_set_oppened(object, FALSE);
  link_set_status(game_get_link_with_id(game, object_get_open(object)), CLOSED);
  return OK;
}

BOOL player_is_illuminating(Game *game){
  Object *currentObject;
  int i=0;
  if (!game){
    return FALSE;
  }
  for(i=0; i<MAX_OBJECT; i++){
    currentObject = game_get_object(game, inventory_get_object_id_at(player_get_object(game->player), i));
    if(object_get_illuminate(currentObject)==TRUE && object_get_turnedOn(currentObject)==TRUE){
      return TRUE;
    }
  }
  return FALSE;
}





void game_callback_turnon(Game *game)
{
  int i=0;
  Object *currentObject=NULL;
  char objectName[10];
  strcpy(objectName, game->last_arg);

  for(i=0; i<MAX_OBJECT; i++){
    
    currentObject = game_get_object(game, inventory_get_object_id_at(player_get_object(game->player), i));
    if(currentObject!=NULL){
    if (strcmp(objectName, object_get_name(currentObject))==0 && object_get_illuminate(currentObject)==TRUE)
    {
      object_set_turnedOn(currentObject, TRUE);
      strcpy(game->last_exc, "OK");
      return;
    }
  }
  }
    strcpy(game->last_exc, "ERROR");
  return;
}


void game_callback_turnoff(Game *game)
{
  int i=0;
  Object *currentObject=NULL;
  char objectName[10];
  strcpy(objectName, game->last_arg);

  for(i=0; i<MAX_OBJECT; i++){
    
    currentObject = game_get_object(game, inventory_get_object_id_at(player_get_object(game->player), i));
    if(currentObject!=NULL){
    if (strcmp(objectName, object_get_name(currentObject))==0 && object_get_illuminate(currentObject)==TRUE )
    {
      object_set_turnedOn(currentObject, FALSE);
      strcpy(game->last_exc, "OK");
      return;
    }
  }
  }
    strcpy(game->last_exc, "ERROR");
  return;
}

void game_callback_open(Game *game)
{
  int i=0;
  Object *currentObject=NULL;
  char linkName[WORD_SIZE +1], with[5];
  char objectName[10];
  
  strcpy(linkName, game->linkName);
  strcpy(with, game->with);
  strcpy(objectName, game->last_arg);

  if(strcmp(with, "with")!=0){
    strcpy(game->last_exc, "ERROR");
    return;
  }
  for(i=0; i<MAX_OBJECT; i++){
    
    currentObject = game_get_object(game, inventory_get_object_id_at(player_get_object(game->player), i));
    if(currentObject!=NULL){
    if (strcmp(objectName, object_get_name(currentObject))==0 && object_get_open(currentObject)!=-1 )
    {
      if(strcmp(link_get_name(game_get_link_with_id(game, object_get_open(currentObject))), linkName)==0){
        game_object_open_link(game, currentObject);
         strcpy(game->last_exc, "OK");
         return;
      }
      else{
        strcpy(game->last_exc, "ERROR");
        return;
      }
    }
  }
  }
    strcpy(game->last_exc, "ERROR");
  return;
}



BOOL game_can_get_object (Game *game, Object *object){
  BOOL result=TRUE;
  int i=0;
  Id *currentObjectId;
  
  if(object_get_incompatible(object)!=NO_ID){
    for(i=0; i<MAX_OBJECT; i++){
      currentObjectId = inventory_get_object_id_at(player_get_object(game->player), i);
      if(currentObjectId==object_get_incompatible(object)){
        result=FALSE;
        return result;
      }
    }
  }
  if(object_get_dependency(object)!=NO_ID){
    for(i=0; i<MAX_OBJECT; i++){
    currentObjectId = inventory_get_object_id_at(player_get_object(game->player), i);
      if(currentObjectId==object_get_dependency(object)){
        result=TRUE;
        return result;
      } 
    }
    result=FALSE;
    return result;
  }
  
  if(object_get_movable(object)==FALSE){
        result=FALSE;
        return result;
      }
  if(object_get_hidden(object)==TRUE){
      result=TRUE;
      return result;
    }
    
  return result;

}


void game_callback_save(Game *game){
  char *filename = NULL;
  scanf("%s", filename);
  game_management_save(game, filename);
  return;
}

void game_callback_load(Game *game){
  char *filename = NULL;
  scanf("%s", filename);
  game_management_load(game, filename); 
  return;
}
