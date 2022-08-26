 /**
 * @file  p2_e1.c
 * @author Santiago Atrio, Daniel Varela
 * @date 14 Marzo 2020
 * @version 1.0
 * @brief Main
 */

#include <stdlib.h>
#include "element.h"

struct _Element {
  char *a;
} ;

Element * element_init() {
  Element *ele;
  ele=(Element*)calloc(1, sizeof(Element));
  if (ele==NULL) return NULL;
  ele->a=NULL;
  return ele;
}

void element_free(Element *ele) {
  free(ele);
}

Element *element_setInfo(Element *ele, void *info) {
  ele->a=(char*)info;
  return ele;
}

void *element_getInfo(Element *ele) {
  return ele->a;
}

Element *element_copy(const Element *ele) {
  Element *eleCopy=NULL;
  eleCopy = element_init();
  eleCopy->a=ele->a;
  return eleCopy;
}

Bool element_equals(const Element *ele1, const Element *ele2) {
  if(strcmp(ele1->a, ele2->a)==0) return TRUE;
  return FALSE;
}

int element_print(FILE *fil, const Element *ele) {
  int printed=0, i=0;
  printed=fprintf(fil, "%c\n", ele->a[i]);
  return printed;
}
