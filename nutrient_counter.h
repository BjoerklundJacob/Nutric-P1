#ifndef NUTRIENT_COUNTER
#define NUTRIENT_COUNTER
#include "json_structs.h"
#include "json_parser.h"
#include <string.h>
#include <ctype.h>
#include "csv_nutrient_parser.h"

#define LETTER_COUNT 26 /* english alphabet */
#define NUTRIENT_COUNT 10

typedef enum _eNUTRIENTS{
  mineral_calcium,
  mineral_iodine,
  mineral_iron,
  mineral_selenium,
  mineral_zinc,
  vitamin_A,
  vitamin_B2,
  vitamin_B3,
  vitamin_B12,
  vitamin_D
}eNUTRIENTS;

void recipe_nutrient_count_add(map_t* recipe, ingredient_nutrients_t* nutrients);
double unit_to_gram(const char* unit);
int ingredient_nutriens_index(ingredient_nutrients_t* nutrients, const char* name);
#endif