#ifndef SETTINGS
#define SETTINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include "data.h"

void user_settings(UserData* userData);
void get_age_input(UserData* userData);
void get_gender_input(UserData* userData);
void get_weight_input(UserData* userData);
void user_settings_text(void);
void save_user_data(UserData userData);
void clear_screen(void);
#endif