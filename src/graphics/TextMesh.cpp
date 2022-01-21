#include "TextMesh.h"
#include "Glyph.h"
#include "Font.h"

TextMesh::TextMesh() {
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

TextMesh::~TextMesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void TextMesh::draw(const std::unique_ptr<Font>& font, const std::string& text, float x, float y, float scale) const {
    glBindVertexArray(vao);

    float initial = x;

    for (const auto& c : text) {
        if (c == '\n') {
            x = initial;
            y -= font->metrics;
            continue;
        }

        const auto it = font->glyphs.find(c);
        const auto& glyph = it != font->glyphs.end() ? it->second : font->glyphs.at(127);

        float px = x + glyph.bearing.x * scale;
        float py = y - (glyph.size.y - glyph.bearing.y) * scale;
        float ox = glyph.size.x / font->width;
        float oy = glyph.size.y / font->height;
        float tx = glyph.uv.x;
        float ty = glyph.uv.y;

        float w = glyph.size.x * scale;
        float h = glyph.size.y * scale;

        float vertices[6][4] = {
            {
                px,
                py + h,
                tx,
                ty
            },
            {
                px + w,
                py,
                tx + ox,
                ty + oy
            },
            {
                px,
                py,
                tx,
                ty + oy
            },
            {
                px,
                py + h,
                tx,
                ty
            },
            {
                px + w,
                py + h,
                tx + ox,
                ty
            },
            {
                px + w,
                py,
                tx + ox,
                ty + oy
            }
        };

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(glm::vec4), &vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += glyph.advance.x * scale;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

