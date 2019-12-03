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
  int counter = 0;

  do{
    char buffer[150];
    fgets(buffer, 150, f);
    counter++;

    if (counter != 1){

    }


  } while ();

  return EXIT_SUCCESS;
}

void read_data(char buffer[]){
  char token = strtok(buffer, ";");
  int counter;

  while (token != NULL){
    counter++;
    printf(" %s\n", token);
    token = strtok(NULL, ";");
  }

}
