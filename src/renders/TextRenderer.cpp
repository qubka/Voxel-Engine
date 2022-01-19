#include "TextRenderer.h"
#include "../Scene.h"
#include "../window/Window.h"

#include <ft2build.h>
#include FT_FREETYPE_H

TextRenderer::TextRenderer() : shader(), text() {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        BOOST_LOG_TRIVIAL(error) << "Failed to init FreeType";
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, "res/fonts/arial.ttf", 0, &face)) {
        BOOST_LOG_TRIVIAL(error) << "Failed to load font: " << "res/fonts/arial.ttf";
        return;
    }

    shader.createVertexShader("res/shaders/text.vs");
    shader.createFragmentShader("res/shaders/text.fs");
    shader.link();
    shader.createAllUniform("projection", "color", "texture");

    /* Create texture atlasses for several font sizes */
    a48 = std::make_unique<Font>(face, 48);
    a24 = std::make_unique<Font>(face, 24);
    a12 = std::make_unique<Font>(face, 12);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

TextRenderer::~TextRenderer() {

}

void TextRenderer::renderText(const std::string& t, float x, float y, float scale, const glm::vec4& color) {
    shader.start();
    shader.setUniform("color", color);
    shader.setUniform("texture", 0);
    shader.setUniform("projection", glm::ortho(0.0f, Window::width, 0.0f, Window::height));

    text.draw(a24, t, x, y, scale);

    shader.stop();
}
