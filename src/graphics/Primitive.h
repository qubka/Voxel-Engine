#ifndef VOX_PRIMITIVE_H
#define VOX_PRIMITIVE_H

class Primitive {
    GLuint vao, vbo;
    GLuint mode;
public:
    std::vector<glm::vec3> vertices;

    Primitive(std::vector<glm::vec3> vertices, GLuint mode);
    ~Primitive();
    void draw() const;
};

#endif //VOX_PRIMITIVE_H
