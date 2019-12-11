#include "output.h"

void NutrientOutput(UserData userdata){
  map_t *map, *meal;
  list_t *list, *nutrient_list;
  double nutrient_ranges[VITAMIN_RANGES];
  double nutrient_count[NUTRIENT_COUNT];
  int i, j, procentage;
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
  SetVitaminRanges(nutrient_ranges, userdata);

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

  printf("Nutrient      |   Value   |     Min     |     Max     |\n");
  /* Print nutrients */
  for(i = 0; i < NUTRIENT_COUNT; ++i){
    char *unit = calloc(3, sizeof(char)), *min_max_unit = calloc(3, sizeof(char));
    double amount = nutrient_count[i], minMax[2]; 

    GetRange(nutrient_ranges, minMax, userdata.age, i, userdata.weight == 'm' ? 0 : 1,userdata.gender);
    strcpy(unit, "g");

    if (i == mineral_zinc || i == mineral_selenium || i == mineral_iodine || i == vitamin_B12 || i == vitamin_A || i == vitamin_D){
      strcpy(min_max_unit, "ug");
    }else{
      strcpy(min_max_unit, "mg");
    }

    convert_unit(&amount, unit, min_max_unit);
    if (strcmp(min_max_unit, "ug") == 0){
      strcpy(min_max_unit, "\xE6g");
    }

    procentage = Percentages(amount, minMax[0], minMax[1]);

    if (amount == 0){
      printf("%-13s |  " RED "\xC4\xC4\xC4\xC4\xC4\xC4\xC4" "(%i%%)" WHITE "  | %8.1lf %s | %8.1lf %s |\n", 
        nutrient_names[i],
        procentage,
        minMax[0],
        min_max_unit,
        minMax[1],
        min_max_unit);
    }else if (amount >= minMax[0] && amount <= minMax[1]){
      printf("%-13s | " GREEN "%6.3lf %s" "(%i%%)" WHITE " | %8.1lf %s | %8.1lf %s |\n", 
        nutrient_names[i], 
        amount,
        unit,
        procentage,
        minMax[0],
        min_max_unit,
        minMax[1],
        min_max_unit);
    }else{
      printf("%-13s | " YELLOW "%6.3lf %s" "(%i%%)" WHITE " | %8.1lf %s | %8.1lf %s |\n", 
        nutrient_names[i], 
        amount,
        unit,
        procentage,
        minMax[0],
        min_max_unit,
        minMax[1],
        min_max_unit);
    }
  }
  map_free(map);
}

int Percentages(double value, double min, double max){
  if(value > max)
    return (double)(value / max *100);
  else if (value < min)
    return (double)(value / min *100);
  else
    return 100;
}

void convert_unit(double* amount, char* unit_from, const char* unit_to){
    double mult = 1;
    switch(unit_from[0]){
        case 'n': mult = pow(10, -9); break;
        case 'u': mult = pow(10, -6); break;
        case 'm': mult = pow(10, -3); break;
        case 'k': mult = pow(10, 3); break;
    }
    switch(unit_to[0]){
        case 'n': *amount *= pow(10, 9) * mult; strcpy(unit_from, "ng"); break;
        case 'u': *amount *= pow(10, 6) * mult; strcpy(unit_from, "\xE6g"); break;
        case 'm': *amount *= pow(10, 3) * mult; strcpy(unit_from, "mg"); break;
        case 'g': *amount *= mult; strcpy(unit_from, "g"); break;
        case 'k': *amount *= pow(10, -3) * mult; strcpy(unit_from, "kg"); break;
    }
}