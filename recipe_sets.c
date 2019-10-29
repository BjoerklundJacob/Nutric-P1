#include <stdio.h>
#include <math.h>

#define RECIPE_COUNT 3
#define INGREDIENT_COUNT 10
#define RECIPE_SET_LEN ceil((double) RECIPE_COUNT / (double) (sizeof(int)*8))
#define LEN(x) (sizeof(x)/sizeof(x[0]))

int main(void){

  typedef struct {
    char* name;
    int prep_time;
    int cook_time;

    int servings;

    int ingredients[INGREDIENT_COUNT];/*int array with all ingredients (value of 0 if ingredient is not in recipe)*/

    int instructions;
    char **instructions;/*instructions string array*/
  }RECIPE;

  RECIPE recipes[RECIPE_COUNT];

  int recipe_set[RECIPE_SET_LEN];
  int i;

  char *tags;

  /* Set to have full 1's as bits */
  for(i = 0; i < RECIPE_SET_LEN; ++i)
    recipe_set[i] = -1;


  find_recipes(recipe_set, tags);  


  return 0;
}

void find_recipes(int* recipe_set, char* tags){
  int i, tag_count;
  int *recipe;
  
  tag_count = LEN(tags);
  for(i = 0; i < tag_count; ++i){
    recipe_junction(recipe_set, recipe);
  }
}

void recipe_junction(int* recipe1, int* recipe2){

}