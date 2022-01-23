#include "Scene.h"
#include "World.h"
#include "Game.h"
#include "Time.h"
#include "Renderer.h"
#include "window/Input.h"
#include "graphics/Camera.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "window/Window.h"
#include "components/Tag.h"
#include "components/Text.h"
#include "geometry/Frustum.h"
#include "geometry/Plane.h"
#include "voxels/Chunk.h"

Scene::Scene() : info(getpid()), terrain(this), camera(20, 90, 0.1f, 100) {
    camera.position(glm::vec3(-10, 10, 1));
}

Scene::~Scene() {
}

void Scene::init() {
    //world = std::make_unique<World>(this);
    //world->drawGeo("res/geodata/nuts_rg_60m_2013_lvl_2.geojson");

    infoText = Debug::createString("", 5, -20, 1, glm::vec4(0, 0, 0, 1));
}

void Scene::update() {
    camera.update();
    terrain.update();

    //Debug::drawLine(camera.position(), camera.position() + camera.forward() * 1000.0f, 0.1f);

    const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    const int totalMemory = glxGpuTotalMemory();
    const int availMemory = glxGpuAvailMemory();

    //auto entity = world->intersectObjects(camera->screenPointToRay(Input::mousePosition()));

    registry.get<Text>(infoText)() =
            "CPU: " + std::to_string(static_cast<int>(info.getProcessCpuUsage())) + "%" + '\n' +
            "Mem: " + std::to_string(static_cast<int>(info.getProcessMemoryUsed())) + "MB" + '\n' +
            "Threads: " + std::to_string(info.getProcessThreadCount()) + '\n' + '\n' +
            "Video Mem: " + std::to_string(static_cast<int>((totalMemory - availMemory) / static_cast<float>(totalMemory) * 100)) + "% " + std::to_string((totalMemory - availMemory) / 1024) + "/" + std::to_string(totalMemory / 1024) + "MB" + '\n' +
            "Display: " + std::to_string(static_cast<int>(Window::width)) + "x" + std::to_string(static_cast<int>(Window::height)) + " (" + vendor + ")" + '\n' +
            renderer + '\n' +
            version + '\n' +
            "Calls: "  + std::to_string(Renderer::drawCalls) + "/" + std::to_string(Renderer::totalCalls) + '\n' +
            "Vertices: " + std::to_string(Renderer::totalVertices) + '\n' + '\n' +
            "FPS: " + std::to_string(Time::framesPerSecond) + '\n' +
            "XYZ: " + glm::to_string(camera.position()) + '\n' +
            "Mouse: " + glm::to_string(Input::mousePosition()) + '\n' +
            "Delta: " + glm::to_string(Input::mouseDelta());// + '\n' +
            //"Looking at: " + (entity.has_value() ? registry.get<Tag>(entity.value())() : "NA");
}
