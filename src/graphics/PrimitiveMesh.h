#ifndef VOX_PRIMITIVEMESH_H
#define VOX_PRIMITIVEMESH_H

class PrimitiveRenderer;

class PrimitiveMesh {
    GLuint vao, vbo;
    GLuint mode;

    std::vector<glm::vec3> vertices;
public:
    PrimitiveMesh(std::vector<glm::vec3> vertices, GLuint mode);
    ~PrimitiveMesh();

    void draw() const;

    friend PrimitiveRenderer;
};

#endif //VOX_PRIMITIVEMESH_H
