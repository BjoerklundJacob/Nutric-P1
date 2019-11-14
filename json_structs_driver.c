#include <stdio.h>
#include <stdlib.h>
#include "json_structs.h"


void print_map_keys(MAP* map);

int main(void){
  MAP* map = map_create();
  MAP* submap = map_create();

  map_add(map, "greeting", "Hej");
  map_add(map, "navn", "Simon");

  map_add(submap, "submap key", "omg it woks!");
  map_add_map(map, "submap", submap);
  printf("%s %s!\n", (char*) map_value(map, "greeting"), (char*) map_value(map, "navn"));

  printf("%s\n", (char*) map_value(map_value(map, "submap"), "submap key"));

  map_add_int(map, "number", 123);
  printf("Decimal: %d\n", *(int*) map_value(map, "number"));

  map_add_double(map, "number2", 4.321);
  printf("Double: %lf\n", *(double*) map_value(map, "number2"));

  print_map_keys(map);
  print_map_keys(submap);

  map_free(map);
  
  return 0;
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