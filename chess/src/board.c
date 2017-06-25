#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "board.h"

void startboard(BOARD *board)
{
    /*This fuction purpose is to get the board ready for the start of the game*/
    /*it will create the array with enums with the pieces is a standard start postion*/

    int x,y;
    PIECES boardarray[8][8]={
        {wr,wp,0,0,0,0,bp,br},
        {wh,wp,0,0,0,0,bp,bh},
        {wb,wp,0,0,0,0,bp,bb},
        {wk,wp,0,0,0,0,bp,bk},
        {wq,wp,0,0,0,0,bp,bq},
        {wb,wp,0,0,0,0,bp,bb},
        {wh,wp,0,0,0,0,bp,bh},
        {wr,wp,0,0,0,0,bp,br}};

     for (x=0;x<8;x++)
     {
         for(y=0;y<8;y++)
         {
            board->board[x+(y*8)]=boardarray[x][y];      
         }
     }
   
}
BOARD *createboard(){
    /*this fuction allocates memory*/
    BOARD *p=malloc(sizeof(BOARD));
    p->board = malloc(sizeof(PIECES)*8*8);
    if(!p){
        perror("out of memory");
        return NULL;
    }
    return p;
}

void copyboard(BOARD *board,BOARD *board2){
    int x,y;
    for (x=0;x<8;x++){
        for(y=0;y<8;y++){
            board->board[x+(y*8)]=board2->board[x+(y*8)];
            
        }
    }
}

void movep(BOARD *board,int y, int x, int y2 , int x2,int AIon){
    assert(board);
    char promotepawn[20];
    if( ((pieceOnSquare(board,x,y) == wk) 
	&& (pieceOnSquare(board,x2,y2) == wr)) 
	|| ((pieceOnSquare(board,x,y) == bk) 
	&& (pieceOnSquare(board,x2,y2) == br)) ) {
		if( (x2 - x) > 0 ) {
			board->board[6 + y * 8] = board->board[x + y * 8];
			board->board[(x + 1) + y * 8] = board->board[x2 + y2 * 8];  
			board->board[x + y * 8] = 0;
			board->board[x2 + y2 * 8] = 0;
		}
		else {
			board->board[1 + y * 8] = board->board[x + y * 8];
			board->board[(x - 1) + y * 8] = board->board[x2 + y2 * 8];
			board->board[x + y * 8] = 0;
			board->board[x2 + y2 * 8] = 0;
		}	
	}
     else if( ((pieceOnSquare(board,x,y) == bp) 
		&& (y2 == 0))
		|| ((pieceOnSquare(board,x,y) == wp)  
		&& (y2 == 7)) ) {
		if(AIon == 1 && pieceOnSquare(board,x,y == wp)) {
			board->board[x2 + y2 * 8] = wq;
			board->board[x + y * 8] = 0;
			return;
			}
		else if(AIon == 1 && pieceOnSquare(board,x,y) == bp) {
			board->board[x2 + y2 * 8] = bq;
			board->board[x + y * 8] = 0;
			return;
			}
		while(1) {
		printf("please enter the piece type you want to promote your pawn to:\n(Please enter \"bishop\" \"rook\" \"knight\"or  \"queen\"\n");
		scanf("%s",promotepawn);
		if(strcmp(promotepawn,"bishop") == 0 ) {
			if(pieceOnSquare(board,x,y) == bp) {
				board->board[x2 + y2 * 8] = bb;
			}
			else {
				board->board[x2 + y2 * 8] = wb;
			}
			board->board[x + y * 8] = 0;
			break;
		}
		if(strcmp(promotepawn,"rook") == 0) {
			if(pieceOnSquare(board,x,y) == bp) {
				board->board[x2 + y2 * 8] = br;
			}
			else{
				board->board[x2 + y2 * 8] = wr;
			}
			board->board[x + y * 8] = 0;
			break;
		}
		if(strcmp(promotepawn,"knight")  == 0) {
			if(pieceOnSquare(board,x,y) == bp) {
				board->board[x2 + y2 * 8] = bh;
			}
			else {
				board->board[x2 + y2 * 8] = wh;
			}
			board->board[x + y * 8] = 0;
			break;
		}
		if(strcmp(promotepawn,"queen") == 0) {
			if(pieceOnSquare(board,x,y) == bp) {
				board->board[x2 + y2 * 8] = bq;
			}
			else {
				board->board[x2 + y2 * 8] = wq;
			}
			board->board[x + y * 8] = 0;
			break;
		}
		printf("That is not a valid piece type!\n");	
		}
	}
	else if( ((pieceOnSquare(board,x,y) == bp) 
		|| (pieceOnSquare(board,x,y) == wp)) 
		&&(pieceOnSquare(board,x2,y2) == 0) 
		&& (abs(x2 - x) == 1)
		&& (abs(y2 - y) == 1)) 
		 {
			if(pieceOnSquare(board,x,y) == bp) {
			board->board[x2 + (y2+1) * 8] = 0;
			}
			else{
			board->board[x2 + (y2 - 1) * 8] = 0;
			}
			board->board[x2 + y2 * 8] = pieceOnSquare(board,x,y);
			board->board[x + y * 8] = 0;

	}			

				
	else{		      
    	board->board[x2+(y2*8)] = board->board[x+(y*8)];
    	board->board[x+(y*8)] = 0;
	}
}

PIECES pieceOnSquare(BOARD *board, int x, int y)
{
    assert(board);
    return board->board[x + (y * 8)];
}
