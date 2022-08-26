/*
* File: element.h
* Author: Profesores de PROG2
*/

#ifndef ELEMENT_H
#define ELEMENT_H

#include <string.h>
#include <stdio.h>
#include "types.h"

typedef struct _Element Element;

/**
* @brief Initialices an element
* @return Returns a pointer to the initialiced element
*/
Element * element_init();

/**
* @brief Frees the element
* @param ele is a pointer to the element
*/
void element_free(Element *ele);

/**
* @brief Sets the info of the element
* @param ele is a pointer to the element
* @param info is a pointer to the information to be setted
* @return Returns a pointer to the new element
*/
Element * element_setInfo(Element *ele, void *info);

/**
* @brief Gets the info of the element
* @param ele is a pointer to the element
* @return Returns a pointer to the poped element
*/
void * element_getInfo(Element *ele);

/**
* @brief Creates a copy of the element
* @param ele is a pointer to the element to be copyed
* @return Returns a pointer to the new element (copyed from the arg)
*/
Element * element_copy(const Element *ele);

/**
* @brief Checks if two elements are the same
* @param ele1 is a pointer to one element
* @param ele2 is a pointer to the other element
* @return Returns TRUE if both elements are the same and FALSE otherwise
*/
Bool element_equals(const Element *ele1, const Element *ele2);

/**
* @brief Prints an element
* @param fil is a pointer to the file (should be oppened before)
* @param ele is a pointer to the element
* @return Returns the number of characters that have been printed
*/
int element_print(FILE *fil, const Element *ele);

#endif /* ELESTACK_H */