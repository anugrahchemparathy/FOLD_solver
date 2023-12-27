#ifndef CPP_ENDPOINT_H
#define CPP_ENDPOINT_H

#include <fstream>

#include <nlohmann/json.hpp>
#include "FOLD_datatypes.h"

using json = nlohmann::json;

void dump_polygons(std::vector<polygon_t> all_polygons);
void dump_folding_polygons(std::vector<folding_polygon_t> folded_form);

#endif