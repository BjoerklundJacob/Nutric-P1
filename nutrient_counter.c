#include "nutrient_counter.h"
#include "csv_nutrient_parser.h"
#include <string.h>

void meal_nutrient_count_add(map_t* meal){
  list_t *ingredient_element = map_value(meal, "ingredients");
  double meal_nutrients_array[NUTRIENT_COUNT];
  ingredient_nutrients_t ingredient_nutrients;
  struct _INGREDIENT{
    double amount;
    char unit[64];
    char name[256];
  };
  struct _INGREDIENT ingredient;
  double nutrient_amount;
  char nutrient_unit[10];
  int i;
  void* value;
  list_t *nutrient_list = NULL;

  /* Initialise recipe nutrient array to 0 */
  for(i = 0; i < NUTRIENT_COUNT; ++i){
    meal_nutrients_array[i] = 0.0;
  }

  if (map_value(meal, "nutrients") == NULL){
    /* Loop through each ingredient */
    while(ingredient_element != NULL){
      /* Parse the ingredient string to the values (fx "50 g raw carrot") */
      sscanf(ingredient_element->value, "%lf %s %[a-zA-Z ]", &ingredient.amount, ingredient.unit, ingredient.name);

      ingredient_nutrients = get_ingredient_nutrients(ingredient.name);
      /* Add ingredient nutrients to recipe nutrients */
      for (i = 0; i < NUTRIENT_COUNT; i++)
      {
        /* The nutrient amount is divided by 100, because the amount is per 100 grams */
        sscanf(ingredient_nutrients.calcium + i * sizeof(ingredient_nutrients.calcium), "%lf %s", &nutrient_amount, nutrient_unit);
        meal_nutrients_array[i] += nutrient_amount/100.0 * unit_to_gram(nutrient_unit) * ingredient.amount * unit_to_gram(ingredient.unit);
      }
      /* Go to next ingredient */
      ingredient_element = ingredient_element->next_element;
    }
    /* turn into json structure */
    for(i = 0; i < NUTRIENT_COUNT; ++i){
      value = malloc(sizeof(double));
      if (value == NULL){
        printf("Could not allocate memory.\n");
        exit(EXIT_FAILURE);
      }
      *(double*) value = meal_nutrients_array[i];
      list_add(&nutrient_list, value, value_double);
    }
    /* add to meal map */
    map_add(meal, "nutrients", nutrient_list, value_list);
  }
}
 
/*Give the correct number to convert a unit to gram*/
double unit_to_gram(const char* unit){
  int i;
  char string[50];

  strcpy(string, unit);

  for(i = 0; i < strlen(string); ++i)
    string[i] = tolower(string[i]);

  if(strstr(string, "kg") != NULL)
    return 1000;
  if(strstr(string, "kilo") != NULL)
    return 1000;
  if(strstr(string, "mg") != NULL)
    return 0.001;
  if(strstr(string, "miligram") != NULL)
    return 0.001;
  if(strstr(string, "ug") != NULL)
    return 0.000001;
  if(strstr(string, "lb") != NULL || strstr(string, "pound") != NULL)
    return 453.592;
  if(strstr(string, "dl") != NULL)
    return 100;
  if(strstr(string, "cl") != NULL)
    return 10;
  if(strstr(string, "tsp") != NULL || strstr(string, "teaspoon") != NULL)
    return 4.9;
  if(strstr(string, "tbs") != NULL || strstr(string, "tablespoon") != NULL)
    return 14.78;
  if(strstr(string, "oz") != NULL || strstr(string, "ounc") != NULL)
    return 14.78*2;
  if(strstr(string, "cup") != NULL)
    return 237;
  if(strstr(string, "pint") != NULL)
    return 473;
  if(strstr(string, "quart") != NULL)
    return 960;
  if(strstr(string, "gallon") != NULL)
    return 3800;
  if(strstr(unit, "l") != NULL)
    return 1000;
  return 1.0;
}