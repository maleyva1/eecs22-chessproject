#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>

#include "Move.h"
#include "MoveList.h"

/* 
 * Takes in a MoveList struct and prints
 * the game moves in a text file
 */
void printToFile(MoveList *list);

#endif
