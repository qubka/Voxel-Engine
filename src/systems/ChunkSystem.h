#ifndef VOX_CHUNKSYSTEM_H
#define VOX_CHUNKSYSTEM_H

#include "../System.h"

class ChunkSystem : public System {
    void update(const std::unique_ptr<Scene>& scene) override;

    bool isBlocked(const glm::ivec3& pos);
};

#endif //VOX_CHUNKSYSTEM_H
