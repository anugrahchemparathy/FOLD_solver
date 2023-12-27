#include "FOLD_datatypes.h"


/*
HELPERS FOR POINT STRUCT
*/
std::string point_2_string(point_t point){
    return "Point(" + std::to_string(point.x) + ", " + std::to_string(point.y) + ")";
}

void reflect(const double &m, const double &b, point_t &p) {
    p.y -= b;
    double new_x = ((1 - (m * m)) * p.x + (2 * m) * p.y) / (1 + (m * m));
    double new_y = ((2 * m) * p.x + ((m * m) - 1) * p.y) / (1 + (m * m));
    new_y += b;

    p.x = new_x;
    p.y = new_y;
}

/*
HELPERS FOR  EDGE STRUCT
*/
std::ostream& operator<<(std::ostream& os, const edge_t& e) {
    os << point_2_string(e.start) << "->" << point_2_string(e.end);
    return os;
}


/*
DEFINING polygon_t CLASS
*/

polygon_t::polygon_t(std::vector<point_t> &vertex_coords, int unique_id){
    this->vertex_coords = vertex_coords;
    this->num_points = vertex_coords.size();
    this->unique_id = unique_id;
    this->neighbors_filled = false;
}

std::string polygon_t::toString() const{
    std::string representation = "";
    for (int i = 0; i < num_points; i++){
        representation += point_2_string(this->vertex_coords[i]);
    }
    return representation;
}


void polygon_t::add_neighbor(edge_t &edge, polygon_t* neighbor_ptr) {
    this->neighbors.push_back(std::make_pair(edge, neighbor_ptr));
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

    point_t first = MIN(this->vertex_coords[num_points - 1], this->vertex_coords[0]);
    point_t second = MAX(this->vertex_coords[num_points - 1], this->vertex_coords[0]);
    edge_t last_edge = {first, second};
    edges.push_back(last_edge);

    return edges;
}

std::vector<std::pair<edge_t, polygon_t*>> polygon_t::get_neighbors() {
    // todo: raise error if called before neighbors_filled is true
    return this->neighbors;
}

int polygon_t::get_num_points() const {
    return this->num_points;
}
int polygon_t::get_unique_id() const {
    return this->unique_id;
}


std::ostream& operator<<(std::ostream& os,  polygon_t const& p) {
    os << p.toString();
    return os;
}

/*
DEFINING folding_polygon_t CLASS
*/

folding_polygon_t::folding_polygon_t(std::vector<point_t> vertex_coords, int num_points){
    // should implicitly copy vertex coords when called
    this->vertex_coords = vertex_coords;
    this->num_points = num_points;
}

void folding_polygon_t::fold(edge_t edge){
    point_t first = edge.start;
    point_t second = edge.end;

    double dy = second.y - first.y;
    double dx = second.x - first.x;

    if (dx == 0) {
        // reflection across a vertical line 
        // slope is undefined, so we handle this separately
        double rx = first.x;
        for (auto &p: this->vertex_coords){
            p.x = rx - (p.x - rx);
        }

    } else {
        double m = dy / dx;
        double b = first.y - (first.x * m);
        for (auto &p: this->vertex_coords){
            reflect(m, b, p);
        }
    }
}

std::vector<point_t> folding_polygon_t::get_points() {
    return this->vertex_coords;
}

int folding_polygon_t::get_num_points(){
    return this->num_points;
}

int folding_polygon_t::get_unique_id(){
    return this->unique_id;
}