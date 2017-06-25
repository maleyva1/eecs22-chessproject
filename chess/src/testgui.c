#include "SDL/SDL.h"
#include "stdlib.h"
#include <stdio.h>

int main(int argc,char *argv[])
{
	SDL_Surface *screen;
	SDL_Surface *image;
	SDL_Surface *brook1,*brook2,*bknight1,*bknight2,*bbishop1,*bbishop2,*bking,*bqueen;
	SDL_Surface *wrook1,*wrook2,*wknight1,*wknight2,*wbishop1,*wbishop2,*wking,*wqueen;
	SDL_Surface *bpawn1,*bpawn2,*bpawn3,*bpawn4,*bpawn5,*bpawn6,*bpawn7,*bpawn8;
	SDL_Surface *wpawn1,*wpawn2,*wpawn3,*wpawn4,*wpawn5,*wpawn6,*wpawn7,*wpawn8;

	SDL_Surface *temp,*temp1;
	SDL_Rect src,dest;
	int x,y,i; 
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

	/*loading pieces onto board*/
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
	bpawn2 = SDL_DisplayFormat(temp1);
	bpawn3 = SDL_DisplayFormat(temp1);
	bpawn4 = SDL_DisplayFormat(temp1);
	bpawn5 = SDL_DisplayFormat(temp1);
	bpawn6 = SDL_DisplayFormat(temp1);
	bpawn7 = SDL_DisplayFormat(temp1);
	bpawn8 = SDL_DisplayFormat(temp1);
	SDL_FreeSurface(temp1);

	temp1 = SDL_LoadBMP("whitepawn.bmp");
        if(temp1 == NULL)
        {
                printf("Unable to load bitmap: %s\n",SDL_GetError());
                return 1;
        }
        wpawn1 = SDL_DisplayFormat(temp1);
        wpawn2 = SDL_DisplayFormat(temp1);
        wpawn3 = SDL_DisplayFormat(temp1);
        wpawn4 = SDL_DisplayFormat(temp1);
        wpawn5 = SDL_DisplayFormat(temp1);
        wpawn6 = SDL_DisplayFormat(temp1);
        wpawn7 = SDL_DisplayFormat(temp1);
        wpawn8 = SDL_DisplayFormat(temp1);
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
       	/*load board*/
        SDL_BlitSurface(image, &src, screen, &dest); 

	/*black pieces*/
        SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
	SDL_Surface *array[] = {brook1,bknight1,bbishop1,bqueen,bking,bbishop2,bknight2,brook2};
	SDL_Surface *array1[] = {bpawn1,bpawn2,bpawn3,bpawn4,bpawn5,bpawn6,bpawn7,bpawn8};
	SDL_Surface *array2[] = {wrook1,wknight1,wbishop1,wqueen,wking,wbishop2,wknight2,wrook2};
        SDL_Surface *array3[] = {wpawn1,wpawn2,wpawn3,wpawn4,wpawn5,wpawn6,wpawn7,wpawn8};


while(true){    
	for(i=0;i<8;i++)
	{
		dest.x = 25 +x;
		dest.y = 25;
        if(==){
		SDL_BlitSurface(array[i], &src, screen, &dest);
       		SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		dest.x = 25 +x;
		dest.y = 625 +y;
		SDL_BlitSurface(array2[i],&src,screen,&dest);
		SDL_UpdateRect(screen, dest.x,dest.y,dest.w, dest.h);
		x += 85;	
	}
	x=0;
	for(i=0;i<8;i++)
	{
		dest.x = 25 +x;
                dest.y = 105;
                SDL_BlitSurface(array1[i], &src, screen, &dest);
                SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		dest.x = 25 +x;
		dest.y = 545+y;
		SDL_BlitSurface(array3[i],&src,screen,&dest);
		SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		x+=85;
	}	
	
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
	SDL_FreeSurface(bpawn2);
	SDL_FreeSurface(bpawn3);
	SDL_FreeSurface(bpawn4);
	SDL_FreeSurface(bpawn5);
	SDL_FreeSurface(bpawn6);
	SDL_FreeSurface(bpawn7);
	SDL_FreeSurface(bpawn8);
	SDL_FreeSurface(wrook1);
        SDL_FreeSurface(wrook2);
        SDL_FreeSurface(wknight1);
        SDL_FreeSurface(wknight2);
        SDL_FreeSurface(wbishop1);
        SDL_FreeSurface(wbishop2);
        SDL_FreeSurface(wqueen);
        SDL_FreeSurface(wking);
        SDL_FreeSurface(wpawn1);
        SDL_FreeSurface(wpawn2);
        SDL_FreeSurface(wpawn3);
        SDL_FreeSurface(wpawn4);
        SDL_FreeSurface(wpawn5);
        SDL_FreeSurface(wpawn6);
        SDL_FreeSurface(wpawn7);
        SDL_FreeSurface(wpawn8);
	SDL_Quit();
	return 0;
}
