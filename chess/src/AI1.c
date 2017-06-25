#include "AI.h"

/* Creates a new instance of the AI */
AI *newAI(int col, BOARD *board)
{
    AI *temp = malloc(sizeof(AI));
    temp->moves = NULL;
    temp->color = col;
    temp->tourney = newList();
    Move *mover = newMove(2, 6, 3, 7, board);
    Move *tempT = newMove(4, 0, 2, 2, board);
    Move *tempTT = newMove(2, 0, 5, 3, board);
    Move *tempTTT = newMove(3, 1, 3, 2, board);
    addMove(temp->tourney, newEntry(mover));
    addMove(temp->tourney, newEntry(tempT));
    addMove(temp->tourney, newEntry(tempTT));
    addMove(temp->tourney, newEntry(tempTTT));

    return temp;
}

int calcGain(BOARD *board, int col)
{
    int gain = 0, x, y;

    if(col ==  1)
    {
        for(x = 0; x < 8; x++)
        {
            for(y = 0; y < 8; y++)
            {
                /* check for white */
                if(board->board[x + (y * 8)] > 0)
                {
                    /* Check what piece is on that space */
                    switch(board->board[x + (y * 8)])
                    {
                        case bp:
                            {
                                /* Checkbound checks if the coordinates are within the board */
                                if(checkBounds(x, y) == 0)
                                {
                                    gain += calcPawnGain(board->board, x, y);
                                }
                                break;
                            }
                        /* Knight */
                        case bh:
                            {
                                if(checkBounds(x, y) == 0)
                                {
                                    gain += calcKnightGain(board->board, x, y);
                                }
                                break;
                            }
                        case br:
                            {
                                if(checkBounds(x, y) == 0)
                                {
                                    gain += calcRookGain(board->board, x, y);
                                }
                                break;
                            }
                        case bb:
                            {
                                if(checkBounds(x ,y) == 0)
                                {
                                    gain += calcBishopGain(board->board, x, y);
                                }
                            }
                        case bq:
                            {
                                if(checkBounds(x, y) == 0)
                                {
                                    gain += calcQueenGain(board->board, x, y);
                                }
                                break;
                            }
                        case bk:
                            {
                               if(checkBounds(x, y) == 0)
                               {
                                  gain += calcKingGain(board->board, x, y); 
                               }
                               break;
                            }
                        default:
                            break;
                    }
                }
            }
        }
    }
    else if(col == -1)
    {
        /* Check for black */
        for(x = 0; x < 8; x++)
         {
             for(y = 0; y < 8; y++)
             {
                 if(board->board[x + (y * 8)]  < 0)
                 {
                     /* Check what piece is on the space */
                     switch(board->board[x + (y * 8)])
                     {
                         case wp:
                             {
                                 if(checkBounds(x, y) == 0)
                                 {
                                     gain += calcPawnGain(board->board, x, y);
                                 }
                                 break;
                             }
                         /* Knight */
                         case wh:
                             {
                                 if(checkBounds(x, y) == 0)
                                 {
                                     gain += calcKnightGain(board->board, x, y);
                                 }
                                 break;
                             }
                         case wr:
                             {
                                 if(checkBounds(x, y) == 0)
                                 {
                                     gain += calcRookGain(board->board, x, y);
                                 }
                                 break;
                             }
                         case wb:
                             {
                                 if(checkBounds(x ,y) == 0)
                                 {
                                     gain += calcBishopGain(board->board, x, y);
                                 }
                             }
                         case wq:
                             {
                                 if(checkBounds(x, y) == 0)
                                 {
                                     gain += calcQueenGain(board->board, x, y);
                                 }
                                 break;
                             }
                         case wk:
                             {
                                if(checkBounds(x, y) == 0)
                                {
                                   gain += calcKingGain(board->board, x, y); 
                                }
                                break;
                             }
                         default:
                             break;
                     }
                 }
             }
         } 
    }

     
    
    /* for i in tempBoard do
    *      search for pieces:
    *          if i < 0
    *               if -1, then
    *              search diagonally for pieces > 0
    *                  if any can be captured, gain += piece_value
    *              else if -3, then
    *              search 
    *                  if can_capture, gain += piece_value
    *              else if -4, then
    *              search
    *                  if can_capture, gain += piece_value
    *              else if -9, then 
    *              search around its position for p > 0
    *                  if can capture, gain += piece_value
    */
    
    return gain;
}

