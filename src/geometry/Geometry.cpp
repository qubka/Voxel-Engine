#include "Geometry.h"
#include "Plane.h"

glm::vec3 Geometry::intersectionPoint(const Plane& a, const Plane& b, const Plane& c) {
    float f = -glm::dot(a.normal, glm::cross(b.normal, c.normal));

    glm::vec3 v1 = (a.distance * (glm::cross(b.normal, c.normal)));
    glm::vec3 v2 = (b.distance * (glm::cross(c.normal, a.normal)));
    glm::vec3 v3 = (c.distance * (glm::cross(a.normal, b.normal)));

    return (v1 + v2 + v3) / f;
}
