#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "graph_list.h"
#include "tree.h"

int main (int argc, char *argv[]) {
  Graph *g=NULL;
  Node *n;
  FILE *f=NULL;
  BSTree *t=NULL;
  Status st;
  long *ids;
  int i;

  if (argc != 2) {
    fprintf(stdout, "Error when calling the function. Try this: <./mainfile graphfile>\n");
    return EXIT_FAILURE;
  }

  /* Initiate the graph */
  g=graph_init();
  if (g==NULL) {
    fprintf(stdout, "Error initiating the file\n");
    return EXIT_FAILURE;
  }

  /* Initiate the tree */
  t=tree_init(node_free, node_copy, node_print, node_cmp);
  if (t==NULL) {
    fprintf(stdout, "Error when initiating the file\n");
    graph_free(g);
    return EXIT_FAILURE;
  }

  /* Open the file in read form */
  f=fopen(argv[1], "r");
  if (f==NULL) {
    fprintf(stdout, "Error opening the file ggask\n");
    graph_free(g);
    tree_destroy(t);
    return EXIT_FAILURE;
  }

  /* Read the file and create the graph */
  if (graph_readFromFile(f, g)==ERROR) {
    fprintf(stdout, "Error when reading the file\n");
    tree_destroy(t);
    fclose(f);
    graph_free(g);
    return EXIT_FAILURE;
  }

  /* Print the graph */
  graph_print(stdout, g);
  fprintf(stdout, "\n");

  /* Pass al nodes from the graph to the tree */
  ids=graph_getNodesId(g);
  for (i=0; i<graph_getNumberOfNodes(g); i++) {
    n=graph_getNode(g, ids[i]);
    st=tree_insert(t, n);
    node_free(n);
    if (st==ERROR) {
      fprintf(stdout, "Error when reading the file\n");
      tree_destroy(t);
      fclose(f);
      graph_free(g);
      return EXIT_FAILURE;
    }
  }

  /* Post Order Transversal */
  tree_postOrder(stdout, t);

  /* Pre Order Transversal */
  tree_preOrder(stdout, t);

  /* In Order Transversal */
  tree_inOrder(stdout, t);

  /* Freing memory */
  graph_free(g);
  free(ids);
  tree_destroy(t);
  fclose(f);
  return EXIT_SUCCESS;
}