int calcThreat(BOARD *board, int col)
{
    int threat = 0, x, y, op_col;

    /* Algorithm for searching for threats is same as calcGain's */
    if(col == -1) { op_col = 1; }
    else if(col == 1) { op_col = -1; }
 
    if(op_col == 1)
    {
        for(x = 0; x < 8; x++)
        {
            for(y = 0; y < 8; y++)
            {
                if(board->board[x + (y * 8)] > 0)
                {
                    switch(board->board[x + (y * 8)])
                    {
                        case bp:
                            {
                                if(checkBounds(x, y) == 0)
                                {
                                    threat += calcPawnGain(board->board, x, y);
                                }
                                break;
                            }
                        /* Knight*/
                        case bh:
                            {
                                if(checkBounds(x, y) == 0)
                                {
                                    threat += calcKnightGain(board->board, x, y);
                                }
                                break;
                            }
                        case br:
                            {
                                if(checkBounds(x, y) == 0)
                                {
                                    threat += calcRookGain(board->board, x, y);
                                }
                                break;
                            }
                        case bb:
                            {
                                if(checkBounds(x ,y) == 0)
                                {
                                    threat += calcBishopGain(board->board, x, y);
                                }
                            }
                        case bq:
                            {
                                if(checkBounds(x, y) == 0)
                                {
                                    threat += calcQueenGain(board->board, x, y);
                                }
                                break;
                            }
                        case bk:
                            {
                               if(checkBounds(x, y) == 0)
                               {
                                  threat += calcKingGain(board->board, x, y); 
                               }
                               break;
                            }
                        default:
                            break;
                    }
                }
            }
        }
    }
    else if(op_col == -1)
    {
        /* Check for black */
        for(x = 0; x < 8; x++)
         {
             for(y = 0; y < 8; y++)
             {
                 if(board->board[x + (y * 8)] < 0)
                 {
                     switch(board->board[x + (y * y)])
                     {
                         case wp:
                             {
                                 if(checkBounds(x, y) == 0)
                                 {
                                     threat += calcPawnGain(board->board, x, y);
                                 }
                                 break;
                             }
                         /* Knight */
                         case wh:
                             {
                                 if(checkBounds(x, y) == 0)
                                 {
                                     threat += calcKnightGain(board->board, x, y);
                                 }
                                 break;
                             }
                         case wr:
                             {
                                 if(checkBounds(x, y) == 0)
                                 {
                                     threat += calcRookGain(board->board, x, y);
                                 }
                                 break;
                             }
                         case wb:
                             {
                                 if(checkBounds(x ,y) == 0)
                                 {
                                     threat += calcBishopGain(board->board, x, y);
                                 }
                             }
                         case wq:
                             {
                                 if(checkBounds(x, y) == 0)
                                 {
                                     threat += calcQueenGain(board->board, x, y);
                                 }
                                 break;
                             }
                         case wk:
                             {
                                if(checkBounds(x, y) == 0)
                                {
                                   threat += calcKingGain(board->board, x, y); 
                                }
                                break;
                             }
                         default:
                             break;
                     }
                 }
             }
         } 
    }
    return threat;
}

/*int calcKingsafety(BOARD *board)
{
    int safe = 0;

    // Get all of opponent's legal moves
    // for all opp's pieces:
    //      Check if any of your pieces is in surrounding the king
    //          if yes add it's ABS value to safe
    //          else calculate the opp's piece distance to the king
    //               and add it's negative value to safe

    return safe;
}*/

