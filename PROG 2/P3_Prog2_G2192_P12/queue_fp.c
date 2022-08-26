#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "node.h"
#include "graph.h"
#include "queue_fp.h"

#define MAXQUEUE 1024

extern int errno;

struct _Queue {
  void* items[MAXQUEUE];
  int front;
  int rear;
  destroy_element_function_type free_element_function;
  copy_element_function_type copy_element_function;
  print_element_function_type print_element_function;
} ;

Queue* queue_init(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3) {
  Queue *q = NULL;
  int i;
  if (f1==NULL || f2==NULL || f3==NULL) return NULL;
  q=(Queue*)malloc(sizeof (Queue));
  if (q==NULL) {
    fprintf(stderr, "%s", strerror(errno));
    return NULL;
  }
  q->copy_element_function = f2;
  q->free_element_function = f1;
  q->print_element_function = f3;
  for (i=0; i<MAXQUEUE; i++) {
    q->items[i] = NULL;
    q->front = q->rear = 0;
  }
  return q;
}

void queue_free(Queue *q) {
  int i=q->front;
  if (q==NULL) return; 
  while (i!=(q->rear)) {
    q->free_element_function(q->items[i]);
    q->items[i]=NULL;
    i=(i+1)%MAXQUEUE;
  }
  free(q);
  return;
}

Bool queue_isEmpty(const Queue *q) {
  Queue *qcast=(Queue *)q;
  if (q==NULL) return FALSE;
  if (qcast->front==qcast->rear) return TRUE;
  return FALSE;
}

Status queue_insert(Queue *q, const void* pElem) {
  void *aux=NULL;
  if (q==NULL || pElem==NULL) return ERROR;
  if (q->front==(q->rear+1)%MAXQUEUE) return ERROR;
  aux=q->copy_element_function(pElem);
  if (aux==NULL) return ERROR;
  q->items[q->rear]=aux;
  q->rear=(q->rear+1)%MAXQUEUE;
  return OK;
}

void* queue_extract(Queue *q) {
  void *aux=NULL;
  if (q==NULL) return NULL;
  if (queue_isEmpty(q)==TRUE) return NULL;
  aux=q->items[q->front];
  q->items[q->front]=NULL;
  q->front=(q->front+1)%MAXQUEUE;
  return aux;
}

int queue_size (const Queue *q) {
  if (q==NULL) return -1;
  if (queue_isEmpty(q)==TRUE) return 0;
  if (q->front<q->rear) {
    return (q->rear-q->front);
  } else {
    return (MAXQUEUE-(q->front-q->rear));
  }
  return -1;
}

int queue_print(FILE *pf, const Queue *q) {
  int i, printed=0;
  if (pf==NULL || q==NULL) return printed;
  for (i=q->front; i<q->rear; i=(i+1)%MAXQUEUE) {
    printed+=q->print_element_function(pf, q->items[i]);
  }
  return printed;
}
