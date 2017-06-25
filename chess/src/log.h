#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>

#include "Move.h"
#include "MoveList.h"

void printLog(MoveList *list);

void printToFile(MoveList *list);

#endif
