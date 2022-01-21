#ifndef VOX_TEXTRENDERER_H
#define VOX_TEXTRENDERER_H

#include "../Renderer.h"
#include "../graphics/Shader.h"
#include "../graphics/TextMesh.h"
#include "../graphics/Font.h"

class TextRenderer : public Renderer {
private:
    Shader shader;
    TextMesh mesh;

    std::unique_ptr<Font> a48;
    std::unique_ptr<Font> a24;
    std::unique_ptr<Font> a12;
public:
    TextRenderer();
    ~TextRenderer();

    void render(const std::unique_ptr<Scene>& scene) override;
};

#endif //VOX_TEXTRENDERER_H
