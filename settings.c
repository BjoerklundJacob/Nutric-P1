/*
User Settings
Weight
Food Exclusions
Return to main menu
If $ then eastereggl ("https://pics.me.me/looks-like-meats-back-on-the-menu-boys-when-you-37741962.png")
*/
#include <stdio.h>
#include <stdlib.h>
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
            ClearScreen();
            FoodExclusions(userData);
            
            UserSettingsText();
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
    int scanres;
    printf("Please input your current weight: ");
    scanres = scanf(" %lf", &userData->weight);
    while (scanres != 1){
        char clearBuffer;
        while (clearBuffer != '\n'){
            scanf("%c", &clearBuffer);
        }
        scanres = scanf(" %lf", &userData->weight);
    }
    printf("Your weight is now set to %.1lf\n\n", userData->weight); 
    return;
}

void FoodExclusions(UserData* userData) {
    const char* stringTags[] = {"All", "Tomato", "Nuts", "Gluten", "Soya"};
    int i, input;
    char sign;

    for (i = 0; i < e_recipe_set_tags_size-1; i++){
        userData->foodExclusions[i] = -e_recipe_set_tags_size;
    }

    printf("Type the '+' to must include or '-' to exclude the respective ingredients.\n");
    for (i = 1; i < e_recipe_set_tags_size; i++){
        printf("(%d) %s\n", i, stringTags[i]);
    }
    printf("(0) Return to the main menu\n");
    do {
        if (CheckInput(&sign, &input) == -1){
            break;
        }
        for (i = 0; i < e_recipe_set_tags_size-1; i++){
            if (userData->foodExclusions[i] == -e_recipe_set_tags_size || abs(userData->foodExclusions[i]) == input){        
                if (sign == '-'){
                    userData->foodExclusions[i] = -input;
                }else if (sign == '+'){
                    userData->foodExclusions[i] = input;
                }else{
                    break;
                }
                printf("Food Exclusion %c%s now added/updated\n", sign, stringTags[abs(userData->foodExclusions[i])]);
                break;
            }
        }

    } while (input != 0);

    for (i = 0; i < e_recipe_set_tags_size-1; i++){
        printf("Food exclusions are now %c%s\n", Signed(userData->foodExclusions[i]), stringTags[abs(userData->foodExclusions[i])]);
    }
}

void UserSettingsText(void){
    printf("You're at the User Settings page. \nType 1, 2 or 0 to get to the respective settings.\n");
    printf("(1) Weight\n");
    printf("(2) Food Exclusions\n");
    printf("(0) Return to the main menu\n");
    return;
}

char Signed(int input){
    if (input < 0){
        return '-';
    } else if (input > 0) {
        return '+';
    } else{
        return '?';
    }
}

int CheckInput(char* sign, int* input){
    int scanres;
    scanres = scanf(" %c", sign);
    if (*sign == '0'){
        return -1;
    }
    while (*sign != '-' && *sign != '+' && *sign != '\n'){
        char clearBuffer;
        printf("Unexpected input try again\n");
        while (clearBuffer != '\n'){
            scanf("%c", &clearBuffer);
        }
        scanres = scanf(" %c", sign);

    }

    scanres = scanf(" %d", input);
    while (scanres != 1 || *input >= e_recipe_set_tags_size || *input == 0){
        char clearBuffer;
        while (clearBuffer != '\n'){
            scanf("%c", &clearBuffer);
        }
        scanres = scanf(" %d", input);
    }
    return 0;
}