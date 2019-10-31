/*Dette er et program skal lave skal udskrive inputet som en .txt fil*/

#include <stdio.h>
#include <stdlib.h>

char retter[7][20] = {"Pizza", "Lasagne", "Bøf med løg", "Burger", "Pomfritter", "Ost-fondue", "Gulash"};
char ingredienser[7][20] = {"Svampe", "Salat", "Kartofler", "Rødbeder", "Gulerod", "Ost", "Peber"};

void ascii_output(void); 

int main (){
  FILE *fp;
  int i, ugenummer = 0;

  printf("Indtast uge nummer:  ");
  scanf(" %d", &ugenummer);

   /* open the file for writing*/
   fp = fopen ("VeGen_file.txt","w");

   //fprintf(fp, " __      __   _____\n \\ \\    / /  / ____|\n  \\ \\  / /__| |  __  ___ _ __\n   \\ \\/ / _ \\ | |_ |/ _ \\ '_ \\\n    \\  /  __/ |__| |  __/ | | |\n     \\/ \\___|\\_____|\\___|_| |_|\n \n");
   fprintf(fp, " __      __   _____\n");

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

 void ascii_output(){

 }

 /*
  __      __   _____
  \ \    / /  / ____|
   \ \  / /__| |  __  ___ _ __
    \ \/ / _ \ | |_ |/ _ \ '_ \
     \  /  __/ |__| |  __/ | | |
      \/ \___|\_____|\___|_| |_|

      or


__      __                      ____        _               _
\ \    / /                     / __ \      | |             | |
 \ \  / /__  __ _  ___ _ __   | |  | |_   _| |_ _ __  _   _| |_
  \ \/ / _ \/ _` |/ _ \ '_ \  | |  | | | | | __| '_ \| | | | __|
   \  /  __/ (_| |  __/ | | | | |__| | |_| | |_| |_) | |_| | |_
    \/ \___|\__, |\___|_| |_|  \____/ \__,_|\__| .__/ \__,_|\__|
             __/ |                             | |
            |___/                              |_|


    or

__      __                                          _               _
\ \    / /                                         | |             | |
 \ \  / /__  __ _  ___ _ __    ______    ___  _   _| |_ _ __  _   _| |_
  \ \/ / _ \/ _` |/ _ \ '_ \  |______|  / _ \| | | | __| '_ \| | | | __|
   \  /  __/ (_| |  __/ | | |          | (_) | |_| | |_| |_) | |_| | |_
    \/ \___|\__, |\___|_| |_|           \___/ \__,_|\__| .__/ \__,_|\__|
             __/ |                                     | |
            |___/                                      |_|


  __      __   _____                __         _               _
  \ \    / /  / ____|              / /        | |             | |
   \ \  / /__| |  __  ___ _ __    / /__  _   _| |_ _ __  _   _| |_
    \ \/ / _ \ | |_ |/ _ \ '_ \  / / _ \| | | | __| '_ \| | | | __|
     \  /  __/ |__| |  __/ | | |/ / (_) | |_| | |_| |_) | |_| | |_
      \/ \___|\_____|\___|_| |_/_/ \___/ \__,_|\__| .__/ \__,_|\__|
                                                  | |
                                                  |_|


 */
