/*
 * Data parser to ingredientsList, makes a struct of ingredientsList
 * Bemaerk den er ikke general med specifikt lavet til denne opgave   
 *  
*/

#include "csv_nutrient_parser.h"

void get_ingredient_nutrients(ingredient_nutrients_t* output_array){
  FILE *f = fopen("Ingredient_Nutrients.csv", "r"); 
  int i;

  if(f != NULL){
    /* Reads the CSV-file and makes the nutrient arr */
    for (i = 0; i < MAX_ARRAY_SIZE ; i++){

      fscanf(f, " %[a-zA-Z() ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] \n", 
          output_array[i].ingredient_name, 
          output_array[i].calcium, 
          output_array[i].iodine,
          output_array[i].iron,
          output_array[i].selenium, 
          output_array[i].zinc, 
          output_array[i].vitamin_A,
          output_array[i].vitamin_B2,
          output_array[i].vitamin_B3, 
          output_array[i].vitamin_B12, 
          output_array[i].vitamin_D
      );
    }
    fclose(f);
  }

}

/*void printing_the_chosen_in(ingredient_nutrients_t ingredientsList[MAX_ARRAY_SIZE], int j){
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
}*/