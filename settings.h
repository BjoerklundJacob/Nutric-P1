#ifndef SETTINGS
#define SETTINGS

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
void SaveUserData(UserData userData);
#endif