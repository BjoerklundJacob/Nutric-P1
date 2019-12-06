/*
 * Data paser to ingredientsList, makes a struct of ingredients list. 
 *  
 * Bemeark: Arrayet af structs er nul opdelt. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONG_MAX 30
#define MAX_ARRAY_SIZE 84

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
 
int scan_data();
void printing_the_choosen_in(ingredientsList_struct ingredList[MAX_ARRAY_SIZE], int j);

int main() {
  int i, j; 
  FILE *f = fopen("IngredientsListP_2.csv", "r"); 
  ingredientsList_struct ingredList[MAX_ARRAY_SIZE]; 

  j = scan_data(); 
  
  if (j == 0){
      return EXIT_FAILURE; 
  }

  /*Funktionen afleaser CSV filen og skaber array'et */
  for (i = 0; i <= MAX_ARRAY_SIZE ; i++){

    fscanf(f, " %[a-zA-Z() ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] \n", 
              ingredList[i].ingredientname, ingredList[i].calcium, ingredList[i].iron, 
              ingredList[i].zinc, ingredList[i].selenium, ingredList[i].vitamin_B2, 
              ingredList[i].vitamin_B3, ingredList[i].vitamin_B12, ingredList[i].vitamin_A, 
              ingredList[i].viatamin_D, ingredList[i].iodine);
    
  }

  printing_the_choosen_in(ingredList, j); 

  fclose(f); 
  
  return EXIT_SUCCESS;
}

/*Denne funktion bruges til at teste om programmet fungere*/
int scan_data(){
  int j;
  printf("What ingrediens would you like to have? "); 
  scanf(" %d", &j);

  if (j > 81){
    printf("Try again the nummer is too big\n");
    return 0; 
  } else if(j < 0){
    printf("Try again the nummer is too little\n");
    return 0;    
  }
  return j; 
}

/*Funktion som printer den opskrifte nummer som man gerne ville have*/
void printing_the_choosen_in(ingredientsList_struct ingredList[MAX_ARRAY_SIZE], int j){
  printf("Ingredient: %d\n", j);
      printf("-------------------------------------------------\n");
      printf("Ingredients navn: %s\n", ingredList[j].ingredientname);
      printf("Calcium:          %s\n", ingredList[j].calcium);
      printf("Iron:             %s\n", ingredList[j].iron); 
      printf("Zinc:             %s\n", ingredList[j].zinc);
      printf("Selensium:        %s\n", ingredList[j].selenium);
      printf("Vitamin B2:       %s\n", ingredList[j].vitamin_B2);
      printf("Vitamin B3:       %s\n", ingredList[j].vitamin_B3);
      printf("Vitamin B12:      %s\n", ingredList[j].vitamin_B12);
      printf("Vitamin A:        %s\n", ingredList[j].vitamin_A);
      printf("Vitamin D:        %s\n", ingredList[j].viatamin_D);
      printf("Iodine:           %s\n", ingredList[j].iodine);         
      printf("\n\n"); 
}

