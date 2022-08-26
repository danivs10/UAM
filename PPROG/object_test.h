/** 
 * @brief It declares the tests for the link module
 * 
 * @file link_test.h
 * @author Bea
 */

#ifndef LINK_TEST_H
#define LINK_TEST_H

/**
 * @test Test object creation
 * @pre object ID 
 * @post Non NULL pointer to object
 */
void test1_object_create();

/**
 * @test Test object creation
 * @pre object ID 
 * @post object_ID == Supplied lobject Id
 */
void test2_object_create();

/**
 * @test Test function for object_name setting
 * @pre String with object name
 * @post Ouput==OK 
 */
void test1_object_set_name();

/**
 * @test Test function for object_name setting
 * @pre pointer to object = NULL 
 * @post Output==ERROR
 */
void test2_object_set_name();

/**
 * @test Test function for object_name setting
 * @pre pointer to object_name = NULL (point to object = NON NULL) 
 * @post Output==ERROR
 */
void test3_object_set_name();


void test1_object_get_id();
void test2_object_get_id();
void test1_object_get_name();
void test2_object_get_name();
void test1_object_get_description();
void test2_object_get_description();
void test1_object_set_description();
void test2_object_set_description();

void test1_object_get_turnedOn();
void test2_object_get_turnedOn();
void test1_object_set_turnedOn();
void test2_object_set_turnedOn();
void test1_object_get_hidden();
void test2_object_get_hidden();
void test1_object_set_hidden();
void test2_object_set_hidden();
void test1_object_get_movable();
void test2_object_get_movable();
void test1_object_set_movable();
void test2_object_set_movable();
void test1_object_get_illuminate();
void test2_object_get_illuminate();
void test1_object_set_illuminate();
void test2_object_set_illuminate();
void test1_object_get_open();
void test2_object_get_open();
void test1_object_set_open();
void test2_object_set_open();

void test1_object_set_dependency();
void test2_object_set_dependency();
void test1_object_get_dependency();
void test2_object_get_dependency();
void test1_object_set_incompatible();
void test2_object_set_incompatible();
void test1_object_get_incompatible();
void test2_object_get_incompatible();
#endif
