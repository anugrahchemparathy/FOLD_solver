#include <iostream>
#include <fstream>
#include <vector>
#include <string>


#include "storage_objects.h"
#include "parse_FOLD.h"
#include "get_structures.cpp"


// main function
int main() {
    std::cout << "hello world" << std::endl;
    parsed_fold skeleton = load_fold_file();
    std::cout << "skeleton failed = " << skeleton.failed << std::endl;
    std::cout << "skeleton num_edges = " << skeleton.num_edges << " & num_vertices = " << skeleton.num_vertices << std::endl; 

    // TODO: add in an assert (skeleton.failed == 0)

    // typedef struct {
    //     int failed;
    //     std::vector<point_t> vertices_coords;
    //     std::vector<undirected_edge_t> edge_indexes;
    //     int num_vertices;
    //     int num_edges;
    // } parsed_fold;

    // Data Structure A: vertex -> [neighboring vertices]
    // std::map<point_t, std::vector<point_t>, compare_point_t> vertex_adjacents;
    std::map<point_t, std::vector<point_t>> vertex_adjacents = get_structure_A(skeleton);
    // basic checks
    std::cout << point_2_string(vertex_adjacents[{0, 1}][0]) << std::endl;
    std::cout << vertex_adjacents[{0, 1}].size() << std::endl;

    // Data Structure B: list of all edges in a directional fashion
    std::vector<edge_t> all_edges = get_structure_B(skeleton);

    // Data Structure C: 
    std::map<edge_t, std::vector<polygon_t>> edge_2_polygon = get_structure_C(skeleton);


    
    return 0;
}
