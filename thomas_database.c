#include "thomas_database.h"
int main(void){
  printf("%i", get_ingredient_id("tomato"));
  return 0;
}

int get_ingredient_id(char *ingredient_name){
  char **id;
  int i, chosen, id_val, j;
  char **options;
  char found_name[200];

  /*Acessing the food lookup file*/
  FILE *fp = fopen("Food.csv", "r");
  id_val = 0;

  id = malloc(20 * sizeof(char*));
  for (i = 0; i < 20; i++)
      id[i] = malloc((400+1) * sizeof(char));


  options = malloc(20 * sizeof(char*));
    for (i = 0; i < 20; i++)
      options[i] = malloc((400+1) * sizeof(char));


  i = 0;
  /*Checking if the file was opened*/
  if(fp != NULL){
    /*Checking the current character*/
    int ch = getc(fp);
    /*Looking until the ingredient is found or until the end of the file*/
    while(ch != EOF){
      if(i == 20){
        printf("We break\n");
        break;
      }
      /*finding the file and getting the id*/
      fscanf(fp," %[a-zA-Z() ]", found_name);
      if(strstr(found_name, ingredient_name)){
        printf("Found:");
        strcpy(options[i], found_name);
        printf("%s ", options[i]);
        fscanf(fp," ; %[^\n] ", id[i]);
        printf("%s\n", id[i]);
        i++;
        printf("%i",i);
      }
      /*for(j = 0; j < i; j++){
        printf("%s\n", options[j]);
      }
      */
      ch = getc(fp);
    }
    fclose(fp);
  }
  for(i = 0; i < 20; i++){
    printf("%s\n", options[i]);
  }
  chosen = choose_ingredient(options, ingredient_name);
  id_val = atoi(id[chosen]);
  free(id);
  free(options);
  return id_val;
}

int choose_ingredient(char **options, char *ingredient_name){
  int choice;
  int i;
  choice = 0;
  printf("There are multiple matches to this: %s, search. Please choose the right one\n", ingredient_name);
  for(i = 0; i < 20; i++){
    printf("Number %i: %s\n", i + 1, options[i]);
  }
  scanf("%i", &choice);
  return choice-1;
}
