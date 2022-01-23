#include "World.h"
#include "Game.h"
#include "Scene.h"

#include "graphics/Model.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "graphics/Mesh.h"
#include "graphics/Vertex.h"

#include "geometry/Ray.h"
#include "geometry/Geometry.h"

#include "components/Transform.h"
#include "components/Tag.h"

#include "delaunator.hpp"
#include "geometry/Sphere.h"

World::World(Scene* scene) : scene(scene), plane(vec3::forward, vec3::zero) {
}

World::~World() {
}

void World::drawGeo(const std::filesystem::path& path) {
    auto json = readJsonDocument(path);

    switch (glm::hash(json["type"].GetString())) {
        case glm::hash("Feature"): {
            processGeometry(json["properties"], json["geometry"]);
            break;
        }

        case glm::hash("FeatureCollection"):
            for (const auto& feature : json["features"].GetArray()) {
                processGeometry(feature["properties"], feature["geometry"]);
            }
            break;

        case glm::hash("GeometryCollection"):
            for (const auto& geometry: json["geometries"].GetArray()) {
                processGeometry(geometry["properties"], geometry["geometry"]);
            }
            break;

        default:
            BOOST_LOG_TRIVIAL(error) << "The geoJSON is not valid.";
    }

    BOOST_LOG_TRIVIAL(info) << "Complete!";
}

void World::processGeometry(const value& properties, const value& geometries) {
    Properties prop{properties};

    BOOST_LOG_TRIVIAL(info) << "Processing: " << prop.id << " - " << prop.name;

    switch(glm::hash(geometries["type"].GetString())) {
        case glm::hash("Point"):
            convertCoordinates(geometries["coordinates"]);
            createParticle();
            break;

        case glm::hash("MultiPoint"):
            for (const auto& coords : geometries["coordinates"].GetArray()) {
                convertCoordinates(coords);
                createParticle();
            }
            break;

        case glm::hash("LineString"):
            for (const auto& coords : geometries["coordinates"].GetArray()) {
                convertCoordinates(coords);
            }
            createLine();
            break;

        case glm::hash("Polygon"):
            for (const auto& coords : geometries["coordinates"].GetArray()) {
                auto refined = genInnerVerts(coords);

                delaunator::Delaunator d(refined);
                removeOuterTriangles(coords, d);

                for (size_t i = 0; i < d.coords.size(); i += 2) {
                    convertCoordinates(d.coords[i], d.coords[i+1]);
                }

                createMesh(prop, d.triangles);
            }
            break;

        case glm::hash("MultiLineString"):
            for (const auto& coords : geometries["coordinates"].GetArray()) {
                for (const auto& point : coords.GetArray()) {
                    convertCoordinates(point);
                }
                createLine();
            }
            break;

        case glm::hash("MultiPolygon"):
            for (const auto& polygon : geometries["coordinates"].GetArray()) {
                for (const auto& coords : polygon.GetArray()) {
                    auto refined = genInnerVerts(coords);
                    delaunator::Delaunator d(refined);
                    removeOuterTriangles(coords, d);

                    for (size_t i = 0; i < d.coords.size(); i += 2) {
                        convertCoordinates(d.coords[i], d.coords[i+1]);
                    }

                    createMesh(prop, d.triangles);
                }
            }
            break;

        default:
            BOOST_LOG_TRIVIAL(error) << "The geoJSON is not valid.";
    }
}

void World::convertCoordinates(const value& coordinates) {
    const auto& coords = coordinates.GetArray();
    convertCoordinates(coords[0].GetDouble(), coords[1].GetDouble());
}

void World::convertCoordinates(double lon, double lat) {
    //convert_s_t_p(lon, lat, &lon, &lat);
    values.emplace_back(lon, lat);
}

std::vector<double> World::genInnerVerts(const value& points) {
    std::vector<double> res;
    res.reserve(points.GetArray().Size() * 2);

    glm::dvec2 min {std::numeric_limits<double>::max()};
    glm::dvec2 max {std::numeric_limits<double>::lowest()};

    for (const auto& point : points.GetArray()) {
        const auto& p = point.GetArray();
        double p0 = p[0].GetDouble();
        double p1 = p[1].GetDouble();

        res.push_back(p0);
        res.push_back(p1);

        if (p0 < min.x) {
            min.x = p0;
        }
        if (p0 > max.x) {
            max.x = p0;
        }
        if (p1 < min.y) {
            min.y = p1;
        }
        if (p1 > max.y) {
            max.y = p1;
        }
    }

    const int& step = TRIANGULATION_DENSITY;
    for (int x = min.x + step / 2; x < max.x; x += step) {
        for (int y = min.y + step / 2; y < max.y; y += step) {
            glm::dvec2 p{x, y};
            if (isInsidePolygon(points, p)) {
                res.push_back(p.x);
                res.push_back(p.y);
            }
        }
    }

    return res;
}

void World::removeOuterTriangles(const value& points, delaunator::Delaunator& delaunator) {
    std::vector<size_t> newTriangles;
    newTriangles.reserve(delaunator.triangles.size());

    for (size_t i = 0; i < delaunator.triangles.size(); i += 3) {
        const size_t& t0 = delaunator.triangles[i + 0];
        const size_t& t1 = delaunator.triangles[i + 1];
        const size_t& t2 = delaunator.triangles[i + 2];

        const double& x0 = delaunator.coords[2 * t0];
        const double& y0 = delaunator.coords[2 * t0 + 1];

        const double& x1 = delaunator.coords[2 * t1];
        const double& y1 = delaunator.coords[2 * t1 + 1];

        const double& x2 = delaunator.coords[2 * t2];
        const double& y2 = delaunator.coords[2 * t2 + 1];

        glm::dvec2 p{(x0 + x1 + x2) / 3, (y0 + y1 + y2) / 3};
        if (isInsidePolygon(points, p)) {
            newTriangles.push_back(t0);
            newTriangles.push_back(t1);
            newTriangles.push_back(t2);
        }
    }

    delaunator.triangles = newTriangles;
}

bool World::isInsidePolygon(const value& points, const glm::dvec2& pos) {
    bool inside = false;

    const auto& p = points.GetArray();
    for (size_t i = 0, j = p.Size() - 1; i < p.Size(); j = i++) {
        const auto& ai = p[i];
        const auto& aj = p[j];
        const double xi = ai[0].GetDouble(), yi = ai[1].GetDouble();
        const double xj = aj[0].GetDouble(), yj = aj[1].GetDouble();

        bool intersect = ((yi > pos.y) != (yj > pos.y)) && (pos.x < (xj - xi) * (pos.y - yi) / (yj - yi) + xi);
        if (intersect) inside = !inside;
    }

    return inside;
}

bool World::isInsideTriangle(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c, const glm::vec2& p) {
    glm::vec2 p0 {c - a};
    glm::vec2 p1 {b - a};
    glm::vec2 p2 {p - a};

    float dot00 = glm::dot(p0, p0);
    float dot01 = glm::dot(p0, p1);
    float dot02 = glm::dot(p0, p2);
    float dot11 = glm::dot(p1, p1);
    float dot12 = glm::dot(p1, p2);

    float invDen = 1 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDen;
    float v = (dot00 * dot12 - dot01 * dot02) * invDen;

    return (u >= 0) && (v >= 0) && (u + v < 1);
}

rapidjson::Document World::readJsonDocument(const std::filesystem::path& path) {
    std::ifstream file(path);
    if(!file.is_open()) {
        BOOST_LOG_TRIVIAL(error) << "Unable to open json: " << path;
    }

    std::stringstream contents;
    contents << file.rdbuf();

    rapidjson::Document doc;
    doc.Parse(contents.str().c_str());  // parse the JSON from the string contents
    return doc;
}

void World::createMesh(const Properties& properties, const std::vector<size_t>& triangles) {
    std::vector<Vertex> vertices;
    vertices.reserve(values.size());
    std::vector<GLuint> indices;
    indices.reserve(triangles.size());

    auto& registry = scene->registry;
    auto entity = registry.create();

    glm::vec3 bmin{std::numeric_limits<float>::max()};
    glm::vec3 bmax{std::numeric_limits<float>::lowest()};

    for (const auto& v : values) {
        //float z = glm::perlin(v);
        auto pos = glm::vec3(v, 0);
        bmin = glm::min(bmin, pos);
        bmax = glm::max(bmax, pos);
        vertices.emplace_back(pos, glm::vec3(0), glm::vec3(0));
    }
    for (const auto& t : triangles) {
        indices.push_back(t);
    }

    for (size_t i = 0; i < triangles.size(); i += 3) {
        const auto& t0 = triangles[i + 0];
        const auto& t1 = triangles[i + 1];
        const auto& t2 = triangles[i + 2];

        const glm::vec2& p0 = values[t0];
        const glm::vec2& p1 = values[t1];
        const glm::vec2& p2 = values[t2];

        glm::vec2 min = glm::min(p0, glm::min(p1, p2));
        glm::vec2 max = glm::max(p0, glm::max(p1, p2));

        rtree.insert(boost::make_tuple(box(point(min.x, min.y), point(max.x, max.y)), entity, i));
        //Debug::drawQuad(min, max, 0.1f, 10.0f);
    }

    glm::vec3 center = 0.5f * (bmin + bmax);
    float maxDistance = glm::distance2(center, vertices[0].position);
    for (size_t i = 1; i < vertices.size(); ++i) {
        float dist = glm::distance2(center, vertices[i].position);
        if (dist > maxDistance)
            maxDistance = dist;
    }

    registry.emplace<Mesh>(entity, vertices, indices);
    registry.emplace<Transform>(entity);
    registry.emplace<Tag>(entity, properties.name);
    registry.emplace<Sphere>(entity, center, std::sqrt(maxDistance));

    values.clear();
}

void World::createParticle() {
    BOOST_LOG_TRIVIAL(error) << "Cant create particle";
}

void World::createLine() {
    BOOST_LOG_TRIVIAL(error) << "Cant create line";
}

std::optional<entt::entity> World::intersectObjects(const Ray& ray) {
    float rayDistance;
    if (plane.rayCast(ray, rayDistance)) {
        auto hit = ray.getPoint(rayDistance);
       // Debug::drawLine(ray.origin, hit, 5);

        std::vector<data> res;
        rtree.query(geo::index::nearest(point(hit.x, hit.y), 5), std::back_inserter(res));

        for (const auto& [box, entity, index] : res) {
            const auto& mesh = scene->registry.get<Mesh>(entity);

            if (isInsideTriangle(mesh[index], mesh[index+1], mesh[index+2], hit)) {
                return std::optional<entt::entity>{entity};
            }
        }
    }

    return std::nullopt;
}

/*
 * Properties extraction
 */

void removeAccented(std::string& str) {
    char *p = str.data();
    while ((*p) != 0) {
        const static char*
                //   "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ"
                tr = "AAAAAAECEEEEIIIIDNOOOOOx0UUUUYPsaaaaaaeceeeeiiiiOnooooo/0uuuuypy";
        unsigned char ch = (*p);
        if (ch >= 192) {
            (*p) = tr[ch-192];
        }
        ++p; // http://stackoverflow.com/questions/14094621/
    }
}

World::Properties::Properties(const value& properties) {
    if (properties.HasMember("GID_2")) {
        id = properties["GID_2"].GetString(); removeAccented(id);
    } else if (properties.HasMember("GID_1")) {
        id = properties["GID_1"].GetString(); removeAccented(id);
    } else if (properties.HasMember("GID_0")) {
        id = properties["GID_0"].GetString(); removeAccented(id);
    }
    if (properties.HasMember("NAME_2")) {
        name = properties["NAME_2"].GetString(); removeAccented(name);
    } else if (properties.HasMember("NAME_1")) {
        name = properties["NAME_1"].GetString(); removeAccented(name);
    } else if (properties.HasMember("NAME_0")) {
        name = properties["NAME_0"].GetString(); removeAccented(name);
    }

    textures = { std::make_shared<Texture>(rand()%256, rand()%256, rand()%256) };
}