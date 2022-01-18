#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

Mesh::Mesh(std::vector<Vertex> v, std::vector<GLuint> i, std::vector<std::shared_ptr<Texture>> t) : vertices(std::move(v)), indices(std::move(i)), textures(std::move(t)) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0); // offsetof(Vertex, position)

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Mesh::draw(const Shader& shader) const {
    unsigned char diffuseNr = 0;
    unsigned char specularNr = 0;
    unsigned char normalNr = 0;
    unsigned char heightNr = 0;

    for (int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        const auto& texture = textures[i];

        std::string name;
        switch (texture->type()) {
            case aiTextureType_DIFFUSE:
                name = "diffuse" + std::to_string(diffuseNr++);
                break;
            case aiTextureType_SPECULAR:
                name = "specular" + std::to_string(specularNr++);
                break;
            case aiTextureType_NORMALS:
                name = "normal" + std::to_string(normalNr++);
                break;
            case aiTextureType_HEIGHT:
                name = "height" + std::to_string(heightNr++);
                break;
            default:
                BOOST_LOG_TRIVIAL(error) << "Unknown texture type";
                continue;
        }

        shader.setUniform(name, i);
        texture->bind();
    }

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    for (const auto& texture : textures) {
        texture->unbind();
    }
    glActiveTexture(GL_TEXTURE0);
}