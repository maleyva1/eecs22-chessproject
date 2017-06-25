#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "SDL/SDL.h"

#include "board.h"
#include "RuleSet.h"
#include "Move.h"
#include "MoveList.h"
#include "test.h"

#include "AI.h"
#include "log.h"
#include "ChessUI.h"
#include "BoardList.h"
int convertInput(char input);
void printMenu(void);
void printRules(void);

int main(int argc,char *argv[])
{
    int end = 1;
    int legal = 0;
    int Turn = -1;
    int playerColor = 0;
    int cY, cX, mY, mX;
    int count = 0;
    char CXY[20];
    char MXY[20];
    time_t time1;
    time_t time2;
    PIECES KingToCheck;
    /*Initialize Move object */
    Move *move = NULL;
    MoveList *history = newList();
    BOARDLIST *boardhistory = CreateBoardList();  
    /* Initialize board object */
    BOARD *board = createboard();
    int game = 0, in;

    /* Create AI */
    AI *gameAI = NULL;
    int aiColor;
    
    

    /*Create AI's for AI v AI*/
    AI *blackAI = NULL;
    AI *whiteAI = NULL;
    
    /*intalizing sdl*/
    SDL_Surface *screen;
	SDL_Surface *image;
	SDL_Surface *brook1,*brook2,*bknight1,*bknight2,*bbishop1,*bbishop2,*bking,*bqueen;
	SDL_Surface *wrook1,*wrook2,*wknight1,*wknight2,*wbishop1,*wbishop2,*wking,*wqueen;
	SDL_Surface *bpawn1,*blank;
	SDL_Surface *wpawn1;

	SDL_Surface *temp,*temp1;
	SDL_Rect src,dest;
	int x,y,i,j; 
	


	x = 0;
	y = 0;
   
	if(SDL_Init(SDL_INIT_VIDEO)!=0)
	{
		fprintf(stderr,"Could not initialize SDL video: %s\n",SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);
	screen = SDL_SetVideoMode(700,700,32,SDL_SWSURFACE);
	if(screen == NULL)
	{
				fprintf(stderr,"Could not initialize SDL video 640x480x32: %s\n",SDL_GetError());
				return 1;
	}
	/*change smiley to name of board image*/
	temp = SDL_LoadBMP("chessboard.bmp");
	if(temp == NULL)
	{
		printf("Unable to load bitmap: %s\n",SDL_GetError());
		return 1;
	}
	image = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);

	/*change image to name of each piece*/
	temp1 = SDL_LoadBMP("blackrook.bmp");
		if(temp1 == NULL)
		{
				printf("Unable to load bitmap: %s\n",SDL_GetError());
				return 1;
		}
	brook1 = SDL_DisplayFormat(temp1);
	brook2 = SDL_DisplayFormat(temp1);
	SDL_FreeSurface(temp1);
	
	temp1 = SDL_LoadBMP("whiterook.bmp");
		if(temp1 == NULL)
		{
				printf("Unable to load bitmap: %s\n",SDL_GetError());
				return 1;
		}
		wrook1 = SDL_DisplayFormat(temp1);
		wrook2 = SDL_DisplayFormat(temp1);
		SDL_FreeSurface(temp1);

	temp1 = SDL_LoadBMP("blackknight.bmp");
		if(temp1 == NULL)
		{
				printf("Unable to load bitmap: %s\n",SDL_GetError());
				return 1;
		}
		bknight1 = SDL_DisplayFormat(temp1);
	bknight2 = SDL_DisplayFormat(temp1);
		SDL_FreeSurface(temp1);

	temp1 = SDL_LoadBMP("whiteknight.bmp");
		if(temp1 == NULL)
		{
				printf("Unable to load bitmap: %s\n",SDL_GetError());
				return 1;
		}
		wknight1 = SDL_DisplayFormat(temp1);
		wknight2 = SDL_DisplayFormat(temp1);
		SDL_FreeSurface(temp1);

	temp1 = SDL_LoadBMP("blackbishop.bmp");
		if(temp1 == NULL)
		{
				printf("Unable to load bitmap: %s\n",SDL_GetError());
				return 1;
		}
		bbishop1 = SDL_DisplayFormat(temp1);
		bbishop2 = SDL_DisplayFormat(temp1);
	SDL_FreeSurface(temp1);
	
	temp1 = SDL_LoadBMP("whitebishop.bmp");
		if(temp1 == NULL)
		{
				printf("Unable to load bitmap: %s\n",SDL_GetError());
				return 1;
		}
		wbishop1 = SDL_DisplayFormat(temp1);
		wbishop2 = SDL_DisplayFormat(temp1);
		SDL_FreeSurface(temp1);

	temp1 = SDL_LoadBMP("blackqueen.bmp");
		if(temp1 == NULL)
		{
				printf("Unable to load bitmap: %s\n",SDL_GetError());
				return 1;
		}
	bqueen = SDL_DisplayFormat(temp1);
	SDL_FreeSurface(temp1);
	
	temp1 = SDL_LoadBMP("whitequeen.bmp");
		if(temp1 == NULL)
		{
				printf("Unable to load bitmap: %s\n",SDL_GetError());
				return 1;
		}
		wqueen = SDL_DisplayFormat(temp1);
		SDL_FreeSurface(temp1);

	temp1 = SDL_LoadBMP("blackking.bmp");
		if(temp1 == NULL)
		{
				printf("Unable to load bitmap: %s\n",SDL_GetError());
				return 1;
		}
	bking = SDL_DisplayFormat(temp1);
	SDL_FreeSurface(temp1);

	temp1 = SDL_LoadBMP("whiteking.bmp");
		if(temp1 == NULL)
		{
				printf("Unable to load bitmap: %s\n",SDL_GetError());
				return 1;
		}
		wking = SDL_DisplayFormat(temp1);
		SDL_FreeSurface(temp1);

	temp1 = SDL_LoadBMP("blackpawn.bmp");
		if(temp1 == NULL)
		{
				printf("Unable to load bitmap: %s\n",SDL_GetError());
				return 1;
		}
		bpawn1 = SDL_DisplayFormat(temp1);	
		SDL_FreeSurface(temp1);
		temp1 = SDL_LoadBMP("blank.bmp");
				if(temp1 == NULL)
				{
						printf("Unable to load bitmap: %s\n",SDL_GetError());
						return 1;
				}
				blank = SDL_DisplayFormat(temp1);
		SDL_FreeSurface(temp1);
		
	temp1 = SDL_LoadBMP("whitepawn.bmp");
		if(temp1 == NULL)
		{
				printf("Unable to load bitmap: %s\n",SDL_GetError());
				return 1;
		}
		wpawn1 = SDL_DisplayFormat(temp1);
		SDL_FreeSurface(temp1);
    
		src.x = 0;
		src.y = 0;
		src.w = x + image->w;
		src.h = y + image->h;
		dest.x = 0;
		dest.y = 0;
		dest.w = x + image->w;
		dest.h = y + image->h;
		
	
		       	/*load board*/
		        SDL_BlitSurface(image, &src, screen, &dest); 

			/*black pieces*/
		        SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
			SDL_Surface *array[] = {brook1,bknight1,bbishop1,bqueen,bking,bpawn1,blank};/*bbishop2,bknight2,brook2};*/
			/*SDL_Surface *array1[] = {bpawn1 ,bpawn2,bpawn3,bpawn4,bpawn5,bpawn6,bpawn7,bpawn8};*/
			SDL_Surface *array2[] = {wrook1,wknight1,wbishop1,wqueen,wking,wpawn1};/*,wbishop2,wknight2,wrook2};*/
			/*SDL_Surface *array3[] = {wpawn1,wpawn2,wpawn3,wpawn4,wpawn5,wpawn6,wpawn7,wpawn8};*/
		
    while (end) /*will keep running till end is selected*/
    {
        /* Ask the user for the color they like to start with */
        /*printf("choose a color (1 for black, 0 for white): ");*/
        /*scanf("%d", &color);*/

        /* Initializes the board */
        startboard(board);
        
        printMenu();
        printf("Choice: ");
        scanf("%d", &in);
        /*sdl stuff*/
        x=0;
                y=0;
        	 	for(j=0;j<8;j++,y+=85){
        			for(i=0;i<8;i++,x+=85){
        			{
        				dest.x =25+ x;
        				dest.y =25+ y;
        				if(*(board->board+i+(j*8))==1){
        					SDL_BlitSurface(array[5], &src, screen, &dest);
        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                              
        				}
        				if(*(board->board+i+(j*8))==-1){
        					SDL_BlitSurface(array2[5], &src, screen, &dest);
        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
        				}
        				if(*(board->board+i+(j*8))==4){
        					SDL_BlitSurface(array[0], &src, screen, &dest);
        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
        				}
        				if(*(board->board+i+(j*8))==-4){
        					SDL_BlitSurface(array2[0], &src, screen, &dest);
        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
        				}
        				if(*(board->board+i+(j*8))==5){
        					SDL_BlitSurface(array[2], &src, screen, &dest);
        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
        				}
        				if(*(board->board+i+(j*8))==-5){
        					SDL_BlitSurface(array2[2], &src, screen, &dest);
        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
        				}
        				if(*(board->board+i+(j*8))==3){
        					SDL_BlitSurface(array[1], &src, screen, &dest);
        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
        				}
        				if(*(board->board+i+(j*8))==-3){
        					SDL_BlitSurface(array2[1], &src, screen, &dest);
        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
        				}
        				if(*(board->board+i+(j*8))==9){
        					SDL_BlitSurface(array[3], &src, screen, &dest);
        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
        				}
        				if(*(board->board+i+(j*8))==-9){
        					SDL_BlitSurface(array2[3], &src, screen, &dest);
        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
        				}
        				if(*(board->board+i+(j*8))==100){
        					SDL_BlitSurface(array[4], &src, screen, &dest);
        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
        				}
        				if(*(board->board+i+(j*8))==-100){
        					SDL_BlitSurface(array2[4], &src, screen, &dest);
        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                           
        				}
                        if(*(board->board+i+(j*8))==0){
                            SDL_BlitSurface(array[6], &src, screen, &dest);
                            SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                        }    
                    /*printf("%d  %d\n",x,y);*/
        			}
        		}            
            x=0;}	
        
        
        
        switch(in)
        {
            case 1:
                {
		    addBoard(boardhistory,newBoardEntry(board));
		    /*printBoard(board->board);*/                    
                    game = 1;
                    break;
                }
            case 2:
                {
                    while(playerColor == 0)
                    {
                        printf("Please enter the color you would like to play. Enter 1 for black or -1 for white\n");
                        scanf("%d",&playerColor);
                        if( (playerColor != -1) && (playerColor != 1) )
                        {
                            printf("Incorrect input. Please try again.\n");
                            playerColor = 0;
                        }
                    }
                    if(playerColor == -1) { aiColor = 1; }
                    else { aiColor = -1; }
                    gameAI = newAI(aiColor, board);
                    game = 1;
		    addBoard(boardhistory,newBoardEntry(board));
                    /*sdl board*/
		    
		    x=0;
		                    y=0;
		            	 	for(j=0;j<8;j++,y+=85){
		            			for(i=0;i<8;i++,x+=85){
		            			{
		            				dest.x =25+ x;
		            				dest.y =25+ y;
		            				if(*(board->board+i+(j*8))==1){
		            					SDL_BlitSurface(array[5], &src, screen, &dest);
		            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		                                  
		            				}
		            				if(*(board->board+i+(j*8))==-1){
		            					SDL_BlitSurface(array2[5], &src, screen, &dest);
		            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		            				}
		            				if(*(board->board+i+(j*8))==4){
		            					SDL_BlitSurface(array[0], &src, screen, &dest);
		            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		            				}
		            				if(*(board->board+i+(j*8))==-4){
		            					SDL_BlitSurface(array2[0], &src, screen, &dest);
		            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		            				}
		            				if(*(board->board+i+(j*8))==5){
		            					SDL_BlitSurface(array[2], &src, screen, &dest);
		            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		            				}
		            				if(*(board->board+i+(j*8))==-5){
		            					SDL_BlitSurface(array2[2], &src, screen, &dest);
		            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		            				}
		            				if(*(board->board+i+(j*8))==3){
		            					SDL_BlitSurface(array[1], &src, screen, &dest);
		            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		            				}
		            				if(*(board->board+i+(j*8))==-3){
		            					SDL_BlitSurface(array2[1], &src, screen, &dest);
		            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		            				}
		            				if(*(board->board+i+(j*8))==9){
		            					SDL_BlitSurface(array[3], &src, screen, &dest);
		            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		            				}
		            				if(*(board->board+i+(j*8))==-9){
		            					SDL_BlitSurface(array2[3], &src, screen, &dest);
		            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		            				}
		            				if(*(board->board+i+(j*8))==100){
		            					SDL_BlitSurface(array[4], &src, screen, &dest);
		            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		            				}
		            				if(*(board->board+i+(j*8))==-100){
		            					SDL_BlitSurface(array2[4], &src, screen, &dest);
		            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		                               
		            				}
		            				if(*(board->board+i+(j*8))==0){
		            					SDL_BlitSurface(array[6], &src, screen, &dest);
		            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		            						                               
		            						            				}
		                        /*printf("%d  %d\n",x,y);*/
		            			}
		            		}            
		                x=0;}
                    break;
                }
            case 3:
                {                 
                    blackAI = newAI(1, board);
                    whiteAI = newAI(-1, board);
                    /*printBoard(board->board);*/
                    x=0;
                                    y=0;
                            	 	for(j=0;j<8;j++,y+=85){
                            			for(i=0;i<8;i++,x+=85){
                            			{
                            				dest.x =25+ x;
                            				dest.y =25+ y;
                            				if(*(board->board+i+(j*8))==1){
                            					SDL_BlitSurface(array[5], &src, screen, &dest);
                            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                                  
                            				}
                            				if(*(board->board+i+(j*8))==-1){
                            					SDL_BlitSurface(array2[5], &src, screen, &dest);
                            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                            				}
                            				if(*(board->board+i+(j*8))==4){
                            					SDL_BlitSurface(array[0], &src, screen, &dest);
                            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                            				}
                            				if(*(board->board+i+(j*8))==-4){
                            					SDL_BlitSurface(array2[0], &src, screen, &dest);
                            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                            				}
                            				if(*(board->board+i+(j*8))==5){
                            					SDL_BlitSurface(array[2], &src, screen, &dest);
                            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                            				}
                            				if(*(board->board+i+(j*8))==-5){
                            					SDL_BlitSurface(array2[2], &src, screen, &dest);
                            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                            				}
                            				if(*(board->board+i+(j*8))==3){
                            					SDL_BlitSurface(array[1], &src, screen, &dest);
                            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                            				}
                            				if(*(board->board+i+(j*8))==-3){
                            					SDL_BlitSurface(array2[1], &src, screen, &dest);
                            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                            				}
                            				if(*(board->board+i+(j*8))==9){
                            					SDL_BlitSurface(array[3], &src, screen, &dest);
                            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                            				}
                            				if(*(board->board+i+(j*8))==-9){
                            					SDL_BlitSurface(array2[3], &src, screen, &dest);
                            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                            				}
                            				if(*(board->board+i+(j*8))==100){
                            					SDL_BlitSurface(array[4], &src, screen, &dest);
                            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                            				}
                            				if(*(board->board+i+(j*8))==-100){
                            					SDL_BlitSurface(array2[4], &src, screen, &dest);
                            					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                               
                            				}
                            				if(*(board->board+i+(j*8))==0){
												SDL_BlitSurface(array[6], &src, screen, &dest);
												SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
																				   
																				}
                                        /*printf("%d  %d\n",x,y);*/
                            			}
                            		}            
                                x=0;}
                    
                    
                    game = 1;
                    while(game)
                    {
                        Turn = -1;
                        KingToCheck = wk;
                        if(whiteAI != NULL)
                        {
                            move = getAiMove(whiteAI, board, history, count);
                            count++;
                            if(move == NULL)
                            {
                                game = 0;
                                printf("Player wins!\n");
                            }
                            else
                            {
                                movep(board, move->Ybefore, move->Xbefore, move->Yafter, move->Xafter,1);
                            }
                            addMove(history,newEntry(move));
                        }
                        /*printBoard(board->board);*/
                        x=0;
                                        y=0;
                                	 	for(j=0;j<8;j++,y+=85){
                                			for(i=0;i<8;i++,x+=85){
                                			{
                                				dest.x =25+ x;
                                				dest.y =25+ y;
                                				if(*(board->board+i+(j*8))==1){
                                					SDL_BlitSurface(array[5], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                                     
                                				}
                                				if(*(board->board+i+(j*8))==-1){
                                					SDL_BlitSurface(array2[5], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==4){
                                					SDL_BlitSurface(array[0], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==-4){
                                					SDL_BlitSurface(array2[0], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==5){
                                					SDL_BlitSurface(array[2], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==-5){
                                					SDL_BlitSurface(array2[2], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==3){
                                					SDL_BlitSurface(array[1], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==-3){
                                					SDL_BlitSurface(array2[1], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==9){
                                					SDL_BlitSurface(array[3], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==-9){
                                					SDL_BlitSurface(array2[3], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==100){
                                					SDL_BlitSurface(array[4], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==-100){
                                					SDL_BlitSurface(array2[4], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                                   
                                				}
                                				if(*(board->board+i+(j*8))==0){
													SDL_BlitSurface(array[6], &src, screen, &dest);
													SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
																					   
																					}
                                            /*printf("%d  %d\n",x,y);*/
                                			}
                                		}            
                                    x=0;}
                        
                        
                        if(history)
                        {
                            if (Checkmate(KingToCheck, board, history))
                            {
                                game = 0;
                                printf("White Wins! \n"); 
                            }
                        }
                        Turn = 1;
                        KingToCheck = bk;
                        if(blackAI != NULL)
                        {
                            move = getAiMove(blackAI, board, history, count);
                            count++;
                            if(move == NULL)
                            {
                                game = 0;
                                printf("Player wins!\n");
                            }
                            else
                            {
                                movep(board, move->Ybefore, move->Xbefore, move->Yafter, move->Xafter,1);
                            }
                            addMove(history,newEntry(move));
                        }
                        /*printBoard(board->board);*/
                        x=0;
                                        y=0;
                                	 	for(j=0;j<8;j++,y+=85){
                                			for(i=0;i<8;i++,x+=85){
                                			{
                                				dest.x =25+ x;
                                				dest.y =25+ y;
                                				if(*(board->board+i+(j*8))==1){
                                					SDL_BlitSurface(array[5], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                                      
                                				}
                                				if(*(board->board+i+(j*8))==-1){
                                					SDL_BlitSurface(array2[5], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==4){
                                					SDL_BlitSurface(array[0], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==-4){
                                					SDL_BlitSurface(array2[0], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==5){
                                					SDL_BlitSurface(array[2], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==-5){
                                					SDL_BlitSurface(array2[2], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==3){
                                					SDL_BlitSurface(array[1], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==-3){
                                					SDL_BlitSurface(array2[1], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==9){
                                					SDL_BlitSurface(array[3], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==-9){
                                					SDL_BlitSurface(array2[3], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==100){
                                					SDL_BlitSurface(array[4], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                				}
                                				if(*(board->board+i+(j*8))==-100){
                                					SDL_BlitSurface(array2[4], &src, screen, &dest);
                                					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                                   
                                				}
                                				if(*(board->board+i+(j*8))==0){
													SDL_BlitSurface(array[6], &src, screen, &dest);
													SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
																					   
																					}
                                            /*printf("%d  %d\n",x,y);*/
                                			}
                                		}            
                                    x=0;}
                        
                        
                        if(history)
                        {
                            if(Checkmate(KingToCheck, board, history))
                            {
                                game = 0;
                                printf("Black Wins! \n");
                            }
                        }
                    }
                    break;
                }

            case 4:
                {
                    end = 0;
                    break;
                }
            case 5:
                {
                    printRules();
                    break;
                }
            case 6:
                {
                    testRules(board,legal,Turn,playerColor,KingToCheck,move,history);
                    break;
                }
            default:
                {
                    printf("That is not a valid selection.\n");
                    break;
                }
        }

        while(game)
        { 
            /*get input*/
            while (!legal)
            {
		if((Turn != playerColor) && (in != 1) ) break;
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
                        game = 0;
                        if(Turn == 1) {
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

		

		time1 = time(NULL);
                printf("You have 60 seconds to make a move!\nPlease Input before coordinates(the piece you want to move).\n");
                printf("1st digit X, 2nd digit Y, no spaces i.e \"00\" are the cordinates for the bottom left corner:\n");
                printf("Enter \"undo\" to undo your last move\n");
		scanf("%s",CXY);
		if(strcmp(CXY,"undo") == 0) {
			board = UndoBoard(boardhistory,board);
			/*printBoard(board->board);*/
			x=0;
			                y=0;
			        	 	for(j=0;j<8;j++,y+=85){
			        			for(i=0;i<8;i++,x+=85){
			        			{
			        				dest.x =25+ x;
			        				dest.y =25+ y;
			        				if(*(board->board+i+(j*8))==1){
			        					SDL_BlitSurface(array[5], &src, screen, &dest);
			        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
			                              
			        				}
			        				if(*(board->board+i+(j*8))==-1){
			        					SDL_BlitSurface(array2[5], &src, screen, &dest);
			        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
			        				}
			        				if(*(board->board+i+(j*8))==4){
			        					SDL_BlitSurface(array[0], &src, screen, &dest);
			        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
			        				}
			        				if(*(board->board+i+(j*8))==-4){
			        					SDL_BlitSurface(array2[0], &src, screen, &dest);
			        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
			        				}
			        				if(*(board->board+i+(j*8))==5){
			        					SDL_BlitSurface(array[2], &src, screen, &dest);
			        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
			        				}
			        				if(*(board->board+i+(j*8))==-5){
			        					SDL_BlitSurface(array2[2], &src, screen, &dest);
			        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
			        				}
			        				if(*(board->board+i+(j*8))==3){
			        					SDL_BlitSurface(array[1], &src, screen, &dest);
			        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
			        				}
			        				if(*(board->board+i+(j*8))==-3){
			        					SDL_BlitSurface(array2[1], &src, screen, &dest);
			        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
			        				}
			        				if(*(board->board+i+(j*8))==9){
			        					SDL_BlitSurface(array[3], &src, screen, &dest);
			        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
			        				}
			        				if(*(board->board+i+(j*8))==-9){
			        					SDL_BlitSurface(array2[3], &src, screen, &dest);
			        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
			        				}
			        				if(*(board->board+i+(j*8))==100){
			        					SDL_BlitSurface(array[4], &src, screen, &dest);
			        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
			        				}
			        				if(*(board->board+i+(j*8))==-100){
			        					SDL_BlitSurface(array2[4], &src, screen, &dest);
			        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
			                           
			        				}
			        				if(*(board->board+i+(j*8))==0){
										SDL_BlitSurface(array[6], &src, screen, &dest);
										SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
																		   
																		}
			                    /*printf("%d  %d\n",x,y);*/
			        			}
			        		}            
			            x=0;}
			
			if(in == 1) {
				Turn = -(Turn);
			}
			break;
		}
                sscanf(CXY,"%1d%1d",&cX, &cY);

              printf("Please Input after coordinates(the space you want to move the piece to):\n");
                printf("1st digit X, 2nd digit Y, no spaces i.e \"00\" are the cordinates for the bottom left corner:\n");
		scanf("%s",MXY);
                sscanf(MXY,"%1d%1d", &mX, &mY);
		time2 = time(NULL);

		if((time2 - time1) > 100000) {
		printf("Took too long to make your move!!\n You Lose!\n");
		game = 0;
		break;
		}

                move = newMove(cY, cX, mY, mX,board);
                legal = LegalMove(*move,board,history,Turn) && !(MoveKCheck(KingToCheck,*move,board,history));   
                if(!legal) { printf("That is not a legal move. Please enter a legal move.\n"); } 
                
            }
            if(game && (strcmp(CXY,"undo")) )
            {
		if(move) {
                /* Add the move to the move list */
                addMove(history, newEntry(move));

                legal = 0;
                Turn = -(Turn);
                board = StoreBoard(board);
                addBoard(boardhistory,newBoardEntry(board));               
                movep(board, cY, cX, mY, mX,0); 

		}               
                 
                if(gameAI != NULL)
                {
                    move = getAiMove(gameAI, board, history, count);
                    count++;
                    if(move == NULL)
                    {
                        game = 0;
                        printf("Checkmate! Player wins!\n");
                    }
                    else
                    {
                        movep(board, move->Ybefore, move->Xbefore, move->Yafter, move->Xafter,1);
                    }
		    Turn = -(Turn);
                }
                /*printBoard(board->board);*/
                x=0;
                                y=0;
                        	 	for(j=0;j<8;j++,y+=85){
                        			for(i=0;i<8;i++,x+=85){
                        			{
                        				dest.x =25+ x;
                        				dest.y =25+ y;
                        				if(*(board->board+i+(j*8))==1){
                        					SDL_BlitSurface(array[5], &src, screen, &dest);
                        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                              
                        				}
                        				if(*(board->board+i+(j*8))==-1){
                        					SDL_BlitSurface(array2[5], &src, screen, &dest);
                        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                        				}
                        				if(*(board->board+i+(j*8))==4){
                        					SDL_BlitSurface(array[0], &src, screen, &dest);
                        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                        				}
                        				if(*(board->board+i+(j*8))==-4){
                        					SDL_BlitSurface(array2[0], &src, screen, &dest);
                        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                        				}
                        				if(*(board->board+i+(j*8))==5){
                        					SDL_BlitSurface(array[2], &src, screen, &dest);
                        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                        				}
                        				if(*(board->board+i+(j*8))==-5){
                        					SDL_BlitSurface(array2[2], &src, screen, &dest);
                        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                        				}
                        				if(*(board->board+i+(j*8))==3){
                        					SDL_BlitSurface(array[1], &src, screen, &dest);
                        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                        				}
                        				if(*(board->board+i+(j*8))==-3){
                        					SDL_BlitSurface(array2[1], &src, screen, &dest);
                        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                        				}
                        				if(*(board->board+i+(j*8))==9){
                        					SDL_BlitSurface(array[3], &src, screen, &dest);
                        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                        				}
                        				if(*(board->board+i+(j*8))==-9){
                        					SDL_BlitSurface(array2[3], &src, screen, &dest);
                        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                        				}
                        				if(*(board->board+i+(j*8))==100){
                        					SDL_BlitSurface(array[4], &src, screen, &dest);
                        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                        				}
                        				if(*(board->board+i+(j*8))==-100){
                        					SDL_BlitSurface(array2[4], &src, screen, &dest);
                        					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                                           
                        				}
                        				if(*(board->board+i+(j*8))==0){
											SDL_BlitSurface(array[6], &src, screen, &dest);
											SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
																			   
																			}
                                    /*printf("%d  %d\n",x,y);*/
                        			}
                        		}            
                            x=0;}
                
                	
            }
        }
    }
    SDL_FreeSurface(image);
	SDL_FreeSurface(brook1);
	SDL_FreeSurface(brook2);
	SDL_FreeSurface(bknight1);
	SDL_FreeSurface(bknight2);
	SDL_FreeSurface(bbishop1);
	SDL_FreeSurface(bbishop2);
	SDL_FreeSurface(bqueen);
	SDL_FreeSurface(bking);
	SDL_FreeSurface(bpawn1);
	SDL_Quit();
    return 0;
}


int convertInput(char input)
{
    int i = input - '0';
    if (i >= 0 || i <= 7)
    {
        return i;
    }   
    else 
    {
        switch(input)
        {
            case 'a':
               return 0;
               break;
            case 'b': 
               return 1;
               break;
            case 'c':
               return 3; 
            case 'd':
               return 4;
               break;
            case 'e': 
               return 5;
               break;
            case 'f':
               return 6;
               break;
            case 'g':
               return 7;
               break;
            default: 
               return 111;
               break;      
        }
    }
}

void printMenu()
{
    printf("Select the game mode.\n");
    printf("1.      Player v. Player\n");
    printf("2.      Player v. AI\n");
    printf("3.      AI v. AI\n");
    printf("4.      Quit\n");
    printf("5.      Print rules\n");
    printf("6.      Test\n");
}
void printRules()
{
    printf("\n\nWELCOME TO A GAME OF CHESS, REGULAR CHESS RULES APPLY\n(en passant, castle, stalemate)\n \"bp\" = black pawn \"wp\" = white pawn etc.\n");
    printf("enter a two digit number \n the  first digit for x coordinate, second for y coordinate\n board coordinates start from max y value = 7 and max x value = 7 being located the the top left corner of the board\n");
    printf("\n");
}
