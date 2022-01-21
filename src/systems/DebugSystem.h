#ifndef VOX_DEBUGSYSTEM_H
#define VOX_DEBUGSYSTEM_H

#include "../System.h"

class DebugSystem : public System {
    void update(const std::unique_ptr<Scene>& scene) override;
};

#endif //VOX_DEBUGSYSTEM_H
