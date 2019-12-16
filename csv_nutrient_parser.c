#include "csv_nutrient_parser.h"

<<<<<<< Updated upstream
void get_ingredient_nutrients(ingredient_nutrients_t* output_array){
  FILE *f = fopen("Ingredient_Nutrients.csv", "r"); 
  int i;

  if(f != NULL){
    /* Reads the CSV-file and makes the nutrient arr */
    for (i = 0; i < MAX_ARRAY_SIZE ; i++){

      fscanf(f, " %[a-zA-Z() ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] ; %[a-zA-Z0-9. ] \n", 
          output_array[i].ingredient_name, 
          output_array[i].calcium, 
          output_array[i].iodine,
          output_array[i].iron,
          output_array[i].selenium, 
          output_array[i].zinc, 
          output_array[i].vitamin_A,
          output_array[i].vitamin_B2,
          output_array[i].vitamin_B3, 
          output_array[i].vitamin_B12, 
          output_array[i].vitamin_D
      );
=======
/**
  * Data parser to ingredientsList, makes a struct of ingredientsList  
  */
ingredient_nutrients_t get_ingredient_nutrients(const char* name){
  int id;
  ingredient_nutrients_t nutrients;
  int i;
  char* cp;
  strcpy(nutrients.ingredient_name, name);

  for(i = 0; i < NUTRIENT_COUNT; ++i){
    cp = nutrients.calcium + i * MAX_INGRIDIENT_NUTRIENT_STRING_LEN;
    strcpy(cp, "0.0 g");
  }

  id = get_ingredient_id(name);
  if(id != 0){
    nutrients = nutrient_array_to_struct(get_nutrient_values(id));
    strcpy(nutrients.ingredient_name, name);
  }
  return nutrients;
}

/**
  * Finds ingredients matching searched words in the food database
  * Search options are limited to 5 
  */ 
int get_ingredient_id(const char *search_string){
  int i, chosen, id_val = 0, j, words, search_score = 0;
  char **search_words;
  list_t* options = NULL;
  map_t* option;
  void* value;
  char csv_text[MAX_LINE_LENGTH], csv_id[ID_LENGTH];

  search_words = calloc(50, sizeof(char*));
  for(i = 0; i < 50; ++i){
    search_words[i] = calloc(50, sizeof(char));
  }
  FILE *fp = fopen("Food.csv", "r");

  if(fp != NULL){
    words = string_to_words(search_string, search_words);
    i = 0;
    while(MAX_SEARCH_OPTIONS > i && fscanf(fp, " %[^;]; %s\n", csv_text, csv_id) == 2){
      search_score = 0;
      for(j = 0; j < words; ++j){
        search_score += strstr(csv_text, search_words[j]) != NULL ? 1 : 0;
      }
      if(search_score == words){
        option = map_create();
        /*Text*/
        value = calloc(strlen(csv_text)+1, sizeof(char));
        if(value == NULL){exit(EXIT_FAILURE);}
        strcpy(value, csv_text);
        map_add(option, "text", value, value_string);
        /*Id*/
        value = calloc(ID_LENGTH, sizeof(char));
        if(value == NULL){exit(EXIT_FAILURE);}
        strcpy(value, csv_id);
        map_add(option, "id", value, value_string);
        /*Add to options*/
        list_add(&options, option, value_map);
        /*Increment i to make sure to stop if max matches is found*/
        ++i;
      }
    }
    fclose(fp);
    while((chosen = choose_ingredient(options, search_string)) == -1){
      clear_screen();
      printf("Error, please input a valid option number.\n");
>>>>>>> Stashed changes
    }
    fclose(f);
  }

<<<<<<< Updated upstream
}

/*void printing_the_chosen_in(ingredient_nutrients_t ingredientsList[MAX_ARRAY_SIZE], int j){
  printf("Ingredient: %d\n", j);
      printf("-------------------------------------------------\n");
      printf("Ingredients navn: %s\n", ingredientsList[j].ingredient_name);
      printf("Calcium:          %s\n", ingredientsList[j].calcium);
      printf("Iron:             %s\n", ingredientsList[j].iron); 
      printf("Zinc:             %s\n", ingredientsList[j].zinc);
      printf("Selenium:         %s\n", ingredientsList[j].selenium);
      printf("Vitamin B2:       %s\n", ingredientsList[j].vitamin_B2);
      printf("Vitamin B3:       %s\n", ingredientsList[j].vitamin_B3);
      printf("Vitamin B12:      %s\n", ingredientsList[j].vitamin_B12);
      printf("Vitamin A:        %s\n", ingredientsList[j].vitamin_A);
      printf("Vitamin D:        %s\n", ingredientsList[j].vitamin_D);
      printf("Iodine:           %s\n", ingredientsList[j].iodine);         
      printf("\n\n"); 
}*/
=======
  /** 
    * Free allocated memory 
    */
  for(i = 0; i < 50; ++i){
    free(search_words[i]);
  }
  free(search_words);
  list_free(options);
  return id_val;
}

/**
  * User chooses the specific ingredient that they wanted
  */ 
int choose_ingredient(list_t* options, const char *search_string){
  int choice;
  int i, size;
  map_t* option;
  printf("The matches to <%s> is shown below. Please choose the right one\n"
         "If none of the options are correct, please specify ingredient and try again.\n", search_string);
  printf("Press the number corresponding to an option:\n");
  size = list_size(options);
  if(size > 0){
    for(i = 0; i < size; i++){
      option = list_value(options, i);
      printf("(%i) %s\n", i + 1, map_value(option, "text"));
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

/**
  *
  */  
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
  FILE *fp = fopen("Food_Nutrients.csv", "r");

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
      case 1106:  /* Id for Vitamin A */
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
>>>>>>> Stashed changes
