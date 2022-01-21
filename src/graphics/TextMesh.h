#ifndef VOX_TEXTMESH_H
#define VOX_TEXTMESH_H

class Font;

class TextMesh {
    GLuint vao, vbo;
public:
    TextMesh();
    ~TextMesh();

    void draw(const std::unique_ptr<Font>& font, const std::string& text, float x, float y, float scale) const;
};

#endif //VOX_TEXTMESH_H