#ifndef VOX_POSITION_H
#define VOX_POSITION_H

struct Position {
    glm::vec3 position{0};

    glm::vec3& operator()();
    const glm::vec3& operator()() const;
};

#endif //VOX_POSITION_H
