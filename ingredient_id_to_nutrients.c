#include "ingredient_id_to_nutrients.h"

int main(void){
  nutrient_arrays_t my_nutrients;
  ingredient_nutrients_t nutrients_final;
  my_nutrients = get_nurient_values(174499);
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
  int i, x;
  char ch;
  char id[20];
  char ingredient_id[7];
  FILE *fp = fopen("food_nutrient.csv", "r");
  nutrient_arrays_t nutrients;
  /* Allocating space for the nutrients id's */
  nutrients.nutrient_id = calloc(150, sizeof(char*));
  for (i = 0; i < 80; i++)
      nutrients.nutrient_id[i] = calloc((10),sizeof(char));

  /* Allocating space for the nutrient values */
  nutrients.nutrient_amount = calloc(150, sizeof(char*));
  for (i = 0; i < 80; i++)
      nutrients.nutrient_amount[i] = calloc((10), sizeof(char));
  /* initialising variables */
  x = 0;
  /*
    Converting the base 10 integer id to ascii,
    that is to say a string.
  */
  itoa(ingredient_id_number, ingredient_id, 10);
  if(fp != NULL){
    do{
      //ungetc(ch, fp);
      /* Checking id's for the search id */
      fscanf(fp," %[^;\n];", id);
      if(strstr(id, ingredient_id)){
        printf("We founds %s\n", id);
        /* While we are looking at the correct string read the amounts */
        while(strstr(id,ingredient_id)){
          fscanf(fp," %[^;];", nutrients.nutrient_id[x]);
          printf("Nutrient Id: %s\n", nutrients.nutrient_id[x]);
          fscanf(fp,"%[^\n]", nutrients.nutrient_amount[x]);
          printf("Nutrient Value: %s\n", nutrients.nutrient_amount[x]);
          /*find the ingredient id again and check it's still the same*/
          fscanf(fp," %[^;\n];", id);
          x++;
        }
      }
      ch = getc(fp);
    }while(ch != EOF);
  }
  nutrients.nutrients_found = x;
  return nutrients;
}

ingredient_nutrients_t nutrient_id_to_struct(nutrient_arrays_t nutrients){
  ingredient_nutrients_t ingredient_nutrients;
  int i;

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
      /* calcium */
      case 1087:
        strcpy(ingredient_nutrients.calcium, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.calcium, " mg");
      break;
      /* Iron */
      case 1089:
        strcpy(ingredient_nutrients.iron, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.iron, " mg");
      break;
      /* Zinc */
      case 1095:
        strcpy(ingredient_nutrients.zinc, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.zinc, " mg");
      break;
      /* Selenium */
      case 1103:
        strcpy(ingredient_nutrients.selenium, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.selenium, " ug");
      break;
      /* Vitamin A */
      case 1105:
        strcpy(ingredient_nutrients.vitamin_A, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.vitamin_A, " ug");
      break;
      /* Vitamin D */
      case 1112:
        strcpy(ingredient_nutrients.vitamin_D, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.vitamin_D, " ug");
      break;
      /* Vitamin B2 */
      case 1166:
        strcpy(ingredient_nutrients.vitamin_B2, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.vitamin_B2, " mg");
      break;
      /* Vitamin B3 */
      case 1167:
        strcpy(ingredient_nutrients.vitamin_B3, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.vitamin_B3, " mg");
      break;
      /* Vitamin B12 */
      case 1178:
        strcpy(ingredient_nutrients.vitamin_B12, nutrients.nutrient_amount[i]);
        strcat(ingredient_nutrients.vitamin_B12, " ug");
      break;
      default: break;
    }
  }
  strcpy(ingredient_nutrients.iodine,"0 g");
  return ingredient_nutrients;
}
