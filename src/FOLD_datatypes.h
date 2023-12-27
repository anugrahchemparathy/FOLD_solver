#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <string>
#include <iostream>
#include "general_utils.h"


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
    bool operator==(const point_t& other) const {
        return x == other.x && y == other.y;
    }
} point_t;


std::string point_2_string(point_t point);
void reflect(const double &m, const double &b, point_t &p);

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
    bool operator==(const edge_t& other) const {
        return start == other.start && end == other.end;
    }
} edge_t;
std::ostream& operator<<(std::ostream& os, const edge_t& e);


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
        int unique_id;
    public:
        folding_polygon_t(std::vector<point_t> vertex_coords, int unique_id);

        std::vector<point_t> get_points();
        int get_num_points();

        void fold(edge_t edge);
};


// class Polygon
// used for initial dataloading
class polygon_t {
    private:
        std::vector<int> vertex_indices;
        std::vector<point_t> vertex_coords;
        std::vector<std::pair<edge_t, polygon_t>> neighbors;
        int num_points;
        int unique_id;
        bool neighbors_filled;
    public:
        polygon_t(std::vector<point_t> &polygon_vertices, int unique_id);
        
        std::string toString() const;
        // friend std::ostream& operator<<(std::ostream& os, const polygon_t& p);
        
        void add_neighbor(edge_t &edge, polygon_t &neighbor);
        void neighbors_complete();

        folding_polygon_t create_folding_polygon_t();
        std::vector<point_t> get_points();
        std::vector<std::pair<edge_t, polygon_t>> get_neighbors();
        std::vector<edge_t> get_edges();

        int get_num_points() const;
        int get_unique_id() const;

        friend bool operator<(const polygon_t& lhs, const polygon_t& rhs) {
            return lhs.get_unique_id() < rhs.get_unique_id();
        }

};

std::ostream& operator<<(std::ostream& os, const polygon_t& p);

#endif