int evaluateBoard(BOARD *board, int col, MoveList *history)
{
    int weight = 0;

    /* Add the total potential piece gain and subtract the potential piece loss */
    weight += (calcGain(board, col) - calcThreat(board, col)) + boardControl(board, col, history);

    return weight;
}

Move *getAiMove(AI *ai,BOARD *board, MoveList *history, int count)
{
    assert(ai);


    ai->tree = newNode(board->board, NULL);

    /* MoveList for pieces */
    /*MoveList *pList, *bList, *rList, *hList, *qList, *kList;*/

    /* The movelist struct with all the legal moves */
    /*MoveList *movesTo;*/
    /* Add memory for the list */
    /*movesTo = newList();*/

    /* The move to return */
    Move *moveToReturn, *move;
    BOARD *tempBoard;
    BOARD *EtempBoard = NULL;

    /* Find a piece
     * Calculate all legal possible moves at it's current position
     */
    int enemyEval = 10000, q;

    /* Create a temporary board */
    /*BOARD *boardTo = createboard();*/
    /* Loop through moveToList
     * used boardTo to create new board state
     * evaluate the board state
     * compare the board state to previous board state
     * if higher change it
     */
    MoveList *legalMoves = AllLegalMoveList(board, history, ai->color);
    if(legalMoves->mostRecent == NULL)
    {
        return NULL;
    }

    /* weight is the value of the best move
     * weightTwo is the value we compare it with */
    int weight = 0, weightTwo, opCol;
    
    if(ai->color == -1 && count < 5)
    {
        return getMostRecentMove(ai->tourney);
    }

    /* Temporary move */
    Move *tempMove;
    if(ai->color == -1) { opCol = 1; }
    else { opCol = -1; }
    while(legalMoves->mostRecent != NULL && legalMoves->mostRecent->index != NULL)
    {
        tempMove = getMostRecentMove(legalMoves);

        moveToReturn = tempMove;

        if(tempMove->Xbefore < 8 && tempMove->Xbefore >= 0 && tempMove->Ybefore < 8 && tempMove->Ybefore >= 0 
                && tempMove->Yafter < 8 && tempMove->Yafter >= 0 && tempMove->Xafter < 8 && tempMove->Xafter >= 0)
        {
            for(q = 0; q < 3; q++)
            {  
                tempBoard = createboard();
                copyboard(tempBoard, board);
                movep(tempBoard,tempMove->Ybefore,tempMove->Xbefore,tempMove->Yafter,tempMove->Xafter,1);

                MoveList *EnemyList = AllLegalMoveList(tempBoard,history,opCol);

                while(EnemyList->mostRecent != NULL)
                {
                    move = getMostRecentMove(EnemyList);
                    movep(tempBoard,move->Ybefore,move->Xbefore,move->Yafter,move->Xafter, 1);
                    if(evaluateBoard(tempBoard, opCol, history) < enemyEval)
                    movep(tempBoard,move->Ybefore,move->Xbefore,move->Yafter,move->Xafter,1);
                    if(evaluateBoard(tempBoard, opCol, history) < enemyEval)
                    {
                        enemyEval = evaluateBoard(tempBoard, opCol, history);
                        EtempBoard = tempBoard;
                    }
                }

                if(EtempBoard != NULL)
                {
                    tempBoard = EtempBoard;
                }
                Node *tempNode = newNode(tempBoard->board, tempMove);
                insert(tempNode,ai->tree);
                tempNode->weight = evaluateBoard(tempBoard, ai->color, history);
            }

            Node *temp = ai->tree;
            while(temp != NULL) { temp = temp->child; }
            while(temp != NULL)
            {
                weightTwo = getWeight(temp);
                if(weightTwo > weight)
                {
                    weight = weightTwo;
                    moveToReturn = temp->move;
                }
                temp = temp->parent;
            }
        }
    }

    return moveToReturn;
}
