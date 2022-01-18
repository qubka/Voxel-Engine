#include "Transform.h"

glm::mat4& Transform::operator()() {
    return transform;
}

const glm::mat4& Transform::operator()() const {
    return transform;
}
