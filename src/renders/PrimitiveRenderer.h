#ifndef VOX_PRIMITIVERENDERER_H
#define VOX_PRIMITIVERENDERER_H

#include "../Renderer.h"
#include "../graphics/Texture.h"
#include "../graphics/Shader.h"

class PrimitiveRenderer : public Renderer {
private:
    Shader shader;
public:
    PrimitiveRenderer();
    ~PrimitiveRenderer();
    void render(const std::unique_ptr<Scene>& scene) override;
};

#endif //VOX_PRIMITIVERENDERER_H
