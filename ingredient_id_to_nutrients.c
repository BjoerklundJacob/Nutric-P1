#include "ingredient_id_to_nutrients.h"

int main(void){
  nutrient_arrays_t my_nutrients;
  ingredient_nutrients_t nutrients_final;
  my_nutrients = get_nurient_values(167516);
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

nutrient_arrays_t get_nurient_values(int ingredient_id_number){
  int i, nutrient_count;
  char ch, id[MAX_ID_SIZE], ingredient_id[MAX_NUTRIENT_SIZE];
  nutrient_arrays_t nutrients;
  /* Opening the file */
  FILE *fp = fopen("Food_nutrient.csv", "r");

  /* Allocating space for the nutrients id's */
  nutrients.nutrient_id = calloc(MAX_NUTRIENT_COUNT, sizeof(char*));
  for (i = 0; i < MAX_NUTRIENT_COUNT; i++)
      nutrients.nutrient_id[i] = calloc(MAX_NUTRIENT_SIZE, sizeof(char));

  /* Allocating space for the nutrient values */
  nutrients.nutrient_amount = calloc(MAX_NUTRIENT_COUNT, sizeof(char*));
  for (i = 0; i < MAX_NUTRIENT_COUNT; i++)
      nutrients.nutrient_amount[i] = calloc(MAX_NUTRIENT_SIZE, sizeof(char));
  /* initialising variables */
  nutrient_count = 0;
  /*
    Converting the base 10 integer id to ascii,
    that is to say a string.
  */
  itoa(ingredient_id_number, ingredient_id, 10);
  if(fp != NULL){
    do{
      /* Checking id's for the search id */
      fscanf(fp," %[^;\n];", id);
      if(strstr(id, ingredient_id)){
        /* While we are looking at the correct string read the amounts */
        while(strstr(id,ingredient_id)){
          fscanf(fp," %[^;];", nutrients.nutrient_id[nutrient_count]);
          fscanf(fp,"%[^\n]", nutrients.nutrient_amount[nutrient_count]);

          /*find the ingredient id again and check it's still the same*/
          fscanf(fp," %[^;\n];", id);
          nutrient_count++;
        }
      }
      ch = getc(fp);
    }while(ch != EOF); /* Making sure we are not at the end of the file*/
  }
  /* Saving how many nutrients found to loop through them later */
  nutrients.nutrients_found = nutrient_count;
  /* Remembering to close the file */
  fclose(fp);
  return nutrients;
}

ingredient_nutrients_t nutrient_id_to_struct(nutrient_arrays_t nutrients){
  ingredient_nutrients_t ingredient_nutrients;
  int i;
  /* initialising the nutrients in case we find none in the database */
  strcpy(ingredient_nutrients.calcium, "0 g");
  strcpy(ingredient_nutrients.iron, "0 g");
  strcpy(ingredient_nutrients.zinc, "0 g");
  strcpy(ingredient_nutrients.selenium, "0 g");
  strcpy(ingredient_nutrients.vitamin_A, "0 g");
  strcpy(ingredient_nutrients.vitamin_D, "0 g");
  strcpy(ingredient_nutrients.vitamin_B2, "0 g");
  strcpy(ingredient_nutrients.vitamin_B3, "0 g");
  strcpy(ingredient_nutrients.vitamin_B12, "0 g");

  for(i = 0; i < nutrients.nutrients_found; i++){
    /* Looking through all ingredients found */
    switch(atoi(nutrients.nutrient_id[i])){
      case 1087: /* Id for calcium */
        strcpy(ingredient_nutrients.calcium, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.calcium, " mg");
      break;
      case 1089: /* Id for Iron */
        strcpy(ingredient_nutrients.iron, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.iron, " mg");
      break;
      case 1095:  /* Id for Zinc */
        strcpy(ingredient_nutrients.zinc, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.zinc, " mg");
      break;

      case 1103:  /* Id for Selenium */
        strcpy(ingredient_nutrients.selenium, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.selenium, " ug");
      break;
      case 1105:  /* Id for Vitamin A */
        strcpy(ingredient_nutrients.vitamin_A, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.vitamin_A, " ug");
      break;
      case 1112:  /* Id for Vitamin D */
        strcpy(ingredient_nutrients.vitamin_D, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.vitamin_D, " ug");
      break;
      case 1166: /* Id for Vitamin B2 */
        strcpy(ingredient_nutrients.vitamin_B2, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.vitamin_B2, " mg");
      break;
      case 1167: /* Id for Vitamin B3 */
        strcpy(ingredient_nutrients.vitamin_B3, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.vitamin_B3, " mg");
      break;
      case 1178: /* Id for Vitamin B12 */
        strcpy(ingredient_nutrients.vitamin_B12, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.vitamin_B12, " ug");
      break;
      default: break;
    }
  }
  /* There is no iodine in the database */
  strcpy(ingredient_nutrients.iodine,"0 g");

  free(nutrients.nutrient_amount);
  free(nutrients.nutrient_id);
  return ingredient_nutrients;
}
