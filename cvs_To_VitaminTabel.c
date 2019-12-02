#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define AGE_GROUPS (10)
#define VITAMINS (10)
#define GENDERS (2)
#define ALLVITAMINS (AGE_GROUPS *2 *GENDERS * VITAMINS)

enum{VitaminA, Iron, VitaminD, Calcium, RiboflavinB2, NiacinB3, Selenium, Zinc, VitaminB12, Iodine,};

void GetRange(double VitaminTabel[], double *minMax, int age, int vitamin, int gender, int weight);
int AgeGroupe(int age);
void SetVitamins(double VitaminTabel[]);
void GetVitaminsTabel(FILE *vitamins, double *VitaminTabel);
int PlaceIndTabel(int ageGroupe, int vitamin, int gender);

int main(void){
  double VitaminTabel[ALLVITAMINS];

  SetVitamins(VitaminTabel);

  double minMax[2];
  int age = 19, vitamin = 1, gender = 1, weight = 100;
  GetRange(VitaminTabel, minMax, age, vitamin, gender, weight);

  return 0;
}

void GetRange(double VitaminTabel[], double *minMax, int age, int vitamin, int gender, int weight){
  int place = PlaceIndTabel(AgeGroupe(age), vitamin, gender);

  switch (vitamin){
  case VitaminA:
  case Iron:
  case Zinc:
  case Iodine:
    minMax[0] = VitaminTabel[place] * weight;
    minMax[1] = VitaminTabel[place+1] * weight;
    break;
  case VitaminD:
  case Calcium:
  case RiboflavinB2:
  case NiacinB3:
  case Selenium:
  case VitaminB12:
    minMax[0] = VitaminTabel[place];
    minMax[1] = VitaminTabel[place+1];
    break;
  
  default:
    break;
  }

  return;
}

int AgeGroupe(int age){
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

void SetVitamins(double VitaminTabel[]){
  FILE *vitamins = fopen("C:\\Users\\Malthe\\Documents\\VeGen-P1\\Vitamins.csv", "r");

  if (vitamins == NULL){
    perror("NO");
    exit(1);
  }

  GetVitaminsTabel(vitamins, VitaminTabel);

  fclose(vitamins);

  return;
}

void GetVitaminsTabel(FILE *vitamins, double *VitaminTabel){
  int place;

  for (int vitamin = 0; vitamin < VITAMINS; vitamin++){
    for (int gender = 0; gender < GENDERS; gender++){
      for (int i = 0; i < AGE_GROUPS; i++){
        place = PlaceIndTabel(i,vitamin,gender);
        
        fscanf(vitamins,"%lf - %lf",&VitaminTabel[place], &VitaminTabel[place + 1]);
        
        if(i != AGE_GROUPS-1) 
          fscanf(vitamins, " ;");
      }
    }  
  }
}

int PlaceIndTabel(int ageGroupe, int vitamin, int gender){
  return ageGroupe *2 + (vitamin * (AGE_GROUPS*2*2))  + (gender * AGE_GROUPS*2); 
}