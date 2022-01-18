#ifndef VOX_FONT_H
#define VOX_FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H

class Glyph;

struct Font {
    GLuint textureId;
    int width;
    int height;
    std::map<unsigned char, Glyph> glyphs;

    Font(const FT_Face& face, int size);
    ~Font();

private:
    const static int MAX_WIDTH = 4096;
};

#endif //VOX_FONT_H
