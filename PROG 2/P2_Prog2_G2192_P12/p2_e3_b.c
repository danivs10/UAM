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
#include "element.h"
#include "stack.h"
#include "types.h"

int main (int argc, char* argv[]) {
  Stack *stack=NULL;
  Element *c, *ele;
  char letters[]={'a', 'b', 'c'};
  int i=0;
  stack=stack_init();
  for (i=0; i<3; i++) {
    ele=element_init();
    ele=element_setInfo(ele, (void *)(letters+i));
    stack_push(stack, ele);
    element_free(ele);
  }
  stack_print(stdout, stack);
  fprintf(stdout, "Stack size: %d\n", stack_size(stack));
  do {
    c=stack_pop(stack);
    printf("Extracted element: ");
    element_print(stdout, c);
    element_free(c);
  } while (!(stack_isEmpty(stack)));
  fprintf(stdout, "Stack size: %d\n", stack_size(stack));
  stack_free(stack);
  return (EXIT_SUCCESS);
}
