#include "Chunk.h"

Chunk::Chunk(const glm::ivec2& pos) : pos(pos) {
    for (int y = 0; y < CHUNK_H; y++) {
        for (int z = 0; z < CHUNK_D; z++) {
            for (int x = 0; x < CHUNK_W; x++) {
                int realX = x + pos.x * CHUNK_W;
                //int realY = y + pos.y * CHUNK_H;
                //int realZ = z + pos.z * CHUNK_D;
                int id = y <= (glm::sin(realX * 0.1f) * 0.5f + 0.5f) * 10;
                if (y <= 2)
                    id = 2;
                voxels[(y * CHUNK_D + z) * CHUNK_W + x].id = id;
            }
        }
    }
}