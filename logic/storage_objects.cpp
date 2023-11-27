#include "storage_objects.h"


/*
HELPERS FOR POINT STRUCT
*/
std::string point_2_string(point_t point){
    return "Point(" + std::to_string(point.x) + ", " + std::to_string(point.y) + ")";
}


/*
DEFINING POLYGON CLASS
*/

Polygon::Polygon(std::vector<int> &vertex_indices, int num_points, std::vector<point_t> &all_vertices) {
    this->vertex_indices = vertex_indices;
    this->num_points = num_points;

    for (int i = 0; i < num_points; i++){
        this->vertex_coords.push_back(all_vertices[vertex_indices[i]]);
    }
}

std::string Polygon::toString(){
    std::string representation = "";
    for (int i = 0; i < num_points; i++){
        representation += point_2_string(this->vertex_coords[i]);
    }
    return representation;
}

FoldingPolygon Polygon::create_FoldingPolygon() {
    return FoldingPolygon(this->vertex_coords, this->num_points);
}

std::vector<point_t> Polygon::get_points() {
    return this->vertex_coords;
}

std::vector<edge_t> Polygon::get_edges() {
    std::vector<edge_t> edges;
    for (int i = 0; i < this->num_points - 1; i++) {
        edge_t curr_edge = {this->vertex_coords[i], this->vertex_coords[i+1]};
        edges.push_back(curr_edge);
    }
    edge_t last_edge = {this->vertex_coords[num_points - 1], this->vertex_coords[0]};
    edges.push_back(last_edge);

    return edges;
}

std::vector<undirected_edge_t> Polygon::get_undirected_edges() {
    std::vector<undirected_edge_t> index_edges;
    for (int i = 0; i < this->num_points - 1; i++) {
        int first = MIN(this->vertex_indices[i], this->vertex_indices[i+1]);
        int second = MAX(this->vertex_indices[i], this->vertex_indices[i+1]);

        index_edges.push_back({first, second});
    }
    int first = MIN(this->vertex_indices[num_points-1], this->vertex_indices[0]);
    int second = MAX(this->vertex_indices[num_points-1], this->vertex_indices[0]);
    index_edges.push_back({first, second});
    return index_edges;
}

/*
Defining FoldingPolygon class
*/

FoldingPolygon::FoldingPolygon(std::vector<point_t> &vertex_coords, int num_points){
    this->vertex_coords = vertex_coords;
    this->num_points = num_points;
}

int FoldingPolygon::get_num_points(){
    return this->num_points;
}