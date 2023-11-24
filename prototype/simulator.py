import json
import math
import numpy as np
import random

from datastructures import *
from helpers import *
from visualize import *


def get_datastructures(data):
    # Load from JSON
    vertices = data['vertices_coords']
    edges = data['edges_vertices']
    
    # Preprocessing
    vertex_count = len(vertices)

    # Data Structure A
    vertex_adjacents = [[] for v in range(vertex_count)]
    for e1,e2 in edges:
        vertex_adjacents[e1].append(e2)
        vertex_adjacents[e2].append(e1)


    # Data Structure B
    all_edges = []
    for e1,e2 in edges:
        all_edges.append((e1, e2))
        all_edges.append((e2, e1))

    # Data Structure C
    edge_2_polygon = {}
    for e1, e2 in edges:
        unique_edge = (min(e1, e2), max(e1, e2))
        edge_2_polygon[unique_edge] = []
    
    return vertex_adjacents, all_edges, edge_2_polygon

def DFS(polygon, seen, vertices, edge_2_polygon):
    def get_line(edge):
        v1 = vertices[edge[0]]
        v2 = vertices[edge[1]]
        v1x, v1y = v1
        v2x, v2y = v2
        
        if (v2x - v1x) == 0:
            m = None
            b = v2x
        else:
            m = (v2y - v1y) / (v2x - v1x)
            b = v1y - (v1x * m)
        return m,b
        
    poly_list = [polygon.create_FoldingPolygon(vertices)]
    seen.add(polygon.unique_id)
    
    neighbors = polygon.compute_neighbors(edge_2_polygon)
    for edge in neighbors:
        other_poly = neighbors[edge]
        if other_poly.unique_id in seen: continue
        
        m, b = get_line(edge)
        all_polys = DFS(neighbors[edge], seen, vertices, edge_2_polygon)
        for folding_poly in all_polys:
            folding_poly.fold(m,b)
            poly_list.append(folding_poly)
        
    return poly_list


def fold(path):
    fold_file = open(path)
    data = json.load(fold_file)


    vertices = data['vertices_coords']
    edges = data['edges_vertices']



    vertex_adjacents, all_edges, edge_2_polygon = get_datastructures(data)
    all_polygons = []

    while all_edges:
        polygon_vertices = []
        prev_edge = all_edges[0] # will be popped within the next while loop
        
        v_prev, v_curr = prev_edge
        polygon_vertices.append(v_prev)
        all_edges.remove((v_prev, v_curr))
        polygon_valid = True
        
        while v_curr != polygon_vertices[0]:
            polygon_vertices.append(v_curr)
    #         print(v_prev, v_curr)
            # get next vertex by math
            prev_angle = get_intervertex_angle(v_curr, v_prev, data)
            best_candidate_angle = float('inf')
            best_candidate = -1
            for v_candidate in vertex_adjacents[v_curr]:
                if v_candidate == v_prev: continue
                
                candidate_angle = get_intervertex_angle(v_curr, v_candidate, data) - prev_angle
                if candidate_angle < 0: candidate_angle += 360
                
                if candidate_angle < best_candidate_angle:
                    best_candidate_angle = candidate_angle
                    best_candidate = v_candidate
            
            if (best_candidate_angle >= 180):
                polygon_valid = False
                break
                
            ac_assert((best_candidate != -1), 'Could not find valid next vertex')
            v_next = best_candidate
            
            
            # remove next edge from all_edges
            ac_assert(((v_curr, v_next) in all_edges), 'Unique next edge invariant failed - could not find next edge in all_edges')
            all_edges.remove((v_curr, v_next))
            
            
            # update v_start and v_end
            v_prev = v_curr
            v_curr = v_next

        if polygon_valid == False:
            continue

        polygon = Polygon(polygon_vertices)
        # update edge_2_polygon for all edges
        for edge in polygon.get_edges():
            edge_2_polygon[edge].append(polygon)
        
        all_polygons.append(polygon)

    folded_form = DFS(all_polygons[0], set(), vertices, edge_2_polygon)
    return folded_form


def main():
    # folded_form = fold('../FOLD_examples/diagonal.fold')
    folded_form = fold('../FOLD_examples/crane.fold')

    # turning off clear_vis will randomly shift every polygon by a small amount
    # this helps visualize polygons that have overlapping edges 
    # which makes it easier to see different layers of the folded form
    run_visualization(folded_form, clear_vis=True)

if __name__ == '__main__':
    main()


