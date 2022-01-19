#include "Scene.h"
#include "World.h"
#include "window/Input.h"
#include "graphics/Camera.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "window/Window.h"
#include "components/Tag.h"

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::init() {
    camera = std::make_shared<Camera>(5, 45, 0.1f, 1000 /*-1, 1, -1, 1*/);
    //camera->main = camera;
    camera->position(glm::vec3(0, 45, 10));

    world = std::make_unique<World>(this);
    world->drawGeo("res/geodata/map.geojson");

    //texture = std::make_shared<Texture>(255, 0, 0);
}

void Scene::update(const double& elapsed) {
    camera->update(elapsed);
}

void Scene::input() {
}

void Scene::render() {
    Debug::drawString("Camera position: " + glm::to_string(camera->position()), 5.0f, Window::height - 10.0f, 1.0f, glm::vec4(1, 1, 1, 1));
    Debug::drawString("Mouse position: " + glm::to_string(Input::mousePosition()), 5.0f, Window::height - 25.0f, 1.0f, glm::vec4(1, 1, 1, 1));

    std::string hover = "NA";
    auto ray = camera->screenPointToRay(Input::mousePosition());
    auto entity = world->intersectObjects(ray);
    if (entity.has_value()) {
        hover = registry.get<Tag>(entity.value())();
    }
    Debug::drawString("State name: " + hover, 5.0f, Window::height - 40.0f, 1.0f, glm::vec4(1, 1, 1, 1));
}
