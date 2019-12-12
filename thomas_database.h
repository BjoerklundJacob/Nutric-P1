#ifndef THOMAS
#define THOMAS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#define MAX_LONG_MAX 30
#define MAX_ARRAY_SIZE 82
typedef struct ingredientsList_struct{
  char ingredient_name[MAX_LONG_MAX];
  char calcium[MAX_LONG_MAX];
  char iron[MAX_LONG_MAX];
  char zinc[MAX_LONG_MAX];
  char selenium[MAX_LONG_MAX];
  char iodine[MAX_LONG_MAX];
  char vitamin_B2[MAX_LONG_MAX];
  char vitamin_B3[MAX_LONG_MAX];
  char vitamin_B12[MAX_LONG_MAX];
  char vitamin_A[MAX_LONG_MAX];
  char vitamin_D[MAX_LONG_MAX];
}ingredient_nutrients_t;
int get_ingredient_id(char *ingredient_name);
int choose_ingredient(char **options, char *ingredient_name);
#endif
