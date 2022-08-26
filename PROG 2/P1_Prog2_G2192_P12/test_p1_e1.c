#include <stdlib.h>
#include <stdio.h>

#include "node.h"

void test_node_name(){
  const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  Node* node = NULL;
  Status st = -1;
  char* string;
  int sizes[] = {5, 50, 63, 64, 65, 100, -1};
  int i, j, size;

  node = node_init();
  if (node == NULL){
    fprintf(stderr, "test_node_name: error in node_init\n");
    return;
  }

  for (i=0; sizes[i]!=-1; i++){
    size = sizes[i];
    string = calloc((size+1),sizeof(char));
    for (j=0; j<size; j++){
      int key = rand() % (int) (sizeof(charset) - 1);
      string[j] = charset[key];
    }
    st = node_setName(node, string);
    free(string);
    fprintf(stdout, "test_node_name: node_setName with %d chars: %s --> %s\n", size, (st==ERROR?"Error":"Ok"), node_getName(node));
  }

  node_free(node);
}

void test_node_label(){
  Node* node = NULL;
  Status st = -1;
  int labels[] = {WHITE, BLACK, ERROR_NODE, -1, 10, 5, -2};
  int i, label;

  node = node_init();
  if (node == NULL){
    fprintf(stderr, "test_node_label: error in node_init\n");
    return;
  }

  for (i=0; labels[i]!=-2; i++){
    label = labels[i];
    st = node_setLabel(node, label);
    fprintf(stdout, "test_node_label: node_setLabel with %d: %s --> %d\n", label, (st==ERROR?"Error":"Ok"), node_getLabel(node));
  }

  node_free(node);
}

void test_node_print(){
  Node* node = NULL;
  char* names[] = {"first", "first", "a", "b"};
  int labels[] = {WHITE, BLACK, BLACK, BLACK};
  long ids[] = {111, 222, 1, 2};
  int exp[] = {18, 18, 12, 12};
  int i, j, size;

  node = node_init();
  if (node == NULL){
    fprintf(stderr, "test_node_print: error in node_init\n");
    return;
  }

  size = sizeof(exp) / sizeof(int);
  for (i=0; i<size; i++){
    node_setName(node, names[i]);
    node_setId(node, ids[i]);
    node_setLabel(node, labels[i]);
    fprintf(stdout, "test_node_print: ");
    j = node_print(stdout, node);
    fprintf(stdout, " --> %d (node_print) vs %d (expected)\n", j, exp[i]);
  }

  node_free(node);
}

void test_node_cmp(){
  Node* node1 = NULL;
  Node* node2 = NULL;
  char* names[] = {"first", "first", "sec", "sec", "first"};
  int labels[] = {WHITE, BLACK, BLACK, BLACK, BLACK};
  long ids[] = {111, 222, 111, 222, 111};
  int i, j, size;

  node1 = node_init();
  if (node1 == NULL){
    fprintf(stderr, "test_node_cmp: error in node_init 1\n");
    return;
  }
  node2 = node_init();
  if (node2 == NULL){
    node_free(node1);
    fprintf(stderr, "test_node_cmp: error in node_init 2\n");
    return;
  }

  size = sizeof(ids) / sizeof(long);
  for (i=0; i<size; i++){
    node_setName(node1, names[i]);
    node_setId(node1, ids[i]);
    node_setLabel(node1, labels[i]);
    for (j=0; j<size; j++){
      node_setName(node2, names[j]);
      node_setId(node2, ids[j]);
      node_setLabel(node2, labels[j]);
      fprintf(stdout, "test_node_cmp: ");
      node_print(stdout, node1);
      fprintf(stdout, " vs ");
      node_print(stdout, node2);
      fprintf(stdout, " --> %d\n", node_cmp(node1, node2));
    }
  }

  node_free(node1);
  node_free(node2);
}


int main (int argc, char **argv) {
  int opt=0;

  if (argc > 1){
    opt = atoi(argv[1]);
  }

  switch(opt){
    case 0:
    case 1:
      test_node_name();
      if(opt!=0){
        break;
      }
    case 2:
      test_node_print();
      if(opt!=0){
        break;
      }
    case 3:
      test_node_label();
      if(opt!=0){
        break;
      }
    case 4:
      test_node_cmp();
      if(opt!=0){
        break;
      }
  }
  return EXIT_SUCCESS;
}


