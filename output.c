#include "output.h"

void NutrientOutput(UserData userdata){
  map_t *map, *meal;
  list_t *list, *nutrient_list;
  double nutrient_ranges[VITAMIN_RANGES];
  double nutrient_count[NUTRIENT_COUNT];
  int i, j;
  ingredient_nutrients_t ingredient_nutrients[MAX_ARRAY_SIZE];

  /* Initialise nutrient count to 0 */
  for(i = 0; i < NUTRIENT_COUNT; ++i){
    nutrient_count[i] = 0.0;
  }
  
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
      meal = list_value(list, i);
      recipe_nutrient_count_add(meal, ingredient_nutrients);
      nutrient_list = map_value(meal, "nutrients");
      if (nutrient_list != NULL){
        for(j = 0; j < NUTRIENT_COUNT; ++j){
          nutrient_count[j] += *(double*) list_value(nutrient_list, j);
        }
      }
    }
  }

  /* Print nutrients */
  for(i = 0; i < NUTRIENT_COUNT; ++i){
    printf("Nutrient: %lf\n", nutrient_count[i]);
  }

  map_free(map);
}