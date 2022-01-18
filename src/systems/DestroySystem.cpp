#include "DestroySystem.h"
#include "../Scene.h"
#include "../components/Destroy.h"

void DestroySystem::update(const std::unique_ptr<Scene>& scene) {
    auto entities = scene->registry.view<const Destroy>();

    auto time = static_cast<float>(glfwGetTime());

    for (auto [entity, destroy] : entities.each()) {
        if (time > destroy.time) {
            scene->registry.destroy(entity);
        }
    }
}
