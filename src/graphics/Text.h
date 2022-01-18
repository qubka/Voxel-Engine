#ifndef VOX_TEXT_H
#define VOX_TEXT_H

class Font;

class Text {
    GLuint vao, vbo;
public:
    Text();
    ~Text();

    void draw(const std::unique_ptr<Font>& font, const std::string& text, float x, float y, float scale) const;
};

#endif //VOX_TEXT_H
