#include "log.h"
#include "MoveList.h"

void printToFile(MoveList *list)
{
   if(!list)
   {
      perror("MoveList is empty! Cannot print log!\n");
   }

   Move *move = NULL;
   
   FILE *fp;
   int cX, cY, nX, nY;

   fp = fopen("log.txt", "w+");
   while(list->mostRecent != NULL)
   {
       move = getMostRecentMove(list);
       cX = move->Xbefore;
       cY = move->Ybefore;
       nX = move->Xafter;
       nY = move->Yafter;
       fprintf(fp, "%d %d to %d %d\n", cX, cY, nX, nY);
   }
   fclose(fp);
}
