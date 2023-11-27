#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <string>
#include "utils.h"

typedef struct {
    double x;
    double y;
} point_t;

std::string point_2_string(point_t point);


typedef struct {
    point_t start;
    point_t end;
} edge_t;

typedef struct {
    int first;
    int second;
} undirected_edge_t;


// class Folding Polygon
class FoldingPolygon {
    private:
        std::vector<point_t> vertex_coords;
        int num_points;
    public:
        FoldingPolygon(std::vector<point_t> &vertex_coords, int num_points);
        int get_num_points();
};


// class Polygon
class Polygon {
    private:
        std::vector<int> vertex_indices;
        std::vector<point_t> vertex_coords;
        int num_points;
    public:
        Polygon(std::vector<int> &vertex_indices, int num_points, std::vector<point_t> &all_vertices);
        
        std::string toString();
        FoldingPolygon create_FoldingPolygon();
        std::vector<point_t> get_points();
        std::vector<edge_t> get_edges();
        std::vector<undirected_edge_t> get_undirected_edges();
        int get_num_points();
};



#endif