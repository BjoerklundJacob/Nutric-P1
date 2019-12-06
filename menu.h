#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "output.h"

#define NUTRIENT_PAGE '1'
#define USER_SETTINGS_PAGE '2'
#define INPUT_FILE_PAGE '3'
#define EXIT '0'

void UserSettings(UserData* userData);
void RecipeOutput(void);
void Page(void);
void NutrientPage(UserData);
void Exit(void);
void StartText(void);
void ClearScreen(void);
void LoadUserData(UserData* userData);
