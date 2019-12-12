#ifndef THOMAS

#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define THOMAS

#define ID_LENGTH 7
#define MAX_LINE_LENGTH 128
#define SEARCH_OPTIONS 10


int get_ingredient_id(char *search_string);
int choose_ingredient(char options[SEARCH_OPTIONS][MAX_LINE_LENGTH], const char *search_string);
int string_to_words(char* string, char** words);
#endif