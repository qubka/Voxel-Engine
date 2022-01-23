#ifndef VOX_FONT_H
#define VOX_FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H

class Glyph;
class TextMesh;

class Font {
private:
    GLuint textureId;
    int width;
    int height;
    int metrics;
    std::map<unsigned char, Glyph> glyphs;

public:
    Font(const FT_Face& face, int size);
    ~Font();

    void bind() const;
    void unbind() const;

    friend TextMesh;
};

#endif //VOX_FONT_H
