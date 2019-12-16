#include <stdio.h>
#include <math.h>
#include <string.h>
int main(void){
    FILE *file_input, *file_output;
  int id_count, max_nutrients_per_id;
  int current_nutrient_count, current_id1, first_id = 167512, current_id = first_id, current_id2;
  double value;
  id_count = 7792;
  max_nutrients_per_id = 9;
  char line[22];
  int i;

  file_input = fopen("Food_Nutrient_Old.csv", "r");
  file_output = fopen("Food_Nutrients.csv", "w");
  if(file_input != NULL){
    current_nutrient_count = 0;
    while(fscanf(file_input, "%[^\n]\n", line) > 0){
      sscanf(line, "%d;%d;%lf", &current_id1, &current_id2, &value);
      if(current_id1 != current_id){
        for(i = current_nutrient_count; i < max_nutrients_per_id; ++i){
          fprintf(file_output, "%d;0000;000000.000\n", current_id);
        }
        current_id = current_id1;
        current_nutrient_count = 0;
      }
      if(current_id1 == current_id){
         switch(current_id2){
            case 1087: /* Id for calcium */
            case 1089: /* Id for Iron */
            case 1095: /* Id for Zinc */
            case 1103: /* Id for Selenium */
            case 1106: /* Id for Vitamin A */
            case 1112: /* Id for Vitamin D */
            case 1166: /* Id for Vitamin B2 */
            case 1167: /* Id for Vitamin B3 */
            case 1178: /* Id for Vitamin B12 */
              fprintf(file_output, "%6d;%4d;%010.3lf\n", current_id1, current_id2, value);
              ++current_nutrient_count;
         }
      }
    }
    for(i = current_nutrient_count; i < max_nutrients_per_id; ++i){
      fprintf(file_output, "%d;0000;000000.000\n", current_id);
    }
  }
  fclose(file_input);
  fclose(file_output);
  printf("Done\n");
  return 0;
}