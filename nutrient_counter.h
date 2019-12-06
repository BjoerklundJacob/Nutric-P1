#ifndef NUTRIENT_COUNTER
#define NUTRIENT_COUNTER
#include "json_structs.h"
#include "json_parser.h"
#include <string.h>
#include <ctype.h>
#include "csv_nutrient_parser.h"

#define LETTER_COUNT 26 /* english alphabet */
#define NUTRIENT_COUNT 9

typedef enum _eNUTRIENTS{
  vitamin_D,
  vitamin_B2,
  vitamin_B3,
  mineral_calcium,
  mineral_selenium,
  vitamin_A,
  mineral_iron,
  mineral_zinc,
  mineral_iodine,
  vitamin_B12
}eNUTRIENTS;

void recipe_nutrient_count_add(map_t* recipe, ingredient_nutrients_t* nutrients);
double unit_to_gram(const char* unit);
int ingredient_nutriens_index(ingredient_nutrients_t* nutrients, const char* name);
#endif