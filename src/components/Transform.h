#ifndef VOX_TRANSFORM_H
#define VOX_TRANSFORM_H

struct Transform {
    glm::mat4 transform{1};

    glm::mat4& operator()();
    const glm::mat4& operator()() const;
};

#endif //VOX_TRANSFORM_H
