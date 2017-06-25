#include <stdlib.h>
#include "RuleSet.h"
PIECES GetBoardVal(BOARD *board,int x, int y);
void SetBoardVal(BOARD *board,int x, int y,PIECES v);
int LegalMove(Move move, BOARD *board, MoveList *l, int Turn)
{
    if(!CheckBounds(move)) { return 0; }
    if( (move.Xafter == move.Xbefore) && (move.Yafter == move.Ybefore) ) { return 0; }
    if(Turn < 0 && !(move.willMove < 0)) { return 0; }
    if(Turn > 0 && !(move.willMove > 0)) {return 0; }	 
    if(!GetBoardVal(board,move.Xbefore,move.Ybefore)) { return 0; };

    if( ((GetBoardVal(board,move.Xbefore,move.Ybefore) < 0) 
                && (GetBoardVal(board,move.Xafter,move.Yafter) < 0) && (GetBoardVal(board,move.Xbefore,move.Ybefore) != wk)) 
            || ((GetBoardVal(board,move.Xbefore,move.Ybefore)) > 0 
                && (GetBoardVal(board,move.Xafter,move.Yafter) > 0) && (GetBoardVal(board,move.Xbefore,move.Ybefore) != bk))  )
    {
        return 0;
    }

    if(move.willMove == bp || move.willMove == wp) { return EvalPawn(move,board,l); }
    else if(move.willMove == bh || move.willMove == wh) { return EvalKnight(move); }
    else if(move.willMove == bb || move.willMove == wb) { return EvalBishop(move,board); }
    else if (move.willMove == br || move.willMove == wr) { return EvalRook(move,board); }
    else if (move.willMove == bq || move.willMove == wq) { return EvalQueen(move,board); }
    else if (move.willMove == bk || move.willMove == wk) { return EvalKing(move,board) || Castle(move,board,l); }
    return 0;	
}

int EvalPawn(Move move, BOARD *board,MoveList *l)
{	
    Move *prevmove = NULL;
    if(l->mostRecent){
		prevmove = l->mostRecent->index;
    }
    switch (move.willMove) 
    {
        case wp:
            {
                if( ((move.Xafter - move.Xbefore) == 0) 
                        && ((move.Yafter - move.Ybefore) == 1) 
                        && (GetBoardVal(board,move.Xafter, move.Yafter) == 0) ) { return 1; }
                else if( (abs(move.Xafter - move.Xbefore) == 1) 
                        && ((move.Yafter - move.Ybefore) == 1) 
                        && (GetBoardVal(board,move.Xafter,move.Yafter) != 0) ) { return 1; }
                else if( (move.Ybefore == 1) 
                        && ((move.Yafter - move.Ybefore) == 2) 
                        && (move.Xafter == move.Xbefore) 
                        && (GetBoardVal(board,move.Xbefore,move.Ybefore + 1) == 0) 
                        && (GetBoardVal(board,move.Xafter,move.Yafter) == 0) ) { return 1; } 
                else if ( (l->mostRecent) && (prevmove->willMove == bp) 
                        && (prevmove->Ybefore == 6) 
                        && ((prevmove->Yafter - prevmove->Ybefore) == -2) 
                        && (prevmove->Xafter == prevmove->Xbefore)  
                        && (move.Yafter == prevmove->Yafter + 1) 
                        && (move.Xafter == prevmove->Xafter) 
                        && (abs(move.Xafter - move.Xbefore) == 1) 
                        && (abs(move.Yafter - move.Ybefore) == 1) ) { return 1; }
                else return 0;
            }
        case bp:
            {
                if( ((move.Xafter - move.Xbefore) == 0) 
                        && ((move.Yafter - move.Ybefore) == -1) 
                        && (GetBoardVal(board,move.Xafter,move.Yafter) == 0) ) { return 1; }
                else if( (abs(move.Xafter - move.Xbefore) == 1) 
                        && ((move.Yafter - move.Ybefore) == -1) 
                        && (GetBoardVal(board,move.Xafter,move.Yafter) != 0)  ) { return 1; }
                else if( (move.Ybefore == 6) 
                        && ((move.Yafter - move.Ybefore) == -2) 
                        && (move.Xafter == move.Xbefore) 
                        && (GetBoardVal(board,move.Xafter,move.Yafter) == 0) 
                        && (GetBoardVal(board,move.Xbefore,move.Ybefore - 1) == 0) ) { return 1; }
                else if ( (l->mostRecent) && (prevmove->willMove == wp) 
                        && (prevmove->Ybefore == 1) 
                        && ((prevmove->Yafter - prevmove->Ybefore) == 2) 
                        && (prevmove->Xafter == prevmove->Xbefore)  
                        && (move.Yafter == prevmove->Yafter - 1) 
                        && (move.Xafter == prevmove->Xafter) 
                        && (abs(move.Xafter - move.Xbefore) == 1) 
                        && (abs(move.Yafter - move.Ybefore) == 1) ) { return 1; }
                else return 0;
            }
        default:
            return 0;
        }
}


