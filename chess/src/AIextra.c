#include "board.h"
#include "Move.h"
#include "RuleSet.h"
#include "MoveList.h"

int boardControl(BOARD *board,int PceColor,MoveList *l) {
int i, j,x,y,points = 0;
Move tempmove;
for( i = 0; i < 8; i++)
{
	for (j = 0; j < 8; j++)
    {
		if( (PceColor < 0) && (pieceOnSquare(board,i,j) < 0) ) 
        {
			for(x = 0; x < 8; x++)
            {
				for( y = 0; y < 8; y++) 
                {
					tempmove.willMove = pieceOnSquare(board,i,j);
					tempmove.Xbefore = i;
					tempmove.Ybefore = j;
					tempmove.Xafter = x;
					tempmove.Yafter = y;
					points += LegalMove(tempmove,board,l,-1);
				}
			}
		}
		if( (PceColor > 0) && (pieceOnSquare(board,i,j) > 0) ) {
				for( x = 0; x < 8; x++ ){
					for( y = 0; y < 8; y++) {
						tempmove.willMove = pieceOnSquare(board,i,j);
						tempmove.Xbefore = i;
						tempmove.Ybefore = j;
						tempmove.Xafter = x;
						tempmove.Yafter = y;
						points += LegalMove(tempmove,board,l,1);
					}
				}
		}
	}
}
return points;
}

/*CalcKingsafety*/	 
