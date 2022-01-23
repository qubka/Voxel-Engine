#ifndef VOX_TERRAIN_H
#define VOX_TERRAIN_H

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/geometries/register/point.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

BOOST_GEOMETRY_REGISTER_POINT_2D(glm::ivec2, int, bg::cs::cartesian, x, y)

class Scene;

#include "Chunk.h"
#include "Block.h"

class Terrain {
public:
    bgi::rtree<std::pair<glm::ivec2, entt::entity>, bgi::rstar<8>> rtree;
    std::unordered_map<glm::ivec2, entt::entity> chunks;
    std::vector<entt::entity> visibles;
    std::vector<Block> blocks;
    Scene* scene;

    Terrain(Scene* scene);
    ~Terrain();

    constexpr static const int maxViewDst = 32;
    static constexpr int chunksVisibleInViewDst = maxViewDst / CHUNK_W;

    void update();

    //Voxel& get(int x, int y, int z);
    //void set(int x, int y, int z, int id);
    //Chunk& getChunk(int x, int y, int z);
    //Voxel& rayCast(glm::vec3 a, glm::vec3 dir, float maxDist, glm::vec3& end, glm::vec3& norm, glm::vec3& iend);
};

#endif //VOX_TERRAIN_H
