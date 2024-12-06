#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <climits>

#include "data_structures.h"
#include "util.h"
#include "rbtree.h"

int main(int argCount, char**argVal) {
    //Files and main variables
    FILE *inputFile, *outputFile;
    int lineOutput;
    char word[100];
    int key;

    if (argCount != 3) {
        fprintf(stderr, "Usage: %s <ifile> <ofile>\n", argVal[0]);
        exit(0);
    }

    outputFile = fopen(argVal[2], "w");
    if (!outputFile) {
        fprintf(stderr, "Error: cannot open file %s\n", argVal[2]);
        exit(0);
    }

    //Create RB Tree with a root and NIL nodes
    node *root = new node;
    node *NIL = new node;
    //Init NIL node
    NIL->key = INT_MAX;
    NIL->parent = nullptr;
    NIL->left = nullptr;
    NIL->right = nullptr;
    NIL->color = 0;
    //Init root node
    root->color = 0;
    root->key = INT_MAX;
    root->left = NIL;
    root->right = NIL;
    root->parent = nullptr;

    while (true) {
        lineOutput = instruction(word, &key);

        if (lineOutput == 1) {
            //File functions
            if (strcmp(word, "Stop") == 0) {
                fprintf(stdout, "Instruction: Stop\n");

                fclose(outputFile);

                return 0;
            }
            if (strcmp(word, "Read") == 0) {
                fprintf(stdout, "Instruction: Read\n");

                inputFile = fopen(argVal[1], "r");
                if (!inputFile) {
                    fprintf(stderr, "Error: cannot open file %s\n", argVal[1]);
                    exit(0);
                }
                int nodeCount, key1, color1, key2, color2;
                char child;
                fscanf(inputFile, "%d", &nodeCount);

                //Establish root
                fscanf(inputFile, "%d %d %c %d %d", &key1, &color1, &child, &key2, &color2);
                root->key = key1;
                node *temp = new node;
                temp->key = key2;
                temp->color = color2;
                temp->right = NIL;
                temp->left = NIL;
                temp->parent = root;
                child == 'R' ? root->right = temp : root->left = temp;

                for (int i = 0; i < nodeCount - 1; i++) {
                    node *curr;
                    node *next = new node;
                    fscanf(inputFile, "%d %d %c %d %d", &key1, &color1, &child, &key2, &color2);

                    curr = search(root, key1, NIL);
                    next->parent = curr;
                    next->key = key2;
                    next->color = color2;
                    next->left = NIL;
                    next->right = NIL;
                    child == 'R' ? curr->right = next : curr->left = next;
                }
            }

            if (strcmp(word, "Write") == 0) {
                fprintf(stdout, "Instruction: Write\n");

                outputFile = fopen(argVal[2], "w");
                if (!outputFile) {
                    fprintf(stderr, "Error: cannot open file %s\n", argVal[1]);
                    exit(0);
                }

                printTree(root, NIL, outputFile);
                continue;
            }

            //RBTree functions
            if (strcmp(word, "PrintTree") == 0) {
                fprintf(stdout, "Instruction: PrintTree\n");

                printTree(root, NIL, stdout);
            }

            if (strcmp(word, "Insert") == 0) {
                fprintf(stdout, "Instruction: Insert %d \n", key);

                if (search(root, key, NIL) != NIL) {
                    fprintf(stdout, "Key: %d already in tree \n", key);
                } else {
                    root = insert(root, key, NIL);
                }
            }

            if (strcmp(word, "Delete") == 0) {
                fprintf(stdout, "Instruction: Delete %d \n", key);

                if (search(root, key, NIL) == NIL) {
                    fprintf(stdout, "Key: %d not in tree \n", key);
                } else {
                    root = treeDelete(root, key, NIL);
                }
            }

            if (strcmp(word, "Search") == 0) {
                fprintf(stdout, "Instruction: Search %d \n", key);

                node *temp = new node;
                temp = search(root, key, NIL);

                if (temp == NIL) {
                    fprintf(stdout, "Key: %d not in tree \n", key);
                } else {
                    if (temp->color == 0) {
                        fprintf(stdout, "Node key: %d with color: Black \n", temp->key);
                    } else {
                        fprintf(stdout, "Node key: %d with color: Red \n", temp->key);
                    }
                }
            }
        }

        if (lineOutput == 0) {
            fprintf(stderr, "Warning: Invalid instruction: %s\n", word);
        }
    }
}
