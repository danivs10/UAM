/* Aquí se incluyen las cabeceras que se necesiten*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "node.h"

#define NAME_L 64 /*!< Maximum node name length */

extern int errno;

struct _Node {
  char name[NAME_L]; /*!<Node name */
  long id; /*!<Node id */
  int nConnect; /*!<Node number of connections */
  Label label; /*!<Node state */
} ;

Node *node_init (){
  Node *n;
  n=(Node *)calloc(1, sizeof(Node));
  if (n==NULL) {
    fprintf(stderr, "Value of errno: %s\n", strerror(errno));
    return NULL;
  }
  strcpy(n->name, "");
  n->id=-1;
  n->nConnect=0;
  n->label=WHITE;
  return n;
}

void node_free (void *n){
  free(n);
}

long node_getId (const Node * n){
  if (!n){
    fprintf (stdout, "Value of errno for node get Id: %s\n", strerror(errno));
    return -1;
  }
  return n->id;
}

const char* node_getName (Node * n){
  if (!n){
    fprintf (stdout, "Value of errno: %s\n", strerror(errno));
    return NULL;
  }
  return n->name;
}

int node_getConnect (const Node * n){
  if (!n){
    fprintf (stdout, "Value of errno: %s\n", strerror(errno));
    return -1;
  }
  return n->nConnect;
}

Label node_getLabel (const Node*n){
  if (!n) {
    fprintf (stdout, "Value of errno: %s\n", strerror(errno));
    return ERROR_NODE;
  }
  return n->label;
}

Status node_setLabel (Node *n, Label l){
  if (!n || l==ERROR_NODE){
    fprintf (stdout, "Value of errno: %s\n", strerror(errno));
    return ERROR;
  }
  n->label=l;
  return OK;
}

Status node_setId (Node * n, const long id){
  if (!n || id==-1){
    fprintf (stdout, "Value of errno: %s\n", strerror(errno));
    return -1;
  }
  n->id=id;  
  return OK;
}

Status node_setName (Node *n, const char *name){
  if (strlen(name)>NAME_L || !n){
    fprintf (stdout, "Value of errno: %s\n", strerror(errno));
    return ERROR;
  }
  strcpy(n->name, name);
  return OK;
}

Status node_setNConnect (Node *n, const int cn){
  if (!n || cn<0){
    fprintf (stdout, "Value of errno: %s\n", strerror(errno));
    return ERROR;
  }
  n->nConnect=cn;
  return OK;
}

int node_cmp (const void *n1, const void *n2){
  Node *a = (Node *)n1, *b = (Node *)n2;
  if (!n1 || !n2){
    fprintf (stdout, "Value of errno: %s\n", strerror(errno));
    return -1;
  }
  if (a->id<b->id){
    return -1;
  } else if (a->id>b->id){
    return 1;
  } else if (a->id==b->id){
    return strcmp(a->name, b->name);
  }
  return -1;
}

void * node_copy (const void *src){
  Node* n, *trg;
  if (!src) return NULL;
  trg = node_init();
  if (!trg) return NULL;
  n = (Node*)src;
  if(node_getId(n)==-1) return NULL;
  node_setId(trg, node_getId(n));
  if(node_getName(n)==NULL) return NULL;
  node_setName(trg, node_getName(n));
  if(node_getLabel(n)==ERROR_NODE) return NULL;
  node_setLabel(trg, node_getLabel(n));
  if(node_getConnect(n)==-1) return NULL;
  node_setNConnect(trg, node_getConnect(n));
  return trg;
}

int node_print (FILE *pf, const void *n){
  Node* aux;
  if(!n || !pf) {
    fprintf (stderr, "Value of errno: %s\n", strerror(errno));
    return -1;
  }
  aux = (Node*)n;
  return fprintf(pf, "[%ld, %s, %d, %d]", node_getId(aux), node_getName(aux), node_getLabel(aux), node_getConnect(aux));
}