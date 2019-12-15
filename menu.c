#include "menu.h"
/**
 * Goes to the relevant submenu using dialogue with the user.
*/
int main(void){
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
            clear_screen();
            open_input_file();
            break;
        case EXIT:
            clear_screen();
            printf("See you next time.\n");
            break;
        default:
            printf("The following page was not found. Please try again.\n");
            break;
        }
    } while (pageinput != EXIT);
    return EXIT_SUCCESS;
}

/**
 * Goes to the nutrient submenu
 * @param userData the struct in control of all the users data and modifies the data
 */
void nutrient_page(UserData userdata){
    printf("You're at the nutrient page.\n");
    /* Output nutrients */
    nutrient_output(userdata);
    printf("Press 0 to return to main menu.\n");
    /* Return if pressing '0' */
    while (getch() != '0');
    return;
}


/**
 * Displays the Nutric ascii art and the instructions to the users
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
    printf("(3) Open the input file\n");
    printf("(0) Exit\n");
}

/**
 * Clears the screen on both console and bash
 */
void clear_screen(void){
    system("@cls||clear");
}

/**
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

/** 
 * Opens the input file creating a template if the file doesn't exist
 */
void open_input_file(){
  FILE *file;
  map_t *map, *meal;
  list_t *meals = NULL, *ingredients = NULL;
  char *str;

  file = fopen("Input.json", "r");
  if(file == NULL){
    map = map_create();
    meal = map_create();
    /* Add name */
    str = allocate_string("Snack");
    if(str != NULL){
      map_add(meal, "name", str, value_string);
    }
    /* Add ingredients */
    str = allocate_string("50 g carrot");
    if(str != NULL){
      list_add(&ingredients, str, value_string);
    }
    str = allocate_string("75 g banana");
    if(str != NULL){
      list_add(&ingredients, str, value_string);
    }
    map_add(meal, "ingredients", ingredients, value_list);
    /* Add meal to meals list */
    list_add(&meals, meal, value_map);
    /* Add meals to json map */
    map_add(map, "meals", meals, value_list);
    /* Write to file */
    json_write("Input.json", map);
    /* Free */
    map_free(map);
  }
  system("start %windir%\\notepad.exe \"Input.json\"");
}