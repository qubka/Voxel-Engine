#ifndef VOX_DESTROYSYSTEM_H
#define VOX_DESTROYSYSTEM_H

#include "../System.h"

class DestroySystem : public System {
    void input() override {}
    void update(const std::unique_ptr<Scene>& scene) override;
};

#endif //VOX_DESTROYSYSTEM_H
