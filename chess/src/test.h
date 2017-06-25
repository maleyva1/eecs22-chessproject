/*test.h*/
#include <stdio.h>
#include "RuleSet.h" 
#include "Move.h" 
#include "MoveList.h" 
#include "board.h"
#include "log.h"
#include "ChessUI.h"

#ifndef TEST_H
#define TEST_H

int testRules(BOARD *board, int legal,int Turn, int playerColor, PIECES KingToCheck, Move *move, MoveList *history);

#endif

