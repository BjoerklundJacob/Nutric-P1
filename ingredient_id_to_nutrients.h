#ifndef ID
#define ID
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#define MAX_ARRAY_SIZE 82
#define MAX_INGRIDIENT_NUTRIENT_STRING_LEN 30
#define MAX_NUTRIENT_COUNT 100
#define MAX_NUTRIENT_SIZE 20
#define MAX_ID_SIZE 20

typedef struct nutrient_arrays{
  char **nutrient_id;
  char **nutrient_amount;
  int nutrients_found;
}nutrient_arrays_t;

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
nutrient_arrays_t get_nurient_values(int ingredient_id_number);
ingredient_nutrients_t nutrient_id_to_struct(nutrient_arrays_t nutrients);
#endif
