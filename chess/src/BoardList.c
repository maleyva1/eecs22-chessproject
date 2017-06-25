#include "BoardList.h"
#include <stdlib.h>
#include <stdio.h>
BOARDLIST *CreateBoardList(){
	BOARDLIST *l = malloc(sizeof(BOARDLIST));
	l->mostRecent = NULL;
	l->last = NULL;
	return l;
}
BOARDENTRY *newBoardEntry(BOARD *board) {
	BOARDENTRY *e = malloc(sizeof(BOARDENTRY));
	e->boardindex = board;
	e->next = NULL;
	e->prev = NULL;
	e->list = NULL;
return e;
}
void addBoard(BOARDLIST *l, BOARDENTRY *e) {
	e->list = l;
	if(!l->mostRecent) {
		l->mostRecent = e;
		l->last = e;
	}
	else{
		l->mostRecent->prev = e;
		e->next = l->mostRecent;
		l->mostRecent = e;
	}
}

BOARD *StoreBoard(BOARD *board) {
	BOARD *b = createboard();
	copyboard(b,board);
	return b;
}
			 
BOARD *UndoBoard(BOARDLIST *l,BOARD *board) {
if(l->mostRecent->next) {
	BOARDENTRY *d = l->mostRecent;
	BOARDENTRY *b = l->mostRecent->next;

	l->mostRecent->next->prev = NULL;
	l->mostRecent = l->mostRecent->next;
if(d->boardindex) {
	DeleteBoard(d->boardindex);
}
if(d) {
	DeleteBoardEntry(d);
}

return b->boardindex;
}
else {
	printf("Cannot undo!\n");
	return board;
}
}

void DeleteBoard(BOARD *board) {
if(board) {
	free(board->board);
	free(board);
}
}

void DeleteBoardEntry(BOARDENTRY *e) {
if(e) {
	e->next = NULL;
	e->prev = NULL;
	e->list = NULL;
	free(e);
}
}

void DeleteBoardList(BOARDLIST *l){
if(l) {
	l->mostRecent = NULL;
	l->last = NULL;
	free(l);
}
}	
