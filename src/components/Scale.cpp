#include "Scale.h"

glm::vec3& Scale::operator()() {
    return scale;
}

const glm::vec3& Scale::operator()() const {
    return scale;
}
