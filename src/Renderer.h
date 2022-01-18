#ifndef VOX_RENDERER_H
#define VOX_RENDERER_H

class Scene;

class Renderer {
public:
    virtual void render(const std::unique_ptr<Scene>& scene) = 0;
};

#endif //VOX_RENDERER_H
