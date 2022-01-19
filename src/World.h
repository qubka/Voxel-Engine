#ifndef VOX_WORLD_H
#define VOX_WORLD_H

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

#include <rapidjson/document.h>

#include "geometry/Plane.h"

namespace delaunator {
    class Delaunator;
}

namespace geo = boost::geometry;

class Scene;
class Texture;
class Mesh;
class Ray;

class World {
    typedef rapidjson::GenericValue<rapidjson::UTF8<>> value;
    typedef geo::model::point<float, 2, geo::cs::geographic<geo::degree>> point;
    typedef geo::model::box<point> box;
    typedef boost::tuple<box, entt::entity, uint32_t> data;

    Scene* scene;
    std::vector<glm::vec2> values;
    geo::index::rtree<data, geo::index::quadratic<16>> rtree;
    Plane plane;

    const int TRIANGULATION_DENSITY = 5;
    static rapidjson::Document readJsonDocument(const std::filesystem::path& path);

    void processGeometry(const value& properties, const value& geometries);
    void convertCoordinates(const value& coordinates);
    void convertCoordinates(double lon, double lat);
    std::vector<double> genInnerVerts(const value& points);
    void removeOuterTriangles(const value& points, delaunator::Delaunator& delaunator);
    bool isInsidePolygon(const value& points, const glm::dvec2& pos);
    bool isInsideTriangle(const Mesh& mesh, uint32_t index, const glm::vec2& pos);

    struct Properties {
        std::string id;
        std::string name;
        explicit Properties(const value& properties);
    };

    void createMesh(const Properties& properties, const std::vector<size_t>& triangles);
    void createParticle();
    void createLine();
public:
    explicit World(Scene* scene);
    ~World();

    void drawGeo(const std::filesystem::path& path);
    std::optional<entt::entity> intersectObjects(const Ray& ray);
};

#endif //VOX_WORLD_H
