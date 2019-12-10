#include "settings.h"
/**
 * Handles movement throughout the user settings whilst also giving descriptive text for the user.
 * @param userData the struct in control of all the users data and modifies the data
*/
void UserSettings(UserData* userData){
    char input = '!';
    
    UserSettingsText();

    while (input != 0){
        input = getch();
        switch (input){
            case '1':
                ClearScreen();
                Age(userData);
                UserSettingsText();
                break;
            case '2':
                ClearScreen();
                Weight(userData);
                UserSettingsText();
                break;
            case '3':
                ClearScreen();
                Gender(userData);
                UserSettingsText();
                break;
            case '0':
                SaveUserData(*userData);
                ClearScreen();
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
void Age(UserData* userData){
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
void Gender(UserData* userData){
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
void Weight(UserData* userData){
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
void UserSettingsText(void){
    printf("You're at the user settings page.\n");
    printf("Input the respective number to go to the relevant page.\n");
    printf(" (1) Age\n");
    printf(" (2) Weight\n");
    printf(" (3) Gender\n");
    printf(" (0) Return to the main menu\n");
    return;
}

/**
 * Checks if the input of the user is positive or negative.
 * @param input The users input
 */
char Signed(int input){
    if (input < 0){
        return '-';
    } else if (input > 0) {
        return '+';
    } else{
        return ' ';
    }
}

/**
 * Saves the users data to an ini file and stores it in the directory of the executable.
 * @param userData the struct in control of all the users data
 */
void SaveUserData(UserData userData){
    FILE *file;
    
    /* Opens the file with write permissions and creates it if it does not exist*/
    file = fopen("User Data.ini", "w");

    fprintf(file, "Age=%i\n", userData.age);
    fprintf(file, "Weight=%lf\n", userData.weight);
    fprintf(file, "Gender=%c\n", userData.gender);
    fclose(file);
}