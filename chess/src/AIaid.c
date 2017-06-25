#include "AIaid.h"
#include <assert.h>
int checkBounds(int x, int y)
{
    return (x < 7 && y < 7 && x > 0 && y > 0);
}

void copyBoards(PIECES tboard[][8], PIECES* board)
{
    int x, y;
    for(x = 0; x < 8; x++)
    {
        for(y = 0; y < 8; y++)
        {
            tboard[x][y] = board[x + (y * 8)];
        }
    }
}

int calcPawnGain(PIECES *pboard, int x, int y)
{
    int value = 0;
    PIECES board[8][8];
    copyBoards(board, pboard);

    /* If AI is white */
    if(board[x][y] == 0)
    {
        if(x == 0)
        {
            if(board[x + 1][y - 1] > 0)
            {
                value += board[x + 1][y - 1];
            }
        }
        else if(x == 7)
        {
            if(board[x - 1][y - 1] > 0)
            {
                value += board[x - 1][y - 1];
            }
        }
        else
        {
            if(board[x + 1][y - 1] > 0)
            {
                value += board[x + 1][y - 1];
            }
            if(board[x - 1][y - 1] > 0)
            {
                value += board[x - 1][y - 1];
            }
        }
    }
    else
    {
        if(x == 0)
        {
            if(board[x + 1][y - 1] < 0)
            {
                value += board[x + 1][y - 1];
            }
        }
        else if(x == 7)
        {
            if(board[x - 1][y - 1] < 0)
            {
                value += board[x - 1][y - 1];
            }
        }
        else
        {
            if(board[x + 1][y - 1] < 0)
            {
                value += board[x + 1][y - 1];
            }
            if(board[x - 1][y - 1] < 0)
            {
                value += board[x - 1][y - 1];
            }
        }
    }
    return value;
}

int calcKnightGain(PIECES *pboard, int x, int y)
{
    int value = 0;
    PIECES board[8][8];
    copyBoards(board, pboard);

    if(board[x - 1][y - 2] > 0)
    {
        value += board[x - 1][y - 2];
    }
    if(board[x + 1][y - 2] > 0)
    {
        value += board[x + 1][y - 2];
    }

    return value;
}

int calcRookGain(PIECES *pboard, int x, int y)
{
    int value = 0, i = 0;
    PIECES board[8][8];
    copyBoards(board, pboard);

    while(board[x][y - i] >= 0)
    {
        if(board[x][y - i] > 0)
        {
            value += board[x][y - i];
            break;
        }
        i++;
    }
    i = 0;
    while(board[x][y + i] <= 8)
    {
        if(board[x][y + i] > 0)
        {
            value += board[x][y + i];
            break;
        }
        i++;
    }
    i = 0;
    while(board[x + i][y] <= 8)
    {
        if(board[x + i][y] > 0)
        {
            value += board[x + i][y];
            break;
        }
        i++;
    }
    i = 0;
    while(board[x - i][y] >= 0)
    {
        if(board[x - i][y] > 0)
        {
            value += board[x - i][y];
            break;
        }
        i++;
    }
    return value;
}

int calcBishopGain(PIECES *pboard, int x, int y)
{
    int value = 0, i = 0;
    PIECES board[8][8];
    copyBoards(board, pboard);

    while(board[x + i][y - i] <= 0)
    {
        if(board[x + i][y - i] > 0)
        {
            value += board[x + i][y - i];
            break;
        }
        i++;
    }
    i = 0;
    while(board[x - i][y - i] <= 0)
    {
        if(board[x - i][y - i] > 0)
        {
            value += board[x - i][y - i];
            break;
        }
        i++;
    }
    i = 0;
    while(board[x + i][y + i] <= 8)
    {
        if(board[x + i][y + i] > 0)
        {
            value += board[x + i][y + i];
            break;
        }
        i++;
    }
    i = 0;
    while(board[x - i][y + i] <= 8)
    {
        if(board[x - i][y + i] > 0)
        {
            value += board[x - i][y + i];
            break;
        }
        i++;
    }
    return value;
}

