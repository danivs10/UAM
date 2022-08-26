/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Profesores Pprog
 * @version 2.0 
 * @date 19-01-2016
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H


/**
 * @test Test space creation
 * @pre Space ID 
 * @post Non NULL pointer to space 
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();

/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Ouput==OK 
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space_name = NULL (point to space = NON NULL) 
 * @post Output==ERROR
 */
void test3_space_set_name();

/**
 * @test Test function for space_north setting
 * @pre pointer to space, pointer to link with space north
 * @post Output==OK
 */
void test1_space_set_north();

/**
 * @test Test function for space_north setting
 * @pre pointer to space = NULL , pointer to link
 * @post Output==ERROR
 */
void test2_space_set_north();

/**
 * @test Test function for space_south setting
 * @pre pointer to space, pointer to link with space south
 * @post Output==OK
 */
void test1_space_set_south();

/**
 * @test Test function for space_south setting
 * @pre pointer to space = NULL , pointer to link
 * @post Output==ERROR
 */
void test2_space_set_south();

/**
 * @test Test function for space_east setting
 * @pre pointer to space, pointer to link with space east
 * @post Output==OK
 */
void test1_space_set_east();

/**
 * @test Test function for space_east setting
 * @pre pointer to space = NULL , pointer to link
 * @post Output==ERROR
 */
void test2_space_set_east();

/**
 * @test Test function for space_west setting
 * @pre pointer to space, pointer to link with space west
 * @post Output==OK
 */
void test1_space_set_west();

/**
 * @test Test function for space_west setting
 * @pre pointer to space = NULL , pointer to link
 * @post Output==ERROR
 */
void test2_space_set_west();

/**
 * @test Test function for space_id setting
 * @pre pointer to space with space id
 * @post Output==SPACE_ID
 */
void test1_space_get_id();

/**
 * @test Test function for space_id setting
 * @pre pointer to space = NULL, with space id
 * @post Output==NO_ID
 */
void test2_space_get_id();

/**
 * @test Test function for space_id setting
 * @pre string compare with space_name and a string
 * @post Output==0
 */
void test1_space_get_name();

/**
 * @test Test function for space_id setting
 * @pre pointer to space = NULL
 * @post Output==NULL
 */
void test2_space_get_name();

/**
 * @test Test function for space_north setting
 * @pre pointer to space, pointer to link, with link_source
 * @post Output==LINK_ID
 */
void test1_space_get_north();

/**
 * @test Test function for space_north setting
 * @pre pointer to space = NULL
 * @post Output==NO_ID
 */
void test2_space_get_north();

/**
 * @test Test function for space_south setting
 * @pre pointer to space, pointer to link, with link_source
 * @post Output==LINK_ID
 */
void test1_space_get_south();

/**
 * @test Test function for space_south setting
 * @pre pointer to space = NULL
 * @post Output==NO_ID
 */
void test2_space_get_south();

/**
 * @test Test function for space_east setting
 * @pre pointer to space, pointer to link, with link_source
 * @post Output==LINK_ID
 */
void test1_space_get_east();

/**
 * @test Test function for space_east setting
 * @pre pointer to space = NULL
 * @post Output==NO_ID
 */
void test2_space_get_east();

/**
 * @test Test function for space_west setting
 * @pre pointer to space, pointer to link, with link_source
 * @post Output==LINK_ID
 */
void test1_space_get_west();

/**
 * @test Test function for space_west setting
 * @pre pointer to space = NULL
 * @post Output==NO_ID
 */
void test2_space_get_west();

/**
 * @test Test function for space_object setting
 * @pre pointer to space, set and object. with add_id, add_object
 * @post Output==set_id
 */
void test1_space_get_object();

/**
 * @test Test function for space_object setting
 * @pre pointer to space, no object set
 * @post Output==NO_ID
 */
void test2_space_get_object();

/**
 * @test Test function for space_object setting
 * @pre pointer to space = NULL
 * @post Output==NO_ID
 */
void test3_space_get_object();

/**
 * @test Test function for space_add_object setting
 * @pre pointer to space, id
 * @post Output==OK
 */
void test1_space_add_object();

/**
 * @test Test function for space_add_object setting
 * @pre pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_add_object();


 
/**
 * @test Test function for space_set setting
 * @pre pointer to space, space_id
 * @post Non NULL pointer to set
 */
void test1_space_get_set();

