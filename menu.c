#include "menu.h"
/**
 * Sets the users data as a backup and then tries to get it from the file and goes to the relevant page using dialogue with the user.
*/
void Page(void){
    UserData userData;
    char pageinput = '!';
    
    ClearScreen();
    LoadUserData(&userData);

    do{
        StartText();
        pageinput = getch();

        switch (pageinput){
        case 3:
            ClearScreen();
            NutrientPage(userData);
            ClearScreen();
            break;
        case USER_SETTINGS_PAGE:
            ClearScreen();
            UserSettings(&userData);
            ClearScreen();
            break;
        case INPUT_FILE_PAGE:
            system("cmd /C \"Input.json\"");
            break;
        case EXIT:
            ClearScreen();
            Exit();
            ClearScreen();
            break;
        default:
            printf("The following page was not found. Please try again.\n");
            break;
        }
    } while (pageinput != EXIT);
}

/**
 * Goes to the recipe page
 */
void NutrientPage(UserData userdata){
    do{
        printf("You're at the nutrient page.\n");
        /* Output nutrients */
        NutrientOutput(userdata);
        printf("Press 0 to return to main menu.\n");
    } while (getch() != '0');
    return;
}

/**
 * Exits the program
 */
void Exit(void){
    printf("See you next time.\n");
    return;
}

/**
 * Displays the VeGen ascii art and the instructions to the users
 */
void StartText(void){
    /*
     __      __   _____
     \ \    / /  / ____|
      \ \  / /__| |  __  ___ _ __
       \ \/ / _ \ | |_ |/ _ \ '_ \
        \  /  __/ |__| |  __/ | | |
         \/ \___|\_____|\___|_| |_|
    */
    printf(" __      __   _____\n");
    printf(" \\ \\    / /  / ____|\n");
    printf("  \\ \\  / /__| |  __  ___ _ __\n");
    printf("   \\ \\/ / _ \\ | |_ |/ _ \\ '_ \\\n");
    printf("    \\  /  __/ |__| |  __/ | | |\n");
    printf("     \\/ \\___|\\_____|\\___|_| |_|\n\n");

    printf("(1) Nutrients\n");
    printf("(2) User Settings\n");
    printf("(3) Open the recipe list\n");
    printf("(0) Exit\n");
}

/**
 * Clears the screen on both console and bash
 */
void ClearScreen(void){
    system("@cls||clear");
}

/**
 * Load the data stored in an ini file into the userData struct
 * @param userData the struct in control of all the users data and modifies the data
 */
void LoadUserData(UserData* userData){
    FILE *file;
    
    /* Checks if the file exists if it does not go back to Page and use the initial settings*/
    if ((file = fopen("User Data.ini", "r")) == NULL){
        printf("\x1b[32m" "It is recommended to input your specifics in User Settings for optimal perfomance" "\x1b[0m\n\n");
        userData->age = 20;
        userData->weight = 80;
        userData->gender = 'm';
        return;
    }
    
    fscanf(file, " Age=%i", &userData->age);
    fscanf(file, " Weight=%lf", &userData->weight);
    fscanf(file, " Gender=%c", &userData->gender);
    fclose(file);
    return;
}