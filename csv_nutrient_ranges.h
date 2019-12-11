#pragma once

#include "data.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define VITAMINS (10)
#define GENDERS (2)
#define VITAMIN_RANGES (AGE_GROUPS * 2 * GENDERS * VITAMINS)
#define AGE_GROUPS (10)

enum
{
    Calcium,
    Iron,
    Zinc,
    Selenium,
    Iodine,
    RiboflavinB2,
    NiacinB3,
    VitaminB12,
    VitaminA,
    VitaminD
};

void GetRange(double VitaminTable[], double *minMax, int age, int vitamin, int gender, int weight);
int AgeGroup(int age);
void SetVitaminRanges(double VitaminTable[], UserData userdata);
void GetVitaminsTable(FILE *vitamins, double *VitaminTable, UserData userdata);
int PlaceInTable(int ageGroupe, int vitamin, int gender);
