#ifndef OUTPUT
#define OUTPUT

#include <math.h>
#include "csv_nutrient_parser.h"
#include "nutrient_counter.h"
#include "csv_nutrient_ranges.h"
#include "json_parser.h"
#include "data.h"

#define YELLOW "\x1b[33m"
#define WHITE "\x1b[37m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"

void nutrient_output(UserData userdata);
void convert_unit(double* amount, char* unit_from, const char* unit_to);
int Percentages(double value, double min, double max);
#endif