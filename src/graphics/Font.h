#ifndef VOX_FONT_H
#define VOX_FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H

class Glyph;

class Font {
private:
    GLuint textureId;
    const int NUM_GLYPHS = 128;
public:
    int width;
    int height;
    int metrics;
    std::map<unsigned char, Glyph> glyphs;

    Font(const FT_Face& face, int size);
    ~Font();

    void bind() const;
    void unbind() const;
};

#endif //VOX_FONT_H
