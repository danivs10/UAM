#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "graph_list.h"
#include "queue_fp.h"

#define MAXSTRING 65536

Status graph_breadthFirst(Graph *pg, long ini_id, long end_id, char *nodestraversed){
  Queue *q=NULL;
  Node *aux=NULL;
  Node *aux2=NULL;
  Status st=OK;
  int i=0;
  long *connectedNodes=NULL;
  q=queue_init(node_free, node_copy, node_print);
  if (q==NULL) {
    st=ERROR;
    return st;
  }
  aux=graph_getNode(pg, ini_id);
  if (aux==NULL) {
    st=ERROR;
    queue_free(q);
    return st;
  } 
  st=node_setLabel(aux, BLACK);
  if (st==ERROR) {
    queue_free(q);
    node_free(aux);
    return st;
  }
  st=graph_setNode(pg, aux);
  if (st==ERROR) {
    queue_free(q);
    node_free(aux);
    return st;
  }
  st=queue_insert(q, aux);
  if (st==ERROR) {
    queue_free(q);
    node_free(aux);
    return st;
  }
  node_free(aux);
  while(queue_isEmpty(q)==FALSE){
    aux=queue_extract(q);
    nodestraversed = strcat(nodestraversed, node_getName(aux));
    nodestraversed = strcat(nodestraversed, "  ");
      if(node_getId(aux)==end_id){
        node_free(aux);
        queue_free(q);
        return st;
      } else {
        connectedNodes = graph_getConnectionsFrom(pg, node_getId(aux));
        if (connectedNodes==NULL){
          st=ERROR;
          queue_free(q);
          node_free(aux);
          return st;
        }
        for(i=0; i<graph_getNumberOfConnectionsFrom(pg, node_getId(aux)); i++){
          aux2=graph_getNode(pg, connectedNodes[i]);
          if (aux2==NULL){
            st=ERROR;
            queue_free(q);
            node_free(aux);
            free(connectedNodes);
            return st;
          }
          if (node_getLabel(aux2)==WHITE){
            st=node_setLabel(aux2, BLACK);
            if (st==ERROR){
              queue_free(q);
              node_free(aux);
              node_free(aux2);
              free(connectedNodes);
              return st;
            }
            st=graph_setNode(pg, aux2);
            if (st==ERROR){
              queue_free(q);
              node_free(aux);
              node_free(aux2);
              free(connectedNodes);
              return st;
            }
            st=queue_insert(q, aux2);
            if (st==ERROR){
              queue_free(q);
              node_free(aux);
              node_free(aux2);
              free(connectedNodes);
              return st;
            }
          }
          node_free(aux2);
        }
        free(connectedNodes);
      }
    node_free(aux);
  }
  queue_free(q);
  return st;
}

int main (int argc, char *argv[]) {
  Graph *g=NULL;
  FILE *f=NULL;
  long ini_id, end_id;
  char ntraveled[MAXSTRING]=" ";

  if (argc != 4) {
    fprintf(stdout, "Error when calling function. Try this: <./mainfile graphfile>\n");
    return EXIT_FAILURE;
  }

  /* Initiate the graph, queue and file */
  g=graph_init();
  if (g==NULL) {
    return EXIT_FAILURE;
  }
  f=fopen(argv[1], "r");
  if (f==NULL) {graph_free(g);
    return EXIT_FAILURE;
  }
  ini_id=strtol(argv[2], NULL, 10);
  end_id=strtol(argv[3], NULL, 10);

  /* Read the graph */
  if (graph_readFromFile(f, g)==ERROR) {
    fclose(f);
    graph_free(g);
    return EXIT_FAILURE;
  }

  if (graph_breadthFirst(g, ini_id, end_id, ntraveled)==OK){
    fprintf(stdout, "%s\n", ntraveled);
  }

  fclose(f);
  graph_free(g);
  return 0;
}
