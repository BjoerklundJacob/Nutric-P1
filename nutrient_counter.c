#include "nutrient_counter.h"
#include "csv_nutrient_parser.h"
#include <string.h>

int main(void){
  list_t *hash_lists[LETTER_COUNT];
  map_t *map, *submap, *nutrient_map;
  list_t *list;
  int i;

  /* init hash lists to null */
  for(i = 0; i < LETTER_COUNT; ++i){
    hash_lists[i] = NULL;
  }

  /* load recipes */
  map = json_load(".\\output.json");
  printf("json loaded.\n");

  /* calculate nutrients for all recipes */
  nutrient_map = ingredient_nutrients();

  list = map_value(map, "recipes");
  if (list != NULL){
    recipe_nutrient_count_add(list_value(list, 0), nutrient_map);
  }
  FILE *file = fopen(".\\output.json", "w");
  if (file == NULL){
    return 1;
  }
  fprint_map(file, map, 0);
  fclose(file);
  submap = list_value(list, 0);
  list = map_value(submap, "nutrients");
  printf("::%lf::\n", *(double*) list_value(list, 5));

  map_free(map);
  map_free(nutrient_map);
  printf("succes?\n");
  return 0;
}

void recipe_nutrient_count_add(map_t* recipe, ingredient_nutrients_t* nutrients){
  list_t *ingredient_element = map_value(recipe, "ingredients");
  double recipe_nutrients_array[NUTRIENT_COUNT];
  ingredient_nutrients_t ingredient_nutrients;
  struct _INGREDIENT{
    double amount;
    char unit[64];
    char name[256];
  };
  struct _INGREDIENT ingredient;
  double nutrient_amount;
  char nutrient_unit[10];
  int i, index;
  void* value;
  list_t *nutrient_list = NULL;

  /* Initialise recipe nutrient array to 0 */
  for(i = 0; i < NUTRIENT_COUNT; ++i){
    recipe_nutrients_array[i] = 0.0;
  }

  if (map_value(recipe, "nutrients") == NULL){
    /* Loop through each ingredient */
    while(ingredient_element != NULL){
      /* Parse the ingredient string to the values (fx "50 g carrot") */
      sscanf(ingredient_element->value, "%lf %s %[^\0]", &ingredient.amount, ingredient.unit, ingredient.name);
      index = ingredient_nutriens_index(nutrients, ingredient.name);
      if(index != -1){
        ingredient_nutrients = nutrients[index];
        
        /* Add ingredient nutrients to recipe nutrients */
        sscanf(ingredient_nutrients.calcium, "%lf %s", &nutrient_amount, nutrient_unit);
        recipe_nutrients_array[mineral_calcium] += nutrient_amount * unit_to_gram(nutrient_unit);

        sscanf(ingredient_nutrients.iron, "%lf %s", &nutrient_amount, nutrient_unit);
        recipe_nutrients_array[mineral_iron] += nutrient_amount * unit_to_gram(nutrient_unit);

        sscanf(ingredient_nutrients.zinc, "%lf %s", &nutrient_amount, nutrient_unit);
        recipe_nutrients_array[mineral_zinc] += nutrient_amount * unit_to_gram(nutrient_unit);

        sscanf(ingredient_nutrients.selenium, "%lf %s", &nutrient_amount, nutrient_unit);
        recipe_nutrients_array[mineral_selenium] += nutrient_amount * unit_to_gram(nutrient_unit);

        sscanf(ingredient_nutrients.vitamin_B2, "%lf %s", &nutrient_amount, nutrient_unit);
        recipe_nutrients_array[vitamin_B2] += nutrient_amount * unit_to_gram(nutrient_unit);

        sscanf(ingredient_nutrients.vitamin_B3, "%lf %s", &nutrient_amount, nutrient_unit);
        recipe_nutrients_array[vitamin_B3] += nutrient_amount * unit_to_gram(nutrient_unit);

        sscanf(ingredient_nutrients.vitamin_B12, "%lf %s", &nutrient_amount, nutrient_unit);
        recipe_nutrients_array[vitamin_B12] += nutrient_amount * unit_to_gram(nutrient_unit);

        sscanf(ingredient_nutrients.vitamin_A, "%lf %s", &nutrient_amount, nutrient_unit);
        recipe_nutrients_array[vitamin_A] += nutrient_amount * unit_to_gram(nutrient_unit);

        sscanf(ingredient_nutrients.vitamin_D, "%lf %s", &nutrient_amount, nutrient_unit);
        recipe_nutrients_array[vitamin_D] += nutrient_amount * unit_to_gram(nutrient_unit);

        sscanf(ingredient_nutrients.iodine, "%lf %s", &nutrient_amount, nutrient_unit);
        recipe_nutrients_array[mineral_iodine] += nutrient_amount * unit_to_gram(nutrient_unit);
      }
      else{
        printf("Error, nutrients for ingredient not found!\n");
      }
      ingredient_element = ingredient_element->next_element;
    }
    /* turn into json structure */
    for(i = 0; i < NUTRIENT_COUNT; ++i){
      value = malloc(sizeof(double));
      if (value == NULL){
        printf("Could not allocate memory.\n");
        exit(EXIT_FAILURE);
      }
      *(double*) value = recipe_nutrients_array[i];
      list_add(&nutrient_list, value, value_double);
    }
    /* add to recipe map */
    map_add(recipe, "nutrients", nutrient_list, value_list);
  }
}

double unit_to_gram(const char* unit){
  int i;
  char string[50];
  strcpy(string, unit);
  for(i = 0; i < strlen(string); ++i){
    string[i] = tolower(string[i]);
  }
  if(strstr(string, "kg") != NULL){
    return 1000;
  }
  if(strstr(string, "kilo") != NULL){
    return 1000;
  }
  if(strstr(string, "mg") != NULL){
    return 0.001;
  }
  if(strstr(string, "miligram") != NULL){
    return 0.001;
  }
  if(strstr(string, "lb") != NULL || strstr(string, "pound") != NULL){
    return 453.592;
  }
  if(strstr(string, "dl") != NULL){
    return 100;
  }
  if(strstr(string, "cl") != NULL){
    return 10;
  }
  if(strstr(string, "tsp") != NULL || strstr(string, "teaspoon") != NULL){
    return 4.9;
  }
  if(strstr(string, "tbs") != NULL || strstr(string, "tablespoon") != NULL){
    return 14.78;
  }
  if(strstr(string, "oz") != NULL || strstr(string, "ounc") != NULL){
    return 14.78*2;
  }
  if(strstr(string, "cup") != NULL){
    return 237;
  }
  if(strstr(string, "pint") != NULL){
    return 473;
  }
  if(strstr(string, "quart") != NULL){
    return 960;
  }
  if(strstr(string, "gallon") != NULL){
    return 3800;
  }
  if(strstr(unit, "l") != NULL){
    return 1000;
  }
  return 1.0;
}

int ingredient_nutriens_index(ingredient_nutrients_t* nutrients, char* name){
  int i;
  for(i = 0; i < MAX_ARRAY_SIZE; ++i){
    if(strcmp(nutrients[i].ingredient_name, name) == 0){
      return i;
    }
  }
  return -1;
}