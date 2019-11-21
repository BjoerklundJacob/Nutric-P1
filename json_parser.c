#include "json_parser.h"

int main(void){
  MAP *map;

  map = json_load(".\\test.json");
  printf("json loaded.\n");

  print_map(map);

  map_free(map);
  return 0;
}

/** Parses a json file loading the data to a map, returning the loaded map
  * (simplified parsing - not full json parser)
  * @param file_dir directory to the .json file
  * @return MAP* allocated
  */
MAP* json_load(char* file_dir){
  FILE *file;
  MAP *map;
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
    printf("Could not parse JSON file.\n");
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
  while(c == EOF || c == '\t' || c == '\n' || c == ' ' || c == '\r');
  return c;
}

/** Parses json from an open file to a map returning the allocated map
  * @param file - FILE* to the open file to read from
  * @return MAP* allocated
  */
MAP* json_parse_map(FILE* file){
  MAP* map = map_create();
  char key[MAX_KEY_LEN];
  char c;
  eVALUE_TYPES value_type;
  void* value;

  do{
    /* get first white space character */
    c = non_white_space_char(file);
    if(c != '\"'){
      printf("Invalid key formatting in json.\n");
      exit(EXIT_FAILURE);
    }
    /* read key*/
    c = json_read_key(file, key);
    /* read ':' */
    c = non_white_space_char(file);
    /* parse value */
    value_type = parse_value(file, &value);
    /* add to map */
    map_add(map, key, value, value_type);

    /* check if end of map or more elements*/
    c = non_white_space_char(file);
  }
  while(c == ',');
  if(c != '}'){
    printf("Missing '}' at the end of map.\n");
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
  * @return LIST* to the first element in allocated linked list
  */
LIST* json_parse_list(FILE* file){
  LIST* list = NULL;
  char c;
  eVALUE_TYPES value_type;
  void* value;

  do{
    /* parse value */
    value_type = parse_value(file, &value);
    /* add to list */
    list_add(&list, value, value_type);

    /* check if end of map or more elements*/
    c = non_white_space_char(file);
  }
  while(c == ',');
  if(c != ']'){
    printf("Missing ']' at the end of list.\n");
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
    
    if(ignore_whitespace && (c == EOF || c == '\t' || c == '\n' || c == ' ' || c == '\r')){
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
  * @return eVALUE_TYPES type of value
  */
eVALUE_TYPES parse_value(FILE* file, void** value){
  char c, buffer[BUFFER_LEN];
  eVALUE_TYPES value_type;
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
        printf("Could not parse value string.\n");
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
    /* value not being parsed by simplified json parser or invalid input */
    default:
      printf("Unexpected value format in json. <%c>\n", c);
      exit(EXIT_FAILURE);
  }

  return value_type;
}

/** Prints a map
  * @param map to be printed
  */
void print_map(MAP* map){
  int i;
  printf("{\n");
  for(i = 0; i < list_size(map->key_value_pairs); ++i){
    print_key_value_pair(list_value(map->key_value_pairs, i));
    if (i < list_size(map->key_value_pairs)-1){
      printf(", ");
    }
  }
  printf("\n}");
}

/** Prints a key-value pair
  * @param kv - key-value pair to print
  */
void print_key_value_pair(KEY_VALUE_PAIR* kv){
  printf("\"%s\": ", kv->key);
  print_value(kv->value, kv->value_type);
}

/** Prints a value
  * @param value - void* value to print
  * @param type - eVALUE_TYPES type of value to print
  */
void print_value(void* value, eVALUE_TYPES type){
  if (value != NULL){
    switch(type){
      case value_list: print_list(value); break;
      case value_map: print_map(value); break;
      default: printf("\"%s\"", value);
    }
  }
  else{
    printf("(null)");
  }
}

/** Prints a list
  * @param list - list to be printed
  */
void print_list(LIST* list){
  int i;
  LIST* element;
  printf("[\n");
  for(i = 0; i < list_size(list); ++i){
    element = list_element(list, i);
    print_value(element->value, element->value_type);
    if (i < list_size(list)-1){
      printf(", ");
    }
  }
  printf("\n]");
}