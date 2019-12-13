#include <stdio.h>
#include <math.h>
int main(void){
  int ids = 7792;
  int nutrients = 137;
  int min_len = 14;
  int max_len = 21;
  int i = 0;
  int eof = ids*nutrients*max_len;
  int byte = 0;
  int id = 0;
  while(byte < eof - min_len){
    byte += (ids - id) * min_len;
    id = byte / (nutrients * max_len);
    ++i;
  }
  printf("checks: %d\n", i);
  /*
  FILE *file_input, *file_output;
  int id_count, max_nutrients_per_id;
  int current_nutrient_count, current_id1, first_id = 167512, current_id = first_id, current_id2;
  double value;
  id_count = 7792;
  max_nutrients_per_id = 137;
  char line[30];
  int i;

  file_input = fopen("Food_Nutrient_Old.csv", "r");
  file_output = fopen("Food_Nutrient.csv", "w");
  if(file_input != NULL){
    while(fscanf(file_input, "%[^\n]\n", line) > 0){
      sscanf(line, "%d;%d;%lf", &current_id1, &current_id2, &value);
      if(current_id1 == current_id){
        fprintf(file_output, "%6d;%4d;%07.3lf\n", current_id1, current_id2, value);
        ++current_nutrient_count;
      }
      else{
        for(i = current_nutrient_count; i < max_nutrients_per_id; ++i){
          fprintf(file_output, "%d;0000;000.000\n", current_id);
        }
        fprintf(file_output, "%s\n", line);
        current_id = current_id1;
        current_nutrient_count = 0;
      }
    }
  }
  fclose(file_input);
  fclose(file_output);*/
  return 0;
}