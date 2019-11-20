#include "json_structs.h"
#include <stdio.h>/* for failed allocation error messages */

/** Creates a pointer to a dynamic LIST
  * and sets the variables to NULL
  * @return pointer to dynamic LIST
  */
LIST* list_create(void){
  LIST* list = malloc(sizeof(LIST));
  if(list == NULL){
    printf("Could not allocate memory for list.\n");
    exit(EXIT_FAILURE);
  }
  list->value = NULL;
  list->value_type = value_undefined;
  list->next_element = NULL;
  return list;
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
    *list = list_create();
    (*list)->value = value;
    (*list)->value_type = value_type;
  }
  else{
    last_element = list_last(*list);
    new_element_p = list_create();
    new_element_p->value = value;
    new_element_p->value_type = value_type;
    last_element->next_element = new_element_p;
  }
}

int list_size(LIST* list){
  int size = 0;
  LIST* current_element = list;
  while(current_element != NULL){
    size++;
    current_element = current_element->next_element;
  }
  return size;
}

/* This function returns the value of a list
 * pre: 0 <= index < list_size
 */
void* list_value(LIST* list, int index){
  LIST* element = list_element(list, index);
  return element->value;
}

/* This function returns the element of a list
 * pre: 0 <= index < list_size
 */
LIST* list_element(LIST* list, int index){
  LIST* element = list;
  int i;
  for(i = 0; i < index; ++i){
    element = element->next_element;
  }
  return element;
}

/* remember to free */
MAP* map_create(void){
  MAP* map = malloc(sizeof(MAP));
  if(map == NULL){
    printf("Could not allocate memory for map.\n");
    exit(EXIT_FAILURE);
  }
  map->key_value_pairs = NULL;
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

void map_add(MAP* map, char* key, void* value, char value_type){
  KEY_VALUE_PAIR* key_val_p = malloc(sizeof(KEY_VALUE_PAIR));
  if(key_val_p == NULL){
    exit(EXIT_FAILURE);
  }
  strcpy(key_val_p->key, key);
  key_val_p->value = value;
  key_val_p->value_type = value_type;
  list_add(&map->key_value_pairs, key_val_p, value_key_value_pair);
}

/** Deletes an element from a list
  * @param list is a pointer to the list pointer being changes
  * @param element is the element to be deleted of type LIST*
  */
void list_delete(LIST** list, LIST* element){
  int done = 0;
  LIST *prev_element, *current_element;
  /* if list or element is null - do nothing */
  if (*list == NULL || element == NULL){
    return;
  }
  /* if deleting first element of list */
  if (element == *list){
    *list = (*list)->next_element;
    free_value(element->value, element->value_type);
    free(element);
  }
  else{
    current_element = (*list)->next_element;
    do{
      if (current_element == element){        
        /* set previous element's next element to the next element */
        prev_element->next_element = element->next_element;
        /* free deleted element */
        free_value(element->value, element->value_type);
        free(element);
        done = 1;
      }
      else{
        prev_element = current_element;
        current_element = current_element->next_element;
        if (current_element == NULL){
          done = 1;
        }
      }
    }
    while(!done);
  }
}

void list_free(LIST* list){
  printf("-[");
  while(list != NULL){
    list_delete(&list, list);
  }
  printf("-]");
}

void map_free(MAP* map){
  /* free all key_value pairs */
  printf("-{");
  list_free(map->key_value_pairs);
  free(map);
  printf("-}");
}

void free_value(void* value, char value_type){
  printf("-\n<");
  if (value != NULL){
    switch(value_type){
      case value_list: list_free(value); break;
      case value_map: map_free(value); break;
      case value_key_value_pair: 
        free_value(((KEY_VALUE_PAIR*)value)->value, ((KEY_VALUE_PAIR*)value)->value_type);
        /* free key-value pair */
        free(value);
        break;
      default: free(value);
    }
  }
  printf("->\n");
}