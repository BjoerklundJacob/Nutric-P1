/*
User Settings
Weight
Food Exclusions
Return to main menu
If $ then eastereggl ("https://pics.me.me/looks-like-meats-back-on-the-menu-boys-when-you-37741962.png")
*/
#include <stdio.h>
#include "settings.h"

void UserSettings(UserData* userData){
    char input = 9;
    
    UserSettingsText();

    while (input != 0){
        scanf(" %c", &input);
        switch (input){
        case '1':
            ClearScreen();
            Weight(userData);
            UserSettingsText();
            break;
        case '2':
            break;
        case '0':
            return;
        default:
            printf("The following page was not found. Please try again.\n");
            break;
        }
    } 
    return;
}

void Weight(UserData* userData){
    printf("Please input your current weight: ");
    scanf(" %lf", &userData->weight);
    printf("Your weight is now set to %.0lf\n\n", userData->weight); 
    return;
}

void UserSettingsText(void){
    printf("You're at the User Settings page. \nType 1, 2 or 0 to get to the respective settings.\n");
    printf("(1) Weight\n");
    printf("(2) Food Exclusions\n");
    printf("(0) Return to the main menu\n");
    return;
}

void ClearScreen(void){
    system("@cls||clear");
}