#ifndef VOX_DEBUG_H
#define VOX_DEBUG_H

struct Debug {
    static void drawRay(const glm::vec3& start, const glm::vec3& dir, float duration = 0.0f);
    static void drawLine(const glm::vec3& start, const glm::vec3& end, float duration = 0.0f);
    static void drawQuad(const glm::vec2& min, const glm::vec2& max, float z = 0.0f, float duration = 0.0f);
    static void drawString(const std::string& text, float x, float y, float scale, const glm::vec3& color);
    //drawSphere

    //static void Error(const std::string& message);
    //static void Console(const std::string& message);
};

#endif //VOX_DEBUG_H
