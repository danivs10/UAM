/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   p1_e1.c
 * Author: eps
 *
 * Created on 12 de febrero de 2020, 15:07
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

/*
 * 
 */
int main() {
  Node *first, *second;

  /*Init the first node*/
  first = node_init ();
  if (first==NULL) {
    fprintf(stderr, "ERROR INITIALIZING THE FIRST NODE!\n");
    return EXIT_FAILURE;
  }
  if(node_setId (first, 111)==ERROR){ 
    fprintf(stdout, "ERROR INITIALIZING THE FIRST NODE ID!\n");
    node_free(first);
    return EXIT_FAILURE;
  }
  if(node_setName (first, "first")==ERROR){
    fprintf(stdout, "ERROR INITIALIZING THE FIRST NODE NAME!\n");
    node_free(first);
    return EXIT_FAILURE;
  }
  if(node_setLabel (first, WHITE)==ERROR){
    fprintf(stdout, "ERROR INITIALIZING THE FIRST NODE LABEL!\n");
    node_free(first);
    return EXIT_FAILURE;
  }
  
  /*Init the second node*/
  second = node_init ();
  if (second==NULL){
    fprintf(stdout, "ERROR INITIALIZING THE SECOND NODE!\n");
    node_free(first);
    return EXIT_FAILURE;
  }
  if(node_setId (second, 222)==ERROR){
    fprintf(stdout, "ERROR INITIALIZING THE SECOND NODE ID!\n");
    node_free(first);
    node_free(second);
    return EXIT_FAILURE;
  }
  if(node_setName (second, "second")==ERROR){
    fprintf(stdout, "ERROR INITIALIZING THE SECOND NODE NAME!\n");
    node_free(first);
    node_free(second);
    return EXIT_FAILURE;
  }
  if(node_setLabel (second, WHITE)==ERROR){
    fprintf(stdout, "ERROR INITIALIZING THE SECOND NODE LABEL!\n");
    node_free(first);
    node_free(second);
    return EXIT_FAILURE;
  }

  node_print(stdout, first);
  node_print(stdout, second);
  fprintf(stdout, "\nAre they equal?");
  if (node_cmp(first, second)!=0){
      fprintf(stdout, " No\n");
  } else {
      fprintf(stdout, " Yes\n");
  }
  fprintf(stdout, "Id of first node: %ld\n", node_getId(first));
  fprintf(stdout, "Name of first node: %s\n", node_getName(first));
  node_free(second);
  second = node_copy (first);
  if (second==NULL){
    fprintf(stderr, "ERROR COPYING THE NODE!\n");
    return EXIT_FAILURE;
  }
  node_print(stdout, first);
  node_print(stdout, second);
  printf("\nAre they equal?");
  if (node_cmp(first, second)!=0){
      printf(" No\n");
  } else {
      printf(" Yes\n");
  }
  node_free(first);
  node_free(second);
  return (EXIT_SUCCESS);
}
