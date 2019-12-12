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

void Page(void);
void NutrientPage(UserData userdata);
void Exit(void);
void StartText(void);
void ClearScreen(void);
void LoadUserData(UserData* userData);
void UserSettings(UserData* userData);
#endif