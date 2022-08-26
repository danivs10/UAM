#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "node.h"


void test_graph_numnodes(){
  Graph *graph = NULL;
  Node *node = NULL;
  Status aux;
  int i, max_nodes = 2000;

  graph = graph_init ();
  if (graph == NULL){
    fprintf(stderr, "test_graph_numnodes: error in graph_init\n");
    return;
  }

  node = node_init ();
  if (node == NULL){
    graph_free(graph);
    fprintf(stderr, "test_graph_numnodes: error in node_init\n");
    return;
  }

  node_setName(node, "first");
  node_setLabel (node, WHITE);
  for (i=0; i<max_nodes; i++){
    node_setId (node, (long) i);
    aux = graph_insertNode(graph, node);
    fprintf(stdout, "%s ", (aux==ERROR?"Error":"Ok"));
  }
  fprintf(stdout, "\ntest_graph_numnodes: graph_insertNode: %s (error) <-- %d\n", (aux==ERROR?"Error":"Ok"), graph_getNumberOfNodes(graph));

  graph_free(graph);
  node_free(node);
}

void test_graph_addnode(){
  Graph *graph = NULL;
  Node *node1 = NULL;
  Status aux;

  graph = graph_init ();
  if (graph == NULL){
    fprintf(stderr, "test_graph_addnode: error in graph_init\n");
    return;
  }

  node1 = node_init ();
  if (node1 == NULL){
    graph_free(graph);
    fprintf(stderr, "test_graph_addnode: error in node_init\n");
    return;
  }
  node_setId (node1, 111);
  node_setName(node1, "first");
  node_setLabel (node1, WHITE);

  aux = graph_insertNode(graph, node1);
  fprintf(stdout, "test_graph_addnode: graph_insertNode: %s (ok) <-- %d\n", (aux==ERROR?"Error":"Ok"), graph_getNumberOfNodes(graph));

  aux = graph_insertNode(graph, node1);
  fprintf(stdout, "test_graph_addnode: graph_insertNode: %s (ok/error) <-- %d (unchanged)\n", (aux==ERROR?"Error":"Ok"), graph_getNumberOfNodes(graph));

  graph_free(graph);
  node_free(node1);
}

void test_graph_addconnection(){
  Graph *graph = NULL;
  Node *node1 = NULL, *node2 = NULL;
  Status aux;
  Bool ret;

  graph = graph_init ();
  if (graph == NULL){
    fprintf(stderr, "test_graph_addconnection: error in graph_init\n");
    return;
  }

  node1 = node_init ();
  if (node1 == NULL){
    graph_free(graph);
    fprintf(stderr, "test_graph_addconnection: error in node_init\n");
    return;
  }
  node_setId (node1, 111);
  node_setName(node1, "first");
  node_setLabel (node1, WHITE);

  node2 = node_init ();
  if (node2 == NULL){
    graph_free(graph);
    node_free(node1);
    fprintf(stderr, "test_graph_addconnection: error in node_init\n");
    return;
  }
  node_setId (node2, 222);
  node_setName(node2, "second");
  node_setLabel (node2, WHITE);

  ret = graph_areConnected (graph, 4444, 5555);
  fprintf(stdout, "test_graph_addconnection: graph_areConnected: %s (False)\n", (ret==TRUE?"True":"False"));

  aux = graph_insertEdge(graph, node_getId(node1), node_getId(node2));
  fprintf(stdout, "test_graph_addconnection: graph_insertEdge: %s (error) <-- %d\n", (aux==ERROR?"Error":"Ok"), graph_getNumberOfEdges(graph));

  aux = graph_insertNode(graph, node1);
  fprintf(stdout, "test_graph_addconnection: graph_insertNode: %s (ok)\n", (aux==ERROR?"Error":"Ok"));

  aux = graph_insertNode(graph, node2);
  fprintf(stdout, "test_graph_addconnection: graph_insertNode: %s (ok)\n", (aux==ERROR?"Error":"Ok"));

  ret = graph_areConnected (graph, 111, 222);
  fprintf(stdout, "test_graph_addconnection: graph_areConnected: %s (False)\n", (ret==TRUE?"True":"False"));

  aux = graph_insertEdge(graph, node_getId(node1), node_getId(node2));
  fprintf(stdout, "test_graph_addconnection: graph_insertEdge: %s (ok) <-- %d\n", (aux==ERROR?"Error":"Ok"), graph_getNumberOfEdges(graph));

  ret = graph_areConnected (graph, 111, 222);
  fprintf(stdout, "test_graph_addconnection: graph_areConnected: %s (True)\n", (ret==TRUE?"True":"False"));
  ret = graph_areConnected (graph, 222, 111);
  fprintf(stdout, "test_graph_addconnection: graph_areConnected: %s (False)\n", (ret==TRUE?"True":"False"));

  aux = graph_insertEdge(graph, node_getId(node1), node_getId(node2));
  fprintf(stdout, "test_graph_addconnection: graph_insertEdge: %s (ok/error) <-- %d (unchanged)\n", (aux==ERROR?"Error":"Ok"), graph_getNumberOfEdges(graph));

  graph_free(graph);
  node_free(node1);
  node_free(node2);
}

