#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONG_MAX 15
#define MAX_ARRAY_SIZE 83

struct ingredientsList_struct{
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

typedef struct ingredientsList_struct ingredientsList_struct; 
 

int main() {
  FILE *f = fopen("IngredientsListP_2.csv", "r"); 

  ingredientsList_struct ingredientsList[MAX_ARRAY_SIZE]; 

  int i, j; 

  /*Funktionen afleaser CSV filen og skaber array'et */
  for (i = 1; i <= MAX_ARRAY_SIZE ; i++){

    fscanf(f, " %s ; %s ; %s ; %s ; %s ; %s ; %s ; %s ; %s ; %s \n", 
              ingredientsList[i].ingredientname, ingredientsList[i].calcium, ingredientsList[i].iron, 
              ingredientsList[i].zinc, ingredientsList[i].selenium, ingredientsList[i].vitamin_B2, 
              ingredientsList[i].vitamin_B3, ingredientsList[i].vitamin_B12, ingredientsList[i].vitamin_A, 
              ingredientsList[i].viatamin_D, ingredientsList[i].iodine);
    
  }
  
  fclose(f); 

  /*Funktionen printer array'et */ 
  for (j = 1; j < MAX_ARRAY_SIZE; j++){
      printf("Ingredient: %d\n", j);
      printf("-------------------------------------------------\n");
      printf("Ingredients navn: %s\n", ingredientsList[j].ingredientname);
      printf("Calcium:          %s\n", ingredientsList[j].calcium);
      printf("Iron:             %s\n", ingredientsList[j].iron); 
      printf("Zinc:             %s\n", ingredientsList[j].zinc);
      printf("Selensium:        %s\n", ingredientsList[j].selenium);
      printf("Vitamin B2:       %s\n", ingredientsList[j].vitamin_B2);
      printf("Vitamin B3:       %s\n", ingredientsList[j].vitamin_B3);
      printf("Vitamin B12:      %s\n", ingredientsList[j].vitamin_B12);
      printf("Vitamin A:        %s\n", ingredientsList[j].vitamin_A);
      printf("Vitamin D:        %s\n", ingredientsList[j].iodine);         
      printf("\n\n"); 

  }
  
  return EXIT_SUCCESS;
}

