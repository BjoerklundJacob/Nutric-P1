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
#endif
