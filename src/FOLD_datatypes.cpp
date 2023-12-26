#include "FOLD_datatypes.h"


/*
HELPERS FOR POINT STRUCT
*/
std::string point_2_string(point_t point){
    return "Point(" + std::to_string(point.x) + ", " + std::to_string(point.y) + ")";
}

/*
HELPERS FOR  EDGE STRUCT
*/
std::ostream& operator<<(std::ostream& os, const edge_t& e) {
    os << point_2_string(e.start) << "->" << point_2_string(e.end) << std::endl;
    return os;
}


/*
DEFINING polygon_t CLASS
*/

polygon_t::polygon_t(std::vector<int> &vertex_indices, int num_points, std::vector<point_t> &all_vertices) {
    this->num_points = num_points;
    this->neighbors_filled = false;
    for (int i = 0; i < num_points; i++){
        this->vertex_coords.push_back(all_vertices[vertex_indices[i]]);
    }
}

polygon_t::polygon_t(std::vector<point_t> &vertex_coords){
    this->vertex_coords = vertex_coords;
    this->num_points = vertex_coords.size();
}

std::string polygon_t::toString() const{
    std::string representation = "";
    for (int i = 0; i < num_points; i++){
        representation += point_2_string(this->vertex_coords[i]);
    }
    return representation;
}


void polygon_t::add_neighbor(edge_t edge, polygon_t neighbor) {
    this->neighbors.push_back(neighbor);
}
void polygon_t::neighbors_complete(){
    this->neighbors_filled = true;
}


folding_polygon_t polygon_t::create_folding_polygon_t() {
    return folding_polygon_t(this->vertex_coords, this->num_points);
}

std::vector<point_t> polygon_t::get_points() {
    return this->vertex_coords;
}

std::vector<edge_t> polygon_t::get_edges() {
    std::vector<edge_t> edges;
    for (int i = 0; i < this->num_points - 1; i++) {
        point_t first = MIN(this->vertex_coords[i], this->vertex_coords[i+1]);
        point_t second = MAX(this->vertex_coords[i], this->vertex_coords[i+1]);

        edge_t curr_edge = {first, second};
        edges.push_back(curr_edge);
    }
    edge_t last_edge = {this->vertex_coords[num_points - 1], this->vertex_coords[0]};
    edges.push_back(last_edge);

    return edges;
}

std::vector<polygon_t> polygon_t::get_neighbors() {
    // todo: raise error if called before neighbors_filled is true
    return this->neighbors;
}

int polygon_t::get_num_points() {
    return this->num_points;
}



std::ostream& operator<<(std::ostream& os,  polygon_t const& p) {
    os << p.toString();
    return os;
}

/*
DEFINING folding_polygon_t CLASS
*/

folding_polygon_t::folding_polygon_t(std::vector<point_t> &vertex_coords, int num_points){
    this->vertex_coords = vertex_coords;
    this->num_points = num_points;
}

int folding_polygon_t::get_num_points(){
    return this->num_points;
}