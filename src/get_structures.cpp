/*
==============================================================================
Get Datastructures
==============================================================================
*/

// Data Structure A: vertex -> [neighboring vertices...]
std::map<point_t, std::vector<point_t>> get_structure_A(parsed_fold &skeleton){
    std::map<point_t, std::vector<point_t>> vertex_adjacents;

    for (int i = 0; i < skeleton.num_edges; i++) {
        int v1_i = skeleton.edge_indexes[i].first;
        int v2_i = skeleton.edge_indexes[i].second;

        point_t v1 = skeleton.vertices_coords[v1_i];
        point_t v2 = skeleton.vertices_coords[v2_i];

        vertex_adjacents[v1].push_back(v2);
        vertex_adjacents[v2].push_back(v1);
    }
    return vertex_adjacents;
}

// Data Structure B: list of all edges in a directional fashion
// each edge has 2 copies (one in each direction)
std::vector<edge_t> get_structure_B(parsed_fold &skeleton){
    std::vector<edge_t> all_edges;
    for (int i = 0; i < skeleton.num_edges; i++) {
        int v1_i = skeleton.edge_indexes[i].first;
        int v2_i = skeleton.edge_indexes[i].second;

        point_t v1 = skeleton.vertices_coords[v1_i];
        point_t v2 = skeleton.vertices_coords[v2_i];

        all_edges.push_back({v1, v2});
        all_edges.push_back({v2, v1});
    }
    return all_edges;
}

std::map<edge_t, std::vector<polygon_t>> get_structure_C(parsed_fold &skeleton){
    std::map<edge_t, std::vector<polygon_t>> edge_2_polygon;
    for (int i = 0; i < skeleton.num_edges; i++) {
        int v1_i = skeleton.edge_indexes[i].first;
        int v2_i = skeleton.edge_indexes[i].second;

        point_t v1 = skeleton.vertices_coords[v1_i];
        point_t v2 = skeleton.vertices_coords[v2_i];

        std::vector<polygon_t> empty_list;
        edge_2_polygon[{v1, v2}] = empty_list;
    }
    return edge_2_polygon;
}