#ifndef RULSET_H
#define RULESET_H
#include "Move.h"
#include "MoveList.h"
#include "board.h"

int LegalMove(Move move, BOARD *board, MoveList *l, int Turn);

int EvalPawn(Move move, BOARD *board,MoveList *l);

int EvalKing(Move move,BOARD *board);

int Castle(Move move, BOARD *board,MoveList *l);

int EvalQueen(Move move,BOARD *board);

int EvalKnight(Move move);

int EvalBishop(Move move,BOARD *board);

int CheckBounds(Move move);

int EvalRook(Move move,BOARD *board);

int KCheck(PIECES Ktest, BOARD *NewBoard, MoveList *l);

int MoveKCheck(PIECES Ktest, Move move, BOARD *board, MoveList *l);

int Checkmate(PIECES Ktest, BOARD *board, MoveList *l);

#endif


