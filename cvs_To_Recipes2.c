#include <stdio.h>
#include <string.h>
#define INGREDIENT_COUNT 20
#define MAX_CHARACTERS_COUNT 40

void SetRecipe(char *all_Ingredients[]);
void SetIngredients(FILE *listOfIngredients, char *all_Ingredients[]);


int main(void){
  char *all_Ingredients[INGREDIENT_COUNT];

  SetRecipe(all_Ingredients);

  return 0;
}

typedef struct _RECIPE{
  char *name;
  int prep_time;
  int cook_time;

  int servings;
  int ingredients[INGREDIENT_COUNT];/*int array with all ingredients (value of 0 if ingredient is not in recipe)*/

  double instruction_count;
  char **instructions;/*instructions string array*/
}RECIPE;
RECIPE recipes[2];

void SetRecipe(char *all_Ingredients[])
{
  FILE *csv = fopen(".\\Recipes.csv", "r");

  SetIngredients(csv, all_Ingredients);


  fclose(csv);

  return;
}

void SetIngredients(FILE *csv, char *all_Ingredients[])
{
  printf("\nStart \n");


  char str1[30];

  fscanf(csv, "Name;Prep Time;Cook Time; %[^;] ", str1);
  printf("Have Scaned: %c \n", str1);    
  strcpy(all_Ingredients[0], str1);

  printf("Scan is: %s \n", all_Ingredients[0]);    

  int j = 1;
  while (j < 20)
  {
    fgetc(csv);
    char str2[30];

    fscanf(csv, "%[^;\n]", str2);
    //printf("Scan = %s \n", str2);

    strcpy(all_Ingredients[j], str2);

    //printf("IngredientIndex %i is %s\n",j , all_Ingredients[j]);
    j++;  
  }

  for (int i = 0; i < INGREDIENT_COUNT; i++)
  {
    printf("Ingredient %i is %s\n", i, all_Ingredients[i]);
  }

  
}
