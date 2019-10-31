#include <stdio.h>/* printf, scanf ... */
#include <stdlib.h>/* abs(int) */

#include "recipe_sets.h"

/* Finds all recipes from a recipe set that is in recipe sets with the positive input tags
 * or excludes any recipes from recipe sets with the negative input tags.
 * param 0: IN+OUT - recipe set to modify to include or exclude any shared recipes from.
 * param 1: IN     - array of all recipe sets available
 * param 2: IN     - array of all tags to include or exclude
 * param 3: IN     - length of param 2 array
 */
void find_recipes(RECIPE_SET* recipe_set, RECIPE_SET *recipe_sets, eRECIPE_SET_TAGS *tags, int tag_count){
  int i;
  RECIPE_SET tag_recipe_set;
  
  /* loop through tags and include/exclude them from the recipe_set */
  for(i = 0; i < tag_count; ++i){
    /* get recipe set for current tag */
    tag_recipe_set = recipe_sets[abs(tags[i])];/* make sure enum is treated as a signed int */
    /* if tag is negative, exclude that set instead of including */
    if ((int) tags[i] < 0){
      recipe_set_bit_flip(&tag_recipe_set);
    }
    recipe_junction(recipe_set, tag_recipe_set);
  }
}

/* Finds the junction between the two recipe sets setting the result in the first recipe set
 * param 0: IN+OUT - recipe set 1
 * param 1: IN     - recipe set 2
 */
void recipe_junction(RECIPE_SET* recipe_set1, RECIPE_SET recipe_set2){
  int i;
  /* bitwise AND between the two bit strings, storing result in the first */
  for(i = 0; i < RECIPE_SET_LEN; ++i)
    recipe_set1->bit_string[i] &= recipe_set2.bit_string[i];
}

/* Prints the bit string of recipe set
 * param 0: IN - recipe set 2
 */
void print_recipe_set(RECIPE_SET recipe_set){
  int i, j;
  /* Loop for every bit in a recipe set bit string */
  for(i = 0; i < RECIPE_SET_LEN; ++i){
    for(j = sizeof(int)*8 - 1; j >= 0; --j){
      printf("%c", (recipe_set.bit_string[i] & (1 << j)) ? '1' : '0');
    }
  }
}

/* Flips every bit in the bit string from 0 to 1 or 1 to 0
 * param 0: IN+OUT - recipe set
 * return: The flipped recipe set
 */
RECIPE_SET recipe_set_bit_flip(RECIPE_SET* recipe_set){
  int i;
  for(i = 0; i < RECIPE_SET_LEN; ++i)
    recipe_set->bit_string[i] = ~recipe_set->bit_string[i];
  return *recipe_set;
}

/* Returns the amount of recipes in a recipe set
 * param 0: IN - recipe set
 * return: amount of 1-bits in the recipe set bit string
 */
int recipe_count(RECIPE_SET recipe_set){
  int i, j, count = 0;
  /* Loop for every bit in a recipe set bit string */
  for(i = 0; i < RECIPE_SET_LEN; ++i){
    for(j = sizeof(int)*8 - 1; j >= 0; --j){
      count += recipe_set.bit_string[i] & (1 << j) ? 1 : 0;
    }
  }
  return count;
}