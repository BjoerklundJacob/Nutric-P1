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
    VitaminA,
    Iron,
    VitaminD,
    Calcium,
    RiboflavinB2,
    NiacinB3,
    Selenium,
    Zinc,
    VitaminB12,
    Iodine
};

void GetRange(double VitaminTable[], double *minMax, int age, int vitamin, int gender, int weight);
int AgeGroupe(int age);
void SetVitaminRanges(double VitaminTable[], UserData userdata);
void GetVitaminsTable(FILE *vitamins, double *VitaminTable, UserData userdata);
int PlaceIndTable(int ageGroupe, int vitamin, int gender);
