#ifndef JSON_PARSER
#define JSON_PARSER

#include "json_structs.h"
#include <stdio.h>

#define BUFFER_LEN 512

map_t* json_load(char* file_dir);
char non_white_space_char(FILE* file);
map_t* json_parse_map(FILE* file);
char json_read_key(FILE* file, char *key);
list_t* json_parse_list(FILE* file);
char file_string_read(FILE* file, char* buffer, int buffer_size, const char* stop_chars, int ignore_whitespace);
value_types_t json_parse_value(FILE* file, void** value);
void json_write(const char* file_dir, map_t* map);
void fprint_map(FILE* file, map_t* map, int depth);
void fprint_key_value_pair(FILE* file, key_value_pair_t* kv, int depth);
void fprint_value(FILE* file, void* value, value_types_t type, int depth);
void fprint_list(FILE* file, list_t* list, int depth);
void findent(FILE* file, int depth);
#endif