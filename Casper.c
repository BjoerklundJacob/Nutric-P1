/*Dette er et program skal lave en .txt fil, som der skrives tekst inde i*/

#include <stdio.h>
#include <stdlib.h>

char retter[7][20] = {"Pizza", "Lasagne", "Bof_med_log", "Burger", "Pomfritter", "Ost-fondue", "Gulash"};
char ingredienser[7][20] = {"Mushroom", "Salet", "Katofler", "Rodbeder", "Gulerod", "Ost", "Peber"};
FILE *fp;
int i, ugenummer = 0;

int main ()
{

  printf("Indtast uge nummer:  ");
  scanf(" %d", &ugenummer);

   /* open the file for writing*/
   fp = fopen ("C:\\Users\\caspe\\Desktop\\VeGen_file.txt","w");

   fprintf(fp, "Uge: %d\n\n", ugenummer);

   fprintf(fp, "*********************\n");
   fprintf(fp, "Indkøbslisten:\n");
   fprintf(fp, "*********************\n");
   /* write 10 lines of text into the file stream*/
   for(i = 0; i < 7;i++){
       fprintf (fp, ">  %s\n", ingredienser[i]);
   }

   fprintf(fp, "\n*********************\n");
   fprintf(fp, "Madplan:\n");
   fprintf(fp, "*********************\n\n");

   /* write 10 lines of text into the file stream*/
   for(i = 0; i < 7;i++){
       fprintf(fp, "Dag: %d\n",i);
       fprintf(fp, "-----------------------\n");
       fprintf(fp, "%s:\n", retter [i]);
       fprintf(fp, ">  %s\n", ingredienser[i]);
       fprintf(fp, "\n");
       /*fprintf(fp, "-----------------------\n\n");*/
    }

   /* close the file*/
   fclose (fp);

   printf("Filen er lavet\n");

   return EXIT_SUCCESS;
 }
