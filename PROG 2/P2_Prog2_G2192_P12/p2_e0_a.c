/**
 * @file  p2_e0_a.c
 * @author Santiago Atrio, Daniel Varela
 * @date 2 Marzo 2020
 * @version 1.0
 * @brief Main ex0a
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#include "types.h"

int main (int argc, char* argv[]) {
  char letters[]={'a', 'b', 'c'};
  Stack *stack=NULL;
  int i=0;
  char *c;
  stack=stack_init(char_free, char_copy, char_print);
  for (i=0; i<3; i++) {
    stack_push(stack, letters+i);
  }
  stack_print(stdout, stack);
  fprintf(stdout, "Stack size: %ld", stack_size(stack));
  do {
    c=stack_pop(stack);
    printf("\nExtracted element: ");
    char_print(stdout, c);
    char_free(c);
  } while (!(stack_isEmpty(stack)));
  fprintf(stdout, "\nStack size: %ld\n", stack_size(stack));
  stack_free(stack);
  return (EXIT_SUCCESS);
}
