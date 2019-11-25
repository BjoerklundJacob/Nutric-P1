#ifndef JSON_STRUCTS_H
#define JSON_STRUCTS_H "json_structs.h"
#include JSON_STRUCTS_H
#endif
#include <stdlib.h>

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
  mineral_iodine
}eNUTRIENTS;

MAP* ingredient_nutrients(void){
  MAP* map;
  double *nutrients;
  
  map = map_create();
  nutrients = calloc(NUTRIENT_COUNT, sizeof(double));
  nutrients[vitamin_A] = 1;
  map_add(map, "coconut oil", nutrients, value_undefined);
  
  nutrients = calloc(NUTRIENT_COUNT, sizeof(double));
  nutrients[vitamin_B2] = 3;
  map_add(map, "vegan dark chocolate", nutrients, value_undefined);
  
  nutrients = calloc(NUTRIENT_COUNT, sizeof(double));
  nutrients[vitamin_B3] = 4;
  map_add(map, "golden syrup", nutrients, value_undefined);
  
  nutrients = calloc(NUTRIENT_COUNT, sizeof(double));
  nutrients[vitamin_A] = 100;
  map_add(map, "vegan ginger nuts", nutrients, value_undefined);
  
  nutrients = calloc(NUTRIENT_COUNT, sizeof(double));
  nutrients[mineral_iron] = 12;
  map_add(map, "dried cranberries", nutrients, value_undefined);
  
  nutrients = calloc(NUTRIENT_COUNT, sizeof(double));
  nutrients[mineral_iodine] = .01;
  map_add(map, "pistachios", nutrients, value_undefined);
  
  return map;
}