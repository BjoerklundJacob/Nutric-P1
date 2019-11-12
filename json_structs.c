#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _KEY_VALUE_PAIR{
  char* key;
  void* value;
}KEY_VALUE_PAIR;

typedef struct _LIST{
  void* value;
  struct _LIST* next_element;
}LIST;

typedef struct _MAP{
  LIST key_value_pairs;
  LIST submaps;
}MAP;

MAP* map_create(void);
void list_free(LIST* list);
void list_add(LIST* list, void* value);
LIST* list_last(LIST* list);
void list_delete(LIST* list, LIST* element);
void map_free(MAP* map);
void map_add(MAP* map, char* key, void* value);
void* map_value(MAP* map, char* key);
int list_size(LIST list);
void map_add_map(MAP* map, char* key, MAP* value);

void print_map_keys(MAP* map);


int main(void){
  MAP* map = map_create();
  MAP* submap = map_create();
  int number = 100;

  map_add(map, "greeting", "Hej");
  map_add(map, "navn", "Simon");

  map_add(submap, "submap key", "omg it woks!");
  map_add_map(map, "submap", submap);
  printf("%s %s!\n", (char*) map_value(map, "greeting"), (char*) map_value(map, "navn"));

  printf("%s\n", (char*) map_value(map_value(map, "submap"), "submap key"));

  print_map_keys(map);
  print_map_keys(submap);

  map_free(map);
  
  return 0;
}


void map_add(MAP* map, char* key, void* value){
  KEY_VALUE_PAIR* key_val_p = malloc(sizeof(KEY_VALUE_PAIR));
  key_val_p->key = key;
  key_val_p->value = value;
  list_add(&map->key_value_pairs, key_val_p);
}

void map_free(MAP* map){
  /* free all submaps */
  while(map->submaps.value != NULL){
    map_free((MAP*) map->submaps.value);
    list_delete(&map->submaps, &map->submaps);
  }
  /* free all key_value pairs */
  while(map->key_value_pairs.value != NULL){
    free(map->key_value_pairs.value);
    list_delete(&map->key_value_pairs, &map->key_value_pairs);
  }
}

/* Does not delete any nested lists */
/* First element is static, rest are dynamic */
void list_delete(LIST* list, LIST* element){
  int done = 0;
  LIST *prev_element, *current_element;
  current_element = list;
  prev_element = list;/* removes warning of "unused" */
  do{
    if (current_element == element){
      /* if element to delete is first element in list */
      if (element == list){
        /* set first element of the list to be the next element */
        if (element->next_element != NULL){
          current_element = element->next_element;
          list->value = element->next_element->value;
          list->next_element = element->next_element->next_element;
          /* free deleted element */
          free(current_element);
        }
        /* if trying to delete first and only element */
        else{
          list->value = NULL;
          list->next_element = NULL;
        }
      }
      else{
        /* set previous element's next element to the next element */
        prev_element->next_element = element->next_element;
        /* free deleted element */
        free(element);
      }
      done = 1;
    }
    if (!done){
      prev_element = current_element;
      if (current_element->next_element != NULL){
        current_element = current_element->next_element;
      }
      else{
        done = 1;
      }
    }
  }
  while(!done);
}

LIST* list_last(LIST* list){
  LIST* current_element = list;
  while (current_element->next_element != NULL){
    current_element = current_element->next_element;
  }
  return current_element;
}

void list_add(LIST* list, void* value){
  LIST* new_element_p;
  LIST* last_element;
  if (new_element_p == NULL){
    exit(EXIT_FAILURE);
  }
  last_element = list_last(list);
  if (last_element == list && list->value == NULL){
    list->value = value;
  }
  else{
    new_element_p = malloc(sizeof(LIST));
    new_element_p->value = value;
    new_element_p->next_element = NULL;
    last_element->next_element = new_element_p;
  }
}

void list_free(LIST* list){
  while(list->next_element != NULL){
    list_delete(list, list->next_element);
  }
}

/* remember to free */
MAP* map_create(void){
  MAP* map = malloc(sizeof(MAP));
  map->key_value_pairs.value = NULL;
  map->key_value_pairs.next_element = NULL;
  map->submaps.value = NULL;
  map->submaps.next_element = NULL;
  return map;
}

/* Does not check in nested maps */
void* map_value(MAP* map, char* key){
  LIST* current_element = &map->key_value_pairs;
  KEY_VALUE_PAIR* key_val;
  while(current_element != NULL && current_element->value != NULL){
    key_val = (KEY_VALUE_PAIR*)current_element->value;
    if (strcmp(key_val->key, key) == 0){
      return key_val->value;
    }
    current_element = current_element->next_element;
  }
  return NULL;
}

void print_map_keys(MAP* map){
  LIST* current_element = &map->key_value_pairs;
  KEY_VALUE_PAIR* key_val;
  printf("Keys:\n");
  while(current_element != NULL && current_element->value != NULL){
    key_val = (KEY_VALUE_PAIR*)current_element->value;
    printf("  %s\n", key_val->key);
    current_element = current_element->next_element;
  }
}

int list_size(LIST list){
  int size = 0;
  LIST* current_element = &list;
  while(current_element != NULL && current_element->value != NULL){
    size++;
    current_element = current_element->next_element;
  }
  return size;
}

void map_add_map(MAP* map, char* key, MAP* submap){
  list_add(&map->submaps, submap);
  map_add(map, key, submap);
}