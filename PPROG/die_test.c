/** 
 * @brief It tests die module
 * 
 * @file die_test.c
 * @author Beatriz Sainz
 * @date 08-05-2020
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "die.h"
#include "test.h"
#include "die_test.h"

#define MAX_TESTS 6

int main(int argc, char** argv){
    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module Die:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 && test > MAX_TESTS) {
	  printf("Error: unknown test %d\t", test);
	  exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_die_create();
    if (all || test == 2) test2_die_create();
    if (all || test == 3) test1_die_roll();
    if (all || test == 4) test2_die_roll();
    if (all || test == 5) test1_die_get_number();
    if (all || test == 6) test1_die_get_number();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_die_create(){
    int result = die_create(4)!=NULL;
    PRINT_TEST_RESULT(result);
}

void test2_die_create(){
    Die *d;
    d = die_create(3);
    PRINT_TEST_RESULT(d != NULL);
}

void test1_die_roll(){
    Die *d;
    d = die_create(2);
    PRINT_TEST_RESULT(die_roll(d) == OK);
}

void test2_die_roll(){
    Die *d = NULL;
    PRINT_TEST_RESULT(die_roll(d) == ERROR);
}

void test1_die_get_number(){
    Die *d;
    d = die_create(1);
    die_roll(d);
    PRINT_TEST_RESULT(die_get_number(d) != -1);
}

void test2_die_get_number(){
    Die *d = NULL;
    PRINT_TEST_RESULT(die_get_number(d) == -1);
}