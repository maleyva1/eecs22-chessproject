#ifndef MOVELIST_H
#define MOVELIST_H

#include <stdio.h>
#include <stdlib.h>
#include "Move.h"

/* Original author: Mark Leyva */
/* ID: 25662446                */


typedef struct MList MoveList;
typedef struct MEntry MoveEntry;

/* Use this to keep track of all moves played*/
/* For usage in the int main() function:        */
/*  Create a a MoveList pointer and iterate
 *  through the list printing out to a log,
 *  the Move's (x, y) values                    */

struct MList {
    MoveEntry *mostRecent; /* First in the MoveList */
    MoveEntry *last;
};
struct MEntry {
    MoveList *list;
    MoveEntry *next;
    MoveEntry *prev;
    Move *index;
};

/* Creates an entirely new list */
MoveList *newList(void);

/* Creates a new MoveEntry */
/* Use in conjunction with the addMove() function */
MoveEntry *newEntry(Move *move);

/* This insert the most recent move into the list */
void addMove(MoveList *list, MoveEntry *entry);

/* This function returns and deletes the latest move from the MoveList */
Move *getMostRecentMove(MoveList *list);

/* Deletes entire MoveList */
void deleteList(MoveList *list);

#endif
