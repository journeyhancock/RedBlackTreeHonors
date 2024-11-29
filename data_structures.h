//
// Created by journ on 11/26/2024.
//

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

struct node {
    int key;
    node *parent;
    node *left;
    node *right;
    int color; // 0 = black, 1 = red
};

#endif //DATA_STRUCTURES_H
