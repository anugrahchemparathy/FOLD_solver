#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>

#include <limits>
#include <math.h>


#include "FOLD_datatypes.h"
#include "FOLD_parse.h"
#include "FOLD_utils.h"
#include "FOLD_endpoint.h"
#include "get_structures.cpp"

std::vector<polygon_t> get_polygons(std::map<point_t, std::vector<point_t>> &vertex_adjacents, 
          std::vector<edge_t> &all_edges, 
          parsed_fold &skeleton) {

    std::vector<polygon_t> all_polygons;
    int polygon_id = 0;
    while (!all_edges.empty()) {
        std::vector<point_t> polygon_vertices;
        bool polygon_valid = true;
        bool bug_fixer = true;

        edge_t prev_edge = all_edges[0];
        point_t v_prev = prev_edge.start;
        point_t v_curr = prev_edge.end;

        polygon_vertices.push_back(v_prev);
        all_edges.erase(std::remove(all_edges.begin(), all_edges.end(), prev_edge), all_edges.end());
        
        while (v_curr != polygon_vertices[0]){
            // check if v_curr in polygon_vertices
            if (std::find(polygon_vertices.begin(), polygon_vertices.end(), v_curr) != polygon_vertices.end()){
                std::cout << "v_curr = " << point_2_string(v_curr) << " is already in polygon_vertices, len(polygon_vertices) = " << polygon_vertices.size() << std::endl;
                polygon_valid = false;
                break;
            }

            polygon_vertices.push_back(v_curr);
            double prev_angle = get_intervertex_angle(v_curr, v_prev);
            double best_candidate_angle = std::numeric_limits<double>::infinity();
            point_t best_candidate;


            for (int i = 0; i < vertex_adjacents[v_curr].size(); i++){
                point_t v_candidate = vertex_adjacents[v_curr][i];
                if (v_candidate == v_prev) continue;

                double candidate_angle = get_intervertex_angle(v_curr, v_candidate) - prev_angle;
                if (candidate_angle < 0) candidate_angle += 360;

                
                // update best candidate
                if (candidate_angle < best_candidate_angle){
                    best_candidate_angle = candidate_angle;
                    best_candidate = v_candidate;
                }
            }

            if (best_candidate_angle > 180){
                polygon_valid = false;
                break;
            }
            if (polygon_vertices.size() > 100){
                // some bug happened, so just break out of the loop and report it!
                // TODO: change this to an assert
                std::cout << "polygon_vertices.size() > 100, so breaking out of loop" << std::endl;
                for (int i = 0 ; i < 5; i++){
                    std::cout << "polygon_vertices[" << std::to_string(i) << "] = " << point_2_string(polygon_vertices[i]) << std::endl;
                }
                bug_fixer = false;
                break;
            }


            point_t v_next = best_candidate;
            edge_t remove_edge = {v_curr, v_next};
            all_edges.erase(std::remove(all_edges.begin(), all_edges.end(), remove_edge), all_edges.end());
            
            v_prev = v_curr;
            v_curr = v_next;
        }

        if (!polygon_valid) continue;
        if (!bug_fixer) {
            std::vector<point_t> partial_vertices(polygon_vertices.begin(), polygon_vertices.begin() + 4);
            polygon_t polygon = polygon_t(partial_vertices, polygon_id);
            polygon_id++;
            all_polygons.push_back(polygon);
            break;
        }

        polygon_t polygon = polygon_t(polygon_vertices, polygon_id);
        polygon_id++;
        all_polygons.push_back(polygon);
    }
    return all_polygons;
}

void fill_neighbors(std::vector<polygon_t> &all_polygons){
    std::map<edge_t, polygon_t*> edge_2_polygon;

    for (auto& polygon: all_polygons){
        for (auto& edge: polygon.get_edges()){
            auto it = edge_2_polygon.find(edge);
            if (it != edge_2_polygon.end()){
                polygon_t* other_polygon = it->second;

                polygon.add_neighbor(edge, other_polygon);
                other_polygon->add_neighbor(edge, &polygon);
            } else {
                edge_2_polygon.emplace(edge, &polygon);
            }
        }
    }

    // set all polygons to have valid neighbors
    for (auto& polygon: all_polygons){
        polygon.neighbors_complete();
    }
}


// TODO: implement < operator
std::vector<folding_polygon_t> DFS(polygon_t &start_polygon, std::set<polygon_t> &visited) {
    std::vector<folding_polygon_t> folded_form;
    folded_form.push_back(start_polygon.create_folding_polygon_t());
    visited.insert(start_polygon);

    for (auto edge_neighbor: start_polygon.get_neighbors()){
        edge_t edge = edge_neighbor.first;
        polygon_t neighbor = *(edge_neighbor.second);


        if (visited.count(neighbor)) continue;

        std::vector<folding_polygon_t> all_polys = DFS(neighbor, visited);
        for (auto folding_poly_neighbor : all_polys) {
            folding_poly_neighbor.fold(edge);
            folded_form.push_back(folding_poly_neighbor);
        }
    }

    return folded_form;
}


// main function
int main(int argc, char* argv[]) {
    std::string filepath;
    std::string filename;

    // allow custom filepath from command line
    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "crane";
    }
    filepath = "../FOLD_examples/" + filename + ".fold";

    parsed_fold skeleton = load_fold_file(filepath);
    std::cout << "skeleton failed = " << skeleton.failed << std::endl;
    std::cout << "skeleton num_edges = " << skeleton.num_edges << " & num_vertices = " << skeleton.num_vertices << std::endl;



    // Data Structure A: vertex -> [neighboring vertices]
    std::map<point_t, std::vector<point_t>> vertex_adjacents = get_structure_A(skeleton);
    // Data Structure B: list of all edges in a directional fashion
    std::vector<edge_t> all_edges = get_structure_B(skeleton);

    // Compute polygons and neighbors from skeleton and data structures
    std::vector<polygon_t> all_polygons = get_polygons(vertex_adjacents, all_edges, skeleton);
    fill_neighbors(all_polygons);
    std::cout<< "all_polygons.size() = " << all_polygons.size() << std::endl;




    std::set<polygon_t> visited;
    std::vector<folding_polygon_t> folded_form = DFS(all_polygons[0], visited);
    std::cout << "folded_form.size() = " << folded_form.size() << std::endl;

    // VISUALIZATION
    // dump_polygons(all_polygons);
    dump_folding_polygons(folded_form);

    // std::vector<polygon_t> specific_polygons;
    // visualize specific polygons by pushing them onto this vector by the unique_id field
    // dump_polygons(specific_polygons);

    return 0;
}
