#ifndef MENU
#define MENU
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "output.h"

#define NUTRIENT_PAGE '1'
#define USER_SETTINGS_PAGE '2'
#define INPUT_FILE_PAGE '3'
#define EXIT '0'

void user_settings(UserData* userData);
void recipe_output(void);
void menu(void);
void nutrient_page(UserData);
void exit_message(void);
void start_text(void);
void clear_screen(void);
void load_user_data(UserData* userData);
void nutrient_output(UserData userdata);
#endif