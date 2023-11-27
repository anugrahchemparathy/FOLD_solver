#include "parse_FOLD.h"

parsed_fold load_fold_file(std::string filepath){
    parsed_fold skeleton;

    std::ifstream inFile(filepath);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        skeleton.failed = 1;
        return skeleton;
    }

    json j;
    inFile >> j;
    inFile.close();


    for (int i = 0; i < j["edges_vertices"].size(); i++) {
        int first = j["edges_vertices"][i][0];
        int second = j["edges_vertices"][i][1];
        skeleton.edge_indexes.push_back({first, second});
    }

    for (int i = 0; i < j["vertices_coords"].size(); i++) {
        float first = j["vertices_coords"][i][0];
        float second = j["vertices_coords"][i][1];
        skeleton.vertices_coords.push_back({first, second});
    }
    skeleton.num_edges = skeleton.edge_indexes.size();
    skeleton.num_vertices = skeleton.vertices_coords.size();

    skeleton.failed = 0;
    return skeleton;
}