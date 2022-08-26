 /**
 * @file  p2_e1.c
 * @author Santiago Atrio, Daniel Varela
 * @date 14 Marzo 2020
 * @version 1.0
 * @brief Main
 */

#include <stdlib.h>
#include "stack.h"

#define MAXSTACK 1024

struct _Stack {
  int top;
  Element *item[MAXSTACK];
} ;

Stack* stack_init () {
  Stack *s=NULL;
  int i;
  s=(Stack*)calloc(1, sizeof(Stack));
  if (s==NULL) return NULL;
  for (i=0; i<MAXSTACK; i++) {
      s->item[i]=NULL;
  }
  s->top=-1;
  return s;
}

void stack_free(Stack *s) {
  int i;
  if (s!=NULL) {
    for (i=0; i<=s->top; i++) {
      element_free(s->item[i]);
      s->item[i] = NULL;
    }
    free(s);
  }
}

Status stack_push(Stack *s, const Element *ele) {
  Element *aux=NULL;
  if (s==NULL || ele==NULL || stack_isFull(s)==TRUE) return ERROR;
  aux = element_copy(ele);
  if (aux==NULL) return ERROR;
  s->top++;
  s->item[s->top] = aux;
  return OK;
}

Element* stack_pop(Stack *s) {
  Element *e=NULL;
  if (s==NULL || stack_isEmpty(s)==TRUE) return NULL;
  e = s->item[s->top];
  s->item[s->top] = NULL;
  s->top--;
  return e;
}

Element* stack_top(const Stack *s) {
  if (s==NULL || stack_isEmpty(s)==TRUE) return NULL;
  return element_copy(s->item[s->top]);
}

Bool stack_isEmpty(const Stack *s) {
  if (s==NULL) return TRUE;
  if (s->top==-1) return TRUE;
  return FALSE;
}

Bool stack_isFull(const Stack *s) {
  if (s==NULL) return TRUE;
  if (s->top==MAXSTACK-1) return TRUE;
  return FALSE;
}

int stack_size(Stack *s){
  if (s==NULL) return -1;
  return (s->top)+1;
}

int stack_print(FILE *file, const Stack *s) {
  int i, num=0;
  if (s==NULL) return -1;
  num+=fprintf(file, "Stack:\n");
  for (i=s->top; i>=0; i--) {
    if (s->item[i]!=NULL) num+=element_print(file, s->item[i]);
  }
  return num;
}
