#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nutrien_item{
  char *ingredientname; 
  double calcium; 
  double iron; 
  double zinc; 
  double selenium; 
  double vitamin_B2;
  double vitamin_B3;
  double vitamin_B12; 
  double vitamin_A; 
  double viatamin_D; 
  double iodine;   


};

int main() {
  FILE *f; 

  fopen("IngredientsList.csv", "r"); 

  


  return EXIT_SUCCESS;
}
