/**
 * @brief It defines common types
 *
 * @file types.h
 * @author Daniel Varela and Aran Rodrigo
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1


/*
* @brief Defines id structure
* @author Daniel Varela and Aran Rodrigo
* Ids are long variables
*/
typedef long Id;

/*
* @brief Defines BOOL structure
* @author Daniel Varela and Aran Rodrigo
* Bools are TRUE or FALSE
*/
typedef enum {
  FALSE, TRUE
} BOOL;

/*
* 
* @brief Defines status structure
* @author Daniel Varela and Aran Rodrigo
* Status are ok or error
*/
typedef enum {
  ERROR, OK
} STATUS;

/*
* @brief Defines directions
* @author Daniel Varela and Aran Rodrigo
* Directions are north, south, east and west
*/
typedef enum {
  N, S, E, W
} Direction;


/*
* 
* @brief Defines status of a link
* @author Daniel Varela 
* Status are OPEN or CLOSED
*/
typedef enum {
  CLOSED, OPEN
} openStatus;

#endif
