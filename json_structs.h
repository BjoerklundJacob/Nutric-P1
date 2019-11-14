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
void map_add_int(MAP* map, char* key, int i);
void map_add_double(MAP* map, char* key, double d);