/*
 * Data paser to ingredientsList, makes a struct of ingredientsList
 * Bemeark den er ikke general med specefik lavet til denne opgave   
 *  
*/

#include "csv_nutrient_parser.h"

void get_ingredient_nutrients(list_t** output_list){
  FILE *f = fopen("Ingredient_Nutrients.csv", "r"); 
  int i;
  ingredient_nutrients_t ingredient_nutrients;
  void* value;

  if(f != NULL){
    while(fscanf(f, " %[a-zA-Z() ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] \n", 
            ingredient_nutrients.ingredient_name, 
            ingredient_nutrients.calcium, 
            ingredient_nutrients.iron,
            ingredient_nutrients.zinc, 
            ingredient_nutrients.selenium, 
            ingredient_nutrients.vitamin_B2,
            ingredient_nutrients.vitamin_B3, 
            ingredient_nutrients.vitamin_B12, 
            ingredient_nutrients.vitamin_A,
            ingredient_nutrients.vitamin_D, 
            ingredient_nutrients.iodine
      ) > 0){
        value = malloc(sizeof(ingredient_nutrients_t));
        if(value != NULL){
          memcpy(value, &ingredient_nutrients, sizeof(ingredient_nutrients));
          list_add(output_list, value, value_undefined);
        }
      }
    fclose(f);
  }

}

void printing_the_choosen_in(ingredient_nutrients_t ingredientsList[MAX_ARRAY_SIZE], int j){
  printf("Ingredient: %d\n", j);
      printf("-------------------------------------------------\n");
      printf("Ingredients navn: %s\n", ingredientsList[j].ingredient_name);
      printf("Calcium:          %s\n", ingredientsList[j].calcium);
      printf("Iron:             %s\n", ingredientsList[j].iron); 
      printf("Zinc:             %s\n", ingredientsList[j].zinc);
      printf("Selenium:         %s\n", ingredientsList[j].selenium);
      printf("Vitamin B2:       %s\n", ingredientsList[j].vitamin_B2);
      printf("Vitamin B3:       %s\n", ingredientsList[j].vitamin_B3);
      printf("Vitamin B12:      %s\n", ingredientsList[j].vitamin_B12);
      printf("Vitamin A:        %s\n", ingredientsList[j].vitamin_A);
      printf("Vitamin D:        %s\n", ingredientsList[j].vitamin_D);
      printf("Iodine:           %s\n", ingredientsList[j].iodine);         
      printf("\n\n"); 
}

