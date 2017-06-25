#ifndef AI_H
#define AI_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "board.h"
#include "MoveList.h"
#include "Move.h"
#include "AIaid.h"
#include "Node.h"
#include "AIextra.h"

typedef struct ai AI;

struct ai{
    Node *tree;
    MoveList *moves;
    Move *move; /* The move to return */
    int color;
    MoveList *tourney;
};

AI *newAI(int col, BOARD* board);

void destroyAI(AI *aide);

/* Returns AI's move */
Move *getAiMove(AI *ai, BOARD *board, MoveList *history, int count);

/* Calculate total pieces that you can capture at the given board state */
int calcGain(BOARD *board, int col);

int calcThreat(BOARD *board, int col);

/*int calcKingSafety(BOARD *board);*/

int evaluateBoard(BOARD *board, int col, MoveList* history);

/*void destroyTree(BOARD *boardToDestroy);*/

#endif
