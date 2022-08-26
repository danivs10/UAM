#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "graph.h"

#define MAX_NODES 4096

extern int errno;

struct _Graph { 
  Node *nodes[MAX_NODES]; /*!<Array with the graph nodes */
  Bool connections[MAX_NODES][MAX_NODES]; /*!<Adjacency matrix */
  int num_nodes; /*!<Total number of nodes in the graph */
  int num_edges; /*!<Total number of connection in the graph */
} ;

/* PRIVATE FUNCTIONS DECLARATION */ 

int find_node_index(const Graph * g, long nId1);
int* graph_getConnectionsIndex(const Graph * g, int index);

/* PUBLIC FUNCTIONS */ 

Graph* graph_init (){
  Graph *g;
  int i, j;
  g=(Graph *)calloc(1, sizeof(Graph));
  if (g==NULL) {
    fprintf (stderr, "Value of errno for graph init: %s\n", strerror(errno));
    return NULL;
  }
  for (i=0; i<MAX_NODES; i++) {
    g->nodes[i]=NULL;
  }
  for (i=0; i<MAX_NODES; i++) {
    for (j=0; j<MAX_NODES; j++) {
      g->connections[i][j]=FALSE;
    }
  }
  g->num_edges=0;
  g->num_nodes=0;
  return g;
}

void graph_free (Graph *g){
  int i;
  if (g==NULL) return;
  for (i=0; i<g->num_nodes; i++){
    node_free(g->nodes[i]);
    g->nodes[i]=NULL;
  }
  free(g);
  return;
}

Status graph_insertNode (Graph *g, const Node *n){
  Node *ncopy;
  if (!g || !n) {
    fprintf (stderr, "Value of errno for insertNode 1: %s\n", strerror(errno));
    return ERROR;
  }
  ncopy = (Node *)node_copy(n);
  if (find_node_index(g, node_getId(ncopy))==-1) {
    g->nodes[g->num_nodes]=ncopy;
    g->num_nodes++;
    return OK;
  } else {
    node_free(ncopy);
  }
  return ERROR;	
}

Status graph_insertEdge (Graph *g, const long nId1, const long nId2){
  int index1=find_node_index(g, nId1), index2=find_node_index(g, nId2);
  if (!g || nId1==-1 || nId2==-1 || index1==-1 || index2==-1 || nId2==nId1) return ERROR;
  if (g->connections[index1][index2]==FALSE) {
    g->connections[index1][index2]=TRUE;
    g->num_edges++;
  }
  if(node_setNConnect(g->nodes[index1], node_getConnect(g->nodes[index1])+1)==ERROR) return ERROR;
  return OK;
}

Node *graph_getNode (const Graph *g, long nId){
  Node *ncopy;
  int index=find_node_index(g, nId);
  if (!g || nId==-1 || index==-1) {
    fprintf (stderr, "Value of errno for getNode: %s\n", strerror(errno));
    return NULL;
  }
  ncopy = node_copy(g->nodes[index]);
  return ncopy;
}

Status graph_setNode (Graph *g, const Node *n){
  Node *ncopy;
  int index=find_node_index(g, node_getId(n));
  if (!g || !n || index==-1){
    fprintf (stderr, "Value of errno for setNode: %s\n", strerror(errno));
    return ERROR;
  }
  ncopy=node_copy(n);
  g->nodes[index]=ncopy;
  return OK;
}

long * graph_getNodesId (const Graph *g){
  long* arrayId;
  int i=0, a=0;
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
  for (i=0; i<graph_getNumberOfNodes(g); i++){
    arrayId[a]=node_getId(g->nodes[i]);
	  a++;
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
  int a=0, i, index=find_node_index(g, fromId);
  if (g==NULL || fromId==-1 || index==-1) {
    fprintf (stderr, "Value of errno for getNumberOfConnectionsFrom: %s\n", strerror(errno));
    return -1;
  }
  for (i=0; i<g->num_nodes; i++){
    if (g->connections[index][i]==1){
	    a++;
    }
  }
  return a;
}

long* graph_getConnectionsFrom (const Graph *g, const long fromId){
  long *arrayConnectionsFrom;
  int a=0, i=0, index=find_node_index(g, fromId);
  if (g==NULL || fromId==-1 || index==-1){
    fprintf (stderr, "Value of errno for getConnectionsFrom: %s\n", strerror(errno));
    return NULL;
  }
  arrayConnectionsFrom=(long *)calloc(graph_getNumberOfConnectionsFrom(g, fromId), sizeof(long));
  for (i=0, a=0; i<g->num_nodes; i++){
    if (g->connections[index][i]==1){
      arrayConnectionsFrom[a]=node_getId(g->nodes[i]);
	    a++;
	  }
  }
  return arrayConnectionsFrom;
}

int graph_print (FILE *pf, const Graph *g){
  long *connectionsFrom;
  int a, i, ch;
  if (!g) {
    fprintf (pf, "Value of errno for printgraph: %s\n", strerror(errno));
    return -1;
  }
  for (i=0; i<g->num_nodes; i++){
    ch=node_print(stdout, g->nodes[i]);
    connectionsFrom = graph_getConnectionsFrom(g, node_getId(g->nodes[i]));
    if (connectionsFrom==NULL){
      fprintf (stderr, "Value of errno for printgraph 2: %s\n", strerror(errno));
      return -1;
    }
    if(node_getConnect(g->nodes[i])==-1){
      free(connectionsFrom);
      fprintf (stderr, "Value of errno for printgraph 3: %s\n", strerror(errno));
      return -1;
    }
    for (a=0; a<node_getConnect(g->nodes[i]); a++){
	    ch=+fprintf (pf, " %ld ", connectionsFrom[a]);
    }
    free(connectionsFrom);
    fprintf(pf, "\n");
    }
  return ch;
}

Status graph_readFromFile (FILE *fin, Graph *g){
  Node *n =NULL;
  char name[64];
  int i, numNodes=0;
  long id1, id2, id;
  int label =0;
  if(fin==NULL || g==NULL){
    fprintf(stderr, "Value of errno for readFromFile: %s\n", strerror(errno));
    return ERROR;
  }
  fscanf(fin, "%d", &numNodes);
  n=node_init();
  for (i=0 ; i<numNodes ; i++){
    fscanf(fin, "%ld %s %d", &id, name, &label);
    node_setId(n, id);
    node_setName(n, name);
    node_setLabel(n, label);
    graph_insertNode(g, n);
  }
  node_free(n);
  while (fscanf(fin, "%ld %ld", &id1, &id2)==2){
    graph_insertEdge(g, id1, id2);
  }
  return OK;
}

/* PRIVATE FUNCTIONS IMPLEMENTATION*/ 

int find_node_index(const Graph * g, long nId1) {
  int i;
  if (!g) return -1;
  for(i=0; i < g->num_nodes; i++) {
    if (node_getId (g->nodes[i]) == nId1) return i;
  }
  return -1;
}

int* graph_getConnectionsIndex(const Graph * g, int index) {
  int *array = NULL, i, j = 0, size;
  if (!g) return NULL;
  if (index < 0 || index >g->num_nodes) return NULL;
  size = node_getConnect (g->nodes[index]);
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