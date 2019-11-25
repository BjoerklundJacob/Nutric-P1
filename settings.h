#include "data.h"
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

void UserSettings(UserData* userData);
void Age(UserData* userData);
void Gender(UserData* userData);
void Weight(UserData* userData);
void FoodExclusions(UserData* userData) ;
void UserSettingsText(void);
char Signed(int input);
int CheckInput(char* sign, int* input);
void ClearChar(char* sign);
void ClearScreen(void);
void SaveUserData(UserData userData);
