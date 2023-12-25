#ifndef FOLD_UTILS_H
#define FOLD_UTILS_H

#include "storage_objects.h"

double get_intervertex_angle(point_t v1, point_t v2) {
    double dx = v2.x - v1.x;
    double dy = v2.y - v1.y;
    double theta = 0;

    if (dx == 0) {
        if (dy > 0) theta = M_PI * 1/2;
        else theta = M_PI * 3/2;

    } else {
        theta = atan(dy / dx);
        if (dx < 0) {
            theta += M_PI;
        }
        if (theta < 0) {
            theta += 2 * M_PI;
        }
    }

    return (theta * 180 / M_PI);
}


#endif