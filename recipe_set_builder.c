#include <stdio.h>
#include "recipe_sets.h"

int main(void){
  
  RECIPE recipe = {"Vegan tiffin", 
    15, 3, 2, {tomato, nut}, 4, 
    {"hey", "hi", "damn this might be a ok solution?"}};
  printf("%s %d %d\n", recipe.name, recipe.prep_time, recipe.cook_time);
  printf("Ingredients: %d %d\n", recipe.ingredients[0], recipe.ingredients[1]);
  printf("%s %s\n", recipe.instructions[0],  recipe.instructions[2]);

  RECIPE recipes[RECIPE_COUNT];
  RECIPE_SET recipe_sets[e_recipe_set_tags_size];

  return 0;
}

void recipes_to_recipe_sets(RECIPE recipes[RECIPE_COUNT], RECIPE_SET recipe_sets[e_recipe_set_tags_size]){
  int i, j;
  for(i = 0; i < RECIPE_COUNT; ++i){
    for(j = 0; j < e_recipe_set_tags_size; ++j){
      if(1);
    }
  }
}