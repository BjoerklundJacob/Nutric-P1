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

void get_range(double VitaminTable[], double *minMax, int age, int vitamin, int gender, int weight);
int age_group(int age);
void load_vitamin_ranges(double VitaminTable[], UserData userdata);
void get_vitamins_table(FILE *vitamins, double *VitaminTable, UserData userdata);
int place_in_table(int ageGroupe, int vitamin, int gender);