int EvalKing(Move move,BOARD *board)
{
    if( ((GetBoardVal(board,move.Xafter,move.Yafter) < 0) 
	&& (GetBoardVal(board,move.Xbefore,move.Ybefore) == wk))
	|| ((GetBoardVal(board,move.Xafter,move.Yafter) > 0)
	&& (GetBoardVal(board,move.Xbefore,move.Ybefore) == bk)) ) {
		return 0;
	}
    if(  (abs(move.Yafter - move.Ybefore) <= 1) 
            && (abs(move.Xafter - move.Xbefore) <= 1) )
    {
	    return 1;
    }
    else { return 0; }
}


int Castle(Move move, BOARD *board,MoveList *l)
{
    if(!l->mostRecent) {
	return 0;
    }
    int i;
    PIECES king = move.willMove;
    MoveEntry *e = l->mostRecent;
    MoveEntry *n;
    Move *m;

    if( (king > 0) && ((move.Yafter != 7) 
                || ((move.Xafter != 7) 
                && (move.Xafter != 0)) 
                || (king != GetBoardVal(board,3,7)) 
                || (GetBoardVal(board,move.Xafter,move.Yafter) != br)) ) { return 0; }
    if( (king < 0) && ((move.Yafter != 0) 
                || ((move.Xafter != 7) 
                && (move.Xafter != 0)) 
                || (king != GetBoardVal(board,3,0)) 
                || (GetBoardVal(board,move.Xafter,move.Yafter) != wr)) ) { return 0; } 
    i = 3;
    while(1)
    {
        if(move.Xafter == 7) i++;
        else i--;
        if(i == move.Xafter) break;
        if(GetBoardVal(board,i,move.Yafter) != 0) return 0;
    }

    while(e) 
    {
        n = e->next;
        m = e->index;
        if( (m->Xbefore == move.Xafter) && (m->Ybefore == move.Yafter) ) return 0;
        if( (m->willMove == king)) return 0;
        e = n;
    }

    return 1;
}

int EvalQueen(Move move,BOARD *board)
{

    int i = move.Xbefore;
    int j = move.Ybefore;

    while(1)
    {
        if( (move.Xafter - move.Xbefore) > 0 ) i++;
        if( (move.Xafter - move.Xbefore) < 0 ) i--;
        if( (move.Yafter - move.Ybefore) > 0 ) j++;
        if( (move.Yafter - move.Ybefore) < 0 ) j--;
        
        if( (0 <= i) && (i <= 7) && (0 <= j) && (j <= 7) ){
        if( (i == move.Xafter) && (j == move.Yafter) ) return 1;
        if( (GetBoardVal(board,i,j) != 0) ) return 0;
        }
        else return 0;
    }
}

int EvalKnight(Move move)
{
    if( ((abs(move.Xafter - move.Xbefore) == 2) 
            && (abs(move.Yafter - move.Ybefore) == 1)) 
            || ((abs(move.Xafter - move.Xbefore) == 1) 
            && (abs(move.Yafter - move.Ybefore) == 2)) ) { return 1; }
    else { return 0; }
}

int EvalBishop(Move move,BOARD *board)
{
    int i = move.Xbefore;
    int j = move.Ybefore;

    while(1)
    {

        if( (move.Yafter - move.Ybefore) > 0 ) { j++; } 
        else { j--; }

        if( (move.Xafter - move.Xbefore) > 0 ) { i++; }
        else { i--; }

        if( (0 <= i) && (i<= 7) && (0 <= j) && (j <= 7) )
        {
            if ( (i == move.Xafter) && (j == move.Yafter) ) { return 1; }
            if(GetBoardVal(board,i,j) != 0) { return 0; }
        }
        else { return 0; }
    }
}

int CheckBounds(Move move)
{
    if( (move.Xbefore >= 0) 
            && (move.Xbefore <= 7) 
            && (move.Xafter >= 0) 
            && (move.Xafter <= 7) 
            && (move.Ybefore >= 0) 
            && (move.Ybefore <= 7) 
            && (move.Yafter >= 0) 
            && (move.Yafter <= 7) ) { return 1; }
    else { return 0; }
}

int EvalRook(Move move,BOARD *board)
{
    int i = move.Xbefore;
    int j = move.Ybefore;

    if( (abs(move.Xafter - move.Xbefore) > 0) 
            && (abs(move.Yafter - move.Ybefore) > 0) ) { return 0; }

    while (1)
    {
        if( (move.Xafter - move.Xbefore) > 0) i++;
        if( (move.Xafter - move.Xbefore) < 0) i--;
        if( (move.Yafter - move.Ybefore) > 0) j++;
        if( (move.Yafter - move.Ybefore) < 0) j--;

        if( (0 <= i) && (i <= 7) && (0 <= j) && (j <= 7) )
        {
            if( (i == move.Xafter) && (j == move.Yafter) ) return 1;
            if(GetBoardVal(board,i,j) != 0) return 0;
        }
        else return 0;
    }
}

int KCheck(PIECES Ktest, BOARD *NewBoard, MoveList *l)
{
    int i,j,KX,KY;
    Move tempmove;

    for(i = 0; i < 8; i++)
    {
        for ( j = 0; j < 8; j++)
        {
            if(GetBoardVal(NewBoard,i,j) == Ktest)
            {
                KX = i;
                KY = j;
            }
        }
    }
    for(j = 0; j < 8; j++)
    {
        for( i = 0; i < 8; i++) 
        {
                if( (Ktest == bk) && (GetBoardVal(NewBoard,i,j) < 0) ) {
                    tempmove.Xbefore = i;
                    tempmove.Ybefore = j;
                    tempmove.Xafter = KX;
                    tempmove.Yafter = KY;
                    tempmove.willMove = GetBoardVal(NewBoard,i,j);
                    if(LegalMove(tempmove,NewBoard,l,-1)) return 1;
                }
                else if( (GetBoardVal(NewBoard,i,j) > 0) && (Ktest == wk) ){
                    tempmove.Xbefore = i;
                    tempmove.Ybefore = j;
                    tempmove.Xafter = KX;
                    tempmove.Yafter = KY;
                    tempmove.willMove = GetBoardVal(NewBoard,i,j);
                    if(LegalMove(tempmove,NewBoard,l,1)) return 1;
                }
            }
    }
    return 0;
}

	
int MoveKCheck(PIECES Ktest, Move move, BOARD *board,MoveList *l)
{
    int i ,j;
    BOARD *NewBoard = NULL;
    NewBoard = createboard();


    for(i = 0; i < 8; i++)
    {
        for( j = 0; j < 8; j++)
        {
            if( (move.Xbefore == i) && (move.Ybefore == j) ) SetBoardVal(NewBoard,i,j,0);
            else if( (move.Xafter == i) && (move.Yafter == j) ) SetBoardVal(NewBoard,i,j,move.willMove);
            else SetBoardVal(NewBoard,i,j,GetBoardVal(board,i,j));
        }
    } 

    return KCheck(Ktest,NewBoard,l);
}


int Checkmate(PIECES Ktest, BOARD *board, MoveList *l)
{
    int i,j,x,y, v;
    Move tempmove;
        for(i = 0; i < 8; i++)
        {
            for (j = 0; j < 8; j++)
            {
                if( (Ktest == wk) && (GetBoardVal(board,i,j) < 0) )
                {
                    tempmove.Xbefore = i;
                    tempmove.Ybefore = j;
                    tempmove.willMove = GetBoardVal(board,i,j);
                    for(x = 0; x < 8; x++)
                    {
                        for(y = 0; y < 8; y++)
                        {
                            tempmove.Xafter = x;
                            tempmove.Yafter = y;
			    v = !MoveKCheck(Ktest,tempmove,board,l) && LegalMove(tempmove,board,l,-1);				
                            if(v) return 0;;
                        }
                    }
            
                }
                if( (Ktest == bk) && (GetBoardVal(board,i,j) > 0) )
                {
                    tempmove.Xbefore = i;
                    tempmove.Ybefore = j;
                    tempmove.willMove = GetBoardVal(board,i,j);
                    for( x = 0; x < 8; x++)
                    {
                        for ( y = 0; y < 8; y++)
                        {
                            tempmove.Xafter = x;
                            tempmove.Yafter = y;
			    v = !MoveKCheck(Ktest,tempmove,board,l) && LegalMove(tempmove,board,l,1);
                            if(v) return 0;
                        }
                    }
                }
            }
        }
    return 1;
}

PIECES GetBoardVal(BOARD *board,int x,int y){
	return board->board[x + 8 * y];
}

void SetBoardVal(BOARD *board,int x, int y, PIECES v){
	board->board[x + 8 * y] = v;
}
