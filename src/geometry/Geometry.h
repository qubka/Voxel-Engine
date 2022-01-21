#ifndef VOX_GEOMETRY_H
#define VOX_GEOMETRY_H

#include "Plane.h"

class Geometry {
public:
    static glm::vec3 intersectionPoint(const Plane& a, const Plane& b, const Plane& c);
};

#endif //VOX_GEOMETRY_H
