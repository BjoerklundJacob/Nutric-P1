#include <stdio.h>
#include "recipe_sets.h"

int main(void){
  
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