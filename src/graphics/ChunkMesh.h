#ifndef VOX_CHUNKMESH_H
#define VOX_CHUNKMESH_H

#include "Vertex.h"

class Shader;
class MeshRenderer;

class ChunkMesh {
    GLuint vao, vbo;

    std::vector<Vertex> vertices;
public:
    ChunkMesh();
    ~ChunkMesh();

    void draw(const Shader& shader) const;
    void reload(std::vector<Vertex>&& v);

    friend MeshRenderer;
};

#endif //VOX_CHUNKMESH_H
