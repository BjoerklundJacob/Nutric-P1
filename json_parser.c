#include <stdio.h>
#include "json_structs.h"

#define MAX_KEY_LEN 32
#define BUFFER_LEN 256

char file_string_read(FILE* file, char *buffer, int buffer_size, char* stop_chars, int ignore_whitespace);
MAP* json_load(char* file_dir);
char json_read_key(FILE* file, char *key);

int main(void){
  MAP *map = json_load(".\\test.json");

  map_free(map);
  return 0;
}

MAP* json_load(char* file_dir){
  FILE *file;
  MAP *map = map_create();
  char buffer[BUFFER_LEN];
  int i;
  char c;
  char key[MAX_KEY_LEN];

  for(i = 0; i < BUFFER_LEN; ++i){
    buffer[i] = 0;
  }

  file = fopen(file_dir, "r");
  if(file == NULL){
    printf("Necessary file could not be opened.");
    exit(EXIT_FAILURE);
  }

  /*** Parse json ***/

  /* fix this to only read for { and error if not found first or not? in case of nested data */
  c = file_string_read(file, buffer, BUFFER_LEN, "{},=[]:\"\0\3", 1);
  printf("string = %s\n", buffer);
  printf("c = %c\n", c);
  switch (c){
  case '{':
    c = json_read_key(file, key);
    if (c != ':'){
      printf("Failed to read key from json\n");
      exit(EXIT_FAILURE);
    }
    printf("key = %s\n", key);
    /*map_add(map, key, json_value_parse(file));*/
    break;
  
  default:
    break;
  }

  fclose(file);

  return map;
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
  
  printf("%s\n", buffer);
  printf("c = %c\n", c);
  return c;
}

char json_read_key(FILE* file, char *key){
  char c;
  char buffer[MAX_KEY_LEN];
  c = file_string_read(file, buffer, MAX_KEY_LEN, ":", 1);
  buffer[strlen(buffer)-1] = 0;
  strcpy(key, &buffer[1]);
  return c;
}