/**
 * @test Test function for space_set setting
 * @pre pointer to space = NULL
 * @post Output==NULL
 */
void test2_space_get_set();


/**
 * @test Test function for space_gdesc1 setting
 * @pre pointer to space with space_gdesc1
 * @post Output==OK
 */
void test1_space_set_gdesc1();

/**
 * @test Test function for space_gdesc1 setting
 * @pre pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_gdesc1();

/**
 * @test Test function for space_gdesc1 setting
 * @pre pointer to space , string = NULL
 * @post Output==ERROR
 */
void test3_space_set_gdesc1();

/**
 * @test Test function for space_gdesc2 setting
 * @pre pointer to space with space_gdesc2
 * @post Output==OK
 */
void test1_space_set_gdesc2();

/**
 * @test Test function for space_gdesc2 setting
 * @pre pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_gdesc2();

/**
 * @test Test function for space_gdesc2 setting
 * @pre pointer to space , string = NULL
 * @post Output==ERROR
 */
void test3_space_set_gdesc2();

/**
 * @test Test function for space_gdesc3 setting
 * @pre pointer to space with space_gdesc3
 * @post Output==OK
 */
void test1_space_set_gdesc3();

/**
 * @test Test function for space_gdesc3 setting
 * @pre pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_gdesc3();

/**
 * @test Test function for space_gdesc2 setting
 * @pre pointer to space , string = NULL
 * @post Output==ERROR
 */
void test3_space_set_gdesc3();

/**
 * @test Test function for space_gdesc1 setting
 * @pre pointer to space with strcmp
 * @post Output==0
 */
void test1_space_get_gdesc1();

/**
 * @test Test function for space_gdesc1 setting
 * @pre pointer to space = NULL , with space_gdesc1
 * @post Output==NULL
 */
void test2_space_get_gdesc1();

/**
 * @test Test function for space_gdesc2 setting
 * @pre pointer to space with strcmp
 * @post Output==0
 */
void test1_space_get_gdesc2();

/**
 * @test Test function for space_gdesc2 setting
 * @pre pointer to space = NULL , with space_gdesc2
 * @post Output==NULL
 */
void test2_space_get_gdesc2();

/**
 * @test Test function for space_gdesc3 setting
 * @pre pointer to space with strcmp
 * @post Output==0
 */
void test1_space_get_gdesc3();

/**
 * @test Test function for space_gdesc3 setting
 * @pre pointer to space = NULL , with space_gdesc3
 * @post Output==NULL
 */
void test2_space_get_gdesc3();

/**
 * @test Test function for space_description setting
 * @pre pointer to space , with space_description
 * @post Output==OK
 */
void test1_space_set_description();

/**
 * @test Test function for space_description setting
 * @pre pointer to space = NULL , with space_description
 * @post Output==ERROR
 */
void test2_space_set_description();

/**
 * @test Test function for space_description setting
 * @pre pointer to space , with strcmp, set_description
 * @post Output==0
 */
void test1_space_get_description();

/**
 * @test Test function for space_description setting
 * @pre pointer to space = NULL 
 * @post Output==NULL
 */
void test2_space_get_description();

/**
 * @test Test function for space_north_available setting
 * @pre pointer to space and link , link_status, space_north
 * @post Output==TRUE
 */
void test1_is_north_available();

/**
 * @test Test function for space_north_available setting
 * @pre pointer to space = NULL
 * @post Output==FALSE
 */
void test2_is_north_available();

/**
 * @test Test function for space_south_available setting
 * @pre pointer to space and link , link_status, space_south
 * @post Output==TRUE
 */
void test1_is_south_available();

/**
 * @test Test function for space_south_available setting
 * @pre pointer to space = NULL
 * @post Output==FALSE
 */
void test2_is_south_available();

/**
 * @test Test function for space_east_available setting
 * @pre pointer to space and link , link_status, space_east
 * @post Output==TRUE
 */
void test1_is_east_available();

/**
 * @test Test function for space_east_available setting
 * @pre pointer to space = NULL
 * @post Output==FALSE
 */
void test2_is_east_available();

/**
 * @test Test function for space_west_available setting
 * @pre pointer to space and link , link_status, space_west
 * @post Output==TRUE
 */
void test1_is_west_available();

/**
 * @test Test function for space_west_available setting
 * @pre pointer to space = NULL
 * @post Output==FALSE
 */
void test2_is_west_available();

#endif
