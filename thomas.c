#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
/*Defining the practice structs for the programme these will be set, read and printed*/
typedef struct _NUTRIENT{
  int nutrient_amount;
  char *nutrient_unit;
  char *nutrient_letter;
  int nutrient_number;
}NUTRIENT;
typedef struct _RECIPE{
  char *name;
  int random;
  int prep_time;
  int cook_time;
  int servings;
  int *amount;
  int length;
  char **unit;
  char **ingredients;
  NUTRIENT *nutrients;
}RECIPE;

void RecipeOutput(void);
void RecipePrint(RECIPE Recipe, char day[]);
void IngredientsPrint(RECIPE Recipe);
RECIPE RecipeMaker();
NUTRIENT NutrientMaker();
void NutrientAssigner(NUTRIENT *arr, int r);
void RecipeAssigner(RECIPE *arr);

/**
 * Primary output function for recipes
 */
void RecipeOutput(void){
  RECIPE *Recipes;
  int i;
  srand(time(NULL));
  /*Printf here is just for styling*/
  printf("////////////////////////////////////////////////////////////////////\n");
  /*We staticly initialise this array because we know the exact amount of recipes we need*/
  Recipes = calloc(8, sizeof(RECIPE)+1);
  /*We use this function to make the recipes*/
  RecipeAssigner(Recipes);
  /*Here we generate a random amount of nutrients*/
  for(i = 0; i < 7; i++){
    Recipes[i].nutrients = malloc(Recipes[i].random * sizeof(NUTRIENT));
    NutrientAssigner(Recipes[i].nutrients, Recipes[i].random);
  }
  RecipePrint(Recipes[0], "Monday");
  IngredientsPrint(Recipes[0]);
  printf("---------------------------------------------------------------------\n");
  RecipePrint(Recipes[1], "Tuesday");
  IngredientsPrint(Recipes[1]);
  printf("---------------------------------------------------------------------\n");
  RecipePrint(Recipes[2], "Wednesday");
  IngredientsPrint(Recipes[2]);
  printf("---------------------------------------------------------------------\n");
  RecipePrint(Recipes[3], "Thursday");
  IngredientsPrint(Recipes[3]);
  printf("---------------------------------------------------------------------\n");
  RecipePrint(Recipes[4], "Friday");
  IngredientsPrint(Recipes[4]);
  printf("---------------------------------------------------------------------\n");
  RecipePrint(Recipes[5], "Saturday");
  IngredientsPrint(Recipes[5]);
  printf("---------------------------------------------------------------------\n");
  RecipePrint(Recipes[6], "Sunday");
  IngredientsPrint(Recipes[6]);
  printf("////////////////////////////////////////////////////////////////////\n");
  return;
}
/*Prints the recipes and the nutrients*/
void RecipePrint(RECIPE Recipe, char day[]){
  int i;
  printf("Food for %s: %s\n", day, Recipe.name);
  printf("Prep Time: %i, ", Recipe.prep_time);
  printf("Cook Time: %i, ", Recipe.cook_time);
  printf("Serves: %i.\n", Recipe.servings);
  printf("The vitamins are: ");
  for(i = 0; i < Recipe.random; i++){
    if(i == Recipe.random - 1){
      printf("%s%i %i%s.",
      Recipe.nutrients[i].nutrient_letter, Recipe.nutrients[i].nutrient_number,
      Recipe.nutrients[i].nutrient_amount, Recipe.nutrients[i].nutrient_unit);
    }else{
      printf("%s%i %i%s, ",
      Recipe.nutrients[i].nutrient_letter, Recipe.nutrients[i].nutrient_number,
      Recipe.nutrients[i].nutrient_amount, Recipe.nutrients[i].nutrient_unit);
    }
  }
  printf("\n");
  return;
}
void IngredientsPrint(RECIPE Recipe){
  int i;
  printf("Ingredients: ");
  for(i = 0; i < Recipe.length; i++){
    printf("%s ", Recipe.ingredients[i]);
    printf("%i ", Recipe.amount[i]);
    i == Recipe.length - 1 ? printf("%s.", Recipe.unit[i]) : printf("%s, ", Recipe.unit[i]);
  }
  printf("\n");
  return;
}

RECIPE RecipeMaker(){
  int i;
  char *notMyProblem[] = {"Pasta", "Meatless meat", "Tomato", "Honey", "Sugar", "Cocain", "Crocodile Rock", "Jason", "Mushrooms", "Plantbased lifeforms", "Holy Diver", "Beetles", "The Beetles", "More things"};
  char *stillNotMyProblem[] = {"g", "kg", "mg", "tons"};
  char *names[] = {"Pizza", "Sugarlove", "Water", "Acid with steps", "Honeysicle", "Pie", "Poggers", "Crocodile steak", "More names"};
  int random;
  RECIPE r;
  r.prep_time = rand()%200;
  r.name = names[rand()%9];
  r.cook_time = rand()%200;
  r.servings = rand()%10+1;
  r.length = rand()%6+1;
  r.amount = malloc(r.length * sizeof(int));
  r.unit = malloc(r.length * 30);
  r.ingredients = malloc(r.length * 30);
  for(i = 0; i < r.length; i++){
    r.amount[i] = rand()%1000+1;
    r.unit[i] = stillNotMyProblem[rand()%4];
    r.ingredients[i] = notMyProblem[rand()%13];
  }
  random = rand()%5+1;
  r.random = random;
  return r;
}
/*Makes up fake nutrients*/
NUTRIENT NutrientMaker(){
  NUTRIENT n;
  int letter_num, rand_int, r_weight, r_unit;
  char *letters[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
  char *units[] = {"kg", "mg", "ton", "lb"};
  letter_num = rand() % 26;
  rand_int = rand() % 13 + 1;
  n.nutrient_letter = letters[letter_num];
  n.nutrient_number = rand_int;
  r_weight = rand() % 100 + 1;
  r_unit = rand() % 4;
  n.nutrient_amount = r_weight;
  n.nutrient_unit = units[r_unit];
  return n;
}

void NutrientAssigner(NUTRIENT *arr, int r){
  int i;
  for(i = 0; i < r; i++){
    arr[i] = NutrientMaker();
  }
  return;
}

void RecipeAssigner(RECIPE *arr){
  int i;
  for(i = 0; i < 7; i++){
    arr[i] = RecipeMaker();
  }
  return;
}
