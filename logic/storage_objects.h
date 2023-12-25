#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <string>
#include <iostream>
#include "utils.h"


/*
=================================================================
POINT TOOLS
=================================================================
*/

typedef struct point_t{
    double x;
    double y;
    bool operator<(const point_t& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    bool operator>(const point_t& other) const {
        if (x != other.x) return x > other.x;
        return y > other.y;
    }
    bool operator!=(const point_t& other) const {
        return x != other.x || y != other.y;
    }
} point_t;

// another (unused) way to implement comparison for point_t
struct compare_point_t {
    bool operator()(const point_t& a, const point_t& b) const {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    }
};

std::string point_2_string(point_t point);

/*
=================================================================
EDGE TOOLS
=================================================================
*/


typedef struct edge_t {
    point_t start;
    point_t end;
    bool operator<(const edge_t& other) const {
        if (start != other.start) return start < other.start;
        return end < other.end;
    }
} edge_t;

// another (unused) way to implement comparison for edge_t
struct compare_edge_t {
    compare_point_t point_comparator;

    bool operator()(const edge_t& a, const edge_t& b) const {
        // check if start > or <
        if (point_comparator(a.start, b.start)) return true;
        if (point_comparator(b.start, a.start)) return false;
        // if start ==, check end
        return point_comparator(a.end, b.end);
    }
};


// undirected edges according to sorted order
typedef struct {
    int first;
    int second;
} undirected_edge_t;

/*
=================================================================
POLYGONS
=================================================================
*/

// class Folding Polygon
// used in the final folding process
class folding_polygon_t {
    private:
        std::vector<point_t> vertex_coords;
        int num_points;
    public:
        folding_polygon_t(std::vector<point_t> &vertex_coords, int num_points);
        int get_num_points();
};


// class Polygon
// used for initial dataloading
class polygon_t {
    private:
        std::vector<int> vertex_indices;
        std::vector<point_t> vertex_coords;
        int num_points;
    public:
        polygon_t(std::vector<int> &vertex_indices, int num_points, std::vector<point_t> &all_vertices);
        polygon_t(std::vector<point_t> &polygon_vertices);
        
        std::string toString() const;
        // friend std::ostream& operator<<(std::ostream& os, const polygon_t& p);
        
        folding_polygon_t create_folding_polygon_t();
        std::vector<point_t> get_points();
        std::vector<edge_t> get_edges();
        int get_num_points();
};

std::ostream& operator<<(std::ostream& os, const polygon_t& p);



#endif