int calcQueenGain(PIECES *pboard, int x, int y)
{
    int value = 0, i = 0;
    PIECES board[8][8];
    copyBoards(board, pboard);   

    while(board[x][y - i] >= 0)
    {
        if(board[x][y - i] > 0)
        {
            value += board[x][y - i];
            break;
        }
        i++;
    }
    i = 0;
    while(board[x][y + i] < 8)
    {
        if(board[x][y + i] > 0)
        {
            value += board[x][y + i];
            break;
        }
        i++;
    }
    i = 0;
    while(board[x - i][y] >= 0)
    {
        if(board[x - i][y] > 0)
        {
            value += board[x - i][y];
            break;
        }
        i++;
    }
    i = 0;
    while(board[x + i][y] >= 8)
    {
        if(board[x + i][y] > 0)
        {
            value += board[x + i][y];
            break;
        }
        i++;
    }
    i = 0;
    while(board[x + i][y - i] <= 0)
    {
        if(board[x + i][y - i] > 0)
        {
            value += board[x + i][y - i];
            break;
        }
        i++;
    }
    i = 0;
    while(board[x - i][y - i] <= 0)
    {
        if(board[x - i][y - i] > 0)
        {
            value += board[x - i][y - i];
            break;
        }
        i++;
    }
    i = 0;
    while(board[x + i][y + i] <= 8)
    {
        if(board[x + i][y + i] > 0)
        {
            value += board[x + i][y + i];
            break;
        }
        i++;
    }
    i = 0;
    while(board[x - i][y + i] <= 8)
    {
        if(board[x - i][y + i] > 0)
        {
            value += board[x - i][y + i];
            break;
        }
        i++;
    }
    return value;
}

int calcKingGain(PIECES *pboard, int x, int y)
{
   PIECES board[8][8];
   copyBoards(board, pboard);
   int value = 0;
   if(board[x][y - 1] > 0)
   {
       value += board[x][y + 1];
   }
   if(board[x][y + 1] > 0)
   {
       value += board[x][y + 1];
   }
   if(board[x - 1][y] > 0)
   {
       value += board[x - 1][y];
   }
   if(board[x + 1][y] > 0)
   {
       value += board[x + 1][y];
   }
   return value;
}

MoveList *legalMoveList(BOARD *board, int x, int y,MoveList *PrevMoves) {
    MoveList *l = NULL;
    MoveEntry *e = NULL;
    Move *tempmove = NULL;
    Move testmove;
	l = newList();
    testmove.willMove = pieceOnSquare(board,x,y);
    testmove.Xbefore = x;
    testmove.Ybefore = y;
    /* Checki if K is in check */
	PIECES Ktest;

	int i,j, Turn;



	if(pieceOnSquare(board,x,y) < 0) {
		Ktest = wk;
		Turn = -1;
	}
	else {
		Ktest = bk;
		Turn = 1;
	}

	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++){
			testmove.Xafter = i;
			testmove.Yafter = j;
			if(LegalMove(testmove,board,PrevMoves,Turn) 
                    && !MoveKCheck(Ktest, testmove, board, PrevMoves)){
				
	            tempmove = newMove(y, x, j, i, board);
		    tempmove->willMove = pieceOnSquare(board,x,y);
		    assert(tempmove);
		    assert(tempmove->Xbefore >= 0);
		    assert(tempmove->Ybefore >= 0);
		    assert(tempmove->Xafter >= 0);
		    assert(tempmove->Yafter >= 0);
				e = newEntry(tempmove);
				addMove(l,e);
			}
		}
	}
return l;
}
MoveList *AllLegalMoveList(BOARD *board,MoveList *PrevMoves,int PieceColor) {
    MoveList *l = NULL;
    MoveEntry *e = NULL;
    Move *tempmove = NULL;
    Move testmove;
    PIECES Ktest;
    l = newList();
    int i,j,x,y;
    if (PieceColor == -1) {
        Ktest = wk;
    }
    else{
        Ktest = bk;
    }
	for(i = 0;i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if( (pieceOnSquare(board,i,j) < 0)
				&& (PieceColor < 0) ){
				testmove.Xbefore = i;
				testmove.Ybefore = j;
				testmove.willMove = pieceOnSquare(board,i,j);
				for(x = 0; x < 8; x++) {
					for( y = 0; y < 8; y++) {
						testmove.Xafter = x;
						testmove.Yafter = y;
						if(LegalMove(testmove,board,PrevMoves,PieceColor) 
                             && (!MoveKCheck(Ktest,testmove,board,PrevMoves)) ) {
							tempmove = newMove(j,i,y,x,board);
                           
							tempmove->willMove = pieceOnSquare(board,i,j);
							e = newEntry(tempmove);
							addMove(l,e);
						}
					}
				}
			}
			if( (pieceOnSquare(board,i,j) > 0) 
				&& (PieceColor > 0) ) {
				testmove.Xbefore = i;
				testmove.Ybefore = j;
				testmove.willMove = pieceOnSquare(board,i,j);
				for(x = 0; x < 8; x++) {
					for (y = 0; y < 8; y++) {
						testmove.Xafter = x;
						testmove.Yafter = y;
						if(LegalMove(testmove,board,PrevMoves,PieceColor)
                            && (!MoveKCheck(Ktest,testmove,board,PrevMoves)) ) {
							tempmove = newMove(j,i,y,x,board);
							tempmove->willMove = pieceOnSquare(board,i,j);
							e = newEntry(tempmove);
							addMove(l,e);
						}
					}
				}
			}
		}
	}
return l;
}
