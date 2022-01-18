#ifndef VOX_TRANSFORMSYSTEM_H
#define VOX_TRANSFORMSYSTEM_H

#include "../System.h"

class TransformSystem : public System {
    void input() override {}
    void update(const std::unique_ptr<Scene>& scene) override;
};

#endif //VOX_TRANSFORMSYSTEM_H
