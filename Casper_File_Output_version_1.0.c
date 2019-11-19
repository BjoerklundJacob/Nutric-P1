/*
 * Dette er test kode som printer flere strucs med en funktion
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/***** STRUCTS *****/
typedef struct _NUTRIENT{
  int nutrient_amount;
  char *nutrient_unit;
  char *nutrient_letter;
  int nutrient_number;
}NUTRIENT;

typedef struct _RECIPE{
  char *name;
  int prep_time;
  int cook_time;
  int servings;
  int *amount;
  int length;
  char **unit;
  char **ingredients;
  NUTRIENT *nutrients;
} RECIPE;

char week[7][15] = {"Monday", "Tuesday", "Wensday", "Thursday", "Friday", "Saturday", "Sunday"};
char ingredienser[7][20] = {"Svampe", "Salat", "Kartofler", "Rødbeder", "Gulerod", "Ost", "Peber"};


void print_mealplan_to_file(int weeknumber, struct _RECIPE res[0]);


int main() {
  int weeknumber = 0; 

  /*Array af strucs*/
  struct _RECIPE res[8]; 
  res[0].name = "Pie",            
  res[0].prep_time = 20,  
  res[0].cook_time = 10,
  res[0].servings = 2;
  
  res[1].name = "Meatpie", 
  res[1].prep_time = 10,  
  res[1].cook_time = 13,  
  res[1].servings = 5;
  
  res[2].name = "Vegan pie",
  res[2].prep_time = 15,  
  res[2].cook_time = 11,  
  res[2].servings = 5;
  
  res[3].name = "Pizza",          
  res[3].prep_time = 25,  
  res[3].cook_time = 30,  
  res[3].servings = 1; 

  res[4].name = "Vegan Pizza",    
  res[4].prep_time = 25,  
  res[4].cook_time = 30,  
  res[4].servings = 1; 

  res[5].name = "Meat Pizza",     
  res[5].prep_time = 25,  
  res[5].cook_time = 30,  
  res[5].servings = 1;
 
  res[6].name = "Burger",         
  res[6].prep_time = 25,  
  res[6].cook_time = 30,  
  res[6].servings = 1; 

  res[7].name = "Chicken burger", 
  res[7].prep_time = 25,  
  res[7].cook_time = 30,  
  res[7].servings = 1; 

  
  printf("Vegan file outputter (Number between 1-53)\n\n");
  printf("What week is it? ");
   
  if (scanf(" %d", &weeknumber) <= 53){
      print_mealplan_to_file(weeknumber, &res[0]);
  } else{
    printf("There are no more then 53 mounts in a year, try again\n");
  }

  return 0;
}



void print_mealplan_to_file(int weeknumber, struct _RECIPE res[0]){
  FILE *fp = NULL;
  int i;

  char userfile[255];

  sprintf(userfile, "VeGen_week_%d.txt", weeknumber);

  fp = fopen (userfile,"w");

  // fp = fopen("mealplanner.txt", "w");

  fprintf(fp, "Vegan File Output\n", weeknumber);
  fprintf(fp, "\nUge %d\n\n", weeknumber);
 
  fprintf(fp, "Shoppinglist for the whole week\n"); 
  fprintf(fp, "/////////////////////////////////////////////////////////////////////\n");
     for(i = 0; i <= 7;i++){
       fprintf(fp, ">  %s\n", ingredienser[i]);
    }
  // fprintf(fp, "> Mel\n> Vand\n> Ekstra Vand\n> Ekstra Ekstra Vand\n> Ekstra Ekstra Ekstra Vand\n> Ikke ekstra Vand\n");
  fprintf(fp, "/////////////////////////////////////////////////////////////////////\n\n");

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
  fprintf(fp, "/////////////////////////////////////////////////////////////////////\n");

  fclose(fp);
}


