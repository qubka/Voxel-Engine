#include "Text.h"
#include "Glyph.h"
#include "Font.h"

Text::Text() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Text::~Text() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Text::draw(const std::unique_ptr<Font>& font, const std::string& text, float x, float y, float scale) const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, font->textureId);
    glBindVertexArray(vao);

    std::vector<glm::vec4> vertices;

    for (const auto& c : text) {
        const auto& glyph = font->glyphs.at(c);

        float x2 = x + glyph.bearing.x * scale;
        float y2 = -y - glyph.bearing.y * scale;
        float w = glyph.size.x * scale;
        float h = glyph.size.y * scale;

        vertices.emplace_back(
            x2,
            -y2,
            glyph.uv.x,
            glyph.uv.y
        );

        vertices.emplace_back(
            x2 + w,
            -y2,
            glyph.uv.x + glyph.size.x / font->width,
            glyph.uv.y
        );

        vertices.emplace_back(
            x2,
            -y2 - h,
            glyph.uv.x,
            glyph.uv.y + glyph.size.y / font->height
        );

        vertices.emplace_back(
            x2 + w,
            -y2,
            glyph.uv.x + glyph.size.x / font->width,
            glyph.uv.y
        );

        vertices.emplace_back(
            x2,
            -y2 - h,
            glyph.uv.x,
            glyph.uv.y + glyph.size.y / font->height
        );

        vertices.emplace_back(
            x2 + w,
            -y2 - h,
            glyph.uv.x + glyph.size.x / font->width,
            glyph.uv.y + glyph.size.y / font->height
        );

        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(glm::vec4), vertices.data());
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

