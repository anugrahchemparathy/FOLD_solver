#include "FOLD_parse.h"

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

void dump_polygons(std::vector<polygon_t> all_polygons){
    json out_json;
    for (int i = 0; i < all_polygons.size(); i++){
        polygon_t polygon = all_polygons[i];
        std::vector<point_t> points = polygon.get_points();

        std::string poly_id = "polygon_" + std::to_string(i);
        out_json[poly_id] = {};
        for (int j = 0; j < polygon.get_points().size(); j++){
            std::string point_id = "point_" + std::to_string(j);
            out_json[poly_id][point_id] = {};
            out_json[poly_id][point_id]["x"] = points[j].x;
            out_json[poly_id][point_id]["y"] = points[j].y;
        }
    }

    // create outFile at "out.json"
    // write j to outFile
    std::ofstream outFile("out.json");
    outFile << out_json;
}