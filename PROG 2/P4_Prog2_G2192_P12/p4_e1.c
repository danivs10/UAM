#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <limits.h>
#include "types.h"
#include "list.h"
#include "stack_fp.h"
#include "stack_types.h"

#define MAX_ID 1000

/* Type definition. Pointer function to compare two elements */
typedef int (*f_cmp_type)(const void *, const void*);


/**
* @brief my personal int_print
* @author Santiago Atrio Rodriguez
*/
int my_int_print(FILE *pf, const void *a) {
  int *integer=(int *)a;
  if (pf==NULL || a==NULL) return -1;
  return fprintf(pf, "%d ", *integer);
}

/**
* @brief my personal int_cmp
* @author Santiago Atrio Rodriguez
*/
int my_int_cmp(const void *a, const void *b) {
  if (a==NULL || b==NULL) return -1;
  if (*((int *)a)<*((int *)b)) {
    return -1;
  } else if (*((int *)a)>*((int *)b)) {
    return 1;
  } else {
    return 0;
  }
}

/**
* @brief This function generates an ordered list with random integers between 0 and MAX_ID
*
* This functions modifies the input List.
* @param n, Length of the list
* @param ppl, Address of object List *
* @return This function returns OK or ERROR.
**/
Status listOfRandomOrdered (int n, List *pl) {
  int i, x;
  Status st = OK;
  if (!pl) return ERROR;
  for (i=0; i < n && st == OK; i++) {
    x = rand () % MAX_ID ;
    st = list_pushOrder (pl, &x, 1);
  }
  if (st == ERROR) {
    fprintf (stderr, "%s\n", strerror (errno));
    return ERROR;
  }
  return OK;
}

/**
* @brief This function concatenate two increased ordered lists
*
* This functions does not modified the ordered input lists l1 and l2.
*
* @parameter l1, Pointer to one list
* @parameter l2, Pointer to the second list
* @parameter lout, Pointer to the output concatenated list
* @parameter fun, Function used to compare the list elements
*
* @return This function returns OK or ERROR.
**/
Status listMergeOrdered (List *l1, List *l2, List *lout, f_cmp_type fun) {
  Stack *s1, *s2, *saux;
  List *laux;
  Status st=OK;
  int *ele;
  
  if (l1==NULL || l2==NULL || lout==NULL) {
    st=ERROR;
    return st;
  }

  /* M1 */
  s1=stack_init(int_free, int_copy, my_int_print);
  if (s1==NULL) {
    st=ERROR;
    return st;
  }
  s2=stack_init(int_free, int_copy, my_int_print);
  if (s2==NULL) {
    st=ERROR;
    stack_free(s1);
    return st;
  }
  
  /* M2 */
  while (list_isEmpty(l1)==FALSE && st==OK) {
    ele=(int *)list_popFront(l1);
    st=stack_push(s1, ele);  
    int_free(ele);
  }
  
  if (st==ERROR) {
    stack_free(s1);
    stack_free(s2);
    return st;
  }

  /* M3 */
  while (list_isEmpty(l2)==FALSE && st==OK) {
    ele=(int *)list_popFront(l2);
    st=stack_push(s2, ele);  
    int_free(ele);
  }
  
  if (st==ERROR) {
    stack_free(s1);
    stack_free(s2);
    return st;
  }
  
  /* M4 */
  while (stack_isEmpty(s1)==FALSE && stack_isEmpty(s2)==FALSE && st==OK) {
    if (fun(stack_top(s1), stack_top(s2))==1) {
      ele=(int *)stack_pop(s1);
      st=list_pushFront(l1, ele);
    } else {
      ele=(int *)stack_pop(s2);
      st=list_pushFront(l2, ele);
    }
    if (st==ERROR) {
      stack_free(s1);
      stack_free(s2);
      return st;
    }
    st=list_pushFront(lout, ele);
    int_free(ele);
  }

  if (st==ERROR) {
    stack_free(s1);
    stack_free(s2);
    return st;
  }

  /* M5 */
  if (stack_isEmpty(s1)==TRUE) {
    saux=s2;
    laux=l2;
  } else {
    saux=s1;
    laux=l1;
  }

  /* M6 */
  while (stack_isEmpty(saux)==FALSE) {
    ele=(int *)stack_pop(saux);
    st=list_pushFront(laux, ele);
    if (st==ERROR) {
      int_free(ele);
      break;
    }
    st=list_pushFront(lout, ele);
    if (st==ERROR) {
      int_free(ele);
      break;
    }
    int_free(ele);
  }

  /* M7 */
  stack_free(s1);
  stack_free(s2);
  return st;
}

int main (int argc, char **argv) {
  List *l1, *l2, *lout;
  Status st;
  int size;

  if (argc != 2) {
    fprintf(stdout, "You should use the program this way: ./<mainfile> <list_size>\n");
    return EXIT_FAILURE;
  } else {
    size = atoi(argv[1]);
  }
  
  l1=list_new(int_free, int_copy, my_int_print, my_int_cmp);
  if (l1==NULL) return EXIT_FAILURE;

  l2=list_new(int_free, int_copy, my_int_print, my_int_cmp);
  if (l2==NULL) {
    list_free(l1);
    return EXIT_FAILURE;
  }

  lout=list_new(int_free, int_copy, my_int_print, my_int_cmp);
  if (l2==NULL) {
    list_free(l1);
    list_free(l2);
    return EXIT_FAILURE;
  }

  st=listOfRandomOrdered(size, l1);
  if (st==ERROR) {
    list_free(l1);
    list_free(l2);
    list_free(lout);
    return EXIT_FAILURE;
  }

  st=listOfRandomOrdered(size, l2);
  if (st==ERROR) {
    list_free(l1);
    list_free(l2);
    list_free(lout);
    return EXIT_FAILURE;
  }
  
  st=listMergeOrdered(l1, l2, lout, my_int_cmp);
  if (st==ERROR) {
    fprintf(stdout, "There was an error with the Merged list function.\n");
    list_free(l1);
    list_free(l2);
    list_free(lout);
    return EXIT_FAILURE;
  }

  fprintf(stdout, "\nList 0:\n");
  list_print(stdout, l1);
  fprintf(stdout, "\nsize: %d\n\n", list_size(l1));
  
  fprintf(stdout, "List 1:\n");
  list_print(stdout, l2);
  fprintf(stdout, "\nsize: %d\n\n", list_size(l2));

  fprintf(stdout, "List 2:\n");
  list_print(stdout, lout);
  fprintf(stdout, "\nsize: %d\n\n", list_size(lout));
  
  list_free(l1);
  list_free(l2);
  list_free(lout);
  return EXIT_SUCCESS;
}