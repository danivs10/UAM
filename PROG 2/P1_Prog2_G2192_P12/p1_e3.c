#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "graph.h"
#include "node.h"
#include "types.h"

extern int errno;

#define MAX_FILE_NAME 200
/*
 Initialise a graph pointer and opens a filethat will be sent to the graph_read_from file
 function, datas will be storaged in the graph pointer and then, all graph will be
 printed, includeing their respective nodes.
• Initialise a graph.
• Opens a file
• Calls read_from_file and storage all values on the pointer
• Print the graph.
• Free the resources by destroying the nodes and the graph.
Output:
Graph
[a, 1, 0, 2]
[b, 2, 0, 1]
[c, 3, 0, 0]
 */

int main (int argc, char* argv[]){
  Graph *g;
  FILE *f;
  char fileName[MAX_FILE_NAME];

  if (argc<2){
    fprintf(stdout, "NEEDS THE NAME OF A FILE AS AN ARGUMENT!\n");
    return EXIT_FAILURE;
  }

  strcpy(fileName, argv[1]);

  g=graph_init();
  if (g==NULL) {
    fprintf(stderr, "Value of errno for graph init: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  f=fopen(fileName, "r");
  if (f==NULL) {
    fprintf(stderr, "Value of errno for fopen: %s\n", strerror(errno));
    graph_free(g);
    return EXIT_FAILURE;
  }

  if(graph_readFromFile(f, g)==ERROR) {
    graph_print(stdout, g);
    fprintf(stderr, "Value of errno for readFromFile: %s\n", strerror(errno));
    graph_free(g);
    fclose(f);
    return EXIT_FAILURE;
  }

  fprintf(stdout, "Graph:\n");
  graph_print(stdout, g);
  fclose(f);
  graph_free(g);
  return EXIT_SUCCESS;
}