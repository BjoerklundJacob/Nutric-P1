#include "csv_nutrient_ranges.h"

/**
  * Gets user data as input and uses these to calculate the nutrient requirements
  */
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

/**
  *  Returns the age group of the user 
  */
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

/**
  * Loads the CSV-file with ranges to a double array
  */
void load_vitamin_ranges(double VitaminTable[], UserData userdata){
<<<<<<< Updated upstream
  /*Open the file*/
  FILE *vitamins = fopen(".\\Vitamins.csv", "r");
=======
  FILE *vitamins = fopen(".\\Vitamin_Ranges.csv", "r");
>>>>>>> Stashed changes

  if (vitamins == NULL){
    printf("File Vitamins.csv was not found");
    exit(EXIT_FAILURE);
  }
  get_vitamins_table(vitamins, VitaminTable, userdata);
  fclose(vitamins);

  return;
}

/**
  * Scans the nutrients file dependent on age
  * Uses user data to calculate how many of each nutrient they should have based on age and gender
  */ 
void get_vitamins_table(FILE *vitamins, double *VitaminTable, UserData userdata){
  int place, vitamin, gender, i;
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
  return;
}

/**
  * A function to find a place in the array 
  */
int place_in_table(int ageGroup, int vitamin, int gender){
  return ageGroup *2 + (vitamin * (AGE_GROUPS*2*2))  + (gender * AGE_GROUPS*2); 
}