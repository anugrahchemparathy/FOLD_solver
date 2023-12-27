#include "FOLD_endpoint.h"

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


void dump_folding_polygons(std::vector<folding_polygon_t> folded_form){
    json out_json;
    for (int i = 0; i < folded_form.size(); i++){
        folding_polygon_t polygon = folded_form[i];
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