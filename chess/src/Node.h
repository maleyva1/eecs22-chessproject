#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include "board.h"
#include "MoveList.h"
#include "Move.h"

typedef struct node Node;

struct node {
    Node *parent;
    Node *child;
    int weight;
    Move *move;
    PIECES *board;
};

Node *newNode(PIECES *board, Move *move);

/* Returns the weight of the this board state*/
int getWeight(Node *node);

/* Insert node at the end of a tree*/
void insert(Node *insert, Node *root);

/* Destroys a single node;*/
void destroyNode(Node *nodeToDestroy);

#endif
