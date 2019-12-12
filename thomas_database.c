#include "thomas_database.h"
int main(void){
  printf("%i", get_ingredient_id("chicken wing"));
  return 0;
}

int get_ingredient_id(char *search_string){
  int i, chosen, id_val, j, words, search_score = 0;
  char csv_options[SEARCH_OPTIONS][MAX_LINE_LENGTH], csv_ids[SEARCH_OPTIONS][ID_LENGTH];
  char **search_words;

  search_words = calloc(50, sizeof(char*));
  for(i = 0; i < 50; ++i){
    search_words[i] = calloc(50, sizeof(char));
  }

  printf("Search is <%s>\n", search_string);

  /*Acessing the food lookup file*/
  FILE *fp = fopen("food.csv", "r");
  id_val = 0;

  /*Checking if the file was opened*/
  if(fp != NULL){
    words = string_to_words(search_string, search_words);
    i = 0;
    while(i < words && fscanf(fp, " %[^;]; %s\n", csv_options[i], csv_ids[i]) == 2){
      search_score = 0;
      for(j = 0; j < words; ++j){
        search_score += strstr(csv_options[i], search_words[j]) != NULL ? 1 : 0;
      }
      if(search_score == words)
        i++;
    }
    fclose(fp);
  }

  for(i = 0; i < SEARCH_OPTIONS; i++){
    printf("%s\n", csv_options[i]);
  }
  //chosen = choose_ingredient(csv_options, search_string);
  //id_val = atoi(csv_ids[chosen]);

  for(i = 0; i < 50; ++i){
    free(search_words[i]);
  }
  free(search_words);

  return id_val;
}

int choose_ingredient(char options[SEARCH_OPTIONS][MAX_LINE_LENGTH], const char *search_string){
  int choice;
  int i;
  choice = 0;
  printf("The matches to <%s> is shown below. Please choose the right one\n", search_string);
  for(i = 0; i < SEARCH_OPTIONS; i++){
    printf("Number %i: %s\n", i + 1, options[i]);
  }
  scanf("%i", &choice);
  return choice-1;
}

int string_to_words(char* string, char** words){
  int i = 0;
  char* cp = string;
  while(sscanf(cp, "%[a-zA-Z0-9]", words[i])){
    cp += strlen(words[i])+1;
    printf("%s\n", words[i]);
    ++i;
  }
  return i;
}