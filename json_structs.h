#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 32

typedef enum _value_types_t{
  value_list,
  value_map,
  value_string,
  value_key_value_pair,
  value_double,
  value_undefined
}value_types_t;

typedef struct _key_value_pair_t{
  char key[MAX_KEY_LEN];
  void* value;
  value_types_t value_type;
}key_value_pair_t;

typedef struct _list_t{
  void* value;
  value_types_t value_type;
  struct _list_t* next_element;
}list_t;

typedef struct _map_t{
  list_t* key_value_pairs;
}map_t;

list_t* list_create(void);
void list_add(list_t** list, void* value, value_types_t value_type);
void* list_value(list_t* list, int index);
list_t* list_element(list_t* list, int index);
list_t* list_last(list_t* list);
int list_size(list_t* list);
void list_delete(list_t** list, list_t* element);
void list_free(list_t* list);
map_t* map_create(void);
void map_add(map_t* map, const char* key, void* value, value_types_t value_type);
void* map_value(map_t* map, const char* key);
void map_free(map_t* map);
void free_value(void* value, value_types_t value_type);