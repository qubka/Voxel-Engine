#include "PrimitiveRenderer.h"
#include "../Scene.h"
#include "../graphics/Primitive.h"
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
    shader.setUniform("projview", scene->camera->projview());
    shader.setUniform("color", glm::vec4(1));

    auto entities = scene->registry.view<const Primitive>();

    for (auto [entity, object] : entities.each()) {
        object.draw();
    }

    shader.stop();
}
