#ifndef THOMAS

#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "json_structs.h"

#define THOMAS

#define ID_LENGTH 7
#define MAX_LINE_LENGTH 128
#define MAX_SEARCH_OPTIONS 5

ingredient_nutrients_t nutrient_id_to_struct(nutrient_arrays_t nutrients);
int get_ingredient_id(char *search_string);
int choose_ingredient(list_t* options, const char *search_string);
int string_to_words(char* string, char** words);
#endif
