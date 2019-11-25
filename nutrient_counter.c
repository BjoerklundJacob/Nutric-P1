/*#include "json_structs.h"*/
#include "json_parser.h"
#include "ingredient_nutrients.h"
#include <string.h>
#include <ctype.h>

#define LETTER_COUNT 26 /* english alphabet */

void recipe_nutrient_count_add(MAP* recipe, MAP* nutrient_map);
double unit_to_gram(const char* unit);

int main(void){
  LIST *hash_lists[LETTER_COUNT];
  MAP *map, *submap, *nutrient_map;
  LIST *list;
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

void recipe_nutrient_count_add(MAP* recipe, MAP* nutrient_map){
  LIST *nutrient_element = map_value(recipe, "ingredients");
  LIST *nutrient_list = NULL;
  double nutrients[NUTRIENT_COUNT];
  double *ingredient_nutrients = NULL;
  struct _INGREDIENT{
    double amount;
    char unit[64];
    char name[256];
  };
  struct _INGREDIENT ingredient;
  int i;
  void* value;

  for(i = 0; i < NUTRIENT_COUNT; ++i){
    nutrients[i] = 0.0;
  }

  if (map_value(recipe, "nutrients") == NULL){
    while(nutrient_element != NULL){
      sscanf(nutrient_element->value, "%lf %s %[^\0]", &ingredient.amount, ingredient.unit, ingredient.name);
      ingredient_nutrients = map_value(nutrient_map, ingredient.name);
      if (ingredient_nutrients != NULL){
        for(i = 0; i < NUTRIENT_COUNT; ++i){
          nutrients[i] += ingredient_nutrients[i] * (ingredient.amount * unit_to_gram(ingredient.unit));
        }
      }
      else{
        printf("Error, nutrients for ingredient not found!\n");
      }
      nutrient_element = nutrient_element->next_element;
    }
    /* turn into json structure */
    for(i = 0; i < NUTRIENT_COUNT; ++i){
      value = malloc(sizeof(double));
      if (value == NULL){
        printf("Could not allocate memory.\n");
        exit(EXIT_FAILURE);
      }
      *(double*) value = nutrients[i];
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