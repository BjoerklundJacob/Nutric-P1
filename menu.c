#include "menu.h"
/**
 * Sets the users data as a backup and then tries to get it from the file and goes to the relevant page using dialogue with the user.
*/
void Page(void){
    UserData userData;
    char pageinput = '!';
    int i;
    
    ClearScreen();
    userData.age = 20;
    userData.weight = 80;
    userData.gender = 'm';
    for (i = 0; i < e_recipe_set_tags_size; i++){
        userData.foodExclusions[i] = -5;
    }
    LoadUserData(&userData);

    StartText();
    do{
        pageinput = _getche();

        switch (pageinput){
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
    } while (pageinput != '0');
}

/**
 * Goes to the recipe page (not incorporated yet)
 */
void Recipes(void){
    char recipeinput = '9';

    do{
        printf("You're at the Recipes page. Press 1 to find recipes or smth and 0 to return to main menu.\n");
        recipeinput = _getche();
        if(recipeinput == '1'){
            ClearScreen();
            RecipeOutput();
        }
        else{
            ClearScreen();
            printf("The input does not correspond to any pages. Please try again.\n");
        }
    } while (recipeinput != '0');
    ClearScreen();
    printf("You're leaving recipes page now.\n\n");

    StartText();

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
    printf("     \\/ \\___|\\_____|\\___|_| |_|\n");

    printf("\nType 1,2 or 0 to get to the respective page.\n");
    printf("(1) Recipies\n");
    printf("(2) User Settings\n");
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
    int i;
    
    /* Checks if the file exists if it does not go back to Page and use the initial settings*/
    if ((file = fopen("User Data.ini", "r")) == NULL){
        printf("\x1b[32m" "It is recommended to input your specifics in User Settings for optimal perfomance" "\x1b[0m\n\n");
        return;
    }
    
    fscanf(file, " Age=%i", &userData->age);
    fscanf(file, " Weight=%lf", &userData->weight);
    fscanf(file, " Gender=%c", &userData->gender);
    for (i = 0; i < e_recipe_set_tags_size-1; i++)
    {
        fscanf(file, " FoodExclusions[%d]=%d", &i,  &userData->foodExclusions[i]);
    }
    fclose(file);
    return;
}