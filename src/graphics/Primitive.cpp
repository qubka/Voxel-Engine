#include "Primitive.h"

Primitive::Primitive(std::vector<glm::vec3> v, GLuint mode) : vertices(std::move(v)), mode(mode) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0); // offsetof(Vertex, position)

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Primitive::~Primitive() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Primitive::draw() const {
    glBindVertexArray(vao);
    glDrawArrays(mode, 0, vertices.size());
    glBindVertexArray(0);
}
