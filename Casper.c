/*Dette er et program skal lave skal udskrive inputet som en .txt fil*/

#include <stdio.h>
#include <stdlib.h>

char retter[7][20] = {"Pizza", "Lasagne", "Bøf med løg", "Burger", "Pomfritter", "Ost-fondue", "Gulash"};
char ingredienser[7][20] = {"Svampe", "Salat", "Kartofler", "Rødbeder", "Gulerod", "Ost", "Peber"};

int main (){
  FILE *fp;
  int i, ugenummer = 0;

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
       fprintf(fp, "Dag: %d",i);
       fprintf(fp, "-----------------------------------------------\n");
       fprintf(fp, "Opskrift %d: %s\n", i, retter [i]);
       fprintf(fp, "Info: 2. pers, 45. min\n");
       fprintf(fp, ">  %s\n", ingredienser[i]);
       fprintf(fp, ">  %s\n", ingredienser[i]);
       fprintf(fp, "\n");
       /*fprintf(fp, "-----------------------\n\n");*/
    }

   /* close the file*/
   fclose (fp);

   printf("Filen er genereret\n");

   return EXIT_SUCCESS;
 }
