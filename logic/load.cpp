#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <nlohmann/json.hpp>
#include "storage_objects.h"

using json = nlohmann::json;
using namespace std;

typedef struct {
    string frame_title;
    vector<point_t> vertices_coords;
    vector<undirected_edge_t> edge_indexes;
} ParsedFold;

// main function
int main() {
    std::cout << "hello world" << std::endl;

    ifstream inFile("../FOLD_examples/crane.fold");
    if (!inFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    json j;
    inFile >> j;
    inFile.close();


    ParsedFold skeleton;
    for (int i = 0; i < j["edges_vertices"].size(); i++) {
        int first = j["edges_vertices"][i][0];
        int second = j["edges_vertices"][i][1];
        // cout << first << ", " << second << endl;
        skeleton.edge_indexes.push_back({first, second});
    }

    for (int i = 0; i < j["vertices_coords"].size(); i++) {
        float first = j["vertices_coords"][i][0];
        float second = j["vertices_coords"][i][1];
        // cout << first << ", " << second << endl;
        skeleton.vertices_coords.push_back({first, second});
    }




    
    return 0;
}
