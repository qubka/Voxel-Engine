#ifndef VOX_SCENE_H
#define VOX_SCENE_H

#include "utils/ProcessInfo.h"

class Camera;
class Entity;
class World;

class Scene {
public:
    entt::registry registry;
    std::shared_ptr<Camera> camera;
    std::unique_ptr<World> world;

    ProcessInfo info;

    entt::entity infoText;

    Scene();
    ~Scene();

    void init();
    void update();
};
#endif //VOX_SCENE_H
