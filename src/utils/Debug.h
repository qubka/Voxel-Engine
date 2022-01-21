#ifndef VOX_DEBUG_H
#define VOX_DEBUG_H

class Text;
class Frustum;

class Debug {
public:
    static void drawRay(const glm::vec3& start, const glm::vec3& dir, float duration = 0.0f);
    static void drawLine(const glm::vec3& start, const glm::vec3& end, float duration = 0.0f);
    static void drawQuad(const glm::vec2& min, const glm::vec2& max, float z = 0.0f, float duration = 0.0f);
    static void drawFrustum(const Frustum& frustum, float duration = 0.0f);

    static entt::entity createString(const std::string& text, float x, float y, float scale, const glm::vec4& color);

    //static void Error(const std::string& message);
    //static void Console(const std::string& message);
};

#endif //VOX_DEBUG_H
