#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONG_MAX 15
#define MAX_ARRAY_SIZE 83

struct ingredientsList{
  char ingredientname[MAX_LONG_MAX]; 
  char calcium[MAX_LONG_MAX]; 
  char iron[MAX_LONG_MAX]; 
  char zinc[MAX_LONG_MAX]; 
  char selenium[MAX_LONG_MAX]; 
  char vitamin_B2[MAX_LONG_MAX];
  char vitamin_B3[MAX_LONG_MAX];
  char vitamin_B12[MAX_LONG_MAX]; 
  char vitamin_A[MAX_LONG_MAX]; 
  char viatamin_D[MAX_LONG_MAX]; 
  char iodine[MAX_LONG_MAX];   

};

typedef struct IngredientsList IngredientsList; 
 

int main() {
  FILE *f; 
  fopen("IngredientsListP.csv", "r"); 

  ingredientsList IngredientsList

  int i; 
  for (i = 1; i <= MAX_ARRAY_SIZE ; i++){
      fscanf(f, "%s ; %s ; %s ; %s ; %s ; %s ; %s ; %s ; %s ; %s ;", );

    }
   
  
  return EXIT_SUCCESS;
}

