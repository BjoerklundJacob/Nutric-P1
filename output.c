#include "output.h"

void NutrientOutput(UserData userdata){
  map_t *map, *meal;
  list_t *list, *nutrient_list;
  double nutrient_ranges[VITAMIN_RANGES];
  double nutrient_count[NUTRIENT_COUNT];
  int i, j;
  ingredient_nutrients_t ingredient_nutrients[MAX_ARRAY_SIZE];
  char *nutrient_names[NUTRIENT_COUNT] = {  
    "Calcium",
    "Iron",
    "Zinc",
    "Selenium",
    "Iodine",
    "Vitamin B2",
    "Vitamin B3",
    "Vitamin B12",
    "Vitamin A",
    "Vitamin D"
    };

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
    printf("%s: %lf %s\n", nutrient_names[i], GramToUnit(nutrient_count[i]), NutrientToUnit(nutrient_count[i]));
  }

  map_free(map);
}

double GramToUnit(double nutrient){
  double convertedNutrients;
  /* finds the lowest power and converts it up to the unit*/
  if(nutrient < pow(10.0,-9)){
    convertedNutrients = nutrient * pow(10.0,9);
  }
  else if(nutrient < pow(10.0,-6)){
    convertedNutrients = nutrient * pow(10.0,6);
  }
  else if(nutrient < pow(10.0,-3)){
    convertedNutrients = nutrient * pow(10.0,3);
  }
  else if(nutrient < pow(10.0,0)){
    convertedNutrients = nutrient;
  }
  else if(nutrient < pow(10.0,3)){
    convertedNutrients = nutrient * pow(10.0,-3);
  }
  return convertedNutrients;
}

char* NutrientToUnit(double nutrient){
  /* finds the lowest power and gives the unit back*/
  char *unit = calloc(3,sizeof(char));
  if(nutrient == 0){
    unit = "";
  }
  else if(nutrient < pow(10.0,-9)){
    unit = "ng";
  }
  else if(nutrient < pow(10.0,-6)){
    unit = "\xE6g";
  }
  else if(nutrient < pow(10.0,-3)){
    unit = "mg";
  }
  else if(nutrient < pow(10.0,0)){
    unit = "g";
  }
  else if(nutrient < pow(10.0,3)){
    unit = "kg";
  }
  free(unit);
  return unit;
}
