#include "Debug.h"
#include "../Game.h"
#include "../Scene.h"
#include "../renders/TextRenderer.h"
#include "../graphics/Primitive.h"
#include "../components/Destroy.h"

void Debug::drawRay(const glm::vec3& start, const glm::vec3& dir, float duration) {
    Debug::drawLine(start, start + dir, duration);
}

void Debug::drawLine(const glm::vec3& start, const glm::vec3& end, float duration) {
    auto& registry = Game::instance().defaultScene()->registry;
    auto entity = registry.create();
    registry.emplace<Primitive>(entity, std::vector<glm::vec3>{start, end}, GL_LINES);
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

    registry.emplace<Primitive>(entity, vertices, GL_LINE_LOOP); // GL_QUADS removed
    if (duration > 0.0f) {
        registry.emplace<Destroy>(entity, glfwGetTime() + duration);
    }
}

void Debug::drawString(const std::string& text, float x, float y, float scale, const glm::vec4& color) {
    auto renderer = Game::instance().defaultRenderer();
    renderer->renderText(text, x, y, scale, color);
}
