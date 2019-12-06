#ifndef DATA_H
#define DATA_H

typedef enum _eRECIPE_SET_TAGS{
  all,
  tomato,
  nut,
  gluten,
  soya,
  e_recipe_set_tags_size
}eRECIPE_SET_TAGS;

typedef struct UserData{
    int age;
    int foodExclusions[e_recipe_set_tags_size-1];
    double weight;
    char gender;
} UserData;

#endif