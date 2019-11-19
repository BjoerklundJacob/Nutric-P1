/*
 * Dette er koden til at outputte til en fil
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/***** STRUCTS *****/
typedef struct _RECIPE{
  char *name;
  int prep_time;
  int cook_time;
  int servings;
  int *amount;
  int length;
  char **unit;
  char **ingredients;
  /*NUTRIENT *nutrients;*/
} RECIPE;

/*Her under er der 2 char arrays med ugenummer og 7 random ingredienser*/
char week[7][15] = {"Monday", "Tuesday", "Wensday", "Thursday", "Friday", "Saturday", "Sunday"};
char ingredienser[7][20] = {"Svampe", "Salat", "Kartofler", "Rødbeder", "Gulerod", "Ost", "Peber"};


void print_mealplan_to_file(int weeknumber, struct _RECIPE res[]);


int main() {
  int weeknumber = 0; 

  /*Array af strucs med opskrifter, grunden til array er at det er nemmere at printe det efter*/
  struct _RECIPE res[8]; 
  res[1].name = "Pie",            
  res[1].prep_time = 20,  
  res[1].cook_time = 10,
  res[1].servings = 2;
  
  res[2].name = "Meatpie", 
  res[2].prep_time = 10,  
  res[2].cook_time = 13,  
  res[2].servings = 5;
  
  res[3].name = "Vegan pie",
  res[3].prep_time = 15,  
  res[3].cook_time = 11,  
  res[3].servings = 5;
  
  res[4].name = "Pizza",          
  res[4].prep_time = 25,  
  res[4].cook_time = 30,  
  res[4].servings = 1; 

  res[5].name = "Vegan Pizza",    
  res[5].prep_time = 25,  
  res[5].cook_time = 30,  
  res[5].servings = 1; 

  res[6].name = "Meat Pizza",     
  res[6].prep_time = 25,  
  res[6].cook_time = 30,  
  res[6].servings = 1;
 
  res[7].name = "Burger",         
  res[7].prep_time = 25,  
  res[7].cook_time = 30,  
  res[7].servings = 1; 

  printf("Vegan file outputter (Number between 1-53)\n\n");
  printf("What week is it? ");
  scanf(" %d", &weeknumber);

  /*Tjekker om det inleaste weeknumber/ugenummer er mellem 0 til 53, hvis ikke så printes det ikke*/
  if (weeknumber > 0 && weeknumber < 54){
      print_mealplan_to_file(weeknumber, &res[1]);
  } else{
    printf("There are no more then 53 months in a year, try again\n");
  }

  return EXIT_SUCCESS;
}

void print_mealplan_to_file(int weeknumber, struct _RECIPE res[]){
  FILE *fp = NULL;
  int i;

  char userfile[20];

  sprintf(userfile, "VeGen_week_%d.txt", weeknumber);

  fp = fopen (userfile,"w");

  fprintf(fp, "Vegan File Output\n", weeknumber);
  fprintf(fp, "\nUge %d\n\n", weeknumber);
 
  fprintf(fp, "Shoppinglist (For the whole week)\n"); 
  fprintf(fp, "/////////////////////////////////////////////////////////////////////\n");
     for(i = 0; i < 7;i++){
       fprintf(fp, ">  %s\n", ingredienser[i]);
    }  
  fprintf(fp, "\n");
  /*fprintf(fp, "\n/////////////////////////////////////////////////////////////////////\n\n");*/

  fprintf(fp, "Meal planner\n");
  fprintf(fp, "/////////////////////////////////////////////////////////////////////\n");
  for (i = 0; i < 7; i++){
    fprintf(fp, "%s\n", week[i]);
    fprintf(fp, "---------------------------------------------------------------------\n");
    fprintf(fp, "Meal name: %s\n", res[i].name);
    fprintf(fp, "Prep time: %d min, ", res[i].prep_time);
    fprintf(fp, "Cook time: %d min, ", res[i].cook_time);
    fprintf(fp, "Servings: %d pers\n", res[i].servings);
    fprintf(fp, "The vitamins are: i11 20kg, w1 25kg, u6 90ton.\nIngredients: Cocain 116 tons, Tomato 705 mg, Pasta 307 kg, Meatless meat 22 kg.\n");
    fprintf(fp, "\n");
  }
  /*fprintf(fp, "/////////////////////////////////////////////////////////////////////\n");*/
  fprintf(fp, "\n");

  fprintf(fp, "\nCopyright: VeGen");

  fclose(fp);

  printf("\nSucces file created\n(The file is located in the same folder as this program, with the name: '%s')\n", userfile);

}

/*
 * Funktioner som skal bruges senere 
 * 
 * typedef struct _NUTRIENT{
 * int nutrient_amount;
 * char *nutrient_unit;
 * char *nutrient_letter;
 * int nutrient_number;
 * }NUTRIENT;
 * 
 *
*/

