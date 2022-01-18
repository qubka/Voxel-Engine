#include "Ray.h"

glm::vec3 Ray::getPoint(float distance) const {
    return origin + direction * distance;
}
