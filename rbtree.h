//
// Created by journ on 11/26/2024.
//

#ifndef RBTREE_H
#define RBTREE_H

#include <cstdio>

#include "data_structures.h"

//void updateRoot(node *root, node* NIL);
node* rotate(node *root, node *x, node *grandparent);
void printTree(node *root, node *NIL, FILE *stream);
node* insert(node *root, int key, node* NIL);
node* bstDelete(node *root, int key, node *NIL);
void treeDelete(node *root, int key, node* NIL);
node* search(node *root, int key, node *NIL);

#endif //RBTREE_H
