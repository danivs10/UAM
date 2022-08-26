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
#include "graph.h"
#include "node.h"

/*
 Initialise two nodes. The first one with name "first", id 111, and label
WHITE and the second one with name "second", id 222 and label WHITE.
• Initialise a graph.
• Insert node 1 and verify if the insertion was successful.
• Insert node 2 and verify if the insertion was successful.
• Insert a connection between node 2 and node 1.
• Check if node 1 is connected to node 2 (see message below).
• Check if node 2 is connected to node 1 (see message below).
• Insert node 2 and verify the result.
• Print the graph.
• Free the resources by destroying the nodes and the graph.
Output:
Inserting node 1... result...: 1
Inserting node 2... result...: 1
Inserting edge: node 2 ---> node 1
Connected node 1 and node 2? No
Connected node 2 and node 1? Yes
Inserting node 2... result...: 0
Graph
[first, 111, 0, 0]
[second, 222, 0, 1]111
 */
int main(int argc, char** argv) {
  Node *first, *second, *third;
  Graph *g;
  Status check;
  
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
  if(node_setNConnect (first, 0)==ERROR){
    fprintf(stdout, "ERROR INITIALIZING THE FIRST NODE CONNECTIONS!\n");
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
  if(node_setNConnect (second, 0)==ERROR){
    fprintf(stdout, "ERROR INITIALIZING THE SECOND NODE CONNECTIONS!\n");
    node_free(first);
    node_free(second);
    return EXIT_FAILURE;
  }
  
  /*Init the graph*/
  g=graph_init();
  if(g==NULL){
    node_free(first);
    node_free(second);
    return EXIT_FAILURE;
  }

  /*Inserting node 1 to the graph*/
  check=graph_insertNode(g, first);
  if (check==ERROR) {
    fprintf(stdout, "ERROR INSERTING THE FIRST NODE TO THE GRAPH!\n");
    graph_free(g);
    node_free(first);
    node_free(second);
    return EXIT_FAILURE;
  }
  printf("Inserting node 1... result...: ");
  printf("%d\n", check);

  /*Inserting node 2 to the graph*/
  check=graph_insertNode(g, second);
  if (check==ERROR) {
    fprintf(stdout, "ERROR INSERTING THE SECOND NODE TO THE GRAPH!\n");
    node_free(first);
    node_free(second);
    return EXIT_FAILURE;
  }
  printf("Inserting node 2... result...: ");
  printf("%d\n", check);

  /*Inserting edge from node 2 to node 1*/
  printf("Inserting edge: ");
  if (graph_insertEdge(g, node_getId(second), node_getId(first))==OK){
      printf("node 2 ---> node 1\n");
  } else {
      graph_free(g);
      fprintf(stdout, "ERROR WHEN INSERTING EDGE!\n");
      return EXIT_FAILURE;
  }

  /*Is node1 connected to node2 and viceversa?*/
  printf("Connected node 1 and node 2? ");
  if(graph_areConnected(g,  node_getId(first), node_getId(second))==TRUE){
      printf("Yes\n");
  } else printf("No\n");
  printf("Connected node 2 and node 1? ");
  if(graph_areConnected(g,  node_getId(second), node_getId(first))==TRUE){
      printf("Yes\n");
  } else printf("No\n");

  third=node_init();
  node_setId(third, 333);
  node_setLabel(third, 0);
  node_setName(third, "tercero");
  graph_insertNode(g, third);
  graph_insertEdge(g, node_getId(second), node_getId(third));

  /*Checking that you cannot insert a Node with the same Id as one you already have in the array*/
  check=graph_insertNode(g, second);
  printf("Inserting node 2... result...: ");
  printf("%d\n", check);
  
  /*Printing the graph*/
  printf("Graph\n");
  graph_print(stdout, g);
  node_free(first);
  node_free(second);
  node_free(third);
  graph_free(g);
  return (EXIT_SUCCESS);
}
