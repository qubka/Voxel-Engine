#ifndef VOX_VERTEX_H
#define VOX_VERTEX_H

struct Vertex {
    glm::vec3 position{};
    glm::vec3 normal{};
    glm::vec2 uv{};

    Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& uv);
};

#endif //VOX_VERTEX_H
