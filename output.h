#ifndef OUTPUT
#define OUTPUT

#include "data.h"
#include "json_parser.h"
#include "csv_nutrient_ranges.h"
#include "nutrient_counter.h"
#include "csv_nutrient_parser.h"
#include <math.h>

#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define WHITE "\x1b[37m"
#define RED "\x1b[31m"

void NutrientOutput(UserData userdata);
int Percentages(double value, double min, double max);
void convert_unit(double* amount, char* unit_from, const char* unit_to);
#endif