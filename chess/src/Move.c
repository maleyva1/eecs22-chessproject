#include "Move.h"
#include <stdlib.h>
Move *newMove(int currentY, int currentX, int moveToY, int moveToX,BOARD *board)
{
    Move *move;
    move = malloc(sizeof(Move));
    
    move->Ybefore = currentY;
    move->Xbefore = currentX;
    move->Yafter = moveToY;
    move->Xafter = moveToX;
    if(!board) { move->willMove = bk; }
    else 
    {
        move->willMove = board->board[currentX + currentY * 8]; 
    }
    return move;
}

void delMove(Move *move)
{
    move->Ybefore = 0;
    move->Xbefore = 0;
    move->Yafter = 0;
    move->Xafter = 0;

    free(move);
}
