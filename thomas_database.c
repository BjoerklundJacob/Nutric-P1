#include "thomas_database.h"
int main(void){
  printf("%i", get_ingredient_id("boiled potato"));
  return 0;
}

int get_ingredient_id(char *search_string){
  int i, chosen, id_val, j, words, search_score = 0;
  char **search_words;
  list_t* options = NULL;
  map_t* option;
  void* value;
  char csv_text[MAX_LINE_LENGTH], csv_id[ID_LENGTH];

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
    while(i < MAX_SEARCH_OPTIONS && fscanf(fp, " %[^;]; %s\n", csv_text, csv_id) == 2){
      search_score = 0;
      for(j = 0; j < words; ++j){
        search_score += strstr(csv_text, search_words[j]) != NULL ? 1 : 0;
      }
      if(search_score == words){
        printf("%s\n", csv_text);
        //Add text and id to list
        option = map_create();
        //Text
        value = calloc(strlen(csv_text)+1, sizeof(char));
        if(value == NULL){exit(EXIT_FAILURE);}
        strcpy(value, csv_text);
        map_add(option, "text", value, value_string);
        //Text
        value = calloc(ID_LENGTH, sizeof(char));
        if(value == NULL){exit(EXIT_FAILURE);}
        strcpy(value, csv_id);
        map_add(option, "id", value, value_string);
        //Add to options
        list_add(&options, option, value_map);
        //Increment i to make sure to stop if max matches is found;
        ++i;
      }
    }
    fclose(fp);
  }
  printf("Options: %d\n", list_size(options));

  for(i = 0; i < list_size(options)-1; i++){
    option = list_value(options, i);
    printf("%s\n", map_value(option, "text"));
  }
  chosen = choose_ingredient(options, search_string);
  option = list_value(options, chosen);
  id_val = atoi(map_value(option, "id"));

  for(i = 0; i < 50; ++i){
    free(search_words[i]);
  }
  free(search_words);
  list_free(options);

  return id_val;
}

int choose_ingredient(list_t* options, const char *search_string){
  int choice;
  int i;
  map_t* option;
  choice = 0;
  printf("The matches to <%s> is shown below. Please choose the right one\n", search_string);
  for(i = 0; i < list_size(options); i++){
    option = list_value(options, i);
    printf("Number %i: %s\n", i + 1, map_value(option, "text"));
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
  printf("\n");
  return i;
}
