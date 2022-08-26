/** 
 * @brief It defines the game loop 
 * 
 * @file game_loop.c
 * @author Daniel Varela and Aran Rodrigo
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);
void game_loop_run(Game *game, Graphic_engine *gengine, FILE *logfile);
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

int main(int argc, char *argv[]) {
  Game *game=NULL;
  Graphic_engine *gengine;
  FILE *log=NULL;
  
  if (argc < 2) {
    fprintf(stderr, "Use: %s <game_data_file [-l logfile>]\n", argv[0]);
    return 1;
  }
      
  if (!game_loop_init(&game, &gengine, argv[1])){
    
    if(argv[2]!=NULL){
      log = fopen(argv[3], "w");
      if(log == NULL){
        return 0;
      }
    }else{
      log = NULL;
    }
    game_loop_run(game, gengine, log);
    game_loop_cleanup(game, gengine);
  }
  
  return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name){
  if (game_create_from_file(&(*game), file_name) == ERROR) {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }
  
  if ((*gengine = graphic_engine_create()) == NULL) {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(*game);
    return 1;
  }

  return 0;
}


void game_loop_run(Game *game, Graphic_engine *gengine, FILE *logfile){
  T_Command command = NO_CMD;
  char argument[WORD_SIZE +1] = "";
  char with[5]="";
  char linkName[WORD_SIZE +1]="";
  extern char *cmd_to_str[N_CMD][N_CMDT];

  while ((command != EXIT) && !game_is_over(game)) {
    graphic_engine_paint_game(gengine, game);
    command = get_user_input(argument, with, linkName);
    game_update(game, command, argument, with, linkName);

    if(logfile!=NULL){
      fprintf(logfile, "%s %s %s %s \n", cmd_to_str[command-NO_CMD][CMDL],linkName, with, argument);
    }
  }
  if(logfile!=NULL){
    fclose(logfile);
  }
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine){
  game_destroy(game);
  graphic_engine_destroy(gengine);
}

