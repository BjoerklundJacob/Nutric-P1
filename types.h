typedef struct _RECIPE{
  char *name;
  int prep_time;
  int cook_time;

  int servings;

  int ingredients[INGREDIENT_COUNT];/*int array with all ingredients (value of 0 if ingredient is not in recipe)*/

  int instruction_count;
  char **instructions;/*instructions string array*/
}RECIPE;

typedef struct _RECIPE_SET{
  char tag;
  int bit_string[RECIPE_SET_LEN];
}RECIPE_SET;

typedef enum _eRECIPE_SET_TAGS{
  tomato,
  nut,
  gluten,
  soya,
  e_recipe_set_tags_size
}eRECIPE_SET_TAGS;