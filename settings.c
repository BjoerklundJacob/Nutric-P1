/*If $ then eastereggl ("https://pics.me.me/looks-like-meats-back-on-the-menu-boys-when-you-37741962.png")
*/
#include <stdio.h>
#include <stdlib.h>
#include "settings.h"

/**
 * Handles movement throughout the user settings whilst also giving descriptive text for the user.
 * @param userData the struct in control of all the users data and modifies the data
 */
void UserSettings(UserData* userData){
    char input = '!';
    
    UserSettingsText();

    while (input != 0){
        scanf(" %c", &input);
        switch (input){
            case '1':
                ClearScreen();
                Age(userData);
                UserSettingsText();
                break;
            case '2':
                ClearScreen();
                FoodExclusions(userData);
                UserSettingsText();
                break;
            case '0':
                SaveUserData(*userData);
                return;
            default:
                printf("The following page was not found. Please try again.\n");
                break;
        }
    } 
    return;
}

/**
 * Takes the users age from dialog and inputs it into the structure member age and clearing the buffer on invalid inputs.
 * @param userData the struct in control of all the users data and modifies the data
 */
void Age(UserData* userData){
    int scanres;
    printf("Please input your age: ");
    scanres = scanf(" %lf", &userData->age);
    while (scanres != 1){
        char buffer;
        while (buffer != '\n'){
            scanf("%c", &buffer);
        }
        scanres = scanf(" %lf", &userData->age);
    }
    printf("Your age is now set to %.1lf\n\n", userData->age); 
    return;
}

/**
 * Allows the user to set and unset what ingredients must and must not be in the recipies.
 * @param userData the struct in control of all the users data and modifies the data
 */
void FoodExclusions(UserData* userData) {
    const char* stringTags[] = {"All", "Tomato", "Nuts", "Gluten", "Soya"};
    int i, input;
    char sign;

    /* Sets the whole array to a nonvalid number */
    for (i = 0; i < e_recipe_set_tags_size-1; i++){
        userData->foodExclusions[i] = -e_recipe_set_tags_size;
    }

    /* Gives the user directions on what is possible */
    printf("Type the '+' to must include or '-' to exclude the respective ingredients or '*' to remove in- or exclusion.\n ");
    for (i = 1; i < e_recipe_set_tags_size; i++){
        printf("(%d) %s\n", i, stringTags[i]);
    }
    printf("(0) Return to the User Settings\n\n");
    
    /* Checks the users input and puts it into the foodexclusions member array using -, + and a nonvalid number*/
    do {
        if (CheckInput(&sign, &input) == -1){
            break;
        }
        for (i = 0; i < e_recipe_set_tags_size-1; i++){
            if (i == input-1){        
                if (sign == '-'){
                    userData->foodExclusions[i] = -input;
                }else if (sign == '+'){
                    userData->foodExclusions[i] = input;
                } else if (sign == '*'){
                    userData->foodExclusions[i] = -e_recipe_set_tags_size;
                    printf("Food Exclusion %s now added/updated\n", stringTags[input]);
                    break;
                }else{
                    break;
                }
                printf("Food Exclusion %c%s now added/updated\n", sign, stringTags[abs(userData->foodExclusions[i])]);
                break;
            }
        }
    } while (input != 0);

    /* Gives feedback to the user on what ingredients are in- and excluded */
    printf("\nFood in- and exclusions are now\n");
    for (i = 0; i < e_recipe_set_tags_size-1; i++){
        if (userData->foodExclusions[i] == -e_recipe_set_tags_size){
            printf("   %s\n", stringTags[i+1]);
        }else{
            printf("  %c%s\n", Signed(userData->foodExclusions[i]), stringTags[i+1]);
        }
    }
    printf("\n");
}

/**
 * Prints the introductory text to user settings
 */
void UserSettingsText(void){
    printf("You're at the User Settings page. \nType 1, 2 or 0 to get to the respective settings.\n");
    printf("(1) Age\n");
    printf("(2) Food Exclusions\n");
    printf("(0) Return to the main menu\n");
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
 * Checks the users input whilst clearing the buffer for both inputs: the sign and the number.
 * @param sign the char the user submits 
 * @param input the number the user submits 
 */
int CheckInput(char* sign, int* input){
    int scanres;
    char buffer;
    scanres = scanf(" %c", sign);
    if (*sign == '0'){
        return -1;
    }
    ClearChar(sign, &scanres);

    scanres = scanf(" %d", input);
    while (scanres != 1 || *input > e_recipe_set_tags_size-1 || *input == 0){
        printf("Unexpected number try again\n");
        while (buffer != '\n'){
            scanf("%c", &buffer);
        }
        
        scanres = scanf(" %c", sign);
        if (*sign == '0'){
        return -1;
        }
        ClearChar(sign,&scanres);
        scanres = scanf(" %d", input);
    }
    return 0;
}

/**
 * Clears the input buffer if the sign was incorrect
 * @param sign the char the user submits
 * @param scanres the result from the previous scanf
 */
void ClearChar(char* sign, int* scanres){
    char buffer;
    while (*sign != '-' && *sign != '+' && *sign != '*'){
        printf("Unexpected sign try again\n");
        while (buffer != '\n'){
            scanf("%c", &buffer);
        }
        *scanres = scanf(" %c", sign);
    }
}

/**
 * Saves the users data to an ini file and stores it in the directory of the executable.
 * @param userData the struct in control of all the users data
 */
void SaveUserData(UserData userData){
    FILE *file;
    int i;
    char sign;
    
    /* Opens the file with write permissions and creates it if it does not exist*/
    file = fopen("User Data.ini", "w");
    

    fprintf(file, "Age=%lf\n", userData.age);
    for (i = 0; i < e_recipe_set_tags_size-1; i++){
        sign = Signed(userData.foodExclusions[i]);
        if (sign == '+'){
            fprintf(file, "FoodExclusions[%d]=%c%d\n", i, sign, userData.foodExclusions[i]);
        }else{
            fprintf(file, "FoodExclusions[%d]=%d\n", i, userData.foodExclusions[i]);
        }
    }
    fclose(file);
}

