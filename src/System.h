#ifndef VOX_SYSTEM_H
#define VOX_SYSTEM_H

class Scene;

class System
{
public:
    virtual void input() = 0;
    virtual void update(const std::unique_ptr<Scene>& scene) = 0;
};

#endif //VOX_SYSTEM_H
