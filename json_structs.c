#include "json_structs.h"
#include <stdio.h>/* for failed allocation error messages */

/** Creates a pointer to a dynamic LIST
  * and sets the variables to NULL
  * @return pointer to dynamic LIST
  */
LIST* list_create(void){
  /* allocate memory for LIST */
  LIST* list = malloc(sizeof(LIST));
  /* if allocation fail */
  if(list == NULL){
    printf("Could not allocate memory for list.\n");
    exit(EXIT_FAILURE);
  }
  /* set values to default */
  list->value = NULL;
  list->value_type = value_undefined;
  list->next_element = NULL;

  return list;
}

/** Finds and returns the last element in a linked list
  * @param list - LIST* to a element in a linked list
  * @return last element in linked list
  */
LIST* list_last(LIST* list){
  LIST* current_element = list;
  /* find next element while next element exists */
  while (current_element->next_element != NULL){
    current_element = current_element->next_element;
  }
  return current_element;
}

/** Adds an element at the end of the linked list, if linked list is empty
  * an element will be created.
  * @param list - Pointer to the LIST* that should be added to
  * @param value - void* to the value of value_type
  * @param value_type - eVALUE_TYPES value to specify what type value is 
  */
void list_add(LIST** list, void* value, eVALUE_TYPES value_type){
  LIST* new_element_p;
  LIST* last_element;
  /* if linked list is empty, create the first element */
  if (*list == NULL){
    *list = list_create();
    (*list)->value = value;
    (*list)->value_type = value_type;
  }
  /* else set link new element from last element */
  else{
    last_element = list_last(*list);
    new_element_p = list_create();
    new_element_p->value = value;
    new_element_p->value_type = value_type;
    last_element->next_element = new_element_p;
  }
}

/** Returns the amount of elements in a linked list
  * @param list - the linked list to find size of
  * @return size of list
  */
int list_size(LIST* list){
  int size = 0;
  LIST* current_element = list;
  while(current_element != NULL){
    size++;
    current_element = current_element->next_element;
  }
  return size;
}

/** Returns the value of a linked list at index
  * @param list - linked list
  * @param index - 0 <= index < list_size
  * @return void* value
  */
void* list_value(LIST* list, int index){
  LIST* element = list_element(list, index);
  return element->value;
}

/** Returns the element of a list at index
  * @param list - linked list
  * @param index - 0 <= index < list_size
  * @return LIST* to element at index
  */
LIST* list_element(LIST* list, int index){
  LIST* element = list;
  int i;
  for(i = 0; i < index; ++i){
    element = element->next_element;
  }
  return element;
}

/** Creates a map and sets values to default
  * @return malloced MAP*
  */
MAP* map_create(void){
  MAP* map = malloc(sizeof(MAP));
  if(map == NULL){
    printf("Could not allocate memory for map.\n");
    exit(EXIT_FAILURE);
  }
  map->key_value_pairs = NULL;
  return map;
}

/** Returns the value associated with the key in the map
  * @param map - MAP*
  * @param key - string key
  * @return void* value from the associated key (NULL if key is not in map)
  */
void* map_value(MAP* map, char* key){
  LIST* current_element = map->key_value_pairs;
  KEY_VALUE_PAIR* key_val;
  /* loop through key-value pair list and search for the key */
  while(current_element != NULL && current_element->value != NULL){
    key_val = (KEY_VALUE_PAIR*)current_element->value;
    /* check if key to search for equals the key of current key-value pair */
    if (strcmp(key_val->key, key) == 0){
      return key_val->value;
    }
    /* iterate to next element in key-value pair list */
    current_element = current_element->next_element;
  }
  return NULL;
}

/** Adds a key-value pair to the map
  * @param map - MAP*
  * @param key - string key
  * @param value - void*
  * @param value_type - eVALUE_TYPES to specify type of value
  */
void map_add(MAP* map, const char* key, void* value, eVALUE_TYPES value_type){
  /* allocate memory for KEY_VALUE_PAIR, exit if fail */
  KEY_VALUE_PAIR* key_val_p = malloc(sizeof(KEY_VALUE_PAIR));
  if(key_val_p == NULL){
    exit(EXIT_FAILURE);
  }
  /* copy key to add to the key-value pairs key and store value+type*/
  strcpy(key_val_p->key, key);
  key_val_p->value = value;
  key_val_p->value_type = value_type;
  /* add new key-value pair to key-value pair list in map */
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
    /* if not deleting first element, start from second element */
    prev_element = *list;
    current_element = (*list)->next_element;
    do{
      /* if current element is the element to be deleted */
      if (current_element == element){        
        /* set previous element's next element to the next element */
        prev_element->next_element = element->next_element;
        /* free deleted element */
        free_value(element->value, element->value_type);
        free(element);
        done = 1;
      }
      /* if current element is not element to be deleted, proceed to next element */
      else{
        prev_element = current_element;
        current_element = current_element->next_element;
        /* if reached end, stop */
        if (current_element == NULL){
          done = 1;
        }
      }
    }
    while(!done);
  }
}

/** Frees all memory allocated for a list and any nested data
  * @param list - linked list to free
  */
void list_free(LIST* list){
  while(list != NULL){
    list_delete(&list, list);
  }
}

/** Frees all memory allocated for a map and any nested data
  * @param map - map to free
  */
void map_free(MAP* map){
  /* free all key_value pairs */
  list_free(map->key_value_pairs);
  free(map);
}

/** Frees memory allocated for a value with a specified type
  * @param value - void*
  * @param value_type - eVALUE_TYPES type of value to free
  */
void free_value(void* value, eVALUE_TYPES value_type){
  if (value != NULL){
    /* free value based on its type */
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
}