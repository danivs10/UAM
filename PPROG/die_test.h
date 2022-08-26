/** 
 * @brief It declares the tests for the die module
 * 
 * @file die_test.h
 * @author Bea
 */

#ifndef DIE_TEST_H
#define DIE_TEST_H

/**
 * @test Test die creation
 * @pre die ID 
 * @post Non NULL pointer to die 
 */
void test1_die_create();

/**
 * @test Test die creation
 * @pre die ID 
 * @post Non null
 */
void test2_die_create();

/**
 * @test Test die roll
 * @pre pointer to die
 * @post Output==OK
 */
void test1_die_roll();

/**
 * @test Test die roll
 * @pre pointer to die = NULL
 * @post Output==ERROR
 */
void test2_die_roll();

/**
 * @test Test die roll
 * @pre pointer to die with die_roll
 * @post Output!=-1
 */
void test1_die_get_number();

/**
 * @test Test die roll
 * @pre pointer to die, with die_roll
 * @post Output==-1
 */
void test2_die_get_number();

#endif