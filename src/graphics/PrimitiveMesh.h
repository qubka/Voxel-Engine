#ifndef VOX_PRIMITIVEMESH_H
#define VOX_PRIMITIVEMESH_H

class PrimitiveMesh {
    GLuint vao, vbo;
    GLuint mode;
public:
    std::vector<glm::vec3> vertices;

    PrimitiveMesh(std::vector<glm::vec3> vertices, GLuint mode);
    ~PrimitiveMesh();
    void draw() const;
};

#endif //VOX_PRIMITIVEMESH_H
