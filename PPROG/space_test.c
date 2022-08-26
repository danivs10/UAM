/** 
 * @brief It tests link module
 * 
 * @file link_test.c
 * @author Beatriz Sainz
 * @date 01-05-2020
 */


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "space.h"
#include "space_test.h"
#include "test.h"

#define MAX_TESTS 59

/** 
 * @brief Main function for SPACE unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char** argv) {

    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module Space:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_space_create();
    if (all || test == 2) test2_space_create();
    if (all || test == 3) test1_space_set_name();
    if (all || test == 4) test2_space_set_name();
    if (all || test == 5) test3_space_set_name();
    if (all || test == 6) test1_space_set_north();
    if (all || test == 7) test2_space_set_north();
    if (all || test == 8) test1_space_set_south();
    if (all || test == 9) test2_space_set_south();
    if (all || test == 10) test1_space_set_east();
    if (all || test == 11) test2_space_set_east();
    if (all || test == 12) test1_space_set_west();
    if (all || test == 13) test2_space_set_west();
    if (all || test == 14) test1_space_get_name();
    if (all || test == 15) test2_space_get_name();
    if (all || test == 16) test1_space_get_object();
    if (all || test == 17) test2_space_get_object();
    if (all || test == 18) test3_space_get_object();
    if (all || test == 19) test1_space_get_north();
    if (all || test == 20) test2_space_get_north();
    if (all || test == 21) test1_space_get_south();
    if (all || test == 22) test2_space_get_south();
    if (all || test == 23) test1_space_get_east();
    if (all || test == 24) test2_space_get_east();
    if (all || test == 25) test1_space_get_west();
    if (all || test == 26) test2_space_get_west();
    if (all || test == 27) test1_space_get_id();
    if (all || test == 28) test2_space_get_id();
    if (all || test == 29) test1_space_add_object();
    if (all || test == 30) test2_space_add_object();
    if (all || test == 31) test1_space_get_set();
    if (all || test == 32) test2_space_get_set();
    if (all || test == 33) test1_space_set_gdesc1();
    if (all || test == 34) test2_space_set_gdesc1();
    if (all || test == 35) test3_space_set_gdesc1();
    if (all || test == 36) test1_space_set_gdesc2();
    if (all || test == 37) test2_space_set_gdesc2();
    if (all || test == 38) test3_space_set_gdesc2();
    if (all || test == 39) test1_space_set_gdesc3();
    if (all || test == 40) test2_space_set_gdesc3();
    if (all || test == 41) test3_space_set_gdesc3();
    if (all || test == 42) test1_space_get_gdesc1();
    if (all || test == 43) test2_space_get_gdesc1();
    if (all || test == 44) test1_space_get_gdesc2();
    if (all || test == 45) test2_space_get_gdesc2();
    if (all || test == 46) test1_space_get_gdesc3();
    if (all || test == 47) test2_space_get_gdesc3();
    if (all || test == 48) test1_space_set_description();
    if (all || test == 49) test2_space_set_description();
    if (all || test == 50) test1_space_get_description();
    if (all || test == 51) test2_space_get_description();
    if (all || test == 52) test1_is_north_available();
    if (all || test == 53) test2_is_north_available();
    if (all || test == 54) test1_is_south_available();
    if (all || test == 55) test2_is_south_available();
    if (all || test == 56) test1_is_east_available();
    if (all || test == 57) test2_is_east_available();
    if (all || test == 58) test1_is_west_available();
    if (all || test == 59) test2_is_west_available();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_space_create() {
  int result = space_create(5)!=NULL ;
  PRINT_TEST_RESULT(result);
}

void test2_space_create() {
    Space *s;
    s = space_create(4);
    PRINT_TEST_RESULT(space_get_id(s) == 4);
}

void test1_space_set_name() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
}

void test2_space_set_name() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}

void test3_space_set_name() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
}

void test1_space_set_north() {
    Space *s;
    Link *l;
    l = link_create(2);
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_north(s, l) == OK);
}

void test2_space_set_north() {
    Space *s = NULL;
    Link *l = NULL;
    PRINT_TEST_RESULT(space_set_north(s, l) == ERROR);
}

void test1_space_set_south() {
    Space *s;
    Link *l;
    l = link_create(2);
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_south(s, l) == OK);
}

void test2_space_set_south() {
    Space *s = NULL;
    Link *l = NULL;
    PRINT_TEST_RESULT(space_set_south(s, l) == ERROR);
}

void test1_space_set_east() {
    Space *s;
    Link *l;
    l = link_create(2);
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_east(s, l) == OK);
}

void test2_space_set_east() {
    Space *s = NULL;
    Link *l = NULL;
    PRINT_TEST_RESULT(space_set_east(s, l) == ERROR);
}

void test1_space_set_west() {
    Space *s;
    Link *l;
    l = link_create(2);
    s = space_create(5);
    PRINT_TEST_RESULT(space_set_west(s, l) == OK);
}

void test2_space_set_west() {
    Space *s = NULL;
    Link *l = NULL;
    PRINT_TEST_RESULT(space_set_west(s, l) == ERROR);
}

void test1_space_get_name() {
    Space *s;
    s = space_create(1);
    space_set_name(s, "adios");
    PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);
}

void test2_space_get_name() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_name(s) == NULL);

}

void test1_space_get_object() {
    Space *s;
    Set *e;
    Object *o;
    e = set_create();
    s = space_create(7);
    o = object_create(21);
    set_add_id(e, object_get_id(o));

    space_add_object(s, object_get_id(o));
    PRINT_TEST_RESULT(space_get_object_at(s, 2) == set_get_id(e, 2));
}

void test2_space_get_object() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_get_object_at(s, 2) == NO_ID);
}

void test3_space_get_object() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_object_at(s, 2) == NO_ID);
}

void test1_space_get_north() {
    Space *s;
    Link *l;
    s = space_create(5);
    l = link_create(6);
    space_set_north(s, l);
    link_set_source(l, 3);
    PRINT_TEST_RESULT(space_get_north(s) == 3);
}

void test2_space_get_north() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_north(s) == NO_ID);
}

void test1_space_get_south() {
    Space *s;
    Link *l;
    s = space_create(5);
    l = link_create(7);
    space_set_south(s, l);
    link_set_destiny(l, 4);
    PRINT_TEST_RESULT(space_get_south(s) == 4);
}

void test2_space_get_south() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_south(s) == NO_ID);
}

void test1_space_get_east() {
    Space *s;
    Link *l;
    s = space_create(5);
    l = link_create(8);
    space_set_east(s, l);
    link_set_destiny(l, 5);
    PRINT_TEST_RESULT(space_get_east(s) == 5);
}

void test2_space_get_east() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_east(s) == NO_ID);
}

void test1_space_get_west() {
    Space *s;
    Link *l;
    s = space_create(5);
    l = link_create(6);
    space_set_west(s, l);
    link_set_source(l, 3);
    PRINT_TEST_RESULT(space_get_west(s) == 3);
}

void test2_space_get_west() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_west(s) == NO_ID);
}

void test1_space_get_id() {
    Space *s;
    s = space_create(25);
    PRINT_TEST_RESULT(space_get_id(s) == 25);
}

void test2_space_get_id() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

void test1_space_add_object(){
    Space *s;
    s  = space_create(21);
    PRINT_TEST_RESULT(space_add_object(s, 3) == OK);
}

void test2_space_add_object(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_add_object(s, 3) == ERROR);
}

void test1_space_get_set(){
    Space *s;
    int result;
    s = space_create(5);
    result = space_get_set(s)!=NULL ;
    PRINT_TEST_RESULT(result);
}

void test2_space_get_set(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_set(s) == NULL);
}

void test1_space_set_gdesc1(){
    Space *s;
    s = space_create(4);
    PRINT_TEST_RESULT(space_set_gdesc1(s, ":)") == OK);
}

void test2_space_set_gdesc1(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_gdesc1(s, ":)") == ERROR);
}

void test3_space_set_gdesc1(){
    Space *s;
    s = space_create(4);
    PRINT_TEST_RESULT(space_set_gdesc1(s, NULL) == ERROR);
}

void test1_space_set_gdesc2(){
    Space *s;
    s = space_create(4);
    PRINT_TEST_RESULT(space_set_gdesc2(s, ":)") == OK);
}

void test2_space_set_gdesc2(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_gdesc2(s, ":)") == ERROR);
}

void test3_space_set_gdesc2(){
    Space *s;
    s = space_create(4);
    PRINT_TEST_RESULT(space_set_gdesc2(s, NULL) == ERROR);
}

void test1_space_set_gdesc3(){
    Space *s;
    s = space_create(4);
    PRINT_TEST_RESULT(space_set_gdesc3(s, ":)") == OK);
}

void test2_space_set_gdesc3(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_gdesc3(s, ":)") == ERROR);
}

void test3_space_set_gdesc3(){
    Space *s;
    s = space_create(4);
    PRINT_TEST_RESULT(space_set_gdesc3(s, NULL) == ERROR);
}

void test1_space_get_gdesc1(){
    Space *s;
    s = space_create(4);
    space_set_gdesc1(s, ":)");
    PRINT_TEST_RESULT(strcmp(space_get_gdesc1(s), ":)") == 0);
}

void test2_space_get_gdesc1(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_gdesc1(s) == NULL);
}

void test1_space_get_gdesc2(){
    Space *s;
    s = space_create(4);
    space_set_gdesc2(s, ":)");
    PRINT_TEST_RESULT(strcmp(space_get_gdesc2(s), ":)") == 0);
}

void test2_space_get_gdesc2(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_gdesc2(s) == NULL);
}

void test1_space_get_gdesc3(){
    Space *s;
    s = space_create(4);
    space_set_gdesc3(s, ":)");
    PRINT_TEST_RESULT(strcmp(space_get_gdesc3(s), ":)") == 0);
}

void test2_space_get_gdesc3(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_gdesc3(s) == NULL);
}

void test1_space_set_description(){
    Space *s;
    s = space_create(4);
    PRINT_TEST_RESULT(space_set_description(s, "hi") == OK);
}

void test2_space_set_description(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_description(s, "hi") == ERROR);
}

void test1_space_get_description(){
    Space *s;
    s = space_create(4);
    space_set_description(s, "hi");
    PRINT_TEST_RESULT(strcmp(space_get_description(s), "hi") == 0 );
}

void test2_space_get_description(){
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_description(s) == NULL);
}

void test1_is_north_available(){
    Space *s;
    Link *l; 
    l = link_create(5);
    s = space_create(4);
    link_set_status(l, OPEN);
    space_set_north(s, l);
    PRINT_TEST_RESULT(is_north_available(s) == TRUE);
}

void test2_is_north_available(){
    Space *s = NULL;
    PRINT_TEST_RESULT(is_north_available(s) == FALSE); 
}

void test1_is_south_available(){
    Space *s;
    Link *l;
    l = link_create(5);
    s = space_create(4);
    link_set_status(l, OPEN);
    space_set_south(s, l);
    PRINT_TEST_RESULT(is_south_available(s) == TRUE);
}

void test2_is_south_available(){
    Space *s = NULL;
    PRINT_TEST_RESULT(is_south_available(s) == FALSE); 
}

void test1_is_east_available(){
    Space *s;
    Link *l;
    l = link_create(5);
    s = space_create(4);
    link_set_status(l, OPEN);
    space_set_east(s, l);
    PRINT_TEST_RESULT(is_east_available(s) == TRUE);
}

void test2_is_east_available(){
    Space *s = NULL;
    PRINT_TEST_RESULT(is_east_available(s) == FALSE); 
}

void test1_is_west_available(){
    Space *s;
    Link *l;
    l = link_create(5);
    s = space_create(4);
    link_set_status(l, OPEN);
    space_set_west(s, l);
    PRINT_TEST_RESULT(is_west_available(s) == TRUE);
}

void test2_is_west_available(){
    Space *s = NULL;
    PRINT_TEST_RESULT(is_west_available(s) == FALSE); 
}