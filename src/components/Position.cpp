#include "Position.h"

glm::vec3& Position::operator()() {
    return position;
}

const glm::vec3& Position::operator()() const {
    return position;
}
