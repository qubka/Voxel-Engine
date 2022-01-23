#ifndef VOX_RENDERER_H
#define VOX_RENDERER_H

class Scene;

class Renderer {
public:
    virtual void render(const std::unique_ptr<Scene>& scene) = 0;

    static size_t drawCalls;
    static size_t totalCalls;
    static size_t totalVertices;
};

#endif //VOX_RENDERER_H
