#include "Terrain.h"
#include "../Scene.h"
#include "../graphics/Camera.h"
#include "../components/Transform.h"
#include "../components/Visibility.h"
#include "../geometry/AABB.h"
#include "../components/Position.h"
#include "../graphics/Vertex.h"
#include "../graphics/ChunkMesh.h"

Terrain::Terrain(Scene* scene) : scene(scene) {
    // AIR
    Block block = Block(0,0);
    block.drawGroup = 1;
    block.lightPassing = true;
    block.obstacle = false;
    blocks.push_back(block);

    // STONE
    block = Block(1,2);
    blocks.push_back(block);

    // GRASS
    block = Block(2,4);
    block.textureFaces[2] = 2;
    block.textureFaces[3] = 1;
    blocks.push_back(block);

    // LAMP
    block = Block(3,3);
    block.emission[0] = 15;
    block.emission[1] = 14;
    block.emission[2] = 13;
    blocks.push_back(block);

    // GLASS
    block = Block(4,5);
    block.drawGroup = 2;
    block.lightPassing = true;
    blocks.push_back(block);

    // PLANKS
    block = Block(5,6);
    blocks.push_back(block);
}

Terrain::~Terrain() {
}

void Terrain::update() {
    auto& registry = scene->registry;

    for (const auto& entity : visibles) {
        registry.get<Visibility>(entity)() = false;
    }
    visibles.clear();

    const glm::vec3& viewerPosition = scene->camera.position();
    const glm::ivec2 currentChunk {
            std::round(viewerPosition.x / CHUNK_W),
            std::round(viewerPosition.z / CHUNK_D)
    };

    for (int x = -chunksVisibleInViewDst; x <= chunksVisibleInViewDst; x++) {
        for (int y = -chunksVisibleInViewDst; y <= chunksVisibleInViewDst; y++) {
            glm::ivec2 viewedChunk {currentChunk.x + x, currentChunk.y + y};

            if (auto it { chunks.find(viewedChunk) }; it != chunks.end()) {
                auto entity = it->second;

                //float viewerDstFromNearestEdge = registry.get<AABB>(entity).getDistanceToClosestPoint(viewerPosition);
                float viewerDstFromNearestEdge = glm::distance(registry.get<Position>(entity)(), viewerPosition);
                bool visible = viewerDstFromNearestEdge <= maxViewDst;
                registry.get<Visibility>(entity)() = visible;

                if (visible) {
                    visibles.push_back(entity);
                } else {
                    /*registry.destroy(entity);
                    chunks.erase(viewedChunk);
                    rtree.remove(std::make_pair(viewedChunk, entity));*/
                }

            } else {
                auto entity = registry.create();

                glm::vec3 position = glm::vec3(viewedChunk.x * CHUNK_W, 0, viewedChunk.y * CHUNK_D);

                registry.emplace<Transform>(entity, glm::translate(glm::mat4(1), position));
                registry.emplace<Position>(entity, position);
                registry.emplace<Chunk>(entity, viewedChunk);
                registry.emplace<ChunkMesh>(entity);
                registry.emplace<Visibility>(entity, false);

                //glm::vec3 halfSize = glm::vec3(CHUNK_W * 0.5f, 0, CHUNK_D * 0.5f);
                //registry.emplace<AABB>(entity, position - halfSize, position + halfSize);

                chunks.emplace(viewedChunk, entity);
                rtree.insert(std::make_pair(viewedChunk, entity));

                std::cout << "Create at " << glm::to_string(position) << std::endl;
            }
        }
    }

    std::cout << "visibles: " << visibles.size() << std::endl;
}