#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 32

typedef struct _KEY_VALUE_PAIR{
  char key[MAX_KEY_LEN];
  void* value;
  char value_type;
}KEY_VALUE_PAIR;

typedef struct _LIST{
  void* value;
  char value_type;
  struct _LIST* next_element;
}LIST;

typedef struct _MAP{
  LIST* key_value_pairs;
  LIST* submaps;
}MAP;

enum value_types{
  value_list,
  value_map,
  value_string,
  value_key_value_pair,
  value_undefined
};

LIST* list_create(void);
MAP* map_create(void);
void list_free(LIST* list);
void list_add(LIST** list, void* value, char value_type);
LIST* list_last(LIST* list);
void list_delete(LIST** list, LIST* element);
void map_free(MAP* map);
void map_add(MAP* map, char* key, void* value, char value_type);
void* map_value(MAP* map, char* key);
int list_size(LIST* list);
void map_add_map(MAP* map, char* key, MAP* value);
void map_add_int(MAP* map, char* key, int i);
void map_add_double(MAP* map, char* key, double d);
void free_value(void* value, char value_type);
void* list_value(LIST* list, int index);
LIST* list_element(LIST* list, int index);