//
// Created by journ on 11/26/2024.
//

#include "rbtree.h"
#include <cstddef>
#include <cstdio>
#include <climits>

node* rotate(node *root, node *x, node *grandparent) {
    if (x->parent->right == x) {
        //Left Rotate
        node *alpha = x->parent->left;
        node *beta = x->left;
        node *gamma = x->right;
        node *a = x->parent;
        node *b = x;
        node *pi = grandparent;

        int colorTemp = x->parent->color;
        x->parent->color = x->color;
        x->color = colorTemp;

        if (pi != nullptr) {
            pi->right == a ? pi->right = b : pi->left = b;
        } else {
            root = x;
        }

        b->parent = pi;
        b->left = a;
        a->parent = b;
        a->left = alpha;
        a->right = beta;
        alpha->parent = a;
        beta->parent = a;
        b->right = gamma;
        gamma->parent = b;
    } else {
        //Right Rotate
        node *alpha = x->left;
        node *beta = x->right;
        node *gamma = x->parent->right;
        node *a = x;
        node *b = x->parent;
        node *pi = grandparent;

        int colorTemp = x->parent->color;
        x->parent->color = x->color;
        x->color = colorTemp;

        if (pi != nullptr) {
            pi->right == b ? pi->right = a : pi->left = a;
        } else {
            root = x;
        }

        a->parent = pi;
        a->right = b;
        b->parent = a;
        b->right = gamma;
        b->left = beta;
        gamma->parent = b;
        beta->parent = b;
        a->left = alpha;
        alpha->parent = a;
    }
    return root;
}

void printTree(node *root, node *NIL, FILE *stream) {
    node *curr = root;

    if (curr != NIL) {
        const char* color1 = curr->color == 0 ? "\033[90m" : "\033[91m";
        const char* colorChar1 = curr->color == 0 ? "B" : "R";
        const char* reset = "\033[0m";

        if (curr->left != NIL) {
            const char* color2 = curr->left->color == 0 ? "\033[90m" : "\033[91m";
            const char* colorChar2 = curr->left->color == 0 ? "B" : "R";
            fprintf(stream, "%s%s%d%s%s ->LEFT-> %s%s%d%s%s \n", color1, colorChar1, curr->key, colorChar1, reset, color2, colorChar2, curr->left->key, colorChar2, reset);
            printTree(curr->left, NIL, stream);
        }
        if (curr->right != NIL) {
            const char* color2 = curr->right->color == 0 ? "\033[90m" : "\033[91m";
            const char* colorChar2 = curr->right->color == 0 ? "B" : "R";
            fprintf(stream, "%s%s%d%s%s ->RIGHT-> %s%s%d%s%s \n", color1, colorChar1, curr->key, colorChar1, reset, color2, colorChar2, curr->right->key, colorChar2, reset);
            printTree(curr->right, NIL, stream);
        }
    }
}

node* insert(node *root, int key, node *NIL) {
    node *curr = root;
    node *x = new node; // newely inserted node
    x->key = key;
    x->color = 1;
    x->right = NIL;
    x->left = NIL;
    x->parent = nullptr;

    //BST insertion
    while(curr != NIL) {
        if (key < curr->key) {
            if (curr->left == NIL) {
                curr->left = x;
                x->parent = curr;
                break;
            }
            curr = curr->left;
        }
        if (key > curr->key) {
            if (curr->right == NIL) {
                curr->right = x;
                x->parent = curr;
                break;
            }
            curr = curr->right;
        }
    }

    while (x->color == 1 and x->parent->color == 1) {
        //Case 1: x->color == 1, x->parent->color == 1, uncle->color == 1
        //Get Uncle of x
        node *uncle = new node;
        node *grandparent = new node;
        grandparent = x->parent->parent;
        grandparent->left == x->parent ? uncle = grandparent->right : uncle = grandparent->left;

        if (x->color == 1 and x->parent->color == 1 and uncle->color == 1) {
            x->parent->parent->color = 1;
            x->parent->color = 0;
            uncle->color = 0;
            x = x->parent->parent;
        }

        //Case 2: x->color == 1, x->parent->color == 1, uncle->color == 0, x is near uncle
        //Update Family
        grandparent = x->parent->parent;
        grandparent->left == x->parent ? uncle = grandparent->right : uncle = grandparent->left;

        if (x->color == 1 and x->parent->color == 1) {
            //Check if x is near uncle
            if ((x->parent->right == x and grandparent->right == uncle) or (x->parent->left == x and grandparent->left == uncle)) {
                root = rotate(root, x, grandparent);
                x->left->color == 1 ? x = x->left : x = x->right;
            }
        }

        //Case 3: x->color == 1, x->parent->color == 1, uncle->color == 0, x is far from uncle
        if (x->color == 1 and x->parent->color == 1) {
            //Check if x is far from uncle
            if ((x->parent->right == x and grandparent->left == uncle) or (x->parent->left == x and grandparent->right == uncle)) {
                x = x->parent;
                grandparent = grandparent->parent;
                root = rotate(root, x, grandparent);
            }
        }
    }
    return root;
}

