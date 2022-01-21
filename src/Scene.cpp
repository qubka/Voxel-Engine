#include "Scene.h"
#include "World.h"
#include "Game.h"
#include "window/Input.h"
#include "graphics/Camera.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "window/Window.h"
#include "components/Tag.h"
#include "components/Text.h"
#include "geometry/Frustum.h"
#include "geometry/Plane.h"

Scene::Scene() : info(getpid()) {
}

Scene::~Scene() {
}

void Scene::init() {
    camera = std::make_shared<Camera>(5, 90, 0.1f, 50.0f /*-1, 1, -1, 1*/);
    //camera->main = camera;
    camera->position(glm::vec3(0, 45, 10));

    world = std::make_unique<World>(this);
    world->drawGeo("res/geodata/map.geojson");

    //texture = std::make_shared<Texture>(255, 0, 0);

    infoText = Debug::createString("", 5.0f, -20.0f, 1.0f, glm::vec4(0, 0, 0, 1));

    /*glm::vec3 nearCenter = camera->position() + camera->forward() * camera->nearClip();
    glm::vec3 farCenter = camera->position() + camera->forward() * camera->farClip();

    Debug::drawLine(nearCenter, farCenter);

    float fovRadians = glm::radians(camera->fov());
    float nearHeight = 2 * tan(fovRadians / 2) * camera->nearClip();
    float farHeight = 2 * tan(fovRadians / 2) * camera->farClip();
    float nearWidth = nearHeight * viewRatio;
    float farWidth = farHeight * viewRatio;*/
}

void Scene::update() {
    camera->update();

    const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    const int totalMemory = glxGpuTotalMemory();
    const int availMemory = glxGpuAvailMemory();

    if (Input::getKeyDown(GLFW_KEY_F)) {
        Frustum f {camera};

        Debug::drawFrustum(f, 1.0f);

        std::cout << "left: " << f.getPlane(Frustum::LEFT)  << std::endl;
        std::cout << "right: " << f.getPlane(Frustum::RIGHT)  << std::endl;
        std::cout << "top: " << f.getPlane(Frustum::TOP)  << std::endl;
        std::cout << "bottom: " << f.getPlane(Frustum::BOTTOM) << std::endl;
        std::cout << "near: " <<  f.getPlane(Frustum::NEAR) << std::endl;
        std::cout << "far: " << f.getPlane(Frustum::FAR) << " "  << std::endl;
    };

    auto entity = world->intersectObjects(camera->screenPointToRay(Input::mousePosition()));

    registry.get<Text>(infoText)() =
            "CPU: " + std::to_string(static_cast<int>(info.getProcessCPUUsage())) + "%" + '\n' +
            "Mem: " + std::to_string(static_cast<int>(info.getProcessMemoryUsed())) + "MB" + '\n' +
            "Threads: " + std::to_string(info.getProcessThreadCount()) + '\n' + '\n' +
            "Video Mem: " + std::to_string(static_cast<int>((totalMemory - availMemory) / static_cast<float>(totalMemory) * 100.0f)) + "% " + std::to_string((totalMemory - availMemory) / 1024) + "/" + std::to_string(totalMemory / 1024) + "MB" + '\n' +
            "Display: " + std::to_string(static_cast<int>(Window::width)) + "x" + std::to_string(static_cast<int>(Window::height)) + " (" + vendor + ")" + '\n' +
            renderer + '\n' +
            version + '\n' + '\n' +
            "FPS: " + std::to_string(Game::framesPerSecond) + '\n' +
            "XYZ: " + glm::to_string(camera->position()) + '\n' +
            "Mouse: " + glm::to_string(Input::mousePosition()) + '\n' +
            "Looking at: " + (entity.has_value() ? registry.get<Tag>(entity.value())() : "NA");
}
