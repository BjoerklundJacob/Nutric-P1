#include "settings.h"
/**
 * Handles movement throughout the user settings whilst also giving descriptive text for the user.
 * @param userData the struct in control of all the users data and modifies the data
*/
void user_settings(UserData* userData){
    char input = '!';
    
    user_settings_text();

    while (input != 0){
        input = getch();
        switch (input){
            case '1':
                clear_screen();
                get_age_input(userData);
                user_settings_text();
                break;
            case '2':
                clear_screen();
                get_weight_input(userData);
                user_settings_text();
                break;
            case '3':
                clear_screen();
                get_gender_input(userData);
                user_settings_text();
                break;
            case '0':
                save_user_data(*userData);
                clear_screen();
                return;
            default:
                printf("The following page was not found. Please try again.\n");
                break;
        }
    } 
    return;
}

/**
 * Takes the users weight from dialog and inputs it into the structure member weight and clearing the buffer on invalid inputs.
 * @param userData the struct in control of all the users data and modifies the data
 */
void get_age_input(UserData* userData){
    int scanres;
    printf("Please input your age: ");
    scanres = scanf(" %i", &userData->age);
    while (scanres != 1){
        char buffer;
        while (buffer != '\n'){
            scanf("%c", &buffer);
        }
        scanres = scanf(" %i", &userData->age);
    }
    printf("Your age is now set to %i\n\n", userData->age); 
    return;
}

/**
 * Takes the users gender from dialog and inputs it into the structure member gender and clearing the buffer on invalid inputs.
 * @param userData the struct in control of all the users data and modifies the data
 */
void get_gender_input(UserData* userData){
    char gender;
    printf("Please input your gender (f)emale or (m)ale: ");
    do{
        gender = tolower(getch());
        if (gender == 'm' || gender == 'f'){
            userData->gender = gender; 
        }else{
            printf("\nPlease input a valid gender: ");
        }
    }while(gender != 'm' && gender != 'f');
    printf("\nYour gender is now set to %c\n\n", userData->gender); 
    return;
}

/**
 * Takes the users weight from dialog and inputs it into the structure member weight and clearing the buffer on invalid inputs.
 * @param userData the struct in control of all the users data and modifies the data
 */
void get_weight_input(UserData* userData){
    int scanres;
    printf("Please input your weight: ");
    scanres = scanf(" %lf", &userData->weight);
    while (scanres != 1){
        char buffer;
        while (buffer != '\n'){
            scanf("%c", &buffer);
        }
        scanres = scanf(" %lf", &userData->weight);
    }
    printf("Your weight is now set to %.1lf\n\n", userData->weight); 
    return;
}

/**
 * Prints the introductory text to user settings
 */
void user_settings_text(void){
    printf("You're at the user settings page.\n");
    printf("Input the respective number to go to the relevant page.\n");
    printf(" (1) Age\n");
    printf(" (2) Weight\n");
    printf(" (3) Gender\n");
    printf(" (0) Return to the main menu\n");
    return;
}

/**
 * Saves the users data to an ini file and stores it in the directory of the executable.
 * @param userData the struct in control of all the users data
 */
void save_user_data(UserData userData){
    FILE *file;
    
    /* Opens the file with write permissions and creates it if it does not exist*/
    file = fopen("User_Data.ini", "w");
    
    fprintf(file, "Age=%i\n", userData.age);
    fprintf(file, "Weight=%lf\n", userData.weight);
    fprintf(file, "Gender=%c\n", userData.gender);
    fclose(file);
}