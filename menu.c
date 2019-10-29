#include <stdio.h>
#include "menu.h"
void Page(void){
    switch(GetPage()){
        case '1':
        Recipes();
        break;
        case '2':
        UserSettings();
        break;
        case '3': 
        Exit();
        break;
        default:
        printf("bruh...");
        break;

    }
}

int GetPage(void){
    char menu_page_number;
    scanf("%c", &menu_page_number);
    return menu_page_number;
}

void Recipes(void){
    printf("You're at the Recipes page.");
    return;
}

void UserSettings(void){
    printf("You're at the User Settings page.");
    return;
}

void Exit(void){
    printf("See you next time.");
    return;
}
