#ifndef VOX_RAY_H
#define VOX_RAY_H

struct Ray {
    const glm::vec3 origin;
    const glm::vec3 direction;

    [[nodiscard]] glm::vec3 getPoint(float distance) const;
};

#endif //VOX_RAY_H
