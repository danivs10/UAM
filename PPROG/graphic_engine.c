#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "screen.h"
#include "graphic_engine.h"
#include "command.h"

struct _Graphic_engine{
  Area *map, *descript, *banner, *help, *feedback;
};

Graphic_engine *graphic_engine_create(){
  static Graphic_engine *ge = NULL;

  if (ge)
    return ge;
  
  screen_init();
  ge = (Graphic_engine *) malloc(sizeof(Graphic_engine));
  
  ge->map      = screen_area_init( 1, 1, 68, 24);
  ge->descript = screen_area_init(73, 1, 31, 19);
  ge->banner   = screen_area_init(73,24, 23,  1);
  ge->help     = screen_area_init( 1,26, 81,  3);
  ge->feedback = screen_area_init( 1,30, 81,  3);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge){
  if (!ge)
    return;
  
  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);
  
  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game){
  int i=0;
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID, play_loc = NO_ID;
  Space* space_act = NULL;
  char obj1[27];
  char obj2[27];
  char obj3[27];
  char oName[10]="";
  char* gdesc1[4];
  char* gdesc2[4];
  char* gdesc3[4];
  char str[255];
  Space *space;
  int type;
  char *lastExc;
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID){
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);

    
    if (id_back != NO_ID && link_get_status(space_get_link_north(game_get_space(game, id_act)))==OPEN) {
      space=game_get_space(game, id_back);

      strcpy(oName, " ");
      
      strcpy(obj1, " ");
      strcpy(obj2, "| ");
      strcpy(obj3, " ");

      if((space_get_east(space)!=-1 && link_get_status(space_get_link_east(space))==OPEN) && (space_get_west(space)==-1 || link_get_status(space_get_link_west(space))==CLOSED)){
        type = 1;
      }
      else if((space_get_east(space)==-1 || link_get_status(space_get_link_east(space))==CLOSED) && (space_get_west(space)==-1 || link_get_status(space_get_link_west(space))==CLOSED)){
        type = 2;
      }
      else if((space_get_east(space)==-1 || link_get_status(space_get_link_east(space))==CLOSED) && (space_get_west(space)!=-1 && link_get_status(space_get_link_west(space))==OPEN)){
        type = 3;
      }
      else if((space_get_east(space)!=-1 || link_get_status(space_get_link_east(space))==OPEN) && (space_get_west(space)!=-1 || link_get_status(space_get_link_west(space))==OPEN)){
        type = 4;
      } 

      if(type==1){
        
      sprintf(str, "                        +-----------------+    +-----------------+" );
      screen_area_puts(ge->map, str);

    gdesc1[2] = (char *)space_get_gdesc1(space);
    gdesc2[2] = (char *)space_get_gdesc2(space);
    gdesc3[2] = (char *)space_get_gdesc3(space); 
    
    
    gdesc1[3] = (char *)space_get_gdesc1(game_get_space(game, space_get_east(space)));
    gdesc2[3] = (char *)space_get_gdesc2(game_get_space(game, space_get_east(space)));
    gdesc3[3] = (char *)space_get_gdesc3(game_get_space(game, space_get_east(space))); 

  

    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(space, i)!= NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(space, i)))==FALSE) {
      strncat(obj2, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(space, i))));
      strncat(obj2, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj2)<=16; i++){
      strncat(obj2, " ", sizeof(" "));
    }

    
    strcpy(obj3, "|    |");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(game_get_space(game, space_get_east(space)), i)!=NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(game_get_space(game, space_get_east(space)), i)))==FALSE) {
      strncat(obj3, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(game_get_space(game, space_get_east(space)), i))));
      strncat(obj3, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj3)<=23; i++){
      strncat(obj3, " ", sizeof(" "));
    }
    obj3[23]=124;

    sprintf(str, "                        |               %2d| -> | %ld               |",  (int) space_get_id(space), space_get_east(space));
      
  
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |    |    %s      |", gdesc1[2], gdesc1[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |    |    %s      |", gdesc2[2], gdesc2[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |    |    %s      |", gdesc3[2], gdesc3[3]);


      screen_area_puts(ge->map, str);
      sprintf(str, "                        %s %s",obj2, obj3);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        +-----------------+    +-----------------+");
      screen_area_puts(ge->map, str);
      }
      if(type==2){
        
        
      sprintf(str, "                        +-----------------+                       " );
      screen_area_puts(ge->map, str);

    gdesc1[2] = (char *)space_get_gdesc1(space);
    gdesc2[2] = (char *)space_get_gdesc2(space);
    gdesc3[2] = (char *)space_get_gdesc3(space); 
    
    

  

    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(space, i)!= NO_ID && object_get_hidden(game_get_object(game, space_get_object_at(space, i)))==FALSE) {
      strncat(obj2, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(space, i))));
      strncat(obj2, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj2)<=22; i++){
      strncat(obj2, " ", sizeof(" "));
    }
    obj2[18]=124;

       sprintf(str, "                        |               %2d|        ",  (int) space_get_id(space));
      
  
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |", gdesc1[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |", gdesc2[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |", gdesc3[2]);







      screen_area_puts(ge->map, str);
      sprintf(str, "                        %s",obj2);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        +-----------------+                       ");
      screen_area_puts(ge->map, str);
      }
      if(type==3){
        
        
      sprintf(str, "+-----------------+    +-----------------+" );
      screen_area_puts(ge->map, str);

    gdesc1[2] = (char *)space_get_gdesc1(space);
    gdesc2[2] = (char *)space_get_gdesc2(space);
    gdesc3[2] = (char *)space_get_gdesc3(space); 
    
    
    gdesc1[1] = (char *)space_get_gdesc1(game_get_space(game, space_get_west(space)));
    gdesc2[1] = (char *)space_get_gdesc2(game_get_space(game, space_get_west(space)));
    gdesc3[1] = (char *)space_get_gdesc3(game_get_space(game, space_get_west(space))); 

  
    strcpy(obj1, "|");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(game_get_space(game, space_get_west(space)), i)!=NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(game_get_space(game, space_get_west(space)), i)))==FALSE) {
      strncat(obj1, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(game_get_space(game, space_get_west(space)), i))));
      strncat(obj1, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj1)<=19; i++){
      strncat(obj1, " ", sizeof(" "));
    }
    obj1[18]='|';

    strcpy(obj2, "  |");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(space, i)!= NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(space, i)))==FALSE) {
      strncat(obj2, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(space, i))));
      strncat(obj2, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj2)<=21; i++){
      strncat(obj2, " ", sizeof(" "));
    }
    obj2[20]='|';

    sprintf(str, "|                %ld| <- |               %2d|", space_get_west(space), (int) space_get_id(space));
      
  
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |", gdesc1[1], gdesc1[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |", gdesc2[1], gdesc2[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |", gdesc3[1], gdesc3[2]);


      screen_area_puts(ge->map, str);
      sprintf(str, "%s %s",obj1, obj2);
      screen_area_puts(ge->map, str);
      sprintf(str, "+-----------------+    +-----------------+");
      screen_area_puts(ge->map, str);
      }
      if(type==4){
        
        
      sprintf(str, "+-----------------+    +-----------------+    +-----------------+" );
      screen_area_puts(ge->map, str);

    gdesc1[2] = (char *)space_get_gdesc1(space);
    gdesc2[2] = (char *)space_get_gdesc2(space);
    gdesc3[2] = (char *)space_get_gdesc3(space); 
    
    
    gdesc1[1] = (char *)space_get_gdesc1(game_get_space(game, space_get_west(space)));
    gdesc2[1] = (char *)space_get_gdesc2(game_get_space(game, space_get_west(space)));
    gdesc3[1] = (char *)space_get_gdesc3(game_get_space(game, space_get_west(space))); 
    
    gdesc1[3] = (char *)space_get_gdesc1(game_get_space(game, space_get_east(space)));
    gdesc2[3] = (char *)space_get_gdesc2(game_get_space(game, space_get_east(space)));
    gdesc3[3] = (char *)space_get_gdesc3(game_get_space(game, space_get_east(space))); 

  

    strcpy(obj1, "|");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(game_get_space(game, space_get_west(space)), i)!= NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(game_get_space(game, space_get_west(space)), i)))==FALSE) {
      strncat(obj1, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(game_get_space(game, space_get_west(space)), i))));
      strncat(obj1, oName, sizeof(oName));
    }
    }
    for (i=0; strlen(obj1)<=21; i++){
      strncat(obj1, " ", sizeof(" "));
    }
    obj1[18]=124;



    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(space, i)!=NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(space, i)))==FALSE) {
      strncat(obj2, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(space, i))));
      strncat(obj2, oName, sizeof(oName));
    }
    }
    for (i=0; strlen(obj2)<=21; i++){
      strncat(obj2, " ", sizeof(" "));
    }
    obj2[18]=124;
    
    
    
    
    
    strcpy(obj3, "|");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(game_get_space(game, space_get_east(space)), i)!=NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(game_get_space(game, space_get_east(space)), i)))==FALSE) {
      strncat(obj3, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(game_get_space(game, space_get_east(space)), i))));
      strncat(obj3, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj3)<=21; i++){
      strncat(obj3, " ", sizeof(" "));
    }
    obj3[18]=124;


    sprintf(str, "|                %ld| <- |               %2d| -> | %ld               |",  space_get_west(space), (int) space_get_id(space), space_get_east(space));
      
  
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |    |    %s      |", gdesc1[1], gdesc1[2], gdesc2[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |    |    %s      |", gdesc2[1], gdesc2[2], gdesc2[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |    |    %s      |", gdesc3[1], gdesc3[2], gdesc2[3]);


      screen_area_puts(ge->map, str);
      sprintf(str, "%s %s %s",obj1, obj2, obj3);
      screen_area_puts(ge->map, str);
      sprintf(str, "+-----------------+    +-----------------+    +-----------------+");
      screen_area_puts(ge->map, str);
      }
      sprintf(str, "                                 ^ %ld", id_back);
      screen_area_puts(ge->map, str);
    }
    else{
      sprintf(str, "  ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ");
    }





























      type=0;

    if (id_act != NO_ID) {
      space=space_act;
      

      strcpy(oName, " ");
      
      strcpy(obj1, " ");
      strcpy(obj2, "| ");
      strcpy(obj3, " ");
































      if((space_get_east(space)!=-1 && link_get_status(space_get_link_east(space))==OPEN) && (space_get_west(space)==-1 || link_get_status(space_get_link_west(space))==CLOSED)){
        type = 1;
      }
      else if((space_get_east(space)==-1 || link_get_status(space_get_link_east(space))==CLOSED) && (space_get_west(space)==-1 || link_get_status(space_get_link_west(space))==CLOSED)){
        type = 2;
      }
      else if((space_get_east(space)==-1 || link_get_status(space_get_link_east(space))==CLOSED) && (space_get_west(space)!=-1 && link_get_status(space_get_link_west(space))==OPEN)){
        type = 3;
      }
      else if((space_get_east(space)!=-1 || link_get_status(space_get_link_east(space))==OPEN) && (space_get_west(space)!=-1 || link_get_status(space_get_link_west(space))==OPEN)){
        type = 4;
      } 

      if(type==1){
        
      sprintf(str, "                        +-----------------+    +-----------------+" );
      screen_area_puts(ge->map, str);

    gdesc1[2] = (char *)space_get_gdesc1(space);
    gdesc2[2] = (char *)space_get_gdesc2(space);
    gdesc3[2] = (char *)space_get_gdesc3(space); 
    
    
    gdesc1[3] = (char *)space_get_gdesc1(game_get_space(game, space_get_east(space)));
    gdesc2[3] = (char *)space_get_gdesc2(game_get_space(game, space_get_east(space)));
    gdesc3[3] = (char *)space_get_gdesc3(game_get_space(game, space_get_east(space))); 

  

    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(space, i)!= NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(space, i)))==FALSE) {
      strncat(obj2, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(space, i))));
      strncat(obj2, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj2)<=16; i++){
      strncat(obj2, " ", sizeof(" "));
    }

    
    strcpy(obj3, "|    |");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(game_get_space(game, space_get_east(space)), i)!=NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(game_get_space(game, space_get_east(space)), i)))==FALSE) {
      strncat(obj3, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(game_get_space(game, space_get_east(space)), i))));
      strncat(obj3, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj3)<=23; i++){
      strncat(obj3, " ", sizeof(" "));
    }
    obj3[23]=124;

    sprintf(str, "                        |%s            %2d| -> | %ld               |",  player_get_name(game_get_player(game)), (int) space_get_id(space), space_get_east(space));
      
  
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |    |    %s      |", gdesc1[2], gdesc1[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |    |    %s      |", gdesc2[2], gdesc2[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |    |    %s      |", gdesc3[2], gdesc3[3]);


      screen_area_puts(ge->map, str);
      sprintf(str, "                        %s %s",obj2, obj3);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        +-----------------+    +-----------------+");
      screen_area_puts(ge->map, str);
      }
      if(type==2){
        
        
      sprintf(str, "                        +-----------------+                       " );
      screen_area_puts(ge->map, str);

    gdesc1[2] = (char *)space_get_gdesc1(space);
    gdesc2[2] = (char *)space_get_gdesc2(space);
    gdesc3[2] = (char *)space_get_gdesc3(space); 
    
    

  

    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(space, i)!= NO_ID && object_get_hidden(game_get_object(game, space_get_object_at(space, i)))==FALSE) {
      strncat(obj2, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(space, i))));
      strncat(obj2, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj2)<=22; i++){
      strncat(obj2, " ", sizeof(" "));
    }
    obj2[18]=124;

       sprintf(str, "                        |%s            %2d|        ",  player_get_name(game_get_player(game)), (int) space_get_id(space));
      
  
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |", gdesc1[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |", gdesc2[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |", gdesc3[2]);







      screen_area_puts(ge->map, str);
      sprintf(str, "                        %s",obj2);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        +-----------------+                       ");
      screen_area_puts(ge->map, str);
      }
      if(type==3){
        
        
      sprintf(str, "+-----------------+    +-----------------+" );
      screen_area_puts(ge->map, str);

    gdesc1[2] = (char *)space_get_gdesc1(space);
    gdesc2[2] = (char *)space_get_gdesc2(space);
    gdesc3[2] = (char *)space_get_gdesc3(space); 
    
    
    gdesc1[1] = (char *)space_get_gdesc1(game_get_space(game, space_get_west(space)));
    gdesc2[1] = (char *)space_get_gdesc2(game_get_space(game, space_get_west(space)));
    gdesc3[1] = (char *)space_get_gdesc3(game_get_space(game, space_get_west(space))); 

  
    strcpy(obj1, "|");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(game_get_space(game, space_get_west(space)), i)!=NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(game_get_space(game, space_get_west(space)), i)))==FALSE) {
      strncat(obj1, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(game_get_space(game, space_get_west(space)), i))));
      strncat(obj1, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj1)<=19; i++){
      strncat(obj1, " ", sizeof(" "));
    }
    obj1[18]='|';

    strcpy(obj2, "  |");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(space, i)!= NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(space, i)))==FALSE) {
      strncat(obj2, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(space, i))));
      strncat(obj2, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj2)<=21; i++){
      strncat(obj2, " ", sizeof(" "));
    }
    obj2[20]='|';

    sprintf(str, "|                %ld| <- |%s            %2d|", space_get_west(space),  player_get_name(game_get_player(game)), (int) space_get_id(space));
      
  
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |", gdesc1[1], gdesc1[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |", gdesc2[1], gdesc2[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |", gdesc3[1], gdesc3[2]);


      screen_area_puts(ge->map, str);
      sprintf(str, "%s %s",obj1, obj2);
      screen_area_puts(ge->map, str);
      sprintf(str, "+-----------------+    +-----------------+");
      screen_area_puts(ge->map, str);
      }
      if(type==4){
        
        
      sprintf(str, "+-----------------+    +-----------------+    +-----------------+" );
      screen_area_puts(ge->map, str);

    gdesc1[2] = (char *)space_get_gdesc1(space);
    gdesc2[2] = (char *)space_get_gdesc2(space);
    gdesc3[2] = (char *)space_get_gdesc3(space); 
    
    
    gdesc1[1] = (char *)space_get_gdesc1(game_get_space(game, space_get_west(space)));
    gdesc2[1] = (char *)space_get_gdesc2(game_get_space(game, space_get_west(space)));
    gdesc3[1] = (char *)space_get_gdesc3(game_get_space(game, space_get_west(space))); 
    
    gdesc1[3] = (char *)space_get_gdesc1(game_get_space(game, space_get_east(space)));
    gdesc2[3] = (char *)space_get_gdesc2(game_get_space(game, space_get_east(space)));
    gdesc3[3] = (char *)space_get_gdesc3(game_get_space(game, space_get_east(space))); 

  

    strcpy(obj1, "|");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(game_get_space(game, space_get_west(space)), i)!= NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(game_get_space(game, space_get_west(space)), i)))==FALSE) {
      strncat(obj1, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(game_get_space(game, space_get_west(space)), i))));
      strncat(obj1, oName, sizeof(oName));
    }
    }
    for (i=0; strlen(obj1)<=21; i++){
      strncat(obj1, " ", sizeof(" "));
    }
    obj1[18]=124;



    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(space, i)!=NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(space, i)))==FALSE) {
      strncat(obj2, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(space, i))));
      strncat(obj2, oName, sizeof(oName));
    }
    }
    for (i=0; strlen(obj2)<=21; i++){
      strncat(obj2, " ", sizeof(" "));
    }
    obj2[18]=124;
    
    
    
    
    
    strcpy(obj3, "|");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(game_get_space(game, space_get_east(space)), i)!=NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(game_get_space(game, space_get_east(space)), i)))==FALSE) {
      strncat(obj3, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(game_get_space(game, space_get_east(space)), i))));
      strncat(obj3, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj3)<=21; i++){
      strncat(obj3, " ", sizeof(" "));
    }
    obj3[18]=124;


    sprintf(str, "|                %ld| <- |%s            %2d| -> | %ld               |",   space_get_west(space), player_get_name(game_get_player(game)), (int) space_get_id(space), space_get_east(space));
      
  
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |    |    %s      |", gdesc1[1], gdesc1[2], gdesc2[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |    |    %s      |", gdesc2[1], gdesc2[2], gdesc2[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |    |    %s      |", gdesc3[1], gdesc3[2], gdesc2[3]);


      screen_area_puts(ge->map, str);
      sprintf(str, "%s %s %s",obj1, obj2, obj3);
      screen_area_puts(ge->map, str);
      sprintf(str, "+-----------------+    +-----------------+    +-----------------+");
      screen_area_puts(ge->map, str);
      }
    }
















    if (id_next != NO_ID && link_get_status(space_get_link_south(game_get_space(game, id_act)))==OPEN) {

      
      sprintf(str, "                                 v %ld", id_next);
      screen_area_puts(ge->map, str);
      space=game_get_space(game, id_next);

      strcpy(oName, " ");
      
      strcpy(obj1, " ");
      strcpy(obj2, "| ");
      strcpy(obj3, " ");


      if((space_get_east(space)!=-1 && link_get_status(space_get_link_east(space))==OPEN) && (space_get_west(space)==-1 || link_get_status(space_get_link_west(space))==CLOSED)){
        type = 1;
      }
      else if((space_get_east(space)==-1 || link_get_status(space_get_link_east(space))==CLOSED) && (space_get_west(space)==-1 || link_get_status(space_get_link_west(space))==CLOSED)){
        type = 2;
      }
      else if((space_get_east(space)==-1 || link_get_status(space_get_link_east(space))==CLOSED) && (space_get_west(space)!=-1 && link_get_status(space_get_link_west(space))==OPEN)){
        type = 3;
      }
      else if((space_get_east(space)!=-1 || link_get_status(space_get_link_east(space))==OPEN) && (space_get_west(space)!=-1 || link_get_status(space_get_link_west(space))==OPEN)){
        type = 4;
      } 

      if(type==1){
        
      sprintf(str, "                        +-----------------+    +-----------------+" );
      screen_area_puts(ge->map, str);

    gdesc1[2] = (char *)space_get_gdesc1(space);
    gdesc2[2] = (char *)space_get_gdesc2(space);
    gdesc3[2] = (char *)space_get_gdesc3(space); 
    
    
    gdesc1[3] = (char *)space_get_gdesc1(game_get_space(game, space_get_east(space)));
    gdesc2[3] = (char *)space_get_gdesc2(game_get_space(game, space_get_east(space)));
    gdesc3[3] = (char *)space_get_gdesc3(game_get_space(game, space_get_east(space))); 

  

    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(space, i)!= NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(space, i)))==FALSE) {
      strncat(obj2, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(space, i))));
      strncat(obj2, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj2)<=16; i++){
      strncat(obj2, " ", sizeof(" "));
    }

    
    strcpy(obj3, "|    |");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(game_get_space(game, space_get_east(space)), i)!=NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(game_get_space(game, space_get_east(space)), i)))==FALSE) {
      strncat(obj3, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(game_get_space(game, space_get_east(space)), i))));
      strncat(obj3, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj3)<=23; i++){
      strncat(obj3, " ", sizeof(" "));
    }
    obj3[23]=124;

    sprintf(str, "                        |               %2d| -> | %ld               |",  (int) space_get_id(space), space_get_east(space));
      
  
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |    |    %s      |", gdesc1[2], gdesc1[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |    |    %s      |", gdesc2[2], gdesc2[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |    |    %s      |", gdesc3[2], gdesc3[3]);


      screen_area_puts(ge->map, str);
      sprintf(str, "                        %s %s",obj2, obj3);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        +-----------------+    +-----------------+");
      screen_area_puts(ge->map, str);
      }
      if(type==2){
        
        
      sprintf(str, "                        +-----------------+                       " );
      screen_area_puts(ge->map, str);

    gdesc1[2] = (char *)space_get_gdesc1(space);
    gdesc2[2] = (char *)space_get_gdesc2(space);
    gdesc3[2] = (char *)space_get_gdesc3(space); 
    
    

  

    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(space, i)!= NO_ID && object_get_hidden(game_get_object(game, space_get_object_at(space, i)))==FALSE) {
      strncat(obj2, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(space, i))));
      strncat(obj2, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj2)<=22; i++){
      strncat(obj2, " ", sizeof(" "));
    }
    obj2[18]=124;

       sprintf(str, "                        |               %2d|        ",  (int) space_get_id(space));
      
  
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |", gdesc1[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |", gdesc2[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |    %s      |", gdesc3[2]);







      screen_area_puts(ge->map, str);
      sprintf(str, "                        %s",obj2);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        +-----------------+                       ");
      screen_area_puts(ge->map, str);
      }
      if(type==3){
        
        
      sprintf(str, "+-----------------+    +-----------------+" );
      screen_area_puts(ge->map, str);

    gdesc1[2] = (char *)space_get_gdesc1(space);
    gdesc2[2] = (char *)space_get_gdesc2(space);
    gdesc3[2] = (char *)space_get_gdesc3(space); 
    
    
    gdesc1[1] = (char *)space_get_gdesc1(game_get_space(game, space_get_west(space)));
    gdesc2[1] = (char *)space_get_gdesc2(game_get_space(game, space_get_west(space)));
    gdesc3[1] = (char *)space_get_gdesc3(game_get_space(game, space_get_west(space))); 

  
    strcpy(obj1, "|");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(game_get_space(game, space_get_west(space)), i)!=NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(game_get_space(game, space_get_west(space)), i)))==FALSE) {
      strncat(obj1, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(game_get_space(game, space_get_west(space)), i))));
      strncat(obj1, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj1)<=19; i++){
      strncat(obj1, " ", sizeof(" "));
    }
    obj1[18]='|';

    strcpy(obj2, "  |");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(space, i)!= NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(space, i)))==FALSE) {
      strncat(obj2, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(space, i))));
      strncat(obj2, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj2)<=21; i++){
      strncat(obj2, " ", sizeof(" "));
    }
    obj2[20]='|';

    sprintf(str, "|                %ld| <- |               %2d|", space_get_west(space), (int) space_get_id(space));
      
  
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |", gdesc1[1], gdesc1[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |", gdesc2[1], gdesc2[2]);
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |", gdesc3[1], gdesc3[2]);


      screen_area_puts(ge->map, str);
      sprintf(str, "%s %s",obj1, obj2);
      screen_area_puts(ge->map, str);
      sprintf(str, "+-----------------+    +-----------------+");
      screen_area_puts(ge->map, str);
      }
      if(type==4){
        
        
      sprintf(str, "+-----------------+    +-----------------+    +-----------------+" );
      screen_area_puts(ge->map, str);

    gdesc1[2] = (char *)space_get_gdesc1(space);
    gdesc2[2] = (char *)space_get_gdesc2(space);
    gdesc3[2] = (char *)space_get_gdesc3(space); 
    
    
    gdesc1[1] = (char *)space_get_gdesc1(game_get_space(game, space_get_west(space)));
    gdesc2[1] = (char *)space_get_gdesc2(game_get_space(game, space_get_west(space)));
    gdesc3[1] = (char *)space_get_gdesc3(game_get_space(game, space_get_west(space))); 
    
    gdesc1[3] = (char *)space_get_gdesc1(game_get_space(game, space_get_east(space)));
    gdesc2[3] = (char *)space_get_gdesc2(game_get_space(game, space_get_east(space)));
    gdesc3[3] = (char *)space_get_gdesc3(game_get_space(game, space_get_east(space))); 

  

    strcpy(obj1, "|");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(game_get_space(game, space_get_west(space)), i)!= NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(game_get_space(game, space_get_west(space)), i)))==FALSE) {
      strncat(obj1, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(game_get_space(game, space_get_west(space)), i))));
      strncat(obj1, oName, sizeof(oName));
    }
    }
    for (i=0; strlen(obj1)<=21; i++){
      strncat(obj1, " ", sizeof(" "));
    }
    obj1[18]=124;



    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(space, i)!=NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(space, i)))==FALSE) {
      strncat(obj2, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(space, i))));
      strncat(obj2, oName, sizeof(oName));
    }
    }
    for (i=0; strlen(obj2)<=21; i++){
      strncat(obj2, " ", sizeof(" "));
    }
    obj2[18]=124;
    
    
    
    
    
    strcpy(obj3, "|");
    for(i=0; i<MAX_OBJECT; i++){
    if (space_get_object_at(game_get_space(game, space_get_east(space)), i)!=NO_ID&& object_get_hidden(game_get_object(game, space_get_object_at(game_get_space(game, space_get_east(space)), i)))==FALSE) {
      strncat(obj3, "  ", sizeof("  "));
      strcpy(oName, object_get_name(game_get_object(game, space_get_object_at(game_get_space(game, space_get_east(space)), i))));
      strncat(obj3, oName, sizeof(oName));
    }
    }

    for (i=0; strlen(obj3)<=21; i++){
      strncat(obj3, " ", sizeof(" "));
    }
    obj3[18]=124;


    sprintf(str, "|                %ld| <- |               %2d| -> | %ld               |",  space_get_west(space), (int) space_get_id(space), space_get_east(space));
      
  
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |    |    %s      |", gdesc1[1], gdesc1[2], gdesc2[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |    |    %s      |", gdesc2[1], gdesc2[2], gdesc2[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "|    %s      |    |    %s      |    |    %s      |", gdesc3[1], gdesc3[2], gdesc2[3]);


      screen_area_puts(ge->map, str);
      sprintf(str, "%s %s %s",obj1, obj2, obj3);
      screen_area_puts(ge->map, str);
      sprintf(str, "+-----------------+    +-----------------+    +-----------------+");
      screen_area_puts(ge->map, str);
      }
    }
    else{
      sprintf(str, "  ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ");
    }
  }

  /* Paint the in the description area */
  screen_area_clear(ge->descript);
  sprintf(str, "  Objects location:");
  screen_area_puts(ge->descript, str);
    for( i=0; i<=MAX_OBJECT; i++){
      
      if (game_get_object_location(game, i)!=NO_ID){
        obj_loc = game_get_object_location(game, i);
       /*strcpy(obj_name, object_get_name(game_get_object(game, i)));*/
        sprintf(str, "  %s:%d", object_get_name(game_get_object(game, i)), (int)obj_loc);
        screen_area_puts(ge->descript, str);
  }
  }
  
    sprintf(str, "  ");
    screen_area_puts(ge->descript, str);

    play_loc = game_get_player_location(game);
    sprintf(str, "  Player location:%d", (int)play_loc);
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Player Objects:");
    screen_area_puts(ge->descript, str);
    for (i=0; i<MAX_OBJECT; i++){
      if(inventory_get_object_id_at(player_get_object(game_get_player(game)), i) != NO_ID){

          sprintf(str, "    %s", object_get_name(game_get_object(game, inventory_get_object_id_at(player_get_object(game_get_player(game)), i))));
          screen_area_puts(ge->descript, str);
      }
    }
    sprintf(str, "  ");
    screen_area_puts(ge->descript, str);


    sprintf(str, "  Die value:%d", die_get_number(game_get_die(game)));
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Descriptions: ");
    screen_area_puts(ge->descript, str);
    sprintf(str, "  %s ", game_get_desc(game));
    screen_area_puts(ge->descript, str);


  /* Paint the in the banner area */
  screen_area_puts(ge->banner, " The game of the Goose ");

  /* Paint the in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "next or n, back or b, exit or e, take or t, drop or d, roll or rl, left or l,");
  screen_area_puts(ge->help, str);
  sprintf(str, "right or r, move or m, inspect or i, exit or e, i or inspect, dn or down, u or up, ton or turnon, toff or turnoff, open <lnk> with <obj>, s or save");
  screen_area_puts(ge->help, str);

  /* Paint the in the feedback area */
  last_cmd = game_get_last_command(game);

  lastExc=game_get_last_execution(game);
  sprintf(str, " %s: %s", cmd_to_str[last_cmd-NO_CMD][CMDL], lastExc);
  screen_area_puts(ge->feedback, str);
  
  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");

}

