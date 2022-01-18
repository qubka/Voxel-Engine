#include "Scene.h"
#include "World.h"
#include "window/Input.h"
#include "graphics/Camera.h"

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::init() {
    //camera = std::make_shared<Camera>(5, 45, 0.1f, 1000 /*-1, 1, -1, 1*/);
    //camera->main = camera;

    world = std::make_unique<World>(this);
    world->drawGeo("res/geodata/map.geojson");
}

void Scene::update(const double& elapsed) {
    //camera->update(elapsed);
}

void Scene::input() {
    if (Input::getMouseButtonDown(0)) {
        //world->intersectObjects(camera->screenPointToRay(Input::mousePosition()));

        //auto& entityManager = EntityManager::getOrCreateManager();
        //entityManager.destroyEntity(entityManager.getAllEntities()[0]);
        //world->intersectObjects(camera->screenPointToRay(Input::mousePosition()));
    }
}

void Scene::render() {
    Debug::drawString("Camera position", 0.0f, 0.0f, 1.0f, glm::vec3(1, 1, 1));
    Debug::drawString("Camera position", 5.0f, 5.0f, 1.0f, glm::vec3(1, 1, 1));
    Debug::drawString("Camera position", 300.0f, 200.0f, 1.0f, glm::vec3(1, 1, 1));
    //Debug::drawString("Camera position: " + glm::to_string(camera->position()), 0.0f, 0.0f, 1.0f, glm::vec3(1, 1, 1));
}
