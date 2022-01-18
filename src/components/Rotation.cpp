#include "Rotation.h"

glm::quat& Rotation::operator()() {
    return rotation;
}

const glm::quat& Rotation::operator()() const {
    return rotation;
}
