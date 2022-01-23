#ifndef VOX_CULLINGSYSTEM_H
#define VOX_CULLINGSYSTEM_H

#include "../System.h"

class CullingSystem : public System {
    void update(const std::unique_ptr<Scene>& scene) override;
};

#endif //VOX_CULLINGSYSTEM_H
