#include "Game.h"

#include "window/Window.h"
#include "window/Input.h"

#include "Scene.h"
#include "Renderer.h"
#include "System.h"
#include "Time.h"

#include "renders/MeshRenderer.h"
#include "renders/PrimitiveRenderer.h"
#include "renders/TextRenderer.h"

#include "systems/TransformSystem.h"
#include "systems/DestroySystem.h"
#include "systems/CullingSystem.h"
#include "systems/ChunkSystem.h"

Game::Game() {
}

void Game::init() {
    Window::init(1280, 720, "Vox", true);
    Input::init();

    // Create renders
    renders.push_back(std::make_shared<MeshRenderer>());
    renders.push_back(std::make_shared<PrimitiveRenderer>());
    renders.push_back(std::make_shared<TextRenderer>());

    // Create systems
    systems.push_back(std::make_shared<TransformSystem>());
    systems.push_back(std::make_shared<CullingSystem>());
    systems.push_back(std::make_shared<ChunkSystem>());
    systems.push_back(std::make_shared<DestroySystem>());

    scene = std::make_unique<Scene>();
    scene->init();
}

Game::~Game() {
    Window::terminate();
}

void Game::run() {
    Time::init();

    while (!Window::isShouldClose()) {
        update();
        render();
    }
}

void Game::update() {
    Time::update();

    if (Input::getKeyDown(GLFW_KEY_ESCAPE)) {
        Window::setShouldClose(true);
    }

    if (Input::getKeyDown(GLFW_KEY_TAB)) {
        Window::toggleCursor();
    }

    if (Input::getKeyDown(GLFW_KEY_GRAVE_ACCENT)) {
        Window::toggleWireframe();
    }

    scene->update();

    for (const auto& system : systems) {
        system->update(scene);
    }
}

void Game::render() {
    Window::clear();

    if (!Window::minimized) {
        for (const auto& renderer : renders) {
            renderer->render(scene);
        }
    }

    Input::update();
    Window::update();
}

const std::unique_ptr<Scene>& Game::defaultScene() {
    return scene;
}

int main() {
    Game& game = Game::instance();
    game.init();
    game.run();
    return 0;
}