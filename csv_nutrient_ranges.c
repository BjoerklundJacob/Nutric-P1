#include "csv_nutrient_ranges.h"
/*int main(void){
  double VitaminTable[ALLVITAMINS];

  SetVitamins(VitaminTable);

  double minMax[2];
  int age = 19, vitamin = 1, gender = 1, weight = 100;
  get_range(VitaminTable, minMax, age, vitamin, gender, weight);

  return 0;
*/

/*This function set a output array paremeter to too ranges*/
/*From the inputs that it gets*/
void get_range(double VitaminTable[], double *minMax, int age, int vitamin, int gender, int weight){
  int place = place_in_table(age_group(age), vitamin, gender);

  switch (vitamin){
  case mineral_iodine:
  case mineral_iron:
  case mineral_zinc:
  case vitamin_A:
    minMax[0] = VitaminTable[place] * weight;
    minMax[1] = VitaminTable[place+1] * weight;
    break;
  case mineral_calcium:
  case mineral_selenium:
  case vitamin_B2:
  case vitamin_B3:
  case vitamin_B12:
  case vitamin_D:
    minMax[0] = VitaminTable[place];
    minMax[1] = VitaminTable[place+1];
    break;
  }
}

/* Returns the age group of age */
int age_group(int age){
  if (age<20) {return 0;}
  else if (age<30) {return 1;}
  else if (age<40) {return 2;}
  else if (age<50) {return 3;}
  else if (age<60) {return 4;}
  else if (age<70) {return 5;}
  else if (age<80) {return 6;}
  else if (age<90) {return 7;}
  else if (age<100) {return 8;}
  else {return 9;}
}

/* Loads the CSVs of ranges to a double array of 400 numbers */
void set_vitamin_ranges(double VitaminTable[], UserData userdata){
  /*Open the file*/
  FILE *vitamins = fopen(".\\Vitamins.csv", "r");

  if (vitamins == NULL){
    printf("File Vitamins.csv was not found");
    exit(EXIT_FAILURE);
  }

  get_vitamins_table(vitamins, VitaminTable, userdata);

  fclose(vitamins);

  return;
}

void get_vitamins_table(FILE *vitamins, double *VitaminTable, UserData userdata){
  int place, vitamin, gender, i;
  /*Go through all the vitamins for both genders and all the age groups, to the array*/
  for (vitamin = 0; vitamin < VITAMINS; vitamin++){
    for (gender = 0; gender < GENDERS; gender++){
      for (i = 0; i < AGE_GROUPS; i++){
        place = place_in_table(i,vitamin,gender);
        
        fscanf(vitamins,"%lf - %lf",&VitaminTable[place], &VitaminTable[place + 1]);

        if(i != AGE_GROUPS-1) 
          fscanf(vitamins, " ;");
      }
    }  
  }
}

/* A function to get to a place in the array */
int place_in_table(int ageGroup, int vitamin, int gender){
  return ageGroup *2 + (vitamin * (AGE_GROUPS*2*2))  + (gender * AGE_GROUPS*2); 
}