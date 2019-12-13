#include "ingredient_id_to_nutrients.h"

int main(void){
  nutrient_arrays_t my_nutrients;
  ingredient_nutrients_t nutrients_final;
  my_nutrients = get_nurient_values(174348);
  nutrients_final = nutrient_id_to_struct(my_nutrients);
  printf("Calcium nutrient: %s\n", nutrients_final.calcium);
  printf("Iron nutrient: %s\n", nutrients_final.iron);
  printf("zinc nutrient: %s\n", nutrients_final.zinc);
  printf("selenium nutrient: %s\n", nutrients_final.selenium);
  printf("vitamin_A nutrient: %s\n", nutrients_final.vitamin_A);
  printf("vitamin_D nutrient: %s\n", nutrients_final.vitamin_D);
  printf("vitamin_B2 nutrient: %s\n", nutrients_final.vitamin_B2);
  printf("vitamin_B3 nutrient: %s\n", nutrients_final.vitamin_B3);
  printf("vitamin_B12 nutrient: %s\n", nutrients_final.vitamin_B12);
  return 0;
}