#ifndef CSV_NUTRIENT_RANGES
#define CSV_NUTRIENT_RANGES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nutrient_counter.h"
#include "data.h"

#define AGE_GROUPS (10)
#define VITAMINS (10)
#define GENDERS (2)
#define VITAMIN_RANGES (AGE_GROUPS * 2 * GENDERS * VITAMINS)

void GetRange(double VitaminTable[], double *minMax, int age, int vitamin, int gender, int weight);
int AgeGroup(int age);
void SetVitaminRanges(double VitaminTable[], UserData userdata);
void GetVitaminsTable(FILE *vitamins, double *VitaminTable, UserData userdata);
int PlaceInTable(int ageGroup, int vitamin, int gender);
#endif