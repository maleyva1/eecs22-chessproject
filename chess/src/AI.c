#include "AI.h"
#include "Node.h"
/* Creates a new instance of the AI */
AI *newAI(int col)
{
    AI *temp = malloc(sizeof(AI));
    temp->moves = NULL;
    temp->color = col;

    return temp;
}

int calcGain(BOARD *board, int col)
{
    int gain = 0, x, y;

    if(col ==  -1)
    {
        for(x = 0; x < 8; x++)
        {
            for(y = 0; y < 8; y++)
            {
                /* check for white */
                if(board->board[x + (y * 8)] < 0)
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
    else if(col == 1)
    {
        /* Check for black */
        for(x = 0; x < 8; x++)
         {
             for(y = 0; y < 8; y++)
             {
                 if(board->board[x + (y * 8)]  > 0)
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
 
    /* If opponent is white */
    if(op_col == -1)
    {
        for(x = 0; x < 8; x++)
        {
            for(y = 0; y < 8; y++)
            {
                if(board->board[x + (y * 8)] < 0)
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
    else if(op_col == 1)
    {
        /* Check for black */
        for(x = 0; x < 8; x++)
         {
             for(y = 0; y < 8; y++)
             {
                 if(board->board[x + (y * 8)] > 0)
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

int evaluateBoard(BOARD *board, int col)
{
    int weight = 0;

    /* Add the total potential piece gain and subtract the potential piece loss */
    weight += calcGain(board, col) - calcThreat(board, col);

    return weight;
}

Move *getAiMove(AI *ai,BOARD *board, MoveList *history)
{
    assert(ai);


    /*ai->tree = newNode(board);*/

    /* MoveList for pieces */
    MoveList *pList, *bList, *rList, *hList, *qList, *kList;

    /* The movelist struct with all the legal moves */
    MoveList *movesTo;
    /* Add memory for the list */
    movesTo = newList();

    /* The move to return */
    Move *moveToReturn, *move;

    /* Counters for calculating best move using evaluateBoard() */
    int i, t;

    /* Initialize them */
    /*plist = newList;
    blist = newList;
    rlist = newList;
    hlist = newList;
    qlist = newList;
    klist = newList;*/

    /* Find a piece
     * Calculate all legal possible moves at it's current position
     */
    int x, y;
    for(x = 0; x < 8; x++)
    {
        for(y = 0; y < 8; y++)
        {
            /* If AI is white */
            if(ai->color == -1)
            {
                /* Search for white pieces
                 * Calculate all possible legal moves for them
                 */

                if(board->board[x + (y * 8)] < 0)
                {
                    switch(board->board[x + (y * 8)])
                    {
                        case wp:
                            {
                                /* Found a white pawn
                                 * Calculate all possible legal moves at it's
                                 */
                                pList = legalMoveList(board, x, y, history);
                                /* Loop through the legal move list for the pawn */

                                
                                while(pList->mostRecent != NULL)
                                {
                                   /* 'i' is the greatest possible piece gain */
                                    /* 't' is a move that is considered to check agains 'i' */
                                    i = 0, t = 0;
                                    /* Get the most recent move from the legal move list for the pawn */
                                    move = getMostRecentMove(pList);
                                    /* Calculate potential gain for the pawn */
                                    assert(move->Xbefore >= 0);
                                    assert(move->Ybefore >= 0);
                                    t = calcPawnGain(board->board, move->Xafter, move->Yafter);
                                    /* If the piece gain for this move is greater than the previous move
                                     * , the move we return is this move.
                                     * 'i' is then set to 't'
                                     */
                                    if(t > i)
                                    {
                                        moveToReturn = move;
                                        i = t;
                                    }
                                    /* If none have the greatest piece gain, we return some random move */
                                    else { moveToReturn = move; }
                                }
                                /* Add the move as chosen above */
                               if(pList->mostRecent!= NULL ){
                                            addMove(movesTo, newEntry(moveToReturn));
                            }
                                break;
                            }
                        case wb:
                            {
                                bList = legalMoveList(board, x, y, history);
                                while(bList->mostRecent != NULL)
                                {
                                    i = 0, t = 0;
                                    move = getMostRecentMove(bList);
                                assert(move->Xbefore >= 0);
                            assert(move->Ybefore >= 0);
                                    t = calcBishopGain(board->board, move->Xafter, move->Yafter);
                                    if(t > i)
                                    {
                                        moveToReturn = move;
                                        i = t;
                                    }
                                    else { moveToReturn = move; }
                                }
                                if(bList->mostRecent!= NULL ){
                                addMove(movesTo, newEntry(moveToReturn));
				} 
                                break;
                            }
                        case wr:
                            {
                                rList = legalMoveList(board, x, y, history);
                                while(rList->mostRecent != NULL)
                                {
                                    i = 0, t = 0;
                                    move = getMostRecentMove(rList);
                                    assert(move->Xbefore >= 0);
                                    assert(move->Ybefore >= 0);
                                    assert(move->Xafter >= 0);
                                    assert(move->Yafter >= 0);
                                    t = calcRookGain(board->board, move->Xafter, move->Yafter);
                                    if(t > i) 
                                    { 
                                        moveToReturn = move;
                                        i = t;
                                    }
                                    else { moveToReturn = move; }
                                }
				if(rList->mostRecent != NULL) {
				addMove(movesTo, newEntry(moveToReturn));
				}
                                break;
                            }
                        case wh:
                            {
                                hList = legalMoveList(board, x, y, history);
                                while(hList->mostRecent != NULL)
                                {
                                    i = 0, t = 0;
                                    move = getMostRecentMove(hList);
				    assert(move->Xbefore >= 0);
				    assert(move->Ybefore >= 0);

                                    t = calcKnightGain(board->board, move->Xafter, move->Yafter);
                                    if(t > i) 
                                    { 
                                        moveToReturn = move;
                                        i = t;
                                    }
                                    else { moveToReturn = move; }
                                }
				if(hList->mostRecent !=NULL) {
				addMove(movesTo, newEntry(moveToReturn));
				}
                                break;
                            }
                        case wq:
                            {
                                qList = legalMoveList(board, x, y, history);
                                while(qList->mostRecent != NULL)
                                {
                                    i = 0, t = 0;
                                    move = getMostRecentMove(qList);
				    assert(move->Xbefore >= 0);
				    assert(move->Ybefore >= 0);

                                    t = calcQueenGain(board->board, move->Xafter, move->Yafter);
                                    if(t > i) 
                                    { 
                                        moveToReturn = move;
                                        i = t;
                                    }
                                    else { moveToReturn = move; }
                                }
				if(qList->mostRecent != NULL) {
				addMove(movesTo, newEntry(moveToReturn));
                                }
				break;
                            }
                        case wk:
                            {
                                kList = legalMoveList(board, x, y, history);
                                while(kList->mostRecent != NULL)
                                {
                                    i = 0, t = 0;
                                    move = getMostRecentMove(kList);
				    assert(move->Xbefore >= 0);
				    assert(move->Ybefore >= 0);

                                    t = calcKingGain(board->board, move->Xafter, move->Yafter);
                                    if(t > i) 
                                    { 
                                        moveToReturn = move;
                                        i = t;
                                    }
                                    else { moveToReturn = move; }
                                }
				if(kList->mostRecent != NULL) {
				addMove(movesTo, newEntry(moveToReturn));
                                }
				break;
                            }
                        default:
                            break;
                    }
                }
            }
            else if(ai->color == 1)
            {
                switch(board->board[x + (y * 8)])
                {
                    case bp:
                        {
                            /* Found a white pawn
                             * Calculate all possible legal moves at it's
                             * current position
                             * Evaluate Moves by comparing which Move returns the highest gain
                             * Add that move to the movelist that contains moves to decide on
                             */
                            pList = legalMoveList(board, x, y, history);
                            while(pList->mostRecent != NULL)
                            {
                                i = 0, t = 0;
                                move = getMostRecentMove(pList);
				assert(move->Xbefore >= 0);
				assert(move->Ybefore >= 0);

                                t = calcPawnGain(board->board, move->Xafter, move->Yafter);
                                if(t > i)
                                {
                                    moveToReturn = move;
                                    i = t;
                                }
                                else { moveToReturn = move; }
                            }
			    if(pList->mostRecent != NULL) {
                            addMove(movesTo, newEntry(moveToReturn));
                            }
			    break;
                        }
                    case bb:
                        {
                            bList = legalMoveList(board, x, y, history);
                            while(bList->mostRecent != NULL)
                            {
                                i = 0, t = 0;
                                move = getMostRecentMove(bList);
				assert(move->Xbefore >= 0);
				    assert(move->Ybefore >= 0);

                                t = calcBishopGain(board->board, move->Xafter, move->Yafter);
                                if(t > i)
                                {
                                    moveToReturn = move;
                                    i = t;
                                }
                                else { moveToReturn = move; }
                            }
			    if(bList->mostRecent != NULL) {
                            addMove(movesTo, newEntry(moveToReturn));
			    }
                            break;
                        }
                    case br:
                        {
                            rList = legalMoveList(board, x, y, history);
                            while(rList->mostRecent != NULL)
                            {
                                i = 0, t = 0;
                                move = getMostRecentMove(rList);
				assert(move->Xbefore >= 0);
				    assert(move->Ybefore >= 0);

                                t = calcRookGain(board->board, move->Xafter, move->Yafter);
                                if(t > i) 
                                { 
                                    moveToReturn = move;
                                    i = t;
                                }
                                else { moveToReturn = move; }
                            }
			    if(rList != NULL) {
			    addMove(movesTo, newEntry(moveToReturn));
			    }
                            break;
                        }
                    case bh:
                        {
                            hList = legalMoveList(board, x, y, history);
                            while(hList->mostRecent != NULL)
                            {
                                i = 0, t = 0;
                                move = getMostRecentMove(hList);
				assert(move->Xbefore >= 0);
				    assert(move->Ybefore >= 0);

                                t = calcKnightGain(board->board, move->Xafter, move->Yafter);
                                if(t > i) 
                                { 
                                    moveToReturn = move;
                                    i = t;
                                }
                                else { moveToReturn = move; }
                            }
			    if(hList != NULL) {
			    addMove(movesTo, newEntry(moveToReturn));
			    }
                            break;
                        }
                    case bq:
                        {
                            qList = legalMoveList(board, x, y, history);
                            while(qList->mostRecent != NULL)
                            {
                                i = 0, t = 0;
                                move = getMostRecentMove(qList);
				assert(move->Xbefore >= 0);
				    assert(move->Ybefore >= 0);

                                t = calcQueenGain(board->board, move->Xafter, move->Yafter);
                                if(t > i)
                                {
                                    moveToReturn = move;
                                    i = t;
                                }
                                else { moveToReturn = move; }
                            }
			    if(qList != NULL) {
			    addMove(movesTo, newEntry(moveToReturn));
			    }
                            break;
                        }
                    case bk:
                        {
                            kList = legalMoveList(board, x, y, history);
                            while(kList->mostRecent != NULL)
                            {
                                i = 0, t = 0;
                                move = getMostRecentMove(kList);
                                assert(move->Xbefore >= 0);
                                assert(move->Ybefore >= 0);

                                t = calcKingGain(board->board, move->Xafter, move->Yafter);
                                if(t > i)
                                {
                                    moveToReturn = move;
                                    i = t;
                                }
                                else { moveToReturn = move; }
                            }
			    if(kList != NULL) {
			    addMove(movesTo, newEntry(moveToReturn));
                            }
			    break;
                        }
                    default:
                        break;
                }
            }
        }
    }

    /* Create new board state */
    /*BOARD *pawnBoard = createboard();
    BOARD *bishopBoard = createboard();
    BOARD *rookBoard= createboard();
    BOARD *knightBoard = createboard();
    BOARD *queenBoard = createboard();
    Board *kingBoard = createboard();*/

    /* Create a temporary board */
    BOARD *boardTo = createboard();
    /* Loop through moveToList
     * used boardTo to create new board state
     * evaluate the board state
     * compare the board state to previous board state
     * if higher change it
     */
    /* weight is the value of the best move
     * weightTwo is the value we compare it with */
    int weight = 0, weightTwo;
    /* Temporary move */
    Move *tempMove;
    while( (movesTo->mostRecent != NULL) && (movesTo->mostRecent->index != NULL) )
    {
        tempMove = getMostRecentMove(movesTo);
        /* Make sure we don't pass a unitialized move lmfao */
        assert(tempMove);
        assert(tempMove->Xbefore >= 0);
        assert(tempMove->Ybefore >= 0);
        if(tempMove->Xbefore < 8 && tempMove->Xbefore >= 0)
        {
            /* Copy the current board into the temporary board */
            copyboard(boardTo, board);
            /* Move a piece to a location */
            movep(boardTo, tempMove->Ybefore, tempMove->Xbefore, tempMove->Yafter, tempMove->Xafter);
            /* Evaluate the overall value of the board state */
            weightTwo = evaluateBoard(boardTo, ai->color);
            /* If this move is better than the previous move
             * , this is the move we return */
            if(weightTwo > weight)
            {
                moveToReturn = tempMove;
                weight = weightTwo;
            }
            else { moveToReturn = tempMove; }
        }
    }

    return moveToReturn;


    
    /* Move the choosen piece to the choosen position */

    /* Algorithm:
     *          While TIMER < 50 secs:
     *              Find a piece
     *                  Get all possible moves for that piece at its position
     *              If KING_SAFETY > SAFETY_THRESHOLD:
     *                  Select a random move from P, Kn, R, B or Q
     *                  Create a new node:
     *                      Create a new board state after the piece chosen moved
     *                  Add it to the tree
     *              Else:
     *                  If IN_CHECK:
     *                      Move K out of check
     *                  Else:
     *                      Find a board state that pushes KING_SAFETY >= SAFETY_THRESHOLD
     *          negaMax(ai->tree, depth, ai->color);
     */
}

/*int negaMax(Node* node, int depth, int color)
{
    assert(node);
    if(!node->child || depth = 0)
    {
        return (color * evaluateBoard(node->board));
    }

    int bestValue = -1000000000, value = 0;
    while(temp !== NULL)
    {
        value = -negaMax(temp->child, depth - 1, color);
        bestValue = max(bestValue, value);
    }

    return bestValue;
}*/
