#ifndef CSV_NUTRIENT_PARSER
#define CSV_NUTRIENT_PARSER

#include "json_structs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_ARRAY_SIZE 82
#define MAX_LONG_MAX 30

typedef struct ingredientsList_struct{
  char ingredient_name[MAX_LONG_MAX];
  char calcium[MAX_LONG_MAX];
  char iodine[MAX_LONG_MAX];
  char iron[MAX_LONG_MAX];
  char selenium[MAX_LONG_MAX];
  char zinc[MAX_LONG_MAX];
  char vitamin_A[MAX_LONG_MAX];
  char vitamin_B2[MAX_LONG_MAX];
  char vitamin_B3[MAX_LONG_MAX];
  char vitamin_B12[MAX_LONG_MAX];
  char vitamin_D[MAX_LONG_MAX];
}ingredient_nutrients_t;


/*void printing_the_choosen_in(ingredient_nutrients_t ingredientsList[MAX_ARRAY_SIZE], int j);*/
void get_ingredient_nutrients(ingredient_nutrients_t* output_array);
#endif