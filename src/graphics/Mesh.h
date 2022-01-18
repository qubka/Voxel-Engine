#ifndef VOX_MESH_H
#define VOX_MESH_H

#include "Vertex.h"

class Shader;
class Texture;

class Mesh {
    GLuint vao, vbo, ebo;
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<std::shared_ptr<Texture>> textures);
    ~Mesh();
    void draw(const Shader& shader) const;
};

#endif //VOX_MESH_H
