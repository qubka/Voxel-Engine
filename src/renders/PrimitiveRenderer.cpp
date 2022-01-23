#include "PrimitiveRenderer.h"
#include "../Scene.h"
#include "../graphics/PrimitiveMesh.h"
#include "../graphics/Camera.h"

PrimitiveRenderer::PrimitiveRenderer() : shader() {
    shader.createVertexShader("res/shaders/primitive.vs");
    shader.createFragmentShader("res/shaders/primitive.fs");
    shader.link();
    shader.createAllUniform("projview", "color");
}

PrimitiveRenderer::~PrimitiveRenderer() {
}

void PrimitiveRenderer::render(const std::unique_ptr<Scene>& scene) {
    shader.start();
    shader.setUniform("projview", scene->camera.projview());
    shader.setUniform("color", glm::vec4(1));

    auto entities = scene->registry.view<const PrimitiveMesh>();

    for (auto [entity, mesh] : entities.each()) {
        mesh.draw();

        drawCalls++;
        totalCalls++;
        totalVertices += mesh.vertices.size();
    }

    shader.stop();
}
