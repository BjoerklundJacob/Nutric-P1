
/*             case '4':
                ClearScreen();
                FoodExclusions(userData);
                UserSettingsText();
                break; */

// /**
//  * Allows the user to set and unset what ingredients must and must not be in the recipies.
//  * @param userData the struct in control of all the users data and modifies the data
//  */
// void FoodExclusions(UserData* userData) {
//     const char* stringTags[] = {"All", "Tomato", "Nuts", "Gluten", "Soya"};
//     int i, input;
//     char sign;

//     /* Gives the user directions on what is possible */
//     printf("Type the '+' to must include or '-' to exclude the respective ingredients or '*' to remove in- or exclusion.\n");
//     for (i = 1; i < e_recipe_set_tags_size; i++){
//         printf(" (%d) %s\n", i, stringTags[i]);
//     }
//     printf(" (0) Return to the User Settings\n\n");
    
//     /* Checks the users input and puts it into the foodexclusions member array using -, + and a nonvalid number*/
//     do {
//         if (CheckInput(&sign, &input) == -1){
//             break;
//         }
//         for (i = 0; i < e_recipe_set_tags_size-1; i++){
//             if (i == input-1){        
//                 if (sign == '-'){
//                     userData->foodExclusions[i] = -input;
//                 }else if (sign == '+'){
//                     userData->foodExclusions[i] = input;
//                 } else if (sign == '*'){
//                     userData->foodExclusions[i] = -e_recipe_set_tags_size;
//                     printf("Food Exclusion %s now added/updated\n", stringTags[input]);
//                     break;
//                 }else{
//                     break;
//                 }
//                 printf("Food Exclusion %c%s now added/updated\n", sign, stringTags[abs(userData->foodExclusions[i])]);
//                 break;
//             }
//         }
//     } while (input != 0);

//     /* Gives feedback to the user on what ingredients are in- and excluded */
//     printf("\nFood in- and exclusions are now\n");
//     for (i = 0; i < e_recipe_set_tags_size-1; i++){
//         if (userData->foodExclusions[i] == -e_recipe_set_tags_size){
//             printf("   %s\n", stringTags[i+1]);
//         }else{
//             printf("  %c%s\n", Signed(userData->foodExclusions[i]), stringTags[i+1]);
//         }
//     }
//     printf("\n");
// }