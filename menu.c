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

char* StartText(void)
{
    /*
     __      __   _____
     \ \    / /  / ____|
      \ \  / /__| |  __  ___ _ __
       \ \/ / _ \ | |_ |/ _ \ '_ \
        \  /  __/ |__| |  __/ | | |
         \/ \___|\_____|\___|_| |_|
    */
    printf(" __      __   _____\n \\ \\    / /  / ____|\n  \\ \\  / /__| |  __  ___ _ __\n   \\ \\/ / _ \\ | |_ |/ _ \\ '_ \\\n    \\  /  __/ |__| |  __/ | | |\n     \\/ \\___|\\_____|\\___|_| |_|\n");

    printf("\nType 1,2 or 3 to get to the respective page.\n");
    printf("(1) Recipies\n");
    printf("(2) User Settings\n");
    printf("(3) Exit\n");
}
