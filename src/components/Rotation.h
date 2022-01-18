#ifndef VOX_ROTATION_H
#define VOX_ROTATION_H

struct Rotation {
    glm::quat rotation{1,0,0,0};

    glm::quat& operator()();
    const glm::quat& operator()() const;
};

#endif //VOX_ROTATION_H
