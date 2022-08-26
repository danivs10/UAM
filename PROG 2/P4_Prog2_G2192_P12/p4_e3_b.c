

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "graph_list.h"
#include "list.h"
#include "stack_types.h"
#include "tree.h"




Status listOfRandomAndOrdered(int n, List *pl[]) {
    int num[20], i = 0, k = 0, sm=0;
    Status st = OK;

   if(!pl || !n){
      st=ERROR;
      return st;
    }
    

    for (i = 0; i < n && st == OK; i++) {
        num[i] = rand() % 1000;
        if (list_pushFront(pl[1], &num[i]) == ERROR)
            st = ERROR;
    }

    for (sm = 0, i = 0; st == OK && i < n; i++, num[sm]=-1) {
        for (k = 0; k < n; k++)
            if (num[sm] < num[k])
                sm = k;
        if (list_pushFront(pl[0], &num[sm]) == ERROR)
            st = ERROR;
    }

    return st;
}




/**
* @brief my personal int_print
* @author Daniel Varela
*/
int my_int_print(FILE *f,const void *a){
    int suma=-1;
    
    suma = fprintf(f, "%d ", (*(int*)a));
    
    return suma;
}

/**
* @brief my personal int_cmp
* @author Daniel Varela
*/
int my_int_cmp(const void *a1, const void*a2){
    if(!a1 || !a2)
        return 0;
    
    return (*(int*)a1) - (*(int*)a2);
}


/**
* @brief my personal int_copy
* @author Daniel Varela
*/
void *my_int_copy (const void *p) {
  int *c = NULL;
 
  if (!p) return NULL;
 
  c = (int *) malloc(sizeof(int));
  if (c == NULL) {
    return NULL;
  }

  *c = *(int*)p;
  return c;
}


/**
* @brief my personal int_free
* @author Daniel Varela
*/
void my_int_free(void *a){
    free(a);
}
int main(int argc, char* argv[]) {

    List * l[2];
    BSTree * t[2];
    int i = 0, k=0, n = 0;
    Status st = OK;
    int *aux = NULL;

    if (argv[1] == NULL)
        st = ERROR;

    for (i = 0; (i < 2) && (st == OK); i++) {
        l[i] = list_new(my_int_free, my_int_copy, my_int_print, my_int_cmp);
        if (l[i] == NULL)
            st = ERROR;
    }
    for (i = 0; (i < 2) && (st == OK); i++) {
        t[i] = tree_init(my_int_free, my_int_copy, my_int_print, my_int_cmp);
        if (t[i] == NULL)
            st = ERROR;
    }

    n = atoi(argv[1]);
    if (listOfRandomAndOrdered(n, l) == ERROR){
        st = ERROR;
    }


  

    for (i = 0; (i < 2) && (st == OK); i++) {

        fprintf(stdout, "\n\n--- Printing List: %i...\n", i);
        if (list_print(stdout, l[i]) < 0)
            st = ERROR;

    for (k = 0; st == OK && k<n; k++) {
        aux = list_popFront(l[i]);
        if (tree_insert(t[i], (int*) aux) == ERROR)
            st = ERROR;
        my_int_free(aux);
    }
        fprintf(stdout, "\n\nTree depth: %i\n", tree_depth(t[i]));

        tree_postOrder(stdout, t[i]);
        fprintf(stdout, "\n");
        tree_preOrder(stdout, t[i]);
        fprintf(stdout, "\n");
        tree_inOrder(stdout, t[i]);
        fprintf(stdout, "\n\n");
    }

    if(l!=NULL){
      list_free(l[0]);
      list_free(l[1]);
    }
    if(t!=NULL){
      tree_destroy(t[0]);
      tree_destroy(t[1]);
    }


    return st;
}
