#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "node.h"
#include "tree.h"

typedef struct _BTNode {
  void *info;
  struct _BTNode *left;
  struct _BTNode *right;
} BTNode;

struct _BSTree {
  BTNode *root;
  destroy_element_function_type destroy_element;
  copy_element_function_type copy_element;
  print_element_function_type print_element;
  cmp_element_function_type cmp_element;
};

/*** DECLARACIÓN DE FUNCIONES PRIVADAS ***/

BTNode* bt_node_new();
void bt_node_free (BTNode *pn, destroy_element_function_type free_elem);
void tree_destroy_rec(BSTree *tree, BTNode *aux);
int tree_depth_rec (BTNode *aux, int *i);
BTNode *tree_insert_rec(BSTree *tree, BTNode *aux, const void *elem);
void tree_postOrder_rec (FILE *f, BSTree *tree, BTNode *n);
void tree_preOrder_rec (FILE *f, BSTree *tree, BTNode *n);
void tree_inOrder_rec (FILE *f, BSTree *tree, BTNode *n);

/*** PRIMITIVAS PRIVADAS DE BT-NODOS ***/

BTNode * bt_node_new(){
  BTNode* pn = NULL;
  pn = malloc(sizeof(BTNode));
  if (!pn) {
    fprintf (stderr,"%s\n", strerror (errno));
    return NULL;
  }
  pn->left = pn->right = NULL;
  pn->info = NULL;
  return pn;
}

void bt_node_free (BTNode *pn, destroy_element_function_type free_elem){
  if (!pn) return;
  free_elem(pn->info);
  free(pn);
}

/*** CREACIÓN Y LIBERACIÓN DE UN ÁRBOL ***/

BSTree* tree_init(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3,
 cmp_element_function_type f4){
  BSTree* tree = malloc (sizeof(BSTree));
  if (!tree) {
    fprintf (stderr,"%s\n", strerror (errno));
    return NULL;
  }
  tree->root = NULL;
  tree->destroy_element=f1;
  tree->copy_element=f2;
  tree->print_element=f3;
  tree->cmp_element=f4;
  return tree;
}

Bool tree_isEmpty( const BSTree *tree){
  if (tree==NULL) return TRUE;
  if (tree->root==NULL) return TRUE;
  return FALSE;
}

void tree_destroy (BSTree *tree) {
  BTNode *aux=NULL;
  if (tree_isEmpty(tree)!=TRUE) {
    aux=tree->root;
    if (aux->left!=NULL) tree_destroy_rec(tree, aux->left);
    if (aux->right!=NULL) tree_destroy_rec(tree, aux->right);
  }
  bt_node_free(tree->root, tree->destroy_element);
  free(tree);
}

void tree_destroy_rec(BSTree *tree, BTNode *aux) {
  if (aux->left!=NULL) tree_destroy_rec(tree, aux->left);
  if (aux->right!=NULL) tree_destroy_rec(tree, aux->right);
  bt_node_free(aux, tree->destroy_element);
}

int tree_depth (const BSTree *tree) {
  int i=0, s=0;
  if (tree_isEmpty(tree)==TRUE) return 0;
  s=tree_depth_rec(tree->root, &i);
  return s;
}

int tree_depth_rec (BTNode *aux, int *i) {
  int count1, count2;
  if (aux==NULL) return 0;
  if (aux->right!=NULL || aux->left!=NULL) {
    (*i)++;
    count1=tree_depth_rec(aux->left, i);
    count2=tree_depth_rec(aux->right, i);
    if (count1>=count2) {
      return count1;
    } else {
      return count2;
    }
  } else {
    return (*i);
  }
}

/*** INSERCIÓN ***/
Status tree_insert (BSTree *tree, const void *elem){
  BTNode *aux=NULL;
  if (tree==NULL || elem==NULL) return ERROR;
  aux = tree_insert_rec(tree, tree->root, elem);
  if (aux==NULL) return ERROR;
  tree->root = aux;
  return OK;
}

BTNode *tree_insert_rec(BSTree *tree, BTNode *root, const void *elem) {
  BTNode *aux=NULL;
  int i;
  if (root==NULL) {
    root = bt_node_new();
    if (root==NULL) return NULL;
    root->info = tree->copy_element(elem);
    if (root->info==NULL) {
      bt_node_free(root, tree->destroy_element);
      return NULL;
    }
    return root;
  } else {
    i = tree->cmp_element(elem, root->info);
    if (i < 0) {
      aux = tree_insert_rec(tree, root->left, elem);
      if (aux==NULL) return NULL;
      root->left = aux;
      return root;
    } else if (i > 0) {
      aux = tree_insert_rec(tree, root->right, elem);
      if (aux==NULL) return NULL;
      root->right = aux;
      return root;
    }
    return root;
  }
}

/*** RECORRIDOS ***/
void tree_preOrder (FILE *f, const BSTree *tree){
  BTNode *aux;
  BSTree *taux = (BSTree *) tree;
  fprintf(f, "Tree preOrder Transversal ...\n");
  if (f==NULL || tree==NULL) return;
  if (tree_isEmpty(tree)==TRUE) return;
  aux = tree->root;
  tree->print_element(f, aux->info);
  tree_preOrder_rec(f, taux, aux->left);
  tree_preOrder_rec(f, taux, aux->right);
  fprintf(f, "\n\n");
  return;
}

void tree_preOrder_rec (FILE *f, BSTree *tree, BTNode *n) {
  if (n==NULL) return;
  tree->print_element(f, n->info);
  tree_preOrder_rec(f, tree, n->left);
  tree_preOrder_rec(f, tree, n->right);
}

void tree_inOrder (FILE *f, const BSTree *tree){
  BTNode *aux;
  BSTree *taux = (BSTree *) tree;
  fprintf(f, "Tree inOrder Transversal ...\n");
  if (f==NULL || tree==NULL) return;
  if (tree_isEmpty(tree)==TRUE) return;
  aux = tree->root;
  tree_inOrder_rec(f, taux, aux->left);
  tree->print_element(f, aux->info);
  tree_inOrder_rec(f, taux, aux->right);
  fprintf(f, "\n\n");
  return;
}

void tree_inOrder_rec (FILE *f, BSTree *tree, BTNode *n) {
  if (n==NULL) return;
  tree_inOrder_rec(f, tree, n->left);
  tree->print_element(f, n->info);
  tree_inOrder_rec(f, tree, n->right);
}

void tree_postOrder (FILE *f, const BSTree *tree){
  BTNode *aux;
  BSTree *taux = (BSTree *) tree;
  fprintf(f, "Tree postOrder Transversal ...\n");
  if (f==NULL || tree==NULL) return;
  if (tree_isEmpty(tree)==TRUE) return;
  aux = tree->root;
  tree_postOrder_rec(f, taux, aux->left);
  tree_postOrder_rec(f, taux, aux->right);
  tree->print_element(f, aux->info);
  fprintf(f, "\n\n");
  return;
}

void tree_postOrder_rec (FILE *f, BSTree *tree, BTNode *n) {
  if (n==NULL) return;
  tree_postOrder_rec(f, tree, n->left);
  tree_postOrder_rec(f, tree, n->right);
  tree->print_element(f, n->info);
}