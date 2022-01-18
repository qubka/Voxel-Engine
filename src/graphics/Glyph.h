#ifndef VOX_GLYPH_H
#define VOX_GLYPH_H

struct Glyph {
    glm::ivec2 advance;
    glm::ivec2 size;
    glm::ivec2 bearing;
    glm::vec2 uv;
};

#endif //VOX_GLYPH_H
