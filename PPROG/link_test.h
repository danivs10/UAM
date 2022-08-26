/** 
 * @brief It declares the tests for the link module
 * 
 * @file link_test.h
 * @author Bea
 */

#ifndef LINK_TEST_H
#define LINK_TEST_H

/**
 * @test Test link creation
 * @pre link ID 
 * @post Non NULL pointer to link 
 */
void test1_link_create();

/**
 * @test Test link creation
 * @pre link ID 
 * @post link_ID == Supplied link Id
 */
void test2_link_create();

/**
 * @test Test function for link_name setting
 * @pre String with link name
 * @post Ouput==OK 
 */
void test1_link_set_name();

/**
 * @test Test function for link_name setting
 * @pre pointer to link = NULL 
 * @post Output==ERROR
 */
void test2_link_set_name();

/**
 * @test Test function for link_name setting
 * @pre pointer to link_name = NULL (point to link = NON NULL) 
 * @post Output==ERROR
 */
void test3_link_set_name();

/**
 * @test Test function for link_destiny setting
 * @pre pointer to link 
 * @post Output==OK
 */
void test1_link_set_destiny();

/**
 * @test Test function for link_destiny setting
 * @pre pointer to link = NULL
 * @post Output==ERROR
 */
void test2_link_set_destiny();

/**
 * @test Test function for link_source setting
 * @pre pointer to link 
 * @post Output==OK
 */
void test1_link_set_source();

/**
 * @test Test function for link_source setting
 * @pre pointer to link = NULL
 * @post Output==ERROR
 */
void test2_link_set_source();

/**
 * @test Test function for link_status setting
 * @pre pointer to link
 * @post Output==OK
 */
void test1_link_set_status();

/**
 * @test Test function for link_status setting
 * @pre pointer to link = NULL
 * @post Output==ERROR
 */
void test2_link_set_status();

/**
 * @test Test function for link_id setting
 * @pre pointer to link
 * @post Output==link_id
 */
void test1_link_get_id();

/**
 * @test Test function for link_id setting
 * @pre pointer to link = NULL
 * @post Output==NO_ID
 */
void test2_link_get_id();

/**
 * @test Test function for link_name setting
 * @pre pointer to link with link_name, strcmp
 * @post Output==0
 */
void test1_link_get_name();

/**
 * @test Test function for link_name setting
 * @pre pointer to link = NULL
 * @post Output==NULL
 */
void test2_link_get_name();

/**
 * @test Test function for link_source setting
 * @pre pointer to link with link_source
 * @post Output==link_source
 */
void test1_link_get_source();

/**
 * @test Test function for link_source setting
 * @pre pointer to link = NULL
 * @post Output==NO_ID
 */
void test2_link_get_source();

/**
 * @test Test function for link_destiny setting
 * @pre pointer to link with link_destiny
 * @post Output==link_destiny
 */
void test1_link_get_destiny();

/**
 * @test Test function for link_destiny setting
 * @pre pointer to link = NULL
 * @post Output==NO_ID
 */
void test2_link_get_destiny();

/**
 * @test Test function for link_status setting
 * @pre pointer to link , link_status
 * @post Output==OPEN
 */
void test1_link_get_status();

/**
 * @test Test function for link_status setting
 * @pre pointer to link = NULL
 * @post Output==CLOSED
 */
void test2_link_get_status();

#endif
