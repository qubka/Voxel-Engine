#include "Plane.h"
#include "Ray.h"

Plane::Plane(const glm::vec3& n, const glm::vec3& p) {
    set(n, p);
}

Plane::Plane(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) {
    set(a, b, c);
}

Plane::Plane(const glm::vec4& abcd) {
    set(abcd);
}

void Plane::set(const glm::vec3& n, const glm::vec3& p) {
    if(glm::length(n) == 0.0f)
        throw std::invalid_argument("Degenerate сase exception");

    normal = glm::normalize(n);
    distance = -glm::dot(normal, p);
}

void Plane::set(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) {
    glm::vec3 n = glm::cross(b - a, c - a);

    if(glm::length(n) == 0.0f) {
        throw std::invalid_argument("Degenerate сase exception");
    }

    normal = glm::normalize(n);
    distance = -dot(normal, a);
}

void Plane::set(const glm::vec4& m) {
    auto n = glm::vec3(m);

    float length = glm::length(n);
    if (length == 0.0f) {
        throw std::invalid_argument("Degenerate сase exception");
    }

    normal = glm::normalize(n);
    distance = -m.w / length;
}

float Plane::getDistanceToPoint(const glm::vec3& point) const {
    return glm::dot(normal, point) + distance;
}

bool Plane::getSide(const glm::vec3& point) const {
    return getDistanceToPoint(point) > 0.0f;
}

bool Plane::sameSide(const glm::vec3& p0, const glm::vec3& p1) const {
    float d0 = getDistanceToPoint(p0);
    float d1 = getDistanceToPoint(p1);
    return (d0 >  0.0f && d1 >  0.0f) ||
           (d0 <= 0.0f && d1 <= 0.0f);
}

bool Plane::rayCast(const Ray& ray, float& enter) const {
    float vdot = glm::dot(ray.direction, normal);

    if (std::abs(vdot) < FLT_EPSILON) {
        enter = 0.0f;
        return false;
    }

    float ndot = -glm::dot(ray.origin, normal) - distance;

    enter = ndot / vdot;

    return enter > 0.0f;
}

std::ostream& operator<<(std::ostream &o, const Plane& p) {
    return o << "(" << glm::to_string(p.normal) << ", " << p.distance << ")";
}