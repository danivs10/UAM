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
#include "inventory.h"
#include "test.h"
#include "inventory_test.h"

#define MAX_TESTS 16

int main(int argc, char** argv){
    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module Inventory:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_inventory_create();
    if (all || test == 2) test2_inventory_create();
    if (all || test == 3) test1_inventory_add_object();
    if (all || test == 4) test2_inventory_add_object();
    if (all || test == 5) test1_inventory_del_object();
    if (all || test == 6) test2_inventory_del_object();
    if (all || test == 7) test1_inventory_del_object_with_id();
    if (all || test == 8) test2_inventory_del_object_with_id();
    if (all || test == 9) test1_inventory_get_object_id_at();
    if (all || test == 10) test2_inventory_get_object_id_at();
    if (all || test == 11) test1_inventory_get_set();
    if (all || test == 12) test2_inventory_get_set();
    if (all || test == 13) test1_inventory_set_max();
    if (all || test == 14) test2_inventory_set_max();
    if (all || test == 15) test1_inventory_get_max();
    if (all || test == 16) test2_inventory_get_max();


    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_inventory_create(){
    int result = inventory_create() != NULL;
    PRINT_TEST_RESULT(result);
}

void test2_inventory_create(){
    Inventory *i;
    i = inventory_create();
    PRINT_TEST_RESULT(i != NULL);
}

void test1_inventory_add_object(){
    Inventory *i;
    i =inventory_create();
    PRINT_TEST_RESULT(inventory_add_object(i, 4) == OK);
}

void test2_inventory_add_object(){
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_add_object(i, NO_ID) == ERROR);

}

void test1_inventory_del_object(){
    Inventory *i;
    Object *o;
    o = object_create(2);
    i = inventory_create();
    inventory_add_object(i, object_get_id(o));
    PRINT_TEST_RESULT(inventory_del_object(i, o) == OK);
}

void test2_inventory_del_object(){
    Inventory *i = NULL;
    Object *o = NULL;
    PRINT_TEST_RESULT(inventory_del_object(i, o) == ERROR);
}

void test1_inventory_del_object_with_id(){
    Inventory *i;
    Object *o;
    o = object_create(2);
    i = inventory_create();
    inventory_add_object(i, object_get_id(o));
    PRINT_TEST_RESULT(inventory_del_object_with_id(i, object_get_id(o)) == OK);
}

void test2_inventory_del_object_with_id(){
    Inventory *i = NULL;
    Object *o = NULL;
    PRINT_TEST_RESULT(inventory_del_object_with_id(i, object_get_id(o)) == ERROR);
}

void test1_inventory_get_object_id_at(){
    Inventory *i;
    i = inventory_create();
    PRINT_TEST_RESULT(inventory_get_object_id_at(i, 5) == NO_ID);
}

void test2_inventory_get_object_id_at(){
    Inventory *i;
    i = inventory_create();
    PRINT_TEST_RESULT(inventory_get_object_id_at(i, -1) == NO_ID);
}

void test1_inventory_get_set(){
    int result;
    Inventory *i;
    i = inventory_create();
    result = inventory_get_set(i)!=NULL ;
    PRINT_TEST_RESULT(result);
}

void test2_inventory_get_set(){
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_get_set(i) == NULL);
}

void test1_inventory_set_max(){
    Inventory *i;
    i = inventory_create();
    PRINT_TEST_RESULT(inventory_set_max(i, 33) == OK);
}

void test2_inventory_set_max(){
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_set_max(i, 0) == ERROR);
}

void test1_inventory_get_max(){
    Inventory *i;
    i = inventory_create();
    inventory_set_max(i, 33);
    PRINT_TEST_RESULT(inventory_get_max(i) == 33);
}

void test2_inventory_get_max(){
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_get_max(i) == -1);
}