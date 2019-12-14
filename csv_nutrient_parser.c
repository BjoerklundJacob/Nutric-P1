/*
 * Data parser to ingredientsList, makes a struct of ingredientsList
 * Bemaerk den er ikke general med specifikt lavet til denne opgave   
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
    nutrients = nutrient_array_to_struct(get_nutrient_values(id));
    strcpy(nutrients.ingredient_name, name);
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

  /*Accessing the food lookup file*/
  FILE *fp = fopen("Food.csv", "r");
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
        //Add text and id to list
        option = map_create();
        //Text
        value = calloc(strlen(csv_text)+1, sizeof(char));
        if(value == NULL){exit(EXIT_FAILURE);}
        strcpy(value, csv_text);
        map_add(option, "text", value, value_string);
        //Id
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
    while((chosen = choose_ingredient(options, search_string)) == -1){
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
  printf("The matches to <%s> is shown below. Please choose the right one\n"
         "If none of the options are correct, please specify ingredient and try again.\n", search_string);
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
    return NO_RESULTS;
  }
  if(choice != -1){
    option = list_value(options, (choice - '1'));
    printf("Selected <%s> (%d)\n\n", map_value(option, "text"), (choice - '1')+1);
    return (choice - '1');
  }
  return -1;
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

nutrient_arrays_t get_nutrient_values(int ingredient_id_number){
  int i, nutrient_count;
  char ch, id[MAX_ID_SIZE], ingredient_id[MAX_NUTRIENT_SIZE];
  nutrient_arrays_t nutrients;
  /* Opening the file */
  FILE *fp = fopen("Food_Nutrient.csv", "r");

  /* Allocating space for the nutrients id's */
  nutrients.nutrient_id = calloc(MAX_NUTRIENT_COUNT, sizeof(int));
  /* Allocating space for the nutrient values */
  nutrients.nutrient_amount = calloc(MAX_NUTRIENT_COUNT, sizeof(double));
  
  if(fp != NULL){
    /* Jump to id position in file */
    fseek(fp, JUMP_PER_ID_DIFFERENCE * (ingredient_id_number - FIRST_ID), SEEK_SET);
    /* Load nutrients for id */
    for(nutrient_count = 0; nutrient_count < MAX_NUTRIENT_COUNT; ++nutrient_count){
      fscanf(fp," %*[^;];%d;%lf", &nutrients.nutrient_id[nutrient_count], &nutrients.nutrient_amount[nutrient_count]);
    }
    /* Remembering to close the file */
    fclose(fp);
  }
  return nutrients;
}

ingredient_nutrients_t nutrient_array_to_struct(nutrient_arrays_t nutrients){
  ingredient_nutrients_t ingredient_nutrients;
  int i;
  /* initialising the nutrients in case we find none in the database */
  strcpy(ingredient_nutrients.calcium, "0 g");
  strcpy(ingredient_nutrients.iron, "0 g");
  strcpy(ingredient_nutrients.zinc, "0 g");
  strcpy(ingredient_nutrients.selenium, "0 g");
  strcpy(ingredient_nutrients.vitamin_A, "0 g");
  strcpy(ingredient_nutrients.vitamin_D, "0 g");
  strcpy(ingredient_nutrients.vitamin_B2, "0 g");
  strcpy(ingredient_nutrients.vitamin_B3, "0 g");
  strcpy(ingredient_nutrients.vitamin_B12, "0 g");
  strcpy(ingredient_nutrients.iodine, "0 g");/* There is no iodine in the database */

  for(i = 0; i < MAX_NUTRIENT_COUNT; i++){
    /* Looking through all ingredients found */
    switch(nutrients.nutrient_id[i]){
      case 1087: /* Id for calcium */
        sprintf(ingredient_nutrients.calcium, "%lf %s", nutrients.nutrient_amount[i], "mg");
        break;
      case 1089: /* Id for Iron */
        sprintf(ingredient_nutrients.iron, "%lf %s", nutrients.nutrient_amount[i], "mg");
        break;
      case 1095:  /* Id for Zinc */
        sprintf(ingredient_nutrients.zinc, "%lf %s", nutrients.nutrient_amount[i], "mg");
        break;
      case 1103:  /* Id for Selenium */
        sprintf(ingredient_nutrients.selenium, "%lf %s", nutrients.nutrient_amount[i], "ug");
        break;
      case 1105:  /* Id for Vitamin A */
        sprintf(ingredient_nutrients.vitamin_A, "%lf %s", nutrients.nutrient_amount[i], "ug");
        break;
      case 1112:  /* Id for Vitamin D */
        sprintf(ingredient_nutrients.vitamin_D, "%lf %s", nutrients.nutrient_amount[i], "ug");
      break;
      case 1166: /* Id for Vitamin B2 */
        sprintf(ingredient_nutrients.vitamin_B2, "%lf %s", nutrients.nutrient_amount[i], "mg");
      break;
      case 1167: /* Id for Vitamin B3 */
        sprintf(ingredient_nutrients.vitamin_B3, "%lf %s", nutrients.nutrient_amount[i], "mg");
      break;
      case 1178: /* Id for Vitamin B12 */
        sprintf(ingredient_nutrients.vitamin_B12, "%lf %s", nutrients.nutrient_amount[i], "ug");
      break;
    }
  }
  
  /* Freeing the calloced arrays */
  free(nutrients.nutrient_amount);
  free(nutrients.nutrient_id);
  return ingredient_nutrients;
}
