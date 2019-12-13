/*
 * Data paser to ingredientsList, makes a struct of ingredientsList
 * Bemeark den er ikke general med specefik lavet til denne opgave   
 *  
*/

#include "csv_nutrient_parser.h"

ingredient_nutrients_t get_ingredient_nutrients(const char* name){
  int id;
  ingredient_nutrients_t nutrients;
  int i;
  char* cp;
  strcpy(nutrients.ingredient_name, name);
  /* Initialise all nutrients to 0 g */
  for(i = 0; i < NUTRIENT_COUNT; ++i){
    cp = nutrients.calcium + i * MAX_INGRIDIENT_NUTRIENT_STRING_LEN;
    strcpy(cp, "0.0 g");
  }
  id = get_ingredient_id(name);
  if(id != 0){
    /* Load ingredient nutrients */

  }
  return nutrients;
}

int get_ingredient_id(const char *search_string){
  int i, chosen, id_val = 0, j, words, search_score = 0;
  char **search_words;
  list_t* options = NULL;
  map_t* option;
  void* value;
  char csv_text[MAX_LINE_LENGTH], csv_id[ID_LENGTH];

  /* Make string array for splitting search into words */
  search_words = calloc(50, sizeof(char*));
  for(i = 0; i < 50; ++i){
    search_words[i] = calloc(50, sizeof(char));
  }

  printf("Search is <%s>\n", search_string);

  /*Accessing the food lookup file*/
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
    while(chosen = choose_ingredient(options, search_string) == -1){
      clear_screen();
      printf("Error, please input a valid option number.\n");
    }
    if(chosen != NO_RESULTS){
      option = list_value(options, chosen);
      id_val = atoi(map_value(option, "id"));
    }
  }
  else{
    printf("Ingredient nutrient data file could not be opened!\n");
    exit(EXIT_FAILURE);
  }

  /* Free allocated memory */
  for(i = 0; i < 50; ++i){
    free(search_words[i]);
  }
  free(search_words);
  list_free(options);

  return id_val;
}

int choose_ingredient(list_t* options, const char *search_string){
  int choice;
  int i, size;
  map_t* option;
  choice = 0;
  printf("The matches to <%s> is shown below. Please choose the right one\n", search_string);
  size = list_size(options);
  if(size > 0){
    for(i = 0; i < size; i++){
      option = list_value(options, i);
      printf("Number %i: %s\n", i + 1, map_value(option, "text"));
    }
    choice = getch();
    while(!(choice >= '1' && choice < '1' + size)){
      printf("Error, please input a valid option number.\n");
      choice = getch();
    }
  }
  else{
    printf("No matches to <%s> was found.\n", search_string);
    choice = -1;
  }
  return choice-1;
}

int string_to_words(const char* string, char** words){
  int i = 0;
  char _string[strlen(string)+1];
  char* cp;
  strcpy(_string, string);
  cp = _string;
  while(sscanf(cp, "%[a-zA-Z0-9]", words[i])){
    cp += strlen(words[i])+1;
    ++i;
  }
  return i;
}