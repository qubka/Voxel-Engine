#ifndef VOX_MESHRENDERER_H
#define VOX_MESHRENDERER_H

#include "../Renderer.h"
#include "../graphics/Texture.h"
#include "../graphics/Shader.h"

class MeshRenderer : public Renderer {
private:
    Shader shader;
    Texture texture;
public:
    MeshRenderer();
    ~MeshRenderer();

    void render(const std::unique_ptr<Scene>& scene) override;
};

#endif //VOX_MESHRENDERER_H
