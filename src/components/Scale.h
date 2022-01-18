#ifndef VOX_SCALE_H
#define VOX_SCALE_H

struct Scale {
    glm::vec3 scale{1};

    glm::vec3& operator()();
    const glm::vec3& operator()() const;
};

#endif //VOX_SCALE_H