node* bstDelete(node *root, int key, node *NIL) {
    node *z = new node; // node to be deleted
    z = search(root, key, NIL);

    //Case 1
    if (z->left == NIL and z->right == NIL) {
        z->parent->left == z ? z->parent->left = NIL : z->parent->right = NIL;
        return z;
    }

    //Case 2
    if (z->left == NIL or z->right == NIL) {
        if (z->left != NIL) {
            z->parent->left == z ? z->parent->left = z->left : z->parent->right = z->left;
            return z;
        }
        z->parent->left == z ? z->parent->left = z->right : z->parent->right = z->right;
        return z;
    }

    //Case 3
    //Find successor
    node *curr = new node;
    node *successor = new node;
    curr = root;
    while (curr != NIL) {
        if (z->key < curr->key) {
            successor = curr;
            curr = curr->left;
        } else if (z->key >= curr->key) {
            curr = curr->right;
        } else {
            break;
        }
    }

    return bstDelete(root, successor->key, NIL); //Delete successor
}

node* treeDelete(node *root, int key, node *NIL) {
    node *y = new node;
    y = bstDelete(root, key, NIL); //Successor node

    node *x = new node; //x is what moves into the spot of y
    if (y->left != NIL) {
        x = y->left;
    } else if (y->right != NIL) {
        x = y->right;
    } else {
        x->parent = y->parent;
        x->key = INT_MAX;
        x->color = 0;
        x->right = NIL;
        x->left = NIL;
    }

    node *w = new node;
    if (x->color == 0) {
        y->parent->left->key == x->key ? w = y->parent->right : w = y->parent->left; //Set w as sibling of x
    }

    if (x->color == 1) {
        x->color = 0;
        //Now a valid RBTree
    } else {
        //Need to perform fixup
        while (x != root and x->color == 0) {
            //Case 1: x->color == 0, w->color == 1
            if (w->color == 1) {
                root = rotate(root, w, w->parent->parent);
                if (x != root) x->parent->left->key == x->key ? w = x->parent->right : w = x->parent->left; //Update w based on new x
            }

            //Case 2: x->color == 0, w->color == 0, w->left->color == 0, w->right->color == 0
            if (w->color == 0 and w->left->color == 0 and w->right->color == 0) {
                x = w->parent;
                if (x != root) {
                    w->color = 1;
                    if (x->color == 1) {
                        x->color = 0;
                    }
                }
                if (x != root) x->parent->left->key == x->key ? w = x->parent->right : w = x->parent->left; //Update w based on new x
            }

            //Case 3: w->color == 0, w->nearChild->color == 1, w->otherChild->color == 1
            if (w->color == 0) {
                if (w->parent->right == w) {
                    if (w->left->color == 1 and w->right->color == 0) {
                        root = rotate(root, w->left, w->left->parent->parent);
                        if (x != root) x->parent->left->key == x->key ? w = x->parent->right : w = x->parent->left; //Update w based on new x
                    }
                } else if (w->parent->left == w) {
                    if (w->right->color == 1 and w->left->color == 0) {
                        root = rotate(root, w->right, w->right->parent->parent);
                        if (x != root) x->parent->left->key == x->key ? w = x->parent->right : w = x->parent->left; //Update w based on new x
                    }
                }
            }

            //Case 4: w->color == 0, w->farChild->color == 1
            if (w->color == 0) {
                if (w->parent->right == w) {
                    if (w->right->color == 1) {
                        root = rotate(root, w, w->parent->parent);
                        w->right->color = 0;
                        break; //End loop since RBTree is valid after Case 4 solved
                    }
                } else if (x->parent->left == w) {
                    if (w->left->color == 1) {
                        root = rotate(root, w, w->parent->parent);
                        w->left->color = 0;
                        break; //End loop since RBTree is valid after Case 4 solved
                    }
                }

            }
        }
    }
    return root;
}

node* search(node *root, int key, node *NIL) {
    node *curr = root;

    if (curr->key == INT_MAX) {
        return NIL;
    }
    if (key == curr->key) {
        return curr;
    }
    if (key < curr->key) {
        return search(curr->left, key, NIL);
    }
    return search(curr->right, key, NIL);
}
