#include "Ray.h"

glm::vec3 Ray::getPoint(float distance) const {
    return origin + direction * distance;
}

// algorithm from "Fast, Minimum Storage Ray-Triangle Intersection"
bool Ray::triangleIntersection(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, float& result) const {
    glm::vec3 e1 {v1 - v0};
    glm::vec3 e2 {v2 - v0};

    glm::vec3 p = glm::cross(direction, e2);
    float det = glm::dot(e1, p);

#if 0 // we don't want to backface cull
    if (det < FLT_EPSILON)
		  return false;

    glm::vec3 t {origin - v0};

	float u = glm::dot(t, p);
	if (u < 0.0f || u > det)
		return false;

    glm::vec3 q = glm::cross(t, e1);
	float v = glm::dot(direction, q);
	if (v < 0.0f || u + v > det)
		return false;

	result = glm::dot(e2, q) / det;
	return true;
#else
    if(det > -FLT_EPSILON && det < FLT_EPSILON)
        return false;

    glm::vec3 t {origin - v0};

    float invDet = 1.0f / det;

    float u = glm::dot(t, p) * invDet;
    if (u < 0.0f || u > 1.0f)
        return false;

    glm::vec3 q = glm::cross(t, e1);

    float v = glm::dot(direction, q) * invDet;
    if (v < 0.0f || u + v > 1.0f)
        return false;

    result = glm::dot(e2, q) * invDet;
    return true;
#endif
}

bool Ray::planeIntersection(const glm::vec3& planeOrigin, const glm::vec3& normal, float& result) const {
    float denominator = glm::dot(normal, direction);

    if (denominator != 0.0f) {
        result = glm::dot(normal, planeOrigin - origin) / denominator;
        return true;
    }

    return false;
}

std::ostream& operator<<(std::ostream &o, const Ray& r) {
    return o << "(" << glm::to_string(r.origin) << ", " << glm::to_string(r.direction) << ")";
}
