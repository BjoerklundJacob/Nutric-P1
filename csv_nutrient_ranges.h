#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define AGE_GROUPS (10)
#define VITAMINS (10)
#define GENDERS (2)
#define VITAMIN_RANGES (AGE_GROUPS *2 *GENDERS * VITAMINS)

enum{VitaminA, Iron, VitaminD, Calcium, RiboflavinB2, NiacinB3, Selenium, Zinc, VitaminB12, Iodine,};

void GetRange(double VitaminTabel[], double *minMax, int age, int vitamin, int gender, int weight);
int AgeGroupe(int age);
void SetVitaminRanges(double VitaminTable[]);
void GetVitaminsTable(FILE *vitamins, double *VitaminTable);
int PlaceIndTable(int ageGroupe, int vitamin, int gender);