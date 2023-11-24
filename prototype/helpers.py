import math


def ac_assert(statement, complaint):
    assert statement, complaint


def get_line(edge, vertices):
        v1 = vertices[edge[0]]
        v2 = vertices[edge[1]]
        v1x, v1y = v1
        v2x, v2y = v2

        m = (v2y - v1y) / (v2x - v1x)
        b = v1y - (v1x * m)
        return m,b

def get_intervertex_angle(v1, v2, data):
    vertices = data['vertices_coords']
    # assumes v1 != v2
    # get counter-clockwise angle (of v1 -> v2) starting from 0
    v1x, v1y = vertices[v1]
    v2x, v2y = vertices[v2]
    
    dx = v2x - v1x
    dy = v2y - v1y
    theta = 0
    if dx == 0:
        if dy > 0: theta = math.pi * 1/2
        else: theta = math.pi * 3/2
    else:
        theta = math.atan(dy / dx)
        if dx < 0:
            theta += math.pi
        if theta < 0:
            theta += 2 * math.pi
    
    to_degrees = lambda x: x * 180 / math.pi
    return to_degrees(theta)