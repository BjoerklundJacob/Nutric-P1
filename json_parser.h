#include <stdio.h>
#ifndef JSON_STRUCTS_H
#define JSON_STRUCTS_H "json_structs.h"
#include JSON_STRUCTS_H
#endif

#define BUFFER_LEN 512

MAP* json_load(char* file_dir);
char non_white_space_char(FILE* file);
MAP* json_parse_map(FILE* file);
char json_read_key(FILE* file, char *key);
LIST* json_parse_list(FILE* file);
char file_string_read(FILE* file, char* buffer, int buffer_size, const char* stop_chars, int ignore_whitespace);
eVALUE_TYPES parse_value(FILE* file, void** value);
void json_write(const char* file_dir, MAP* map);
void fprint_map(FILE* file, MAP* map, int depth);
void fprint_key_value_pair(FILE* file, KEY_VALUE_PAIR* kv, int depth);
void fprint_value(FILE* file, void* value, eVALUE_TYPES type, int depth);
void fprint_list(FILE* file, LIST* list, int depth);
void findent(FILE* file, int depth);