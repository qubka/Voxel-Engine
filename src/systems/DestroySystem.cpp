#include "DestroySystem.h"
#include "../Scene.h"
#include "../components/Destroy.h"
#include "../Time.h"

void DestroySystem::update(const std::unique_ptr<Scene>& scene) {
    /*auto entities = scene->registry.view<const Destroy>();

    for (auto [entity, destroy] : entities.each()) {
        if (Time::time > destroy.time) {
            scene->registry.destroy(entity);
        }
    }*/
}
