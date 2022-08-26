/*
* File: stack.h
* Author: Profesores de PROG2
*/
#ifndef STACK_H
#define STACK_H

#include <string.h>
#include "element.h"

typedef struct _Stack Stack;

/**
* @brief Initialices the stack
* @return Returns pointer to the stack
*/
Stack * stack_init ();

/**
* @brief Frees the node
* @param s is a pointer to the stack
*/
void stack_free(Stack *s);

/**
* @brief Pushes an element to the stack
* @param s is a pointer to the stack
* @param ele is a pointer to the element
* @return Returns OK if everything has gonne right and ERROR otherwise
*/
Status stack_push(Stack *s, const Element *ele);

/**
* @brief Pops an element from the stack
* @param s is a pointer to the stack
* @return Returns a pointer to the poped element
*/
Element * stack_pop(Stack *s);

/**
* @brief Gets the top element of the stack without changeing it
* @param s is a pointer to the stack
* @return Returns a pointer to the top element of the stack
*/
Element * stack_top(const Stack *s);

/**
* @brief Checks if the stack is Empty or not
* @param s is a pointer to the stack
* @return Returns TRUE if the stack is Empty or FALSE otherwise
*/
Bool stack_isEmpty(const Stack *s);

/**
* @brief Checks if the stack is Full or not
* @param s is a pointer to the stack
* @return Returns TRUE if the stack is Full or FALSE otherwise
*/
Bool stack_isFull(const Stack *s);

/**
* @brief Prints the stack
* @param file is a pointer to the file (should have been opened before)
* @param s is a pointer to the stack
* @return Returns the label of a given node, or -1 in case of error
*/
int stack_print(FILE *file, const Stack *s);

/**
* @brief Returns the stack size
* @param s is a pointer to the stack
* @return Returns the the stack size. If the stack doesn't exist it returns -1
*/
int stack_size(Stack *s);



#endif /* STACK_H */
