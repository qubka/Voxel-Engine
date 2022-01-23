#ifndef VOX_SCENE_H
#define VOX_SCENE_H

#include "utils/ProcessInfo.h"
#include "voxels/Terrain.h"
#include "graphics/Camera.h"

class Scene {
public:
    entt::registry registry;
    Camera camera;
    Terrain terrain;
    ProcessInfo info;
    entt::entity infoText;

    Scene();
    ~Scene();

    void init();
    void update();
};
#endif //VOX_SCENE_H
