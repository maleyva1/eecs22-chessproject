#ifndef BOARD_H
#define BOARD_H

typedef enum {
    bp = 1,
    br = 4,
    bh = 3,
    bb = 5,
    bq = 9,
    bk = 100,
    wp = -1,
    wr = -4,
    wh = -3,
    wb = -5,
    wq = -9,
    wk = -100
} PIECES;

typedef struct {
     PIECES *board; /*pointer to the memory storing all the pieces*/
} BOARD;

/* Creates an empty BOARD object */
BOARD *createboard();

/*int *getboard(BOARD *board);*/

/* This function moves pieces on the board */
/* The first two integers are the current  */
/* position of the piece and the last two  */
/* are the position of where it will move  */
/* to.                                     */
void movep(BOARD *board,int y,int x,int y2,int x2,int AIon);

/* This function actually fills the board with */
/* values as defined in this header file       */
void startboard(BOARD *board);

/*copys a board to a board*/
void copyboard(BOARD *board, BOARD *board2);
/* Gets piece on square */
PIECES pieceOnSquare(BOARD *board,int x, int y);

void SetBoardVal(BOARD *board,int x, int y,PIECES v);
#endif
