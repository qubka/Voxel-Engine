#ifndef VOX_MESH_H
#define VOX_MESH_H

#include "Vertex.h"

class Shader;
class Model;
class MeshRenderer;

class Mesh {
    GLuint vao, vbo, ebo;

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
    ~Mesh();

    void draw(const Shader& shader) const;

    const glm::vec3& operator[](size_t i) const;

    friend Model;
    friend MeshRenderer;
};

#endif //VOX_MESH_H
