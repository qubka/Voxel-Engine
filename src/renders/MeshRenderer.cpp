#include "MeshRenderer.h"
#include "../Scene.h"
#include "../Game.h"
#include "../graphics/Mesh.h"
#include "../graphics/ChunkMesh.h"
#include "../graphics/Camera.h"
#include "../components/Transform.h"
#include "../geometry/Frustum.h"

MeshRenderer::MeshRenderer() : shader(), texture("res/textures/blocks.png", false, true) {
    shader.createVertexShader("res/shaders/mesh.vs");
    shader.createFragmentShader("res/shaders/mesh.fs");
    shader.link();
    shader.createAllUniform("projview", "model", "diffuse0");
}

MeshRenderer::~MeshRenderer() {
}

void MeshRenderer::render(const std::unique_ptr<Scene>& scene) {
    glActiveTexture(GL_TEXTURE0);

    shader.start();
    shader.setUniform("projview", scene->camera.projview());
    shader.setUniform("diffuse0", 0);
    texture.bind();

    //shader->setUniform("u_gamma", 1.6f);
    //shader->setUniform("u_skyLightColor", glm::vec3(1.8f));
    //shader->setUniform("u_fogColor", glm::vec3(0.7f,0.85f,1.0f));

    //Frustum frustum { scene->camera.projview() };

    auto entities = scene->registry.view<const ChunkMesh, const Transform>();

    drawCalls = 0;
    totalCalls = 0;
    totalVertices = 0;

    for (auto [entity, mesh, transform] : entities.each()) {
        shader.setUniform("model", transform());
        mesh.draw(shader);

        drawCalls++;
        totalCalls++;
        totalVertices += mesh.vertices.size();
    }

    texture.unbind();
    shader.stop();
}
