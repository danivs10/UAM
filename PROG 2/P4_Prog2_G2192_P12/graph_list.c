#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "graph_list.h"

#define MAX_NODES 1064

extern int errno;

struct _Graph { 
  List *plnode; /*!<List with the graph nodes */
  Bool connections[MAX_NODES][MAX_NODES]; /*!<Adjacency matrix */
  int num_nodes; /*!<Total number of nodes in the graph */
  int num_edges; /*!<Total number of connection in the graph */
} ;

/* PRIVATE FUNCTIONS DECLARATION */ 

int find_node_index(const Graph * g, long nId1);
int* graph_getConnectionsIndex(const Graph * g, int index);

/* PUBLIC FUNCTIONS */ 

Graph* graph_init () {
  Graph *g;
  int i, j;
  g=(Graph *)calloc(1, sizeof(Graph));
  if (g==NULL) {
    fprintf (stderr, "Value of errno for graph init: %s\n", strerror(errno));
    return NULL;
  }
  g->plnode=list_new(node_free, node_copy, node_print, node_cmp);
  if(!g->plnode){
    fprintf (stderr, "Value of errno for graph init: %s\n", strerror(errno));
    graph_free(g);
    return NULL;
  }
  g->num_edges=0;
  g->num_nodes=0;

  for (i=0; i<MAX_NODES; i++) {
    for (j=0; j<MAX_NODES; j++) {
      g->connections[i][j]=FALSE;
    }
  }
  return g;
}

void graph_free (Graph *g){
  if (g==NULL) return;
  list_free(g->plnode);
  free(g);
  return;
}

Status graph_insertNode (Graph *g, const Node *n){
  if (!g || !n) {
    fprintf (stderr, "Value of errno for insertNode 1: %s\n", strerror(errno));
    return ERROR;
  }
  if (find_node_index(g, node_getId(n))==-1) {
    if(list_pushFront(g->plnode, n)==ERROR){
      fprintf (stderr, "Value of errno for insertNode 2: %s\n", strerror(errno));
      return ERROR;
    }
    g->num_nodes++;
    return OK;
  } else {
    return ERROR;
  }	
}

Status graph_insertEdge (Graph *g, const long nId1, const long nId2){
  int index1=find_node_index(g, nId1), index2=find_node_index(g, nId2), pos=0;
  Node *n=NULL;
  if (!g || nId1==-1 || nId2==-1 || index1==-1 || index2==-1 || nId2==nId1) {
    return ERROR;
  }
  if (g->connections[index1][index2]==FALSE) {
    g->connections[index1][index2]=TRUE;
    g->num_edges++;
    pos= (g->num_nodes - 1) - index1;
    n = (Node*) list_getElementInPos(g->plnode, pos);
    if (n==NULL) return ERROR;
    node_setNConnect(n, 1 + node_getConnect(n));
  }
  return OK;
}

Node *graph_getNode (const Graph *g, long nId){
  Node *n, *ncopy;
  int index=find_node_index(g, nId), pos;
  if (!g || nId==-1) {
    fprintf (stderr, "Value of errno for getNode: %s\n", strerror(errno));
    return NULL;
  }
  pos=g->num_nodes -index -1;
  n=(Node*)list_getElementInPos(g->plnode, pos);
  ncopy = node_copy(n);
  return ncopy;
}

Status graph_setNode (Graph *g, const Node *n){
  Node *ncopy;
  int index=find_node_index(g, node_getId(n)), pos;
  if (!g || !n || index==-1){
    fprintf (stderr, "Value of errno for setNode: %s\n", strerror(errno));
    return ERROR;
  }
  pos = g->num_nodes - index - 1;
  ncopy=(Node*)list_getElementInPos(g->plnode, pos);
  node_setLabel(ncopy, node_getLabel(n));
  node_setNConnect(ncopy, node_getConnect(n));
  node_setName(ncopy, node_getName(n));
  node_setPredecessorId(ncopy, node_getPredecessorId(n));
  return OK;
}

long * graph_getNodesId (const Graph *g){
  long* arrayId=NULL;
  int i=0;
  Node *n=NULL;
  if (!g){
    fprintf (stderr, "Value of errno for getNodesId: %s\n", strerror(errno));
    return NULL;
  }
  arrayId=(long *)calloc(graph_getNumberOfNodes(g), sizeof(long));
  if (!arrayId){
    free(arrayId);
    fprintf (stderr, "Value of errno for getNodesId 2: %s\n", strerror(errno));
    return NULL;
  }
  for (i=0; i<g->num_nodes; i++){
      n=list_popFront(g->plnode);
      arrayId[i]=node_getId(n);
      list_pushBack(g->plnode, n);
      node_free(n);
  }
  return arrayId;
}

int graph_getNumberOfNodes (const Graph *g){
  if (!g){
    fprintf (stderr, "Value of errno for getNumberOfNodes: %s\n", strerror(errno));
    return -1;
  }
  return g->num_nodes;
}

