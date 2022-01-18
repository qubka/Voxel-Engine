#include "MeshRenderer.h"
#include "../Scene.h"
#include "../graphics/Mesh.h"
#include "../graphics/Camera.h"
#include "../components/Transform.h"

MeshRenderer::MeshRenderer() : shader() {
    shader.createVertexShader("res/shaders/mesh.vs");
    shader.createFragmentShader("res/shaders/mesh.fs");
    shader.link();
    shader.createAllUniform("projview", "model", "diffuse0");
}

MeshRenderer::~MeshRenderer() {
}

void MeshRenderer::render(const std::unique_ptr<Scene>& scene) {
    shader.start();
    shader.setUniform("projview", scene->camera->projview());

    //shader->setUniform("u_gamma", 1.6f);
    //shader->setUniform("u_skyLightColor", glm::vec3(1.8f));
    //shader->setUniform("u_fogColor", glm::vec3(0.7f,0.85f,1.0f));

    auto entities = scene->registry.view<const Mesh, const Transform>();

    for (auto [entity, mesh, transform] : entities.each()) {
        shader.setUniform("model", transform());
        mesh.draw(shader);
    }

    shader.stop();
}
