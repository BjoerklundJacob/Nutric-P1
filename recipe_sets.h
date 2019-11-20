/***** PREPROCESSOR CONSTANTS *****/
#define RECIPE_COUNT 29
#define INGREDIENT_COUNT 10
/* RECIPE_SET_LEN is equal to the amount of int's needed to have a bitflag for each recipe */
#define RECIPE_SET_LEN (int) ( ((double) RECIPE_COUNT * 2.0 - 1.0) / (double) (sizeof(int)*8*2)+1 )
#define LEN(x) (sizeof(x)/sizeof(x[0]))


/***** STRUCTS *****/
typedef struct _RECIPE{
  char *name;
  int prep_time;
  int cook_time;

  int servings;

  int ingredients[INGREDIENT_COUNT];/*int array with all ingredients (value of 0 if ingredient is not in recipe)*/

  int instruction_count;
  char *instructions[10];/*instructions string array*/
}RECIPE;

typedef struct _RECIPE_SET{
  char tag;
  int bit_string[RECIPE_SET_LEN];
}RECIPE_SET;

typedef enum _eRECIPE_SET_TAGS{
  all,
  tomato,
  nut,
  gluten,
  soya,
  e_recipe_set_tags_size
}eRECIPE_SET_TAGS;

/***** PROTOTYPES *****/
void find_recipes(RECIPE_SET* recipe_set, RECIPE_SET *recipe_sets, eRECIPE_SET_TAGS *tags, int tag_count);
void recipe_junction(RECIPE_SET* recipe1, RECIPE_SET recipe2);
void print_recipe_set(RECIPE_SET recipe_set);
RECIPE_SET recipe_set_bit_flip(RECIPE_SET* recipe_set);
int recipe_count(RECIPE_SET recipe_set);