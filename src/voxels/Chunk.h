#ifndef VOX_CHUNK_H
#define VOX_CHUNK_H

#include "Voxel.h"

#define CHUNK_W 16
#define CHUNK_H 16
#define CHUNK_D 16
#define CHUNK_VOL (CHUNK_W * CHUNK_H * CHUNK_D)

struct Chunk {
    glm::ivec2 pos;
    bool modified{true};
    Voxel voxels[CHUNK_VOL]{};

    explicit Chunk(const glm::ivec2& pos);
};

#endif //VOX_CHUNK_H
