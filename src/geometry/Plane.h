#ifndef VOX_PLANE_H
#define VOX_PLANE_H

// https://github.com/Unity-Technologies/UnityCsReference/tree/master/Runtime/Export/Geometry

#include "Ray.h"

struct Plane {
    glm::vec3 normal;
    float distance;

    Plane(const glm::vec3& normal, const glm::vec3& point);
    Plane(const glm::vec3& normal, float distance);
    Plane(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);

    void translate(const glm::vec3& translation);
    //static Plane translate(Plane& plane, const glm::vec3& translation);
    void setNormalAndPosition(const glm::vec3& normal, const glm::vec3& point);
    void set3Points(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
    void flip();
    [[nodiscard]] Plane flipped() const;
    [[nodiscard]] glm::vec3 closestPointOnPlane(const glm::vec3& point) const;
    [[nodiscard]] float getDistanceToPoint(const glm::vec3& point) const;
    [[nodiscard]] bool getSide(const glm::vec3& point) const;
    [[nodiscard]] bool sameSide(const glm::vec3& p0, const glm::vec3& p1) const;
    bool rayCast(const Ray& ray, float& enter) const;
};

#endif //VOX_PLANE_H