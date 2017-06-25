#include "board.h"
typedef struct boardentry BOARDENTRY;
typedef struct boardlist BOARDLIST;
struct boardentry {
	BOARDENTRY *next;
	BOARDENTRY *prev;
	BOARD *boardindex;
	BOARDLIST *list;
	};
struct boardlist {
	BOARDENTRY *mostRecent;
	BOARDENTRY *last;
};

BOARDLIST *CreateBoardList();

BOARDENTRY *newBoardEntry(BOARD *board);

void addBoard(BOARDLIST *l, BOARDENTRY *e);

BOARD *StoreBoard(BOARD *board);

BOARD *UndoBoard(BOARDLIST *l,BOARD *board);

void DeleteBoard(BOARD *board);

void DeleteBoardEntry(BOARDENTRY *e);

void DeleteBoardList(BOARDLIST *l);
