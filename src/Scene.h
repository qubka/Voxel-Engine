#ifndef VOX_SCENE_H
#define VOX_SCENE_H

class Camera;
class Entity;
class World;

class Scene {
public:
    entt::registry registry;
    std::shared_ptr<Camera> camera;
    std::unique_ptr<World> world;

    Scene();
    ~Scene();

    void init();
    void input();
    void update(const double& elapsed);
    void render();
};
#endif //VOX_SCENE_H
