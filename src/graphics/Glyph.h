#ifndef VOX_GLYPH_H
#define VOX_GLYPH_H

struct Glyph {
    glm::vec2 advance{0};
    glm::vec2 size{0};
    glm::vec2 bearing{0};
    glm::vec2 uv{0};
};

#endif //VOX_GLYPH_H
