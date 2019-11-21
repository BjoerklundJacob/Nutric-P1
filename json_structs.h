#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 32

typedef enum _eVALUE_TYPES{
  value_list,
  value_map,
  value_string,
  value_key_value_pair,
  value_undefined
} eVALUE_TYPES;

typedef struct _KEY_VALUE_PAIR{
  char key[MAX_KEY_LEN];
  void* value;
  eVALUE_TYPES value_type: 3;
}KEY_VALUE_PAIR;

typedef struct _LIST{
  void* value;
  eVALUE_TYPES value_type: 3;
  struct _LIST* next_element;
}LIST;

typedef struct _MAP{
  LIST* key_value_pairs;
}MAP;

LIST* list_create(void);
MAP* map_create(void);
void list_free(LIST* list);
void list_add(LIST** list, void* value, eVALUE_TYPES value_type);
LIST* list_last(LIST* list);
void list_delete(LIST** list, LIST* element);
void map_free(MAP* map);
void map_add(MAP* map, const char* key, void* value, eVALUE_TYPES value_type);
void* map_value(MAP* map, char* key);
int list_size(LIST* list);
void free_value(void* value, eVALUE_TYPES value_type);
void* list_value(LIST* list, int index);
LIST* list_element(LIST* list, int index);