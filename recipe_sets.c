#include <stdio.h>
#include <math.h>

#define RECIPE_COUNT 33
#define INGREDIENT_COUNT 10
/* RECIPE_SET_LEN is equal to the amount of int's needed to have a bitflag for each recipe */
#define RECIPE_SET_LEN (int) ( ((double) RECIPE_COUNT * 2.0 - 1.0) / (double) (sizeof(int)*8*2)+1 )
#define LEN(x) (sizeof(x)/sizeof(x[0]))

#include "types.h"

void find_recipes(RECIPE_SET* recipe_set, RECIPE_SET *recipe_sets, eRECIPE_SET_TAGS *tags, int tag_count);
void recipe_junction(RECIPE_SET* recipe1, RECIPE_SET recipe2);
void print_recipe_set(RECIPE_SET recipe_set);
RECIPE_SET recipe_set_bit_flip(RECIPE_SET* recipe_set);

int main(void){

  RECIPE recipes[RECIPE_COUNT];
  RECIPE_SET recipe_sets[e_recipe_set_tags_size];
  RECIPE_SET recipe_set;

  int i, j;
  eRECIPE_SET_TAGS tags[] = {nut, gluten};

  /* Initialise all recipe set bit strings to "random" test values" */
  for(j = 0; j < (int) e_recipe_set_tags_size; ++j)
    for(i = 0; i < RECIPE_SET_LEN; ++i)
      recipe_sets[j].bit_string[i] = (345 << j) + 9599*j;

  /* Initialise recipe set bit string to full 1's */
  for(i = 0; i < RECIPE_SET_LEN; ++i)
    recipe_set.bit_string[i] = -1;

  printf("Bit string length = %d\n", RECIPE_SET_LEN);
  for(i = 0; i < (int) e_recipe_set_tags_size; ++i){
    printf("Printing recipe set %d\n", i);
    print_recipe_set(recipe_sets[i]);
    printf("\n\n");
  }

  find_recipes(&recipe_set, recipe_sets, tags, LEN(tags));

  printf("Available recipes from both set 0 and set 1:\n");
  print_recipe_set(recipe_set_bit_flip(&recipe_set));
  printf("\n");

  return 0;
}

void find_recipes(RECIPE_SET* recipe_set, RECIPE_SET *recipe_sets, eRECIPE_SET_TAGS *tags, int tag_count){
  int i;
  RECIPE_SET recipe;
  
  for(i = 0; i < tag_count; ++i){
    recipe = recipe_sets[tags[i]];
    recipe_junction(recipe_set, recipe);
  }
}

void recipe_junction(RECIPE_SET* recipe_set1, RECIPE_SET recipe_set2){
  int i;
  for(i = 0; i < RECIPE_SET_LEN; ++i)
    recipe_set1->bit_string[i] &= recipe_set2.bit_string[i];
}

void print_recipe_set(RECIPE_SET recipe_set){
  int i, j;
  /* Loop for every bit in a recipe set bit string */
  for(i = 0; i < RECIPE_SET_LEN; ++i){
    for(j = sizeof(int)*8 - 1; j >= 0; --j){
      printf("%c", (recipe_set.bit_string[i] & (1 << j)) ? '1' : '0');
    }
  }
}

RECIPE_SET recipe_set_bit_flip(RECIPE_SET* recipe_set){
  int i;
  for(i = 0; i < RECIPE_SET_LEN; ++i)
    recipe_set->bit_string[i] = ~recipe_set->bit_string[i];
  return *recipe_set;
}