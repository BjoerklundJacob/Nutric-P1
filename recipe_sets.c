#include <stdio.h>
#include <math.h>

#define RECIPE_COUNT 3
#define INGREDIENT_COUNT 10
#define RECIPE_SET_LEN ceil((double) RECIPE_COUNT / (double) (sizeof(int)*8))
#define LEN(x) (sizeof(x)/sizeof(x[0]))

typedef struct _RECIPE{
    char *name;
    int prep_time;
    int cook_time;

    int servings;

    int ingredients[INGREDIENT_COUNT];/*int array with all ingredients (value of 0 if ingredient is not in recipe)*/

    int instructions;
    char **instructions;/*instructions string array*/
  }RECIPE;

  typedef struct _RECIPE_SET{
    char tag;
    int bit_string[RECIPE_SET_LEN];
  }RECIPE_SET;

enum eRecipeSetTags{
  tomato,
  nut,
  gluten,
  soya,
  e_recipe_set_tags_size,
  terminator
};

int main(void){

  RECIPE recipes[RECIPE_COUNT];
  RECIPE_SET recipe_sets[e_recipe_set_tags_size];

  int i, j;
  char *tags;

  /* Initialise all recipe set bit strings to full 0's */
  for(j = 0; j < e_recipe_set_tags_size; ++j)
    for(i = 0; i < RECIPE_SET_LEN; ++i)
      recipe_sets[j].bit_string[i] = 0;

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