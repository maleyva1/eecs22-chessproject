#ifndef MOVE_H
#define MOVE_H

#include <stdio.h>
#include "board.h"

/* Original author: Mark Leyva */
/* ID: 25662446                */

/* This is the move struct that contains before and after (x, y) indexes of a player */

typedef struct {
    int Ybefore;    /* Current Y-position of the piece */
    int Xbefore;    /* Current X-position of the piece */
    int Yafter;     /* Y-position of the piece after it moves */
    int Xafter;	    /* X-position of the piece after it moves */
    PIECES willMove;
}Move;

/* Initializes a move object to the indices passed as arguments */
Move *newMove(int currentY, int currentX, int moveToY, int moveToX,BOARD *board);

/* Deletes a move */
void delMove(Move *move);



#endif
