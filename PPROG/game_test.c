/** 
 * @brief It tests game module
 * 
 * @file game_test.c
 * @author Beatriz Sainz
 * @date 01-05-2020
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "test.h"
#include "game_test.h"

#define MAX_TESTS 57

int main(int argc, char** argv){
    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module game:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_game_create();
    if (all || test == 2) test2_game_create();
    if (all || test == 3) test1_game_create_from_file();
    if (all || test == 4) test2_game_create_from_file();
    if (all || test == 5) test1_game_update();
    if (all || test == 6) test2_game_update();
    if (all || test == 7) test1_game_is_over();
    if (all || test == 8) test2_game_is_over();
    if (all || test == 9) test1_game_get_space_id_at();
    if (all || test == 10) test2_game_get_space_id_at();
    if (all || test == 11) test1_game_get_player_location();
    if (all || test == 12) test2_game_get_player_location();
    if (all || test == 13) test1_game_get_object_location();
    if (all || test == 14) test2_game_get_object_location();
    if (all || test == 15) test1_game_get_object_name();
    if (all || test == 16) test2_game_get_object_name();
    if (all || test == 17) test1_game_get_last_command();
    if (all || test == 20) test1_game_add_space();
    if (all || test == 21) test2_game_add_space();
    if (all || test == 22) test1_game_add_object();
    if (all || test == 23) test2_game_add_object();
    if (all || test == 24) test1_game_add_player();
    if (all || test == 25) test2_game_add_player();
    if (all || test == 26) test1_game_add_link();
    if (all || test == 27) test2_game_add_link();
    if (all || test == 28) test1_game_set_player_location();
    if (all || test == 29) test2_game_set_player_location();
    if (all || test == 30) test1_game_set_object_location();
    if (all || test == 31) test2_game_set_object_location();
    if (all || test == 32) test1_game_get_object();
    if (all || test == 33) test2_game_get_object();
    if (all || test == 34) test1_game_get_link_with_id();
    if (all || test == 35) test2_game_get_link_with_id();
    if (all || test == 36) test1_game_set_player();
    if (all || test == 37) test2_game_set_player();
    if (all || test == 38) test1_game_get_player();
    if (all || test == 39) test2_game_get_player();
    if (all || test == 40) test1_game_set_die();
    if (all || test == 41) test2_game_set_die();
    if (all || test == 42) test1_game_get_die();
    if (all || test == 43) test2_game_get_die();
    if (all || test == 44) test1_game_set_desc();
    if (all || test == 45) test2_game_set_desc();
    if (all || test == 46) test1_game_get_desc();
    if (all || test == 47) test2_game_get_desc();
    if (all || test == 48) test1_game_add_to_desc();
    if (all || test == 49) test2_game_add_to_desc();
    if (all || test == 50) test1_game_object_open_link();
    if (all || test == 51) test2_game_object_open_link();
    if (all || test == 52) test1_game_object_close_link();
    if (all || test == 53) test2_game_object_close_link();
    if (all || test == 54) test1_player_is_illuminating();
    if (all || test == 55) test2_player_is_illuminating();
    if (all || test == 56) test1_game_can_get_object();
    if (all || test == 57) test2_game_can_get_object();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_game_create(){
    int result = game_create()!=NULL;
    PRINT_TEST_RESULT(result);
}

void test2_game_create(){
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(g != NULL);
}

void test1_game_create_from_file(){
    Game *g;
    char *filename;
    g = game_create();
    filename = "data.dat";
    PRINT_TEST_RESULT(game_create_from_file(&g, filename) == OK);
}

void test2_game_create_from_file(){
    Game *g;
    char *filename = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_create_from_file(&g, filename) == ERROR);
}

void test1_game_update(){
    Game *g;
    T_Command cmd;
    char *arg, *arg2, *arg3;
    arg = "1";
    arg2 = "2";
    arg3 = "3";
    g = game_create();
    cmd = NEXT;
    PRINT_TEST_RESULT(game_update(g, cmd , arg, arg2, arg3) == OK);
}

void test2_game_update(){
    Game *g;
    T_Command cmd = NO_CMD;
    char *arg = NULL, *arg2 = NULL, *arg3 = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_update(g, cmd , arg, arg2, arg3) == ERROR);
}

void test1_game_is_over(){
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_is_over(g) == FALSE);
}

void test2_game_is_over(){
    Game *g;
    g = game_create();
    game_destroy(g);
    PRINT_TEST_RESULT(game_is_over(g) == FALSE);
}

void test1_game_get_space_id_at(){
    Game *g;
    Space *s;
    s = space_create(3);
    g = game_create();
    game_add_space(g, s);
    PRINT_TEST_RESULT(game_get_space_id_at(g, 1) == space_get_id(s));
}

void test2_game_get_space_id_at(){
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_get_space_id_at(g, 1) == NO_ID);
}

void test1_game_get_player_location(){
    Game *g;
    Player *p;
    p = player_create(4);
    g = game_create();
    game_set_player(g, p);
    game_set_player_location(g, 6);
    PRINT_TEST_RESULT(game_get_player_location(g) == 6);
}

void test2_game_get_player_location(){
    Game *g;
    Player *p = NULL;
    g = game_create();
    game_add_player(g, p);
    game_set_player_location(g, player_get_id(p));
    PRINT_TEST_RESULT(game_get_player_location(g) == NO_ID);
}

void test1_game_get_object_location(){
    Game *g;
    Object *o;
    o = object_create(3);
    g = game_create();
    game_add_object(g, o);
    game_set_object_location(g, 5, object_get_id(o));
    PRINT_TEST_RESULT(game_get_object_location(g, object_get_id(o)) == 5);
}

void test2_game_get_object_location(){
    Game *g;
    Object *o = NULL;
    g = game_create();
    game_set_object_location(g, 4, object_get_id(o));
    PRINT_TEST_RESULT(game_get_object_location(g, object_get_id(o)) == NO_ID);
}

void test1_game_get_object_name(){
    Game *g;
    Object *o;
    o = object_create(2);
    g = game_create();
    object_set_name(o, "hi");
    game_add_object(g, o);
    PRINT_TEST_RESULT(game_get_object_name(g, object_get_id(o)) == object_get_name(o));
}

void test2_game_get_object_name(){
    Game *g;
    Object *o;
    o = object_create(2);
    g = game_create();
    object_set_name(o, NULL);
    PRINT_TEST_RESULT(game_get_object_name(g, object_get_id(o)) == NULL);
}

void test1_game_get_last_command(){
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_get_last_command(g) == NO_CMD);
}


void test1_game_add_space(){
    Game *g;
    Space *s;
    s = space_create(3);
    g = game_create();
    PRINT_TEST_RESULT(game_add_space(g, s) == OK);
}

void test2_game_add_space(){
    Game *g;
    Space *s = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_add_space(g, s) == ERROR);
}

void test1_game_add_object(){
    Game *g;
    Object *o1;
    o1 = object_create(2);
    g = game_create();
    PRINT_TEST_RESULT(game_add_object(g, o1) == OK);
}

void test2_game_add_object(){
    Game *g;
    Object *o1 = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_add_object(g, o1) == ERROR);
}

void test1_game_add_player(){
    Game *g;
    Player *p;
    p = player_create(3);
    g = game_create();
    PRINT_TEST_RESULT(game_add_player(g, p) == OK);
}

void test2_game_add_player(){
    Game *g;
    Player *p = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_add_player(g, p) == ERROR);
}

void test1_game_add_link(){
    Game *g;
    Link *l;
    l = link_create(4);
    g = game_create();
    PRINT_TEST_RESULT(game_add_link(g, l) == OK);
}

void test2_game_add_link(){
    Game *g = NULL;
    Link *l = NULL;
    PRINT_TEST_RESULT(game_add_link(g, l) == ERROR);
}

void test1_game_set_player_location(){
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_set_player_location(g, 3) == OK);
}

void test2_game_set_player_location(){
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_set_player_location(g, NO_ID) == ERROR);
}

void test1_game_set_object_location(){
    Game *g;
    Object *o;
    Space *s;
    s = space_create(3);
    o = object_create(5);
    g = game_create();
    game_add_space(g, s);
    game_add_object(g, o);
    PRINT_TEST_RESULT(game_set_object_location(g, 3, object_get_id(o)) == OK);
}

void test2_game_set_object_location(){
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_set_object_location(g, NO_ID, NO_ID) == ERROR);
}

void test1_game_get_object(){
    Game *g;
    Object *o;
    o = object_create(5);
    g = game_create();
    game_add_object(g,o);
    game_set_object_location(g, 2, object_get_id(o));
    PRINT_TEST_RESULT(game_get_object(g, object_get_id(o))!= NULL);
}

void test2_game_get_object(){
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_get_object(g, 2) == NULL);
}

void test1_game_get_link_with_id(){
    Game *g;
    Link *l;
    g = game_create();
    l = link_create(3);
    game_add_link(g, l);
    PRINT_TEST_RESULT(game_get_link_with_id(g, link_get_id(l)) == l);
}

void test2_game_get_link_with_id(){
    Game *g;
    Link *l = NULL;
    g = game_create();
    game_add_link(g, l);
    PRINT_TEST_RESULT(game_get_link_with_id(g, link_get_id(l)) == NULL);
}

void test1_game_set_player(){
    Game *g;
    Player *p;
    g = game_create();
    p = player_create(3);
    PRINT_TEST_RESULT(game_set_player(g, p) == OK);
}

void test2_game_set_player(){
    Game *g;
    Player *p = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_set_player(g, p) == ERROR);
}

void test1_game_get_player(){
    Game *g;
    Player *p;
    p = player_create(4);
    g = game_create();
    game_set_player(g, p);
    game_set_player_location(g, 5);
    PRINT_TEST_RESULT(game_get_player_location(g) == 5);
}

void test2_game_get_player(){
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_get_player_location(g) == NO_ID);
}

void test1_game_set_die(){
    Game *g;
    Die *d;
    g = game_create();
    d = die_create(3);
    PRINT_TEST_RESULT(game_set_die(g, d) == OK);
}

void test2_game_set_die(){
    Game *g;
    Die *d = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_set_die(g, d) == ERROR);
}

void test1_game_get_die(){
    Game *g;
    Die *d;
    g = game_create();
    d = die_create(3);
    game_set_die(g, d);
    PRINT_TEST_RESULT(game_get_die(g) == d);
}

void test2_game_get_die(){
    Game *g = NULL;
    PRINT_TEST_RESULT(game_get_die(g) == NULL);
}

void test1_game_set_desc(){
    Game *g;
    g = game_create();
    PRINT_TEST_RESULT(game_set_desc(g, "hii") == OK);
}

void test2_game_set_desc(){
    Game *g = NULL;
    PRINT_TEST_RESULT(game_set_desc(g, "hi") == ERROR);
}

void test1_game_get_desc(){
    Game *g;
    g = game_create();
    game_set_desc(g, "hii");
    PRINT_TEST_RESULT(strcmp(game_get_desc(g), "hii") == 0);
}

void test2_game_get_desc(){
    Game *g = NULL;
    game_set_desc(g, "hi");
    PRINT_TEST_RESULT(game_get_desc(g) == NULL);
}

void test1_game_add_to_desc(){
    Game *g; 
    g = game_create();
    PRINT_TEST_RESULT(game_add_to_desc(g, "hi") == OK);
}

void test2_game_add_to_desc(){
    Game *g = NULL; 
    PRINT_TEST_RESULT(game_add_to_desc(g, "hi") == ERROR);
}

void test1_game_object_open_link(){
    Game *g;
    Object *o;
    g = game_create();
    o = object_create(5);
    object_set_open(o, OPEN);
    PRINT_TEST_RESULT(game_object_open_link(g, o) == OK);
}

void test2_game_object_open_link(){
    Game *g;
    Object *o = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_object_open_link(g, o) == ERROR);
}

void test1_game_object_close_link(){
    Game *g;
    Object *o;
    g = game_create();
    o = object_create(5);
    object_set_open(o, CLOSED);
    PRINT_TEST_RESULT(game_object_close_link(g, o) == OK);
}

void test2_game_object_close_link(){
    Game *g;
    Object *o = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_object_close_link(g, o) == ERROR);
}

void test1_player_is_illuminating(){
    Game *g;
    Player *p;
    Object *o;
    o = object_create(3);
    g = game_create();
    p = player_create(3);
    object_set_illuminate(o, TRUE);
    game_add_player(g, p);
    game_set_player(g, p);
    game_add_object(g, o);
    game_set_object_location(g, 1, 3);
    game_set_player_location(g, 1);
    PRINT_TEST_RESULT(player_is_illuminating(g) ==  TRUE);
}

void test2_player_is_illuminating(){
    Game *g = NULL;
    PRINT_TEST_RESULT(player_is_illuminating(g) == FALSE);
}   

void test1_game_can_get_object(){
    Game *g;
    Object *o, *o2;
    o = object_create(5);
    o2 = object_create(4);
    g = game_create();
    object_set_hidden(o, FALSE);
    object_set_movable(o, TRUE);;
    object_set_incompatible(o, object_get_id(o2));
    PRINT_TEST_RESULT(game_can_get_object(g, o) == TRUE);
}

void test2_game_can_get_object(){
    Game *g;
    Object *o;
    o = object_create(5);
    g = game_create();
    object_set_hidden(o, TRUE);
    object_set_movable(o, FALSE);;
    PRINT_TEST_RESULT(game_can_get_object(g, o) == FALSE);

}
