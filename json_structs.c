#include "json_structs.h"
#include <stdio.h>/* for failed allocation error messages */

/** Creates a pointer to a dynamic LIST
  * and sets the variables to NULL
  * @return pointer to dynamic LIST
  */
LIST* list_create(void){
  LIST* list = malloc(sizeof(LIST));
  printf("List create pointer = %p\n", list);
  if(list == NULL){
    printf("Could not allocate memory for list.\n");
    exit(EXIT_FAILURE);
  }
  list->value = NULL;
  list->next_element = NULL;
  return list;
}

/** Deletes an element from a list
  * @param list is a pointer to the list pointer being changes
  * @param element is the element to be deleted of type LIST*
  */
void list_delete(LIST** list, LIST* element){
  int done = 0;
  LIST *prev_element, *current_element;
  current_element = *list;
  do{
    if (current_element == element){
      /* if element to delete is first element in list */
      if (element == *list){
        if ((*list)->next_element != NULL){
          /* set first element of the list to be the next element */
          current_element = (*list)->next_element;
          (*list)->value = (*list)->next_element->value;
          (*list)->next_element = (*list)->next_element->next_element;
          /* free deleted element */
          free_value(current_element->value, current_element->value_type);
          free(current_element);
        }
        /* if deleting first and only element */
        else{
          free_value((*list)->value, (*list)->value_type);
          free(*list);
          *list = NULL;
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

void list_add(LIST** list, void* value, char value_type){
  LIST* new_element_p;
  LIST* last_element;
  if (*list == NULL){
    printf("list is null at add\n");
    *list = list_create();
    (*list)->value = value;
    (*list)->value_type = value_type;
  }
  else{
    printf("list is not null at add\n");
    last_element = list_last(*list);
    new_element_p = list_create();/* this stops program */
    new_element_p->value = value;
    new_element_p->value_type = value_type;
    last_element->next_element = new_element_p;
  }
}

void list_free(LIST** list){
  while(*list != NULL){
    list_delete(list, *list);
  }
  *list = NULL;
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

/* remember to free */
MAP* map_create(void){
  MAP* map = malloc(sizeof(MAP));
  if(map == NULL){
    printf("Could not allocate memory for map.\n");
    exit(EXIT_FAILURE);
  }
  map->key_value_pairs = NULL;
  map->submaps = NULL;
  return map;
}

/* Does not check in nested maps */
void* map_value(MAP* map, char* key){
  LIST* current_element = map->key_value_pairs;
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

void map_add_map(MAP* map, char* key, MAP* submap){
  list_add(&map->submaps, submap, 'M');
  map_add(map, key, submap, 'M');
}

void map_add_int(MAP* map, char* key, int i){
  int* i_p = malloc(sizeof(int));
  if(i_p == NULL){
    exit(EXIT_FAILURE);
  }
  *i_p = i;
  map_add(map, key, i_p, 'i');
}

void map_add_double(MAP* map, char* key, double d){
  double* d_p = malloc(sizeof(double));
  if(d_p == NULL){
    exit(EXIT_FAILURE);
  }
  *d_p = d;
  map_add(map, key, d_p, 'd');
}

void map_add(MAP* map, char* key, void* value, char value_type){
  KEY_VALUE_PAIR* key_val_p = malloc(sizeof(KEY_VALUE_PAIR));
  if(key_val_p == NULL){
    exit(EXIT_FAILURE);
  }
  strcpy(key_val_p->key, key);
  key_val_p->value = value;
  key_val_p->value_type = value_type;
  list_add(&map->key_value_pairs, key_val_p, value_type);
}

void map_free(MAP* map){
  KEY_VALUE_PAIR *key_val_p;
  /* free all submaps */
  while(map->submaps != NULL){
    printf("deleting submap.");
    map_free((MAP*) map->submaps->value);
    list_delete(&map->submaps, map->submaps);
  }
  /* free all key_value pairs */
  while(map->key_value_pairs != NULL){
    printf("deleting key value pair value.");
    /* free key-value pair value */
    if (map->key_value_pairs->value != NULL){
      printf("deleting key value pair value..");
      key_val_p = (KEY_VALUE_PAIR*) map->key_value_pairs->value;
      printf("%s = %p = %c\n", key_val_p->key, key_val_p->value, key_val_p->value_type);
      free_value(key_val_p->value, key_val_p->value_type);
      /* free key-value pair */
      free(key_val_p);
    }
    list_delete(&map->key_value_pairs, map->key_value_pairs);/* this isn't working correctly? */
  }
  free(map);
}

void free_value(void* value, char value_type){
  if (value != NULL){
    switch(value_type){
      case 'M': map_free(value); break;
      case 'L': list_free(value); break;
      default: free(value);
    }
  }
  printf("freed value");
}