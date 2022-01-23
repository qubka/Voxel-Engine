#include "ChunkSystem.h"
#include "../Scene.h"
#include "../voxels/Chunk.h"
#include "../graphics/ChunkMesh.h"

#define SETUP_UV(INDEX) float u1 = ((INDEX) % 16) * uvsize;\
				float v1 = 1-((1 + (INDEX) / 16) * uvsize);\
				float u2 = u1 + uvsize;\
				float v2 = v1 + uvsize;

void ChunkSystem::update(const std::unique_ptr<Scene>& scene) {
    auto entities = scene->registry.view<Chunk, ChunkMesh>();

    for (auto [entity, chunk, mesh] : entities.each()) {
        if (!chunk.modified)
            continue;

        std::vector<Vertex> vertices;

        for (int y = 0; y < CHUNK_H; y++) {
            for (int z = 0; z < CHUNK_D; z++) {
                for (int x = 0; x < CHUNK_W; x++) {
                    uint8_t id = chunk.voxels[(y * CHUNK_D + z) * CHUNK_W + x].id;
                    if (!id)
                        continue;

                    static constexpr float uvsize = 1.0f / 16.0f;
                    //float u = (id % 16) * o;
                    //float v = 1 - ((1 + id / 16) * o);

                    const auto& block = scene->terrain.blocks[id];

                    //scene->terrain

                    if (!isBlocked({x,y+1,z})) {
                        SETUP_UV(block.textureFaces[3]);

                        vertices.emplace_back(glm::vec3(x - 0.5f, y + 0.5f, z - 0.5f), vec3::up, glm::vec2(u2, v1));
                        vertices.emplace_back(glm::vec3(x - 0.5f, y + 0.5f, z + 0.5f), vec3::up, glm::vec2(u2, v2));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f), vec3::up, glm::vec2(u1, v2));

                        vertices.emplace_back(glm::vec3(x - 0.5f, y + 0.5f, z - 0.5f), vec3::up, glm::vec2(u2, v1));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f), vec3::up, glm::vec2(u1, v2));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y + 0.5f, z - 0.5f), vec3::up, glm::vec2(u1, v1));
                    }
                    if (!isBlocked({x,y-1,z})) {
                        SETUP_UV(block.textureFaces[2]);

                        vertices.emplace_back(glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f), vec3::down, glm::vec2(u1, v1));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y - 0.5f, z + 0.5f), vec3::down, glm::vec2(u2, v2));
                        vertices.emplace_back(glm::vec3(x - 0.5f, y - 0.5f, z + 0.5f), vec3::down, glm::vec2(u1, v2));

                        vertices.emplace_back(glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f), vec3::down, glm::vec2(u1, v1));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f), vec3::down, glm::vec2(u2, v1));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y - 0.5f, z + 0.5f), vec3::down, glm::vec2(u2, v2));
                    }
                    if (!isBlocked({x+1,y,z})) {
                        SETUP_UV(block.textureFaces[1]);

                        vertices.emplace_back(glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f), vec3::right, glm::vec2(u2, v1));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y + 0.5f, z - 0.5f), vec3::right, glm::vec2(u2, v2));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f), vec3::right, glm::vec2(u1, v2));

                        vertices.emplace_back(glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f), vec3::right, glm::vec2(u2, v1));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f), vec3::right, glm::vec2(u1, v2));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y - 0.5f, z + 0.5f), vec3::right, glm::vec2(u1, v1));
                    }
                    if (!isBlocked({x-1,y,z})) {
                        SETUP_UV(block.textureFaces[0]);

                        vertices.emplace_back(glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f), vec3::left, glm::vec2(u1, v1));
                        vertices.emplace_back(glm::vec3(x - 0.5f, y + 0.5f, z + 0.5f), vec3::left, glm::vec2(u2, v2));
                        vertices.emplace_back(glm::vec3(x - 0.5f, y + 0.5f, z - 0.5f), vec3::left, glm::vec2(u1, v2));

                        vertices.emplace_back(glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f), vec3::left, glm::vec2(u1, v1));
                        vertices.emplace_back(glm::vec3(x - 0.5f, y - 0.5f, z + 0.5f), vec3::left, glm::vec2(u2, v1));
                        vertices.emplace_back(glm::vec3(x - 0.5f, y + 0.5f, z + 0.5f), vec3::left, glm::vec2(u2, v2));
                    }
                    if (!isBlocked({x,y,z+1})) {
                        SETUP_UV(block.textureFaces[5]);

                        vertices.emplace_back(glm::vec3(x - 0.5f, y - 0.5f, z + 0.5f), vec3::forward, glm::vec2(u1, v1));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f), vec3::forward, glm::vec2(u2, v2));
                        vertices.emplace_back(glm::vec3(x - 0.5f, y + 0.5f, z + 0.5f), vec3::forward, glm::vec2(u1, v2));

                        vertices.emplace_back(glm::vec3(x - 0.5f, y - 0.5f, z + 0.5f), vec3::forward, glm::vec2(u1, v1));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y - 0.5f, z + 0.5f), vec3::forward, glm::vec2(u2, v1));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f), vec3::forward, glm::vec2(u2, v2));
                    }
                    if (!isBlocked({x,y,z-1})) {
                        SETUP_UV(block.textureFaces[4]);

                        vertices.emplace_back(glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f), vec3::back, glm::vec2(u2, v1));
                        vertices.emplace_back(glm::vec3(x - 0.5f, y + 0.5f, z - 0.5f), vec3::back, glm::vec2(u2, v2));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y + 0.5f, z - 0.5f), vec3::back, glm::vec2(u1, v2));

                        vertices.emplace_back(glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f), vec3::back, glm::vec2(u2, v1));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y + 0.5f, z - 0.5f), vec3::back, glm::vec2(u1, v2));
                        vertices.emplace_back(glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f), vec3::back, glm::vec2(u1, v1));
                    }
                }
            }
        }

        mesh.reload(std::move(vertices));

        chunk.modified = false;
    }

    std::cout << std::endl;
}

bool ChunkSystem::isBlocked(const glm::ivec3& pos) {
    return false;
}
