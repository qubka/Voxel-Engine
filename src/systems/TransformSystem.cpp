#include "TransformSystem.h"
#include "../Scene.h"
#include "../components/Transform.h"
#include "../components/Position.h"
#include "../components/Rotation.h"
#include "../components/Scale.h"

void TransformSystem::update(const std::unique_ptr<Scene>& scene) {
    glm::mat4 m{1};

    auto entities = scene->registry.view<Transform, const Position, const Rotation, const Scale>();
    for (auto [entity, transform, position, rotation, scale] : entities.each()) {
        glm::mat4 p = glm::translate(m, position());
        glm::mat4 r = glm::mat4_cast(rotation());
        glm::mat4 s = glm::scale(m, scale());
        transform() = p * r * s;
    }
}
