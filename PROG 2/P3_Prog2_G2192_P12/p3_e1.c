#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "node.h"
#include "graph.h"
#include "queue_fp.h"

#define interal errno

int main (int argc, char *argv[]) {
  Graph *g=NULL;
  Node *aux=NULL;
  Queue *q=NULL;
  FILE *f=NULL;
  Status check1=OK, check2=OK, check3=OK;
  long *ids;
  int i;

  if (argc < 2) {
    fprintf(stdout, "Error when calling function. Try this: <./mainfile graphfile>\n");
    return EXIT_FAILURE;
  }

  /* Initiate the graph, queue and file */
  g=graph_init();
  if (g==NULL) {
    fprintf(stderr, "Value of errno: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  q=queue_init(node_free, node_copy, node_print);
  if (q==NULL) {
    fprintf(stderr, "Value of errno: %s\n", strerror(errno));
    graph_free(g);
    return EXIT_FAILURE;
  }
  f=fopen(argv[1], "r");
  if (f==NULL) {
    fprintf(stderr, "Value of errno: %s\n", strerror(errno));
    queue_free(q);
    graph_free(g);
    return EXIT_FAILURE;
  }

  /* Read the graph */
  if (graph_readFromFile(f, g)==ERROR) {
    fclose(f);
    graph_free(g);
    queue_free(q);
    return EXIT_FAILURE;
  }

  /* Insert all nodes into the queue and change & 
  *  all Labels from the nodes of the graph to BLACK 
  */  
  ids=graph_getNodesId(g);
  for (i=0; i<graph_getNumberOfNodes(g) && check1==OK && check2==OK && check3==OK; i++) {
    aux=graph_getNode(g, ids[i]);
    check1=queue_insert(q, aux);
    check2=node_setLabel(aux, BLACK);
    check3=graph_setNode(g, aux);
    node_free(aux);
  }
  
  /* Exit if any error ocurred in the previous part */
  if (check1==ERROR || check2==ERROR || check3==ERROR){
    fprintf(stdout, "There was some error when inserting the nodes into the queue and changeing the Labels to Black\n");
    fclose(f);
    free(ids);
    graph_free(g);
    queue_free(q);
    return EXIT_FAILURE;
  }

  /* Print the graph */
  fprintf(stdout, "Nodes in Graph:\n");
  graph_print(stdout, g);
  fprintf(stdout, "\n");

  /* Print the queue */
  fprintf(stdout, "Nodes in Queue:\n");
  queue_print(stdout, q);
  fprintf(stdout, "\n");

  /* Print the size of the queue */
  fprintf(stdout, "Queue size: %d\n\n", queue_size(q));

  /* Pop one element of the queue */
  while (queue_size(q)>0) {
    fprintf(stdout, "Extracted element:\n");
    aux=queue_extract(q);
    node_print(stdout ,aux);
    fprintf(stdout, "\n");
    node_free(aux);
  }

  /* Print the size of the queue (with one element poped) */
  fprintf(stdout, "Queue size: %d\n", queue_size(q));

  free(ids);
  graph_free(g);
  queue_free(q);
  fclose(f);
  return EXIT_SUCCESS;
}