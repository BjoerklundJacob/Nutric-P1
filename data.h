typedef enum _eRECIPE_SET_TAGS{
  all,
  tomato,
  nut,
  gluten,
  soya,
  e_recipe_set_tags_size
}eRECIPE_SET_TAGS;

typedef struct UserData{
    double age;
    int foodExclusions[e_recipe_set_tags_size-1];
} UserData;