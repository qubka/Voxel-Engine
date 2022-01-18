#include "Plane.h"

Plane::Plane(const glm::vec3& n, const glm::vec3& p) : normal(glm::normalize(n)), distance(-glm::dot(normal, p)) {
}

Plane::Plane(const glm::vec3& n, float d) : normal(glm::normalize(n)), distance(d) {
}

Plane::Plane(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) : normal(glm::normalize(glm::cross(b - a, c - a))), distance(-glm::dot(normal, a)) {
}

void Plane::translate(const glm::vec3& translation) {
    distance += glm::dot(normal, translation);
}

/*Plane Plane::translate(Plane& plane, const glm::vec3& translation) {
    return { plane.normal, plane.distance += glm::dot(plane.normal, translation) };
}*/

void Plane::setNormalAndPosition(const glm::vec3& n, const glm::vec3& p) {
    normal = glm::normalize(n);
    distance = -glm::dot(normal, p);
}

void Plane::set3Points(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) {
    normal = glm::normalize(glm::cross(b - a, c - a));
    distance = -glm::dot(normal, a);
}

void Plane::flip() {
    normal = -normal;
    distance = -distance;
}

Plane Plane::flipped() const {
    return { -normal, -distance };
}

glm::vec3 Plane::closestPointOnPlane(const glm::vec3& point) const {
    float pointToPlaneDistance = glm::dot(normal, point) + distance;
    return point - (normal * pointToPlaneDistance);
}

float Plane::getDistanceToPoint(const glm::vec3& point) const {
    return glm::dot(normal, point) + distance;
}

bool Plane::getSide(const glm::vec3& point) const {
    return glm::dot(normal, point) + distance > 0.0f;
}

bool Plane::sameSide(const glm::vec3& p0, const glm::vec3& p1) const {
    float d0 = getDistanceToPoint(p0);
    float d1 = getDistanceToPoint(p1);
    return (d0 >  0.0f && d1 >  0.0f) || (d0 <= 0.0f && d1 <= 0.0f);
}

bool Plane::rayCast(const Ray& ray, float& enter) const {
    float vdot = glm::dot(ray.direction, normal);
    float ndot = -glm::dot(ray.origin, normal) - distance;

    if (std::abs(vdot) < FLT_EPSILON) {
        enter = 0.0f;
        return false;
    }

    enter = ndot / vdot;

    return enter > 0.0f;
}
