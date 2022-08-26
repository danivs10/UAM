/**
 * @file  p2_e0_b.c
 * @author Santiago Atrio, Daniel Varela
 * @date 2 Marzo 2020
 * @version 1.0
 * @brief Main ex0b
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "stack_fp.h"
#include "types.h"

int main (int argc, char* argv[]) {
  /* Initializing variables */
  Node *n=NULL, *aux=NULL;
  Stack *stackStrings, *stackNodes;
  char *str;
  /* Initializing First node */ 
  n=node_init();
  if (n==NULL) return EXIT_FAILURE;
  if (node_setId(n,111)==ERROR) return EXIT_FAILURE;
  if (node_setName(n,"First")==ERROR) return EXIT_FAILURE; 
  if (node_setLabel(n,WHITE)==ERROR) return EXIT_FAILURE; 
  /* Initializing the stacks */
  stackStrings=stack_init(string_free, string_copy, string_print);
  stackNodes=stack_init(node_free, node_copy, node_print);
  if (stack_push(stackNodes, n)==ERROR) return EXIT_FAILURE;
  if (stack_push(stackStrings, node_getName(n))==ERROR) return EXIT_FAILURE;
  /* Initializing Second node */ 
  if (node_setId(n,222)==ERROR) return EXIT_FAILURE;
  if (node_setName(n,"Second")==ERROR) return EXIT_FAILURE; 
  if (node_setLabel(n,WHITE)==ERROR) return EXIT_FAILURE;
  if (stack_push(stackNodes, n)==ERROR) return EXIT_FAILURE;
  if (stack_push(stackStrings, node_getName(n))==ERROR) return EXIT_FAILURE;
  /* Printhing the nodes */
  printf("Print stack nodes: \n");
  stack_print(stdout, stackNodes);
  /* Printing the names of the nodes */
  printf("Print stack strings: \n");
  stack_print(stdout, stackStrings);
  /* Poping all the nodes */
  printf("\nPoping nodes . . . \n");
  do {
    aux=stack_pop(stackNodes);
    node_print(stdout, aux);
    printf(" ");
    node_free(aux);
  } while (!(stack_isEmpty(stackNodes)));
  fprintf(stdout, "\n");
  /* Poping all node names */
  printf("Poping nodes-names . . . \n");
  do {
    str=stack_pop(stackStrings);
    string_print(stdout, str);
    printf(" ");
    string_free(str);
  } while (!(stack_isEmpty(stackStrings)));
  /* Free all used allocations */
  fprintf(stdout, "\n");
  node_free(n);
  stack_free(stackNodes);
  stack_free(stackStrings);
  return(EXIT_SUCCESS);
}