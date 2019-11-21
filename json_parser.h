#include <stdio.h>
#include "json_structs.h"

#define BUFFER_LEN 512

MAP* json_load(char* file_dir);
char non_white_space_char(FILE* file);
MAP* json_parse_map(FILE* file);
char json_read_key(FILE* file, char *key);
LIST* json_parse_list(FILE* file);
char file_string_read(FILE* file, char* buffer, int buffer_size, const char* stop_chars, int ignore_whitespace);
eVALUE_TYPES parse_value(FILE* file, void** value);
void print_map(MAP* map);
void print_key_value_pair(KEY_VALUE_PAIR* kv);
void print_value(void* value, eVALUE_TYPES type);
void print_list(LIST* list);