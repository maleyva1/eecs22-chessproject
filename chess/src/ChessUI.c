#include "ChessUI.h"

/*board will display the board by printing gameboard*/		
void printBoard(PIECES *array)
{
	int i,j;
			
	printf("\n------------------------------------------------------\n");
	printf("\n-----------------------------------------\n");

	for(j=7;j>=0;j--)
	{
        	for(i=0;i<8;i++)
		{
			if(array[i + j * 8] == 1) printf("| bp ");
			if(array[i + j * 8] == -1) printf("| wp ");
			if(array[i + j * 8] == 4) printf("| br ");
			if(array[i + j * 8] == -4) printf("| wr ");
			if(array[i + j * 8] == 5) printf("| bb ");
			if(array[i + j * 8] == -5) printf("| wb ");
			if(array[i + j * 8] == 3) printf("| bh ");
			if(array[i + j * 8] == -3) printf("| wh ");
			if(array[i + j * 8] == 9) printf("| bq ");
			if(array[i + j * 8] == -9) printf("| wq ");
			if(array[i + j * 8] == 100) printf("| bk ");
			if(array[i + j * 8] == -100) printf("| wk ");
			if(array[i + j * 8] == 0) printf("|    ");		
        	}
        printf("| %d\n-----------------------------------------\n",j);
	}
	printf("  0    1    2    3    4    5    6    7\n------------------------------------------------------\n");
}

