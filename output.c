#include "output.h"

void NutrientOutput(UserData userdata){
  map_t *map;
  list_t *list;
  double nutrient_ranges[VITAMIN_RANGES];
  int i;
  ingredient_nutrients_t ingredient_nutrients[MAX_ARRAY_SIZE];

  
  /* Load user input */
  map = json_load(".\\Input.json");

  /* Load nutrient ranges */
  SetVitaminRanges(nutrient_ranges);

  /* Load ingredient nutrients */
  get_ingredient_nutrients(ingredient_nutrients);

  /* Calculate nutrients for the user input */
  list = map_value(map, "meals");
  if (list != NULL){
    for(i = 0; i < list_size(list); ++i){
      recipe_nutrient_count_add(list_value(list, i), ingredient_nutrients);
    }
  }
}