//
// Created by journ on 11/26/2024.
//

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

struct node {
    int key; //Key value
    int color; //Color: 0 = black, 1 = red
    node *parent; //Parent
    node *left; //Left Child
    node *right; //Right child
};

#endif //DATA_STRUCTURES_H
