/** 
 * @brief It tests lobject module
 * 
 * @file object_test.c
 * @author Beatriz Sainz
 * @date 01-05-2020
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "test.h"
#include "object_test.h"

#define MAX_TESTS 33

int main(int argc, char** argv){
    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module Object:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_object_create();
    if (all || test == 2) test2_object_create();
    if (all || test == 3) test1_object_get_id();
    if (all || test == 4) test2_object_get_id();
    if (all || test == 5) test1_object_set_name();
    if (all || test == 6) test2_object_set_name();
    if (all || test == 7) test3_object_set_name();
    if (all || test == 8) test1_object_get_name();
    if (all || test == 9) test2_object_get_name();
    if (all || test == 10) test1_object_get_description();
    if (all || test == 11) test2_object_get_description();
    if (all || test == 12) test1_object_set_description();
    if (all || test == 13) test2_object_set_description();

    if (all || test == 14) test1_object_get_turnedOn();
    if (all || test == 15) test2_object_get_turnedOn();
    if (all || test == 16) test1_object_set_turnedOn();
    if (all || test == 17) test2_object_set_turnedOn();
    if (all || test == 18) test1_object_get_hidden();
    if (all || test == 19) test2_object_get_hidden();
    if (all || test == 20) test1_object_set_hidden();
    if (all || test == 21) test2_object_set_hidden();
    if (all || test == 22) test1_object_get_movable();
    if (all || test == 23) test2_object_get_movable();
    if (all || test == 24) test1_object_set_movable();
    if (all || test == 25) test2_object_set_movable();
    if (all || test == 26) test1_object_get_illuminate();
    if (all || test == 27) test2_object_get_illuminate();
    if (all || test == 28) test1_object_set_illuminate();
    if (all || test == 29) test2_object_set_illuminate();
    if (all || test == 30) test1_object_get_open();
    if (all || test == 31) test2_object_get_open();
    if (all || test == 32) test1_object_set_open();
    if (all || test == 33) test2_object_set_open();
    if (all || test == 32) test1_object_set_dependency();
    if (all || test == 33) test2_object_set_dependency();
    if (all || test == 32) test1_object_get_dependency();
    if (all || test == 33) test2_object_get_dependency();
    if (all || test == 32) test1_object_set_incompatible();
    if (all || test == 33) test2_object_set_incompatible();
    if (all || test == 32) test1_object_get_incompatible();
    if (all || test == 33) test2_object_get_incompatible();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_object_create(){
    int result = object_create(5)!=NULL;
    PRINT_TEST_RESULT(result);
}

void test2_object_create(){
    Object *o;
    o = object_create(4);
    PRINT_TEST_RESULT(object_get_id(o) == 4);
}

void test1_object_get_id(){
    Object *o;
    o = object_create(8);
    PRINT_TEST_RESULT(object_get_id(o) == 8);
}

void test2_object_get_id(){
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_id(o) == NO_ID);
}

void test1_object_set_name(){
    Object *o;
    o = object_create(2);
    PRINT_TEST_RESULT(object_set_name(o, "hi") == OK);
}

void test2_object_set_name(){
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_name(o, "hi") == ERROR);
}

void test3_object_set_name(){
    Object *o;
    o = object_create(7);
    PRINT_TEST_RESULT(object_set_name(o, NULL) == ERROR);
}

void test1_object_get_name(){
    Object *o;
    o = object_create(4);
    object_set_name(o, "hi");
    PRINT_TEST_RESULT(strcmp(object_get_name(o), "hi") == 0);
}

void test2_object_get_name(){
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_name(o) == NULL);
}

void test1_object_get_description(){
    Object *o;
    o = object_create(5);
    object_set_description(o, "123");
    PRINT_TEST_RESULT(strcmp(object_get_description(o), "123") == 0);
}

void test2_object_get_description(){
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_description(o) == NULL);
}

void test1_object_set_description(){
    Object *o;
    o = object_create(3);
    PRINT_TEST_RESULT(object_set_description(o, "123") == OK);
}

void test2_object_set_description(){
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_description(o, "123") == ERROR);
}

void test1_object_get_turnedOn(){
    Object *o;
    o = object_create(3);
    object_set_turnedOn(o, TRUE);
    PRINT_TEST_RESULT(object_get_turnedOn(o) == TRUE);
}

void test2_object_get_turnedOn(){
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_turnedOn(o) == FALSE);
}

void test1_object_set_turnedOn(){
    Object *o;
    o = object_create(4);
    PRINT_TEST_RESULT(object_set_turnedOn(o, TRUE) == OK);
}

void test2_object_set_turnedOn(){
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_turnedOn(o, TRUE) == ERROR);
}

void test1_object_get_hidden(){
    Object *o; 
    o = object_create(4);
    object_set_hidden(o, TRUE);
    PRINT_TEST_RESULT(object_get_hidden(o) == TRUE);
}

void test2_object_get_hidden(){
    Object *o; 
    o = object_create(4);
    object_set_hidden(o, FALSE);
    PRINT_TEST_RESULT(object_get_hidden(o) == FALSE);
}

void test1_object_set_hidden(){
    Object *o;
    o = object_create(4);
    PRINT_TEST_RESULT(object_set_hidden(o, TRUE) == OK);
}

void test2_object_set_hidden(){
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_hidden(o, TRUE) == ERROR);
}

void test1_object_get_movable(){
    Object *o; 
    o = object_create(4);
    object_set_movable(o, TRUE);
    PRINT_TEST_RESULT(object_get_movable(o) == TRUE);
}

void test2_object_get_movable(){
    Object *o = NULL; 
    object_set_movable(o, TRUE);
    PRINT_TEST_RESULT(object_get_movable(o) == FALSE);
}

void test1_object_set_movable(){
    Object *o;
    o = object_create(3);
    PRINT_TEST_RESULT(object_set_movable(o, TRUE) == OK);
}

void test2_object_set_movable(){
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_movable(o, TRUE) == ERROR);
}

void test1_object_get_illuminate(){
    Object *o; 
    o = object_create(4);
    object_set_illuminate(o, TRUE);
    PRINT_TEST_RESULT(object_get_illuminate(o) == TRUE);
}

void test2_object_get_illuminate(){
    Object *o = NULL; 
    o = object_create(4);
    PRINT_TEST_RESULT(object_get_illuminate(o) == FALSE);
}

void test1_object_set_illuminate(){
    Object *o;
    o = object_create(4);
    PRINT_TEST_RESULT(object_set_illuminate(o, TRUE) == OK);
}
void test2_object_set_illuminate(){
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_illuminate(o, TRUE) == ERROR);
}

void test1_object_get_open(){
    Object *o; 
    o = object_create(4);
    object_set_open(o, 1);
    PRINT_TEST_RESULT(object_get_open(o) == 1);
}

void test2_object_get_open(){
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_open(o) == NO_ID);
}

void test1_object_set_open(){
    Object *o;
    o = object_create(6);
    PRINT_TEST_RESULT(object_set_open(o, 1) == OK);
}
void test2_object_set_open(){
     Object *o = NULL;
    PRINT_TEST_RESULT(object_set_open(o, 1) == ERROR);
}

void test1_object_set_dependency(){
    Object *o1, *o2;
    o2 = object_create(4);
    o1 = object_create(2);
    PRINT_TEST_RESULT(object_set_dependency(o1, object_get_id(o2)) == OK);
}

void test2_object_set_dependency(){
    Object *o1 = NULL;
    PRINT_TEST_RESULT(object_set_dependency(o1, 2) == ERROR);
}

void test1_object_get_dependency(){
    Object *o1, *o2;
    o1 = object_create(2);
    o2 = object_create(3);
    object_set_dependency(o1, object_get_id(o2));
    PRINT_TEST_RESULT(object_get_dependency(o1) == object_get_id(o2));
}

void test2_object_get_dependency(){
    Object *o1 = NULL;
    PRINT_TEST_RESULT(object_get_dependency(o1) == NO_ID);
}

void test1_object_set_incompatible(){
    Object *o1, *o2;
    o1 = object_create(2);
    o2 = object_create(3);
    PRINT_TEST_RESULT(object_set_incompatible(o1, object_get_id(o2)) == OK);
}

void test2_object_set_incompatible(){
    Object *o1 = NULL, *o2;
    o2 = object_create(2);
    PRINT_TEST_RESULT(object_set_incompatible(o1, object_get_id(o2)) == ERROR);
}

void test1_object_get_incompatible(){
    Object *o1, *o2;
    o1 = object_create(2);
    o2 = object_create(3);
    object_set_incompatible(o1, object_get_id(o2));
    PRINT_TEST_RESULT(object_get_incompatible(o1) == object_get_id(o2));
} 

void test2_object_get_incompatible(){
    Object *o1;
    o1 = object_create(2);
    PRINT_TEST_RESULT(object_get_incompatible(o1) == NO_ID);
}