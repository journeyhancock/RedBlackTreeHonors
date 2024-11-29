//
// Created by journ on 11/26/2024.
//

#include <stdio.h>
#include <string.h>
#include "util.h"

int instruction(char *word, int *key) {
    fscanf(stdin, "%s", word);
    int value;

    // Check commands that have to do with things initialized in main.cpp
    if (strcmp(word, "Stop") == 0 or strcmp(word, "Read") == 0 or strcmp(word, "Write") == 0) {
        return 1;
    }
    // Check commands that have to do with the RBTree in main.cpp
    if (strcmp(word, "PrintTree") == 0) {
        return 1;
    }

    // Check commands that require parameters (if valid send back to main to use RBTree)
    if (strcmp(word, "Insert") == 0) {
        value = fscanf(stdin, "%d", key);
        if (value == 1) {
            return 1;
        }
    }
    if (strcmp(word, "Delete") == 0) {
        value = fscanf(stdin, "%d", key);
        if (value == 1) {
            return 1;
        }
    }
    if (strcmp(word, "Search") == 0) {
        value = fscanf(stdin, "%d", key);
        if (value == 1) {
            return 1;
        }
    }

    return 0;
}