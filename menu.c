#include "menu.h"
/**
 * Sets the users data as a backup and then tries to get it from the file and goes to the relevant page using dialogue with the user.
*/
void menu(void){
    UserData userData;
    char pageinput = '!';
    
    load_user_data(&userData);

    do{
        clear_screen();
        start_text();
        pageinput = getch();

        switch (pageinput){
        case NUTRIENT_PAGE:
            clear_screen();
            nutrient_page(userData);
            clear_screen();
            break;
        case USER_SETTINGS_PAGE:
            clear_screen();
            user_settings(&userData);
            clear_screen();
            break;
        case INPUT_FILE_PAGE:
            system("start %windir%\\notepad.exe \"Input.json\"");
            break;
        case EXIT:
            clear_screen();
            exit_message();
            clear_screen();
            break;
        default:
            printf("The following page was not found. Please try again.\n");
            break;
        }
    } while (pageinput != EXIT);
}

/*
 * Goes to the recipe page
 */
void nutrient_page(UserData userdata){
    do{
        printf("You're at the nutrient page.\n");
        /* Output nutrients */
        nutrient_output(userdata);
        printf("Press 0 to return to main menu.\n");
    } while (getch() != '0');
    return;
}

/**
 * Exits the program
 */
void exit_message(void){
    printf("See you next time.\n");
    return;
}

/*
 * Displays the VeGen ascii art and the instructions to the users
 */
void start_text(void){
    /*
         __       _        _      
      /\ \ \_   _| |_ _ __(_) ___ 
     /  \/ / | | | __| '__| |/ __|
    / /\  /| |_| | |_| |  | | (__ 
    \_\ \/  \__,_|\__|_|  |_|\___|
    */
    printf("     __       _        _\n");
    printf("  /\\ \\ \\_   _| |_ _ __(_) ___\n");
    printf(" /  \\/ / | | | __| '__| |/ __|\n");
    printf("/ /\\  /| |_| | |_| |  | | (__ \n");
    printf("\\_\\ \\/  \\__,_|\\__|_|  |_|\\___|\n");

    printf("(1) Nutrients\n");
    printf("(2) User Settings\n");
    printf("(3) Open the recipe list\n");
    printf("(0) Exit\n");
}

/*
 * Clears the screen on both console and bash
 */
void clear_screen(void){
    system("@cls||clear");
}

/*
 * Load the data stored in an ini file into the userData struct
 * @param userData the struct in control of all the users data and modifies the data
 */
void load_user_data(UserData* userData){
    FILE *file;
    
    /* Checks if the file exists if it does not go back to menu and use the initial settings*/
    if ((file = fopen("User_Data.ini", "r")) == NULL){
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