void test_graph_free(){
  int i;
  Graph *graph = NULL;
  Node *node1 = NULL, *node2 = NULL;
  Status aux;

  graph = graph_init ();
  if (graph == NULL){
    fprintf(stderr, "test_graph_free: error in graph_init\n");
    return;
  }

  node1 = node_init ();
  if (node1 == NULL){
    graph_free(graph);
    fprintf(stderr, "test_graph_free: error in node_init\n");
    return;
  }
  node_setId (node1, 111);
  node_setName(node1, "first");
  node_setLabel (node1, WHITE);

  node2 = node_init ();
  if (node2 == NULL){
    graph_free(graph);
    node_free(node1);
    fprintf(stderr, "test_graph_free: error in node_init\n");
    return;
  }
  node_setId (node2, 222);
  node_setName(node2, "second");
  node_setLabel (node2, WHITE);

  aux = graph_insertNode(graph, node1);
  fprintf(stdout, "test_graph_free: graph_insertNode: %s (ok)\n", (aux==ERROR?"Error":"Ok"));

  aux = graph_insertNode(graph, node2);
  fprintf(stdout, "test_graph_free: graph_insertNode: %s (ok)\n", (aux==ERROR?"Error":"Ok"));

  node_free(node1);
  node_free(node2);
  graph_free(graph);
}

void test_graph_setnode(){
  Graph *graph = NULL;
  Node *node1 = NULL, *node2 = NULL;
  Status aux;

  graph = graph_init ();
  if (graph == NULL){
    fprintf(stderr, "test_graph_setnode: error in graph_init\n");
    return;
  }

  node1 = node_init ();
  if (node1 == NULL){
    graph_free(graph);
    fprintf(stderr, "test_graph_setnode: error in node_init\n");
    return;
  }
  node_setId (node1, 111);
  node_setName(node1, "first");
  node_setLabel (node1, WHITE);

  aux = graph_insertNode(graph, node1);
  fprintf(stdout, "test_graph_setnode: graph_insertNode: %s (ok)\n", (aux==ERROR?"Error":"Ok"));
  node_free(node1); /* this memory is not needed anymore */

  node2 = graph_getNode(graph, 111);
  node_setName(node2, "not_first");
  aux = graph_setNode(graph, node2);
  fprintf(stdout, "test_graph_setnode: graph_setNode: %s (ok)\n", (aux==ERROR?"Error":"Ok"));
  node1 = graph_getNode(graph, 111);
  /* let's check if the two nodes remain the same */
  fprintf(stdout, "test_graph_setnode: check names: %s (equal)\n", (strcmp(node_getName(node1), node_getName(node2))==0?"equal":"diff"));

  node_free(node1);
  node_free(node2);
  graph_free(graph);
}

void test_graph_getnode(){
  Graph *graph = NULL;
  Node *node1 = NULL, *node2 = NULL;
  Status aux;

  graph = graph_init ();
  if (graph == NULL){
    fprintf(stderr, "test_graph_getnode: error in graph_init\n");
    return;
  }

  node1 = node_init ();
  if (node1 == NULL){
    graph_free(graph);
    fprintf(stderr, "test_graph_getnode: error in node_init\n");
    return;
  }
  node_setId (node1, 111);
  node_setName(node1, "first");
  node_setLabel (node1, WHITE);

  aux = graph_insertNode(graph, node1);
  fprintf(stdout, "test_graph_getnode: graph_insertNode: %s (ok)\n", (aux==ERROR?"Error":"Ok"));
  node_free(node1); /* this memory is not needed anymore */

  node2 = graph_getNode(graph, 111);
  node_setName(node2, "not_first");
  node1 = graph_getNode(graph, 111);
  /* let's check if the two nodes remain the same */
  fprintf(stdout, "test_graph_getnode: check names: %s (diff)\n", (strcmp(node_getName(node1), node_getName(node2))==0?"equal":"diff"));

  node_free(node1);
  node_free(node2);
  graph_free(graph);
}



int main (int argc, char **argv) {
  int opt=0;

  if (argc > 1){
    opt = atoi(argv[1]);
  }

  switch(opt){
    case 0:
    case 1:
      test_graph_numnodes();
      if(opt!=0){
        break;
      }
    case 2:
      test_graph_addnode();
      if(opt!=0){
        break;
      }
    case 3:
      test_graph_addconnection();
      if(opt!=0){
        break;
      }
    case 4:
      test_graph_free();
      if(opt!=0){
        break;
      }
    case 5:
      test_graph_getnode();
      if(opt!=0){
        break;
      }
    case 6:
      test_graph_setnode();
      if(opt!=0){
        break;
      }
  }
  return EXIT_SUCCESS;
}