int graph_getNumberOfEdges (const Graph *g){
  if (!g){
    fprintf (stderr, "Value of errno for getNumberOfEdges: %s\n", strerror(errno));
    return -1;
  }
  return g->num_edges;
}

Bool graph_areConnected (const Graph *g, const long nId1, const long nId2){
  int index1=find_node_index(g, nId1), index2=find_node_index(g, nId2);
  if (!g || nId1==-1 || nId2==-1 || index1==-1 || index2==-1) return FALSE;
  if (g->connections[index1][index2]==TRUE){
    return TRUE;
  }
  return FALSE;
}

int graph_getNumberOfConnectionsFrom (const Graph *g, const long fromId){
  int index=find_node_index(g, fromId), pos;
  Node *n;
  if (g==NULL || fromId==-1 || index==-1) {
    fprintf (stderr, "Value of errno for getNumberOfConnectionsFrom: %s\n", strerror(errno));
    return -1;
  }
  pos=g->num_nodes - 1 - index;
  n=(Node*) list_getElementInPos(g->plnode, pos);
  return node_getConnect(n);
}

long* graph_getConnectionsFrom (const Graph *g, const long fromId){
  Node *n;
  long *arrayConnectionsFrom;
  int a=graph_getNumberOfConnectionsFrom(g, fromId), i=0, narray, index=find_node_index(g, fromId), pos;
  if (g==NULL || fromId==-1 || index==-1){
    fprintf (stderr, "Value of errno for getConnectionsFrom: %s\n", strerror(errno));
    return NULL;
  }
  arrayConnectionsFrom=(long *)calloc(graph_getNumberOfConnectionsFrom(g, fromId), sizeof(long));
  for (i=0, narray=0; narray<a && i<MAX_NODES; i++){
    if (g->connections[index][i]==TRUE){
      pos=g->num_nodes-i-1;
      n=(Node*)list_getElementInPos(g->plnode, pos);
      arrayConnectionsFrom[narray]=node_getId(n);
       narray++;
	  }
  }
  return arrayConnectionsFrom;
}

int graph_print (FILE *pf, const Graph *g){
  Node *na, *ni;
  int a, i, ch, posa;
  if (!g) {
    fprintf (pf, "Value of errno for printgraph: %s\n", strerror(errno));
    return -1;
  }
  for (i=0; i<g->num_nodes; i++){
    ni=(Node*)list_getElementInPos(g->plnode, i);
    ch=node_print(pf, ni);
      for (a=0; a<g->num_nodes; a++){
        posa=g->num_nodes-a-1;
        na=(Node*)list_getElementInPos(g->plnode, posa);
        if(graph_areConnected(g, node_getId(ni), node_getId(na))==TRUE){
	        ch+=fprintf (pf, " %ld ", node_getId(na));
        }
      }
      fprintf(pf, "\n");
    }
  return ch;
}

Status graph_readFromFile (FILE *fin, Graph *g){
  Node *n;
  char name[64];
  int i, numNodes=0;
  long id1, id2, id;
  int label =0;
  if(fin==NULL || g==NULL){
    fprintf(stderr, "Value of errno for readFromFile: %s\n", strerror(errno));
    return ERROR;
  }
  fscanf(fin, "%d", &numNodes);
  for (i=0 ; i<numNodes ; i++){
    n=node_init();
    fscanf(fin, "%ld %s %d", &id, name, &label);
    node_setId(n, id);
    node_setName(n, name);
    node_setLabel(n, label);
    graph_insertNode(g, n);
    node_free(n);
  }
  while (fscanf(fin, "%ld %ld", &id1, &id2)==2){
    graph_insertEdge(g, id1, id2);
  }
  return OK;
}

/* PRIVATE FUNCTIONS IMPLEMENTATION*/ 

int find_node_index(const Graph * g, long nId1) {
  int i, pos;
  if (g==NULL) return -1;
  for (i=0; i<g->num_nodes; i++) {
    if (node_getId(list_getElementInPos(g->plnode, i))==nId1) {
      pos = g->num_nodes -1 -i;
      return pos;
    }
  }
  return -1;
}

int* graph_getConnectionsIndex(const Graph * g, int index) {
  int *array = NULL, i, j = 0, size, pos;
  if (!g) return NULL;
  if (index < 0 || index >g->num_nodes) return NULL;
  pos=g->num_nodes-index-1;
  size = node_getConnect ((Node*)list_getElementInPos(g->plnode, pos));
  array = (int *) malloc(sizeof (int) * size); 
  if (!array) {
    fprintf (stderr, "%s\n", strerror(ERROR)); 
    return NULL;
  }
  for(i = 0; i< g->num_nodes; i++) {
    if (g->connections[index][i] == TRUE) {
      array[j++] = i;
    }
  }
  return array;
}