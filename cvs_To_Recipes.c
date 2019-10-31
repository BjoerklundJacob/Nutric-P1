#include <stdio.h>
#include <string.h>
#define INGREDIENT_COUNT 20

void SetRecipe(void);
int all_Ingredients[INGREDIENT_COUNT];

int main(void){

  SetRecipe();

  return 0;
}


typedef struct _RECIPE{
  char *name;
  int prep_time;
  int cook_time;

  int servings;
  int ingredients[INGREDIENT_COUNT];/*int array with all ingredients (value of 0 if ingredient is not in recipe)*/

  int instruction_count;
  char **instructions;/*instructions string array*/
}RECIPE;

/*RECIPE recipes[];*/


void SetRecipe(void)
{
  printf("Start \n\n");

  FILE *csv = fopen(".\\Recipes.csv", "r");

  char str1[10];

  all_Ingredients[0] = fscanf(csv, "Name;Prep Time;Cook Time; %[^;]", str1);
  printf("\nScan is: %s \n\n", str1);    


  int j = 1;
  while (fgetc(csv) != EOF)
  {
    all_Ingredients[j] = fscanf(csv, "\n %[^;]", str1);
    printf("\nScan is: %s \n\n", str1);
  }

  printf("Mid \n\n");

  for (int i = 0; i < INGREDIENT_COUNT; i++)
  {
    printf("Ingredient %i is %s\n", i, all_Ingredients[i]);
  }

  fclose(csv);

  printf("End \n\n");

  return;
}
