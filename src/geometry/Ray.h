#ifndef VOX_RAY_H
#define VOX_RAY_H

struct Ray {
    glm::vec3 origin{0};
    glm::vec3 direction{0};

    glm::vec3 getPoint(float distance) const;
    bool triangleIntersection(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, float& result) const;
    bool planeIntersection(const glm::vec3& planeOrigin, const glm::vec3& normal, float& result) const;
};

std::ostream& operator<<(std::ostream &o, const Ray& r);

#endif //VOX_RAY_H
