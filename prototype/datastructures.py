from helpers import *


class Polygon:
    def __init__(self, vertex_indices):
        self.vertex_indices = vertex_indices
        self.vertex_coordinates = None
    
    def unique_id(self):
        return str(self.vertex_indices)
        
    def get_edges(self):
        ac_assert((len(self.vertex_indices) >= 3), 'not enough vertices')
        edges = []
        for i in range(len(self.vertex_indices) - 1):
            v1 = self.vertex_indices[i]
            v2 = self.vertex_indices[i+1]
            edges.append((min(v1, v2), max(v1, v2)))
        
        v1 = self.vertex_indices[-1]
        v2 = self.vertex_indices[0]
        edges.append((min(v1, v2), max(v1, v2)))
        return edges
    
    def get_vertex_coordinates(self, vertices, save=False):
        vertex_coordinates = []
        for vertex_i in self.vertex_indices:
            vertex_coordinates.append(vertices[vertex_i])
        
        if save:
            self.vertex_coordinates = vertex_coordinates
            
        return vertex_coordinates
    
    def compute_neighbors(self, edge_2_polygon):
        neighbors = {}
        for edge in self.get_edges():
            ac_assert((len(edge_2_polygon[edge]) <= 2), 'too many polygons along this edge')
            for other in edge_2_polygon[edge]:
                if other != self:
                    neighbors[edge] = other
        return neighbors
    
    def create_FoldingPolygon(self, vertices):
        return FoldingPolygon(self.get_vertex_coordinates(vertices))


class FoldingPolygon:
    def __init__(self, vertices):
        self.vertices = vertices
    def fold(self, m, b):
        def reflect(m, b, point):
            px, py = point
            
            # reflection across a vertical line
            if m is None:
                new_px = b - (px - b)
                new_py = py
                return new_px, new_py
            
            # all other cases
            else:
                py -= b

                new_px = ((1 - m**2)*px + (2*m)*py) / (1 + m**2)
                new_py = ((2*m)*px + (m**2 - 1)*py) / (1 + m**2)

                new_py += b
                return (new_px, new_py)
            
        for i in range(len(self.vertices)):
            new_vertex = reflect(m, b, self.vertices[i])
            self.vertices[i] = new_vertex