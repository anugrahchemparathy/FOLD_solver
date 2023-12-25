#ifndef PARSE_FOLD_H
#define PARSE_FOLD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <nlohmann/json.hpp>
#include "storage_objects.h"

using json = nlohmann::json;

typedef struct {
    int failed;
    std::vector<point_t> vertices_coords;
    std::vector<undirected_edge_t> edge_indexes;
    int num_vertices;
    int num_edges;
} parsed_fold;


parsed_fold load_fold_file(std::string filepath = "../FOLD_examples/crane.fold");

void dump_polygons(std::vector<polygon_t> all_polygons);

#endif