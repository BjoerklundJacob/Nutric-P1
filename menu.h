#ifndef MENU
#define MENU

#include "output.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define USER_SETTINGS_PAGE '2'
#define INPUT_FILE_PAGE '3'
#define EXIT '0'
#define NUTRIENT_PAGE '1'

void user_settings(UserData* userData);
void menu(void);
void nutrient_page(UserData);
void exit_message(void);
void start_text(void);
void clear_screen(void);
void load_user_data(UserData* userData);
#endif