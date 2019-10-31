#include <stdio.h>
#include <stdlib.h>
#include "recipe_sets.h"

int main(void){

  RECIPE recipes[RECIPE_COUNT];
  RECIPE_SET recipe_sets[e_recipe_set_tags_size];

  int i, j;
  eRECIPE_SET_TAGS tags[] = {tomato, -nut};

  /* Initialise all recipe set bit strings to full 0's */
  for(j = 0; j < (int) e_recipe_set_tags_size; ++j)
    for(i = 0; i < RECIPE_SET_LEN; ++i)
      recipe_sets[j].bit_string[i] = 0;

  /* Initialise test recipe set bit strings to "random" test values" */
  for(j = 1; j < (int) e_recipe_set_tags_size; ++j)
    for(i = 0; i < RECIPE_SET_LEN; ++i)
      recipe_sets[j].bit_string[i] = (345 << j) + 9599*j << 5;

  /* Initialise recipe set of all recipes, starting from left moving right */
  for(i = 0; i < RECIPE_COUNT; ++i){
    j = (sizeof(int)*8);
    recipe_sets[all].bit_string[i / j] += 1 << (31-(i % j));
  }

  printf("Bit string length = %d\n", RECIPE_SET_LEN);

  /* Print all recipe sets */
  for(i = 0; i < (int) e_recipe_set_tags_size; ++i){
    //printf("Printing recipe set %d\n", i);
    print_recipe_set(recipe_sets[i]);
    printf("\n");
  }

  find_recipes(&recipe_sets[all], recipe_sets, tags, LEN(tags));

  printf("Available recipes with tags:\n");
  print_recipe_set(recipe_sets[all]);
  printf("\n");

  return 0;
}