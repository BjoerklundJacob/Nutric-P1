#ifndef CSV_NUTRIENT_PARSER
#define CSV_NUTRIENT_PARSER

#include "json_structs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_ARRAY_SIZE 82
#define MAX_INGRIDIENT_NUTRIENT_STRING_LEN 30

typedef struct ingredientsList_struct{
  char ingredient_name[MAX_INGRIDIENT_NUTRIENT_STRING_LEN];
  char calcium[MAX_INGRIDIENT_NUTRIENT_STRING_LEN];
  char iodine[MAX_INGRIDIENT_NUTRIENT_STRING_LEN];
  char iron[MAX_INGRIDIENT_NUTRIENT_STRING_LEN];
  char selenium[MAX_INGRIDIENT_NUTRIENT_STRING_LEN];
  char zinc[MAX_INGRIDIENT_NUTRIENT_STRING_LEN];
  char vitamin_A[MAX_INGRIDIENT_NUTRIENT_STRING_LEN];
  char vitamin_B2[MAX_INGRIDIENT_NUTRIENT_STRING_LEN];
  char vitamin_B3[MAX_INGRIDIENT_NUTRIENT_STRING_LEN];
  char vitamin_B12[MAX_INGRIDIENT_NUTRIENT_STRING_LEN];
  char vitamin_D[MAX_INGRIDIENT_NUTRIENT_STRING_LEN];
}ingredient_nutrients_t;


/*void printing_the_choosen_in(ingredient_nutrients_t ingredientsList[MAX_ARRAY_SIZE], int j);*/
void get_ingredient_nutrients(ingredient_nutrients_t* output_array);
#endif