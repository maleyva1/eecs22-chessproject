#ifndef AIAID_H
#define AIAID_H

#include "RuleSet.h"
#include "board.h"
#include "MoveList.h"
#include "Move.h"

/* Check if we're within the bounds */
int checkBounds(int x, int y);

void copyBoards(PIECES tboard[][8], PIECES* board);

/* This calculated piecs that could be gained by the pawn */
int calcPawnGain(PIECES *pboard, int x, int y);

int calcKnightGain(PIECES *pboard, int x, int y);

int calcBishopGain(PIECES *pboard, int x, int y);

int calcRookGain(PIECES *pboard, int x, int y);

int calcQueenGain(PIECES *pboard, int x, int y);

int calcKingGain(PIECES *pboard, int x, int y);

/* Returns list of all possible legal moves */
MoveList *legalMoveList(BOARD *board, int x, int y, MoveList *PrevMoves);

MoveList *AllLegalMoveList(BOARD *board, MoveList *PrevMoves, int PieceColor);
#endif
