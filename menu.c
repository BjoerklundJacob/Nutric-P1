#include <stdio.h>
#include <stdlib.h>
#include "menu.h"


void Page(void){
    UserData userData;

    char pageinput = '9';
    StartText();
    do{
        pageinput = GetPage();
        
        switch(pageinput){
            case '1':
                ClearScreen();
                Recipes();
                ClearScreen();
                StartText();
                break;
            case '2':
                ClearScreen();
                UserSettings(&userData);
                ClearScreen();
                StartText();
                break;
            case '0': 
                ClearScreen();
                Exit();
                break;
            default:
                printf("The following page was not found. Please try again.\n");
                break;

        }
    } while(pageinput !='0');
}

char GetPage(void){
    char menu_page_number;
    scanf(" %c", &menu_page_number);
    return menu_page_number;
}

void Recipes(void){
    char recipeinput = '9';
     
    do{
        printf("You're at the Recipes page. Press 1 to find recipes or smth and 0 to return to main menu.\n");
        scanf(" %c", &recipeinput);
    } while (recipeinput != '0');
    printf("You're leaving recipes page now.\n\n");
    
    StartText();

    return;
}

void Exit(void){
    printf("See you next time.\n");
    return;
}

void StartText(void)
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

    printf("\nType 1,2 or 0 to get to the respective page.\n");
    printf("(1) Recipies\n");
    printf("(2) User Settings\n");
    printf("(0) Exit\n");
}

void ClearScreen(void){
    system("@cls||clear");
}