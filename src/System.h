#ifndef VOX_SYSTEM_H
#define VOX_SYSTEM_H

class Scene;
class Game;

class System
{
    friend Game;
    virtual void update(const std::unique_ptr<Scene>& scene) = 0;
};

#endif //VOX_SYSTEM_H
