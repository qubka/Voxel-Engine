#ifndef VOX_PLANE_H
#define VOX_PLANE_H

// https://github.com/Unity-Technologies/UnityCsReference/tree/master/Runtime/Export/Geometry

class Ray;

struct Plane {
    glm::vec3 normal{0};
    float distance{0};

    Plane() = default;
    Plane(const glm::vec3& normal, const glm::vec3& point);
    Plane(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
    explicit Plane(const glm::vec4& abcd);

    void set(const glm::vec3& normal, const glm::vec3& point);
    void set(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
    void set(const glm::vec4& mZ);

    float getDistanceToPoint(const glm::vec3& point) const;
    bool getSide(const glm::vec3& point) const;
    bool sameSide(const glm::vec3& p0, const glm::vec3& p1) const;
    bool rayCast(const Ray& ray, float& enter) const;
};

std::ostream& operator<<(std::ostream &o, const Plane& p);

#endif //VOX_PLANE_H