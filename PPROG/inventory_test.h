/** 
 * @brief It declares the tests for the inventory module
 * 
 * @file inventory_test.h
 * @author Bea
 */

#ifndef LINK_TEST_H
#define LINK_TEST_H

/**
 * @test Test inventory creation
 * @pre inventory_create
 * @post Non NULL pointer to inventory 
 */
void test1_inventory_create();

/**
 * @test Test inventory creation
 * @pre inventory_create 
 * @post Non null pointer to inventory
 */
void test2_inventory_create();

/**
 * @test Test inventory_add_object
 * @pre pointer to inventory
 * @post Output==OK
 */
void test1_inventory_add_object();

/**
 * @test Test inventory_add_object
 * @pre pointer to inventory = NULL , NO_ID
 * @post Output==ERROR
 */
void test2_inventory_add_object();

/**
 * @test Test inventory_del_object
 * @pre pointer to inventory and object, with add_object
 * @post Output==OK
 */
void test1_inventory_del_object();

/**
 * @test Test inventory_del_object
 * @pre pointer to inventory and object = NULL
 * @post Output==ERROR
 */
void test2_inventory_del_object();

/**
 * @test Test inventory_del_object_with_id
 * @pre pointer to inventory and object, with add_object, object_id
 * @post Output==OK
 */
void test1_inventory_del_object_with_id();

/**
 * @test Test inventory_del_object_with_id
 * @pre pointer to inventory and object = NULL with object_id
 * @post Output==ERROR
 */
void test2_inventory_del_object_with_id();

/**
 * @test Test inventory_object_at
 * @pre pointer to inventory
 * @post Output==NO_ID
 */
void test1_inventory_get_object_id_at();

/**
 * @test Test inventory_object_at
 * @pre pointer to inventory = NULL
 * @post Output==NO_ID
 */
void test2_inventory_get_object_id_at();

/**
 * @test Test inventory_set
 * @pre pointer to inventory and object = NULL
 * @post Non NULL pointer set
 */
void test1_inventory_get_set();

/**
 * @test Test inventory_set
 * @pre pointer to inventory = NULL
 * @post Output==NULL
 */
void test2_inventory_get_set();

/**
 * @test Test inventory_set_max
 * @pre pointer to inventory
 * @post Output==OK
 */
void test1_inventory_set_max();

/**
 * @test Test inventory_set_max
 * @pre pointer to inventory = NULL
 * @post Output==ERROR
 */
void test2_inventory_set_max();

/**
 * @test Test inventory_get_max
 * @pre pointer to inventory, with set max
 * @post Output==max
 */
void test1_inventory_get_max();

/**
 * @test Test inventory_get_max
 * @pre pointer to inventory = NULL, with set max
 * @post Output==0
 */
void test2_inventory_get_max();

#endif
