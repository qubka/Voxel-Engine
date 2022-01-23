#include "TextRenderer.h"
#include "../Scene.h"
#include "../window/Window.h"
#include "../components/Text.h"

#include <ft2build.h>
#include FT_FREETYPE_H

TextRenderer::TextRenderer() : shader(), mesh() {
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

void TextRenderer::render(const std::unique_ptr<Scene>& scene) {
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);

    shader.start();
    shader.setUniform("projection", glm::ortho(0.0f, Window::width, 0.0f, Window::height));
    shader.setUniform("texture", 0);

    a24->bind();

    auto entities = scene->registry.view<const Text>();

    for (auto [entity, text] : entities.each()) {
        shader.setUniform("color", text.color);
        mesh.draw(a24, text(), text.x < 0 ? text.x + Window::width : text.x, text.y < 0 ? text.y + Window::height : text.y, text.scale);

        drawCalls++;
        totalCalls++;

        totalVertices += 6 * sizeof(glm::vec4);
    }

    a24->unbind();

    shader.stop();

    glEnable(GL_DEPTH_TEST);
}

