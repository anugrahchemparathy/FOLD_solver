#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <limits>
#include <math.h>


#include "FOLD_datatypes.h"
#include "FOLD_parse.h"
#include "FOLD_utils.h"
#include "get_structures.cpp"

std::vector<polygon_t> get_polygons(std::map<point_t, std::vector<point_t>> &vertex_adjacents, 
          std::vector<edge_t> &all_edges, 
          std::map<edge_t, std::vector<polygon_t>> &edge_2_polygon,
          parsed_fold &skeleton) {

    std::vector<polygon_t> all_polygons;
    while (!all_edges.empty()) {
        // std::cout << "all_edges[0] = " << all_edges[0] << "len(all_edges) = " << all_edges.size() << std::endl << std::endl << std::endl; 
        std::vector<point_t> polygon_vertices;
        bool polygon_valid = true;
        bool bug_fixer = true;

        edge_t prev_edge = all_edges[0];
        point_t v_prev = prev_edge.start;
        point_t v_curr = prev_edge.end;

        polygon_vertices.push_back(v_prev);
        all_edges.erase(std::remove(all_edges.begin(), all_edges.end(), prev_edge), all_edges.end());
        
        point_t test_point = {0.716773, 0.576120};
        bool test_printer = false;
        bool x_close = fabs(v_prev.x - test_point.x) < 0.0001;
        bool y_close = fabs(v_prev.y - test_point.y) < 0.0001;
        // if (x_close && y_close) test_printer = true;
        // std::cout << "test_printer = " << test_printer << ", v_prev = "<< point_2_string(v_prev) << std::endl;


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



            bool x_close = fabs(v_curr.x - 0.5) < 0.0001;
            bool y_close = fabs(v_curr.y - 0.5) < 0.0001;
            bool danger_point = x_close && y_close;
            if (test_printer && danger_point) {
                std::cout << "\n============\n";
                std::cout << "v_curr = " << point_2_string(v_curr) << std::endl;
            }
            for (int i = 0; i < vertex_adjacents[v_curr].size(); i++){
                point_t v_candidate = vertex_adjacents[v_curr][i];
                if (v_candidate == v_prev) continue;

                double candidate_angle = get_intervertex_angle(v_curr, v_candidate) - prev_angle;
                if (candidate_angle < 0) candidate_angle += 360;

                if (test_printer && danger_point){
                    std::cout << "\n\n";
                    std::cout << "len(polygon_vertices) = " << polygon_vertices.size() << ", iva = " << std::to_string(get_intervertex_angle(v_curr, v_candidate)) << ", pa = " << std::to_string(prev_angle) << std::endl;
                    std::cout << "v_candidate = " << point_2_string(v_candidate) << ", candidate_angle = " << std::to_string(candidate_angle) << ", best_candidate_angle = " << std::to_string(best_candidate_angle) << std::endl;
                } 

                
                // update best candidate
                if (candidate_angle < best_candidate_angle){
                    if (test_printer && danger_point)
                        std::cout << "updating\n";
 
                    best_candidate_angle = candidate_angle;
                    best_candidate = v_candidate;
                    if (test_printer && danger_point){
                        std::cout<< "candidate = " << point_2_string(v_candidate) << ", candidate_angle = " << std::to_string(candidate_angle) << ", best_candidate_angle = " << std::to_string(best_candidate_angle) << std::endl << std::endl << std::endl;
                        // return all_polygons;
                    }
                }

                if (test_printer && danger_point) std::cout <<"\n\n";
            }

            if (best_candidate_angle > 180){
                polygon_valid = false;
                break;
            }
            if (polygon_vertices.size() > 100){
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
            polygon_t polygon = polygon_t(partial_vertices);
            all_polygons.push_back(polygon);
            break;
        }

        polygon_t polygon = polygon_t(polygon_vertices);
        all_polygons.push_back(polygon);


    }

    return all_polygons;
}


// main function
int main() {
    parsed_fold skeleton = load_fold_file();
    std::cout << "skeleton failed = " << skeleton.failed << std::endl;
    std::cout << "skeleton num_edges = " << skeleton.num_edges << " & num_vertices = " << skeleton.num_vertices << std::endl; 

    // TODO: add in an assert (skeleton.failed == 0)

    // REFERENCE: parsed_fold definition
    // typedef struct {
    //     int failed;
    //     std::vector<point_t> vertices_coords;
    //     std::vector<undirected_edge_t> edge_indexes;
    //     int num_vertices;
    //     int num_edges;
    // } parsed_fold;


    /*
    Load up standard datastructures
    */
    // Data Structure A: vertex -> [neighboring vertices]
    std::map<point_t, std::vector<point_t>> vertex_adjacents = get_structure_A(skeleton);

    // Data Structure B: list of all edges in a directional fashion
    std::vector<edge_t> all_edges = get_structure_B(skeleton);

    // Data Structure C: mapping of edge -> [polygons] (max size of list is 2 since at most 2 polygons per edge)
    std::map<edge_t, std::vector<polygon_t>> edge_2_polygon = get_structure_C(skeleton);


    /*
    Compute polygons using interior hull
    */
    std::vector<polygon_t> all_polygons = get_polygons(vertex_adjacents, all_edges, edge_2_polygon, skeleton);

    dump_polygons(all_polygons);

    return 0;
}
