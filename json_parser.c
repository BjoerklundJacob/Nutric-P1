#include "json_parser.h"
/*int main(void){
  map_t *map;

  map = json_load(".\\test.json");
  printf("json loaded.\n");

  json_write(".\\test.json", map);

  map_free(map);
  return 0;
*/
/** Parses a json file loading the data to a map, returning the loaded map
  * (simplified parsing - not full json parser)
  * @param file_dir directory to the .json file
  * @return map_t* allocated
*/
map_t* json_load(char* file_dir){
  FILE *file;
  map_t *map;
  char c;

  file = fopen(file_dir, "r");
  if(file == NULL){
    printf("Necessary file could not be opened.\n");
    exit(EXIT_FAILURE);
  }

  /*** Parse json ***/
  /* clear whitespace until c is a non-whitespace char */
  c = non_white_space_char(file);
  
  /* if first char is not a '{' the json is formatted wrong */
  if (c != '{'){
    printf("Could not parse JSON file. Missing initial <{>\n");
    exit(EXIT_FAILURE);
  }

  /* load the map */
  map = json_parse_map(file);

  fclose(file);

  return map;
}


/** scans a char until a non white space char is read returning the last char read
  * @param file - FILE* to the open file to read from
  * @return first non-whitespace char being read
  */
char non_white_space_char(FILE* file){
  char c;
  do{c = fgetc(file);}
  while(c != EOF && (c == '\t' || c == '\n' || c == ' ' || c == '\r'));
  return c;
}

/** Parses json from an open file to a map returning the allocated map
  * @param file - FILE* to the open file to read from
  * @return map_t* allocated
  */
map_t* json_parse_map(FILE* file){
  map_t* map = map_create();
  char key[MAX_KEY_LEN];
  char c;
  value_types_t value_type;
  void* value;

  do{
    /* get first white space character */
    c = non_white_space_char(file);
    if(c != '\"'){
      printf("Invalid key formatting in json. The keys should be wrapped in <\">\n");
      exit(EXIT_FAILURE);
    }
    /* read key*/
    c = json_read_key(file, key);
    /* read ':' */
    c = non_white_space_char(file);
    /* parse value */
    value_type = json_parse_value(file, &value);
    /* add to map */
    map_add(map, key, value, value_type);

    /* check if end of map or more elements*/
    c = non_white_space_char(file);
  }
  while(c == ',');
  if(c != '}'){
    printf("Missing <}> at the end of map.\n");
    exit(EXIT_FAILURE);
  }

  return map;
}

/** Parses a key from an open file storing it in key and returning the char last read
  * @param file - FILE* to the open file to read from
  * @param key - char array to store key in
  * @return last char read
  */
char json_read_key(FILE* file, char *key){
  char c;
  char buffer[MAX_KEY_LEN];
  c = file_string_read(file, buffer, MAX_KEY_LEN, "\"}", 0);
  buffer[strlen(buffer)] = 0;
  strcpy(key, &buffer[0]);
  return c;
}

/** Parses json from an open file to a list returning the allocated list
  * @param file - FILE* to the open file to read from
  * @return list_t* to the first element in allocated linked list
  */
list_t* json_parse_list(FILE* file){
  list_t* list = NULL;
  char c;
  value_types_t value_type;
  void* value;

  do{
    /* parse value */
    value_type = json_parse_value(file, &value);
    /* add to list */
    list_add(&list, value, value_type);

    /* check if end of map or more elements*/
    c = non_white_space_char(file);
  }
  while(c == ',');
  if(c != ']'){
    printf("Missing <]> at the end of list.\n");
    exit(EXIT_FAILURE);
  }

  return list;
}

/** Reads a string from a file until a character from the break string is read
  * or end of buffer size returning the position in the buffer of the last read char
  * @param file - FILE* of open file to read from
  * @param buffer - char array to read to of size buffer_size
  * @param buffer_size - size of buffer
  * @param stop_chars - characters that should stop the reading
  * @param ignore_whitespace - boolean if whitespace should be stored in buffer or not
  * @return last char read
  */
char file_string_read(FILE* file, char* buffer, int buffer_size, const char* stop_chars, int ignore_whitespace){
  int i, j;
  char c;
  for(i = 0; i < buffer_size-1; ++i){
    c = fgetc(file);
    if (c == EOF){
      break;
    }
    if(ignore_whitespace && (c == '\t' || c == '\n' || c == ' ' || c == '\r')){
      --i;/* don't proceed in buffer */
    }
    else{
      /* check if last read is a char from the stop_chars */
      j = 0;
      while(stop_chars[j] != 0){
        if(stop_chars[j] == c){
          break;
        }
        ++j;
      }
      /* exit loop if a stop char has been read */
      if (stop_chars[j] == c){
        break;
      }
      else{
        buffer[i] = c;
      }
    }
  }
  /* end string (char array to string) */
  buffer[i] = 0;
  
  return c;
}

/** Parses value from open file storing it in output parameter and returning its type
  * @param file - FILE* of open file to read from
  * @param value - adress to store value in
  * @return value_types_t type of value
  */
value_types_t json_parse_value(FILE* file, void** value){
  char c, buffer[BUFFER_LEN];
  value_types_t value_type;
  /* read first char of value */
  c = non_white_space_char(file);
  switch(c){
    /* value is a map */
    case '{':
      *value = (void*) json_parse_map(file);
      value_type = value_map;
      break;
    /* value is a list */
    case '[':
      *value = (void*) json_parse_list(file);
      value_type = value_list;
      break;
    /* value is a string */
    case '\"':
      c = file_string_read(file, buffer, BUFFER_LEN, "\"", 0);
      if (c != '\"'){
        printf("Missing <\">. Could not parse value string.\n");
        exit(EXIT_FAILURE);
      }
      *value = malloc(strlen(buffer)+1);
      if (*value == NULL){
        printf("Could not allocate memory.\n");
        exit(EXIT_FAILURE);
      }
      strcpy(*value, buffer);
      value_type = value_string;
      break;
      /* value is a double */
    case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '0':
      ungetc(c, file);
      c = file_string_read(file, buffer, BUFFER_LEN, " ,", 0);
      if (c == ','){
        /* put c back since will be read by call to determine if there are more elements */
        ungetc(',', file);
      }
      *value = malloc(sizeof(double));
      if (*value == NULL){
        printf("Could not allocate memory.\n");
        exit(EXIT_FAILURE);
      }
      sscanf(buffer, "%lf", (double*) *value);
      value_type = value_double;
      break;
    /* value not being parsed by simplified json parser or invalid input */
    default:
      if(c == ']'){
        printf("Error: Excess comma after last value in list\n", c);
      }
      else if(c == '}'){
        printf("Error: Excess comma after last value in map\n", c);
      }
      else{
        printf("Unexpected value format in json. <%c>\n", c);
      }
      exit(EXIT_FAILURE);
  }

  return value_type;
}

/** Writes json to a .json file from a map
  * @param file_dir - directory of file to write to
  * @param map - map to parse to json
  */
void json_write(const char* file_dir, map_t* map){
  FILE* file = fopen(file_dir, "w");
  if (file == NULL){
    printf("Could not open file to write.\n");
    exit(EXIT_FAILURE);
  }
  fprint_map(file, map, 0);
  fclose(file);
}

/** Prints a map to a file
  * @param file - FILE* to open file to write to
  * @param map - to be printed
  * @param depth - depth of the nested data
  */
void fprint_map(FILE* file, map_t* map, int depth){
  int i;
  fprintf(file, "{\n");
  for(i = 0; i < list_size(map->key_value_pairs); ++i){
    findent(file, depth+1);
    fprint_key_value_pair(file, list_value(map->key_value_pairs, i), depth+1);
    if (i < list_size(map->key_value_pairs)-1){
      fprintf(file, ",\n");
    }
  }
  fprintf(file, "\n");
  findent(file, depth);
  fprintf(file, "}");
}

/** Prints a key-value pair to a file
  * @param file - FILE* to open file to write to
  * @param kv - key-value pair to print
  * @param depth - depth of the nested data
  */
void fprint_key_value_pair(FILE* file, key_value_pair_t* kv, int depth){
  fprintf(file, "\"%s\": ", kv->key);
  fprint_value(file, kv->value, kv->value_type, depth);
}

/** Prints a value to a file
  * @param file - FILE* to open file to write to
  * @param value - void* value to print
  * @param type - value_types_t type of value to print
  * @param depth - depth of the nested data
  */
void fprint_value(FILE* file, void* value, value_types_t type, int depth){
  if (value != NULL){
    switch(type){
      case value_list: fprint_list(file, value, depth); break;
      case value_map: fprint_map(file, value, depth); break;
      case value_double: fprintf(file, "%lf", *(double*) value); break;
      default: fprintf(file, "\"%s\"", value);
    }
  }
  else{
    fprintf(file, "(null)");
  }
}

/** Prints a list to a file
  * @param file - FILE* to open file to write to
  * @param list - list to be printed
  * @param depth - depth of the nested data
  */
void fprint_list(FILE* file, list_t* list, int depth){
  int i;
  list_t* element;
  fprintf(file, "[\n");
  for(i = 0; i < list_size(list); ++i){
    findent(file, depth+1);
    element = list_element(list, i);
    fprint_value(file, element->value, element->value_type, depth+1);
    if (i < list_size(list)-1){
      fprintf(file, ",\n");
    }
  }
  fprintf(file, "\n");
  findent(file, depth);
  fprintf(file, "]");
}

/** Writes 2 spaces per depth to a file
  * @param file - FILE* to open file to write to
  * @param depth - depth of the nested data
  */
void findent(FILE* file, int depth){
  int i;
  for(i = 0; i < depth; ++i){
    fprintf(file, "  ");
  }
}