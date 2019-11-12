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
            SaveUserData(*userData);
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
        char buffer;
        while (buffer != '\n'){
            scanf("%c", &buffer);
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

    printf("Type the '+' to must include or '-' to exclude the respective ingredients or '*' to remove in- or exclusion.\n");
    for (i = 1; i < e_recipe_set_tags_size; i++){
        printf("(%d) %s\n", i, stringTags[i]);
    }
    printf("(0) Return to the User Settings\n\n");
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
        return ' ';
    }
}

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
        ClearChar(sign,&scanres);
        scanres = scanf(" %d", input);
    }
    return 0;
}

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

void SaveUserData(UserData UserData){
    FILE *file;
    int i;
    
    file = fopen("User Data.ini", "w");
    

    fprintf(file, "Weight=%lf\n", UserData.weight);
    for (i = 0; i < e_recipe_set_tags_size-1; i++){
        fprintf(file, "FoodExclusions[%d]=%lf\n", i, UserData.foodExclusions[i]);
    }
}

void LoadUserData(){

}