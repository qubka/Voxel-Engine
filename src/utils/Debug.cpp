#include "Debug.h"
#include "../Game.h"
#include "../Scene.h"
#include "../renders/TextRenderer.h"
#include "../graphics/PrimitiveMesh.h"
#include "../components/Destroy.h"
#include "../components/Text.h"
#include "../geometry/Geometry.h"
#include "../geometry/Frustum.h"

void Debug::drawRay(const glm::vec3& start, const glm::vec3& dir, float duration) {
    Debug::drawLine(start, start + dir, duration);
}

void Debug::drawLine(const glm::vec3& start, const glm::vec3& end, float duration) {
    auto& registry = Game::instance().defaultScene()->registry;
    auto entity = registry.create();
    registry.emplace<PrimitiveMesh>(entity, std::vector<glm::vec3>{start, end}, GL_LINES);
    if (duration > 0.0f) {
        registry.emplace<Destroy>(entity, glfwGetTime() + duration);
    }
}

void Debug::drawQuad(const glm::vec2& min, const glm::vec2& max, float z, float duration) {
    auto& registry = Game::instance().defaultScene()->registry;
    auto entity = registry.create();

    std::vector<glm::vec3> vertices {
        glm::vec3(min.x, min.y, z),
        glm::vec3(min.x, max.y, z),
        glm::vec3(max.x, max.y, z),
        glm::vec3(max.x, min.y, z)
    };

    registry.emplace<PrimitiveMesh>(entity, vertices, GL_LINE_LOOP); // GL_QUADS removed
    if (duration > 0.0f) {
        registry.emplace<Destroy>(entity, glfwGetTime() + duration);
    }
}

entt::entity Debug::createString(const std::string& text, float x, float y, float scale, const glm::vec4& color) {
    auto& registry = Game::instance().defaultScene()->registry;
    auto entity = registry.create();

    registry.emplace<Text>(entity, text, x, y, scale, color);

    return entity;
}

void Debug::drawFrustum(const Frustum& f, float duration) {
    glm::vec3 n1 = Geometry::intersectionPoint(f.getPlane(Frustum::TOP), f.getPlane(Frustum::LEFT), f.getPlane(Frustum::NEAR));
    glm::vec3 n2 = Geometry::intersectionPoint(f.getPlane(Frustum::TOP), f.getPlane(Frustum::RIGHT), f.getPlane(Frustum::NEAR));
    glm::vec3 n3 = Geometry::intersectionPoint(f.getPlane(Frustum::BOTTOM), f.getPlane(Frustum::LEFT), f.getPlane(Frustum::NEAR));
    glm::vec3 n4 = Geometry::intersectionPoint(f.getPlane(Frustum::BOTTOM), f.getPlane(Frustum::RIGHT), f.getPlane(Frustum::NEAR));

    Debug::drawLine(n1, n2, duration);
    Debug::drawLine(n2, n4, duration);
    Debug::drawLine(n3, n1, duration);
    Debug::drawLine(n3, n4, duration);

    glm::vec f1 = Geometry::intersectionPoint(f.getPlane(Frustum::TOP), f.getPlane(Frustum::LEFT), f.getPlane(Frustum::FAR));
    glm::vec f2 = Geometry::intersectionPoint(f.getPlane(Frustum::TOP), f.getPlane(Frustum::RIGHT), f.getPlane(Frustum::FAR));
    glm::vec f3 = Geometry::intersectionPoint(f.getPlane(Frustum::BOTTOM), f.getPlane(Frustum::LEFT), f.getPlane(Frustum::FAR));
    glm::vec f4 = Geometry::intersectionPoint(f.getPlane(Frustum::BOTTOM), f.getPlane(Frustum::RIGHT), f.getPlane(Frustum::FAR));

    Debug::drawLine(f1, f2, duration);
    Debug::drawLine(f2, f4, duration);
    Debug::drawLine(f3, f1, duration);
    Debug::drawLine(f3, f4, duration);

    Debug::drawLine(f1, n1, duration);
    Debug::drawLine(f2, n2, duration);
    Debug::drawLine(f3, n3, duration);
    Debug::drawLine(f4, n4, duration);
}
