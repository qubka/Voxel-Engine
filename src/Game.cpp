#include "Game.h"

#include "window/Window.h"
#include "window/Input.h"

#include "Scene.h"
#include "Renderer.h"
#include "System.h"

#include "renders/MeshRenderer.h"
#include "renders/PrimitiveRenderer.h"
#include "renders/TextRenderer.h"

#include "systems/TransformSystem.h"
#include "systems/DebugSystem.h"
#include "systems/DestroySystem.h"

void Game::init() {
    Window::init(1280, 720, "Vox", false);
    Input::init();

    // Create renders
    renders.push_back(std::make_shared<TextRenderer>());
    renders.push_back(std::make_shared<MeshRenderer>());
    renders.push_back(std::make_shared<PrimitiveRenderer>());

    // Create systems
    systems.push_back(std::make_shared<TransformSystem>());
    systems.push_back(std::make_shared<DebugSystem>());
    systems.push_back(std::make_shared<DestroySystem>());

    scene = std::make_unique<Scene>();
    scene->init();
}

Game::~Game() {
    Window::terminate();
}

void Game::run() {
    double previous = glfwGetTime();
    double steps = 0.0;

    while (!Window::isShouldClose()) {
        double current = glfwGetTime();
        double elapsed = current - previous;
        previous = current;
        steps += elapsed;

        input();

        while (steps >= MS_PER_UPDATE) {
            update(elapsed);
            steps -= MS_PER_UPDATE;
        }

        render();
        sync(current);
    }
}

void Game::input() {
    if (Input::getKeyDown(GLFW_KEY_ESCAPE)) {
        Window::setShouldClose(true);
    }

    if (Input::getKeyDown(GLFW_KEY_TAB)) {
        Window::setCursorMode(Input::toggleCursor());
    }

    if (Input::getKeyDown(GLFW_KEY_GRAVE_ACCENT)) {
        Window::toogleWireframe();
    }

    scene->input();

    for (const auto& system : systems) {
        system->input();
    }
}

void Game::update(double elapsed) {
    scene->update(elapsed);

    for (const auto& system : systems) {
        system->update(scene);
    }
}

void Game::render() {
    Window::clear();

    scene->render();

    for (const auto& renderer : renders) {
        renderer->render(scene);
    }

    Input::update();
    Window::update();
}

void Game::sync(double currentTime) {
    double endTime = currentTime + MS_PER_UPDATE;
    while (glfwGetTime() < endTime) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

const std::unique_ptr<Scene>& Game::defaultScene() {
    return scene;
}

std::shared_ptr<TextRenderer> Game::defaultRenderer() {
    return std::dynamic_pointer_cast<TextRenderer>(renders[0]);
}

int main() {
    Game& game = Game::instance();
    game.init();
    game.run();
    return 0;
}