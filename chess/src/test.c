/*test*/
#include <stdio.h>

#include "RuleSet.h" 
#include "Move.h" 
#include "MoveList.h" 
#include "board.h"
#include "log.h"
#include "ChessUI.h"

int testRules(BOARD *board,int legal,int Turn, int playerColor, PIECES KingToCheck, Move *move, MoveList *history)
{
    int choice,i, count, end = 1;
    int checkmate[50] = {6,1,6,3,4,6,4,4,5,1,5,2,3,7,7,3};
    int allMoves[50] = {0,1,0,3,1,7,0,5,0,0,0,2,3,6,3,5,4,1,4,2,2,7,5,4,3,0,7,4,4,7,3,6};
    int enpassant[50] = {0,1,0,3,7,6,7,5,0,3,0,4,1,6,1,4,0,4,1,5};
    int castling[50] = {5,1,5,3,0,6,0,5,6,1,6,3,0,5,0,4,5,0,7,2,0,4,0,3,6,0,5,2,0,3,0,2,4,0,7,0};
    int check[50] =  {6,1,6,3,4,6,4,4,5,1,5,2,0,6,0,5,4,1,4,2,3,7,7,3,4,0,4,1};
    int illegal[50] = {3,0,4,4};
    int cY, cX, mX, mY;
    int gen[50];
    
    
    while (end)
    {
        printf("1 - demo all moves\n2 - en passant\n3 - castling\n4 - check\n5 - checkmate\n6 - illegal input\n");
        printf("input 0 to end\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                count = 8;
                for (i = 0; i < 32; i++) {
                       gen[i] = allMoves[i];
                }
                break;
            case 2:
                for (i = 0; i < 20; i++) {
                       gen[i] = enpassant[i];
                }
                count = 5;
                break;
            case 3:
                for (i = 0; i < 36; i++) {
                       gen[i] = castling[i];
                }
                count = 9;
                break;
            case 4:
                for (i = 0; i < 28; i++) {
                       gen[i] = check[i];
                }
                count = 7;
                break;
            case 5:
                for (i = 0; i < 16; i++) {
                       gen[i] = checkmate[i];
                }
                count = 4;
                break;
            case 6:
                for (i = 0; i < 28; i++) {
                       gen[i] = illegal[i];
                }
                count = 1;
                break;
            default:
               end = 0;
               count = 0; 
               break;
        }
        for(i = 0; i < count; i++)
        {
            if(Turn == -1) {
		    printf("White Piece Turn:\n");
                    KingToCheck = wk;
                }
            else {
            KingToCheck = bk;
		    printf("Black Piece Turn:\n");
                }

            if(history)
            {  
                if(Checkmate(KingToCheck,board,history))
                {
                    end = 0;
                    if(Turn == 1)
                    {
                        printf("White Wins!!\n");
                        printToFile(history);
                    }
                    else {
                        printf("Black Wins!!\n");
                        printToFile(history);
                    }
                        break;
                }
            }
            cX = gen[4 * i];
            cY = gen[4 * i + 1];
            mX = gen[4 * i + 2];
            mY = gen[4 * i + 3];
            printf("(X,Y) coordinates for piece to move: (%d,%d)\n",cX,cY);
            printf("(X,Y) coordinates for place to move the piece (%d,%d)\n",mX,mY);
            move = newMove(cY, cX, mY, mX,board);
            legal = LegalMove(*move,board,history,Turn) && !(MoveKCheck(KingToCheck,*move,board,history));   
            if(!legal) 
            { printf("That is not a legal move. \n"); } 
            if(legal) {
                addMove(history, newEntry(move));
                legal = 0;
                Turn = -(Turn);
    		    movep(board, cY, cX, mY, mX,0);
            } 
                printBoard(board->board);
           
        }
        end = 0;
    }
       return 0;
      
}
