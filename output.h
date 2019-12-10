#ifndef OUTPUT
#define OUTPUT

#include <math.h>
#include "csv_nutrient_parser.h"
#include "nutrient_counter.h"
#include "csv_nutrient_ranges.h"
#include "json_parser.h"
#include "data.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define WHITE "\x1b[37m"


void NutrientOutput(UserData userdata);
void convert_unit_from_gram(double* amount, char* unit);
void convert_unit(double* amount, char* unit_from, const char* unit_to);
#endif
