#include <stdio.h>
#include "json_structs.h"

#define MAX_KEY_LEN 32
#define BUFFER_LEN 512

char file_string_read(FILE* file, char *buffer, int buffer_size, char* stop_chars, int ignore_whitespace);
MAP* json_load(char* file_dir);
char json_read_key(FILE* file, char *key);
char non_white_space_char(FILE* file);
MAP* json_parse_map(FILE* file);
LIST* json_parse_list(FILE* file);

int main(void){
  MAP *map = json_load(".\\test.json");

  map_free(map);
  printf("success?");
  return 0;
}

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


/* scans a char until a non white space char is read returning the last char read */
char non_white_space_char(FILE* file){
  char c;
  do{c = fgetc(file);}
  while(c == EOF || c == '\t' || c == '\n' || c == ' ' || c == '\r');
  return c;
}

MAP* json_parse_map(FILE* file){
  MAP* map = map_create();
  char key[MAX_KEY_LEN];
  char c, value_type;
  char buffer[BUFFER_LEN];
  void* value;
  
  printf("started parsing map\n");

  do{
    c = non_white_space_char(file);
    if (c == ','){
      c = non_white_space_char(file);
    }
    if(c == '\"'){
      /* read key*/
      c = json_read_key(file, key);
      /* read ':' */
      c = non_white_space_char(file);
      /* read first char of value */
      c = non_white_space_char(file);

      /* parse value */
      switch(c){
        case '{':
          value = (void*) json_parse_map(file);
          value_type = 'M';
          break;
        case '[':
          value = (void*) json_parse_list(file);
          value_type = 'L';
          break;
        case ',':case '}':
          value = NULL;
          value_type = 0;
          break;
        case '\"':
          c = file_string_read(file, buffer, BUFFER_LEN, "\"", 0);
          if (c != '\"'){
            printf("Could not parse value string.\n");
            exit(EXIT_FAILURE);
          }
          value = malloc(strlen(buffer));
          if (value == NULL){
            printf("Could not allocate memory.\n");
            exit(EXIT_FAILURE);
          }
          strcpy(value, buffer);
          value_type = 'S';
          break;
        case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
          break;
        default:
          printf("Could not parse JSON file. default %c\n", c);
          exit(EXIT_FAILURE);
      }
      map_add(map, key, value, value_type);
    }
    else if (c != '}'){
      printf("Could not parse json..\n");
      exit(EXIT_FAILURE);
    }
  }
  while(c != '}');

  printf("ended parsing map\n");

  return map;
}

char json_read_key(FILE* file, char *key){
  char c;
  char buffer[MAX_KEY_LEN];
  c = file_string_read(file, buffer, MAX_KEY_LEN, "\"}", 1);
  buffer[strlen(buffer)] = 0;
  strcpy(key, &buffer[0]);
  printf("key = %s\n", key);
  return c;
}

LIST* json_parse_list(FILE* file){
  LIST* list = list_create();
  char c, value_type;
  char buffer[BUFFER_LEN];
  void* value;

  printf("started parsing list\n");
  do{
    c = non_white_space_char(file);

    /* parse value */
    switch(c){
      case '{':
        value = (void*) json_parse_map(file);
        value_type = 'M';
        break;
      case '[':
        value = (void*) json_parse_list(file);
        value_type = 'L';
        break;
      case ',':case ']':
        value = NULL;
        value_type = 0;
        break;
      case '\"':
        c = file_string_read(file, buffer, BUFFER_LEN, "\"", 0);
        if (c != '\"'){
          printf("Could not parse value string.\n");
          exit(EXIT_FAILURE);
        }
        value = malloc(strlen(buffer));
        if (value == NULL){
          printf("Could not allocate memory.\n");
          exit(EXIT_FAILURE);
        }
        strcpy(value, buffer);
        printf("%s strlen = %d\n", value, strlen(value));
        value_type = 'S';
        printf("string done\n");
        break;
      case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
        break;
      default:
        printf("Could not parse JSON file.\n");
        exit(EXIT_FAILURE);
    }
    printf("+ %p %c\n", value, value_type);
    list_add(&list, value, value_type);
    printf("+");
    c = non_white_space_char(file);
    printf("%c", c);
    if (c != ',' && c != ']'){
      printf("Error with ,\n");
      exit(EXIT_FAILURE);
    }
  }
  while(c != ']');
  printf("ended parsing list\n");

  return list;
}

/* reads a string from a file until a character from the break string is read
 * or end of buffer size.
 * returns the position in the buffer of the last read char
 */
char file_string_read(FILE* file, char *buffer, int buffer_size, char* stop_chars, int ignore_whitespace){
  int i, j;
  char c;
  for(i = 0; i < buffer_size-1; ++i){
    c = fgetc(file);
    
    if(ignore_whitespace && (c == '\t' || c == '\n' || c == ' ')){
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
  buffer[i] = 0;
  
  printf("%s _ %c\n", buffer, c);
  return c;
}