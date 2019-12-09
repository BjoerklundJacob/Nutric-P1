#ifndef OUTPUT
#define OUTPUT
#include <math.h>
#include "csv_nutrient_parser.h"
#include "nutrient_counter.h"
#include "csv_nutrient_ranges.h"
#include "json_parser.h"
#include "data.h"

void NutrientOutput(UserData userdata);
char* NutrientToUnit(double gram);
double GramToUnit(double nutrient);
void convert_unit_from_gram(double* amount, char* unit);
void convert_unit(double* amount, char* unit_from, const char* unit_to);
#endif
