#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include "data.h"

void UserSettings(UserData* userData);
void Age(UserData* userData);
void Gender(UserData* userData);
void Weight(UserData* userData);
void UserSettingsText(void);
char Signed(int input);
int CheckInput(char* sign, int* input);
void ClearChar(char* sign);
void SaveUserData(UserData userData);
