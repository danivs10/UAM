#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "graph.h"
#include "queue_fp.h"
#include "stack_fp.h"

#define MAXSTRING 65536

/** graph_deepFirst:
* @brief This function implements the DFS algorithm starting
* from the node with id ini_id
* @param pg, Graph
* @param ini_id, Origin node Id
* @param end_id, Destination node Id
* @param path, String with the traversed node's name.
* This parameter is modified by the function.
**/
Status graph_deepFirst (Graph *pg, long ini_id, long end_id, char *nodestraversed){
  Stack *s=NULL;
  Node *aux=NULL;
  Node *aux2=NULL;
  Status st=OK;
  int i=0;
  long *connectedNodes=NULL;
  s=stack_init(node_free, node_copy, node_print);
  if (s==NULL) {
    st=ERROR;
    return st;
  }
  aux=graph_getNode(pg, ini_id);
  if (aux==NULL) {
    st=ERROR;
    stack_free(s);
    return st;
  } 
  st=node_setLabel(aux, BLACK);
  if (st==ERROR) {
    stack_free(s);
    node_free(aux);
    return st;
  }
  st=graph_setNode(pg, aux);
  if (st==ERROR) {
    stack_free(s);
    node_free(aux);
    return st;
  }
  st=stack_push(s, aux);
  if (st==ERROR) {
    stack_free(s);
    node_free(aux);
    return st;
  }
  node_free(aux);
  while(stack_isEmpty(s)==FALSE){
    aux=stack_pop(s);
    nodestraversed = strcat(nodestraversed, node_getName(aux));
    nodestraversed = strcat(nodestraversed, "  ");
      if(node_getId(aux)==end_id){
        node_free(aux);
        stack_free(s);
        return st;
      } else {
        connectedNodes = graph_getConnectionsFrom(pg, node_getId(aux));
        if (connectedNodes==NULL){
          st=ERROR;
          stack_free(s);
          node_free(aux);
          return st;
        }
        for(i=0; i<graph_getNumberOfConnectionsFrom(pg, node_getId(aux)); i++){
          aux2=graph_getNode(pg, connectedNodes[i]);
          if (aux2==NULL){
            st=ERROR;
            stack_free(s);
            node_free(aux);
            free(connectedNodes);
            return st;
          }
          if (node_getLabel(aux2)==WHITE){
            st=node_setLabel(aux2, BLACK);
            if (st==ERROR){
              stack_free(s);
              node_free(aux);
              node_free(aux2);
              free(connectedNodes);
              return st;
            }
            st=node_setPredecessorId(aux2, node_getId(aux));
            if (st==ERROR){
              stack_free(s);
              node_free(aux);
              node_free(aux2);
              free(connectedNodes);
              return st;
            }
            st=graph_setNode(pg, aux2);
            if (st==ERROR){
              stack_free(s);
              node_free(aux);
              node_free(aux2);
              free(connectedNodes);
              return st;
            }
            st=stack_push(s, aux2);
            if (st==ERROR){
              stack_free(s);
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
  stack_free(s);
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
  g=graph_init();
  if (g==NULL) return EXIT_FAILURE;
  f=fopen(argv[1], "r");
  if (f==NULL) {
    graph_free(g);
    return EXIT_FAILURE;
  }
  ini_id=strtol(argv[2], NULL, 10);
  end_id=strtol(argv[3], NULL, 10);
  if (graph_readFromFile(f, g)==ERROR) {
    fclose(f);
    graph_free(g);
    return EXIT_FAILURE;
  }
  if (graph_deepFirst(g, ini_id, end_id, ntraveled)==OK){
    fprintf(stdout, "%s\n", ntraveled);
  }
  fclose(f);
  graph_free(g);
  return 0;
}