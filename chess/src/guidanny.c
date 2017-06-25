#include "SDL/SDL.h"
#include "stdlib.h"
#include <stdio.h>

int main(int argc,char *argv[])
{
	SDL_Surface *screen;
	SDL_Surface *image;
	SDL_Surface *brook1,*brook2,*bknight1,*bknight2,*bbishop1,*bbishop2,*bking,*bqueen;
	SDL_Surface *wrook1,*wrook2,*wknight1,*wknight2,*wbishop1,*wbishop2,*wking,*wqueen;
	SDL_Surface *bpawn1;
	SDL_Surface *wpawn1;

	SDL_Surface *temp,*temp1;
	SDL_Rect src,dest;
	int x,y,i,j; 
	
	/*arrayb[0]=1;
    arrayb[1]=-1;
    arrayb[25]=1;
    arrayb[34]=1;
    arrayb[47]=-1;
    arrayb[54]=1;*/
    /*arrayb[1]=1;*/
	SDL_Event event;
	int running = 1;
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

	temp1 = SDL_LoadBMP("whitepawn.bmp");
        if(temp1 == NULL)
        {
                printf("Unable to load bitmap: %s\n",SDL_GetError());
                return 1;
        }
        wpawn1 = SDL_DisplayFormat(temp1);
        SDL_FreeSurface(temp1);
/*initialized SDL, board,and pieces*/
/*------------------------------------------------------------------------------*/
	src.x = 0;
	src.y = 0;
	src.w = x + image->w;
	src.h = y + image->h;
	dest.x = 0;
	dest.y = 0;
	dest.w = x + image->w;
	dest.h = y + image->h;


	int arrayb[64]={
        1,-1,0,0,0,0,1,-9,
        -100,-1,0,0,0,0,1,100,
        4,-1,0,0,0,0,1,100,
        5,-1,0,0,100,0,1,3,
        -5,-1,0,-100,0,0,1,1,
        9,-1,0,0,0,0,1,-4,
        9,-1,0,0,0,100,1,-3,
        -9,-1,0,0,0,0,1,3};
       	/*load board*/
        SDL_BlitSurface(image, &src, screen, &dest); 

	/*black pieces*/
        SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
	SDL_Surface *array[] = {brook1,bknight1,bbishop1,bqueen,bking,bpawn1};/*bbishop2,bknight2,brook2};*/
	/*SDL_Surface *array1[] = {bpawn1 ,bpawn2,bpawn3,bpawn4,bpawn5,bpawn6,bpawn7,bpawn8};*/
	SDL_Surface *array2[] = {wrook1,wknight1,wbishop1,wqueen,wking,wpawn1};/*,wbishop2,wknight2,wrook2};*/
	/*SDL_Surface *array3[] = {wpawn1,wpawn2,wpawn3,wpawn4,wpawn5,wpawn6,wpawn7,wpawn8};*/

	while(running && SDL_WaitEvent(&event))
        {
                switch(event.type)
                {
                        /*case SDL_MOUSEBUTTONDOWN:
                       {
                       	dest.x = event.button.x;
			dest.y = event.button.y;
			SDL_BlitSurface(image, &src, screen, &dest);
			SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
			break;
			}*/
                        case SDL_QUIT:
                        {
                                running = 0;
                                break;
                        }
                        default:
                        {
                                break;
                        }
                }
        x=0;
        y=0;
	 	for(j=0;j<8;j++,y+=85){
			for(i=0;i<8;i++,x+=85){
			{
				dest.x =25+ x;
				dest.y =25+ y;
				if(arrayb[i+j*8]==1){
					SDL_BlitSurface(array[5], &src, screen, &dest);
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                    printf("%d  %d   %d\n",x,y,i+(j*8));  
				}
				if(arrayb[i+j*8]==-1){
					SDL_BlitSurface(array2[5], &src, screen, &dest);
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
				}
				if(arrayb[i+j*8]==4){
					SDL_BlitSurface(array[0], &src, screen, &dest);
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
				}
				if(arrayb[i+j*8]==-4){
					SDL_BlitSurface(array2[0], &src, screen, &dest);
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
				}
				if(arrayb[i+j*8]==5){
					SDL_BlitSurface(array[2], &src, screen, &dest);
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
				}
				if(arrayb[i+j*8]==-5){
					SDL_BlitSurface(array2[2], &src, screen, &dest);
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
				}
				if(arrayb[i+j*8]==3){
					SDL_BlitSurface(array[1], &src, screen, &dest);
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
				}
				if(arrayb[i+j*8]==-3){
					SDL_BlitSurface(array2[1], &src, screen, &dest);
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
				}
				if(arrayb[i+j*8]==9){
					SDL_BlitSurface(array[3], &src, screen, &dest);
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
				}
				if(arrayb[i+j*8]==-9){
					SDL_BlitSurface(array2[3], &src, screen, &dest);
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
				}
				if(arrayb[i+j*8]==100){
					SDL_BlitSurface(array[4], &src, screen, &dest);
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
				}
				if(arrayb[i+j*8]==-100){
					SDL_BlitSurface(array2[4], &src, screen, &dest);
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
                   
				}
            /*printf("%d  %d\n",x,y);*/
			}
		}            
    x=0;}	
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
