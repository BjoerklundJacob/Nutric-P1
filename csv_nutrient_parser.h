#ifndef CSV_NUTRIENT_PARSER
#define CSV_NUTRIENT_PARSER

#include "json_structs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "nutrient_counter.h"
#include "menu.h"

#define ID_LENGTH 7
#define MAX_LINE_LENGTH 128
#define MAX_SEARCH_OPTIONS 5
#define MAX_ARRAY_SIZE 82
#define MAX_INGRIDIENT_NUTRIENT_STRING_LEN 30
#define NO_RESULTS -2

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

int get_ingredient_id(const char *search_string);
int choose_ingredient(list_t* options, const char *search_string);
int string_to_words(const char* string, char** words);
ingredient_nutrients_t get_ingredient_nutrients(const char* name);
#endif