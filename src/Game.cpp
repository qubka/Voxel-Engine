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

float Game::elapsedTime;
int Game::framesPerSecond;

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
    systems.push_back(std::make_shared<DebugSystem>());
    systems.push_back(std::make_shared<DestroySystem>());

    scene = std::make_unique<Scene>();
    scene->init();
}

Game::~Game() {
    Window::terminate();
}

void Game::run() {
    double previousTime = glfwGetTime();
    //double elapsedTime = 0.0;
    double frameTime = 0.0;
    int frameCount = 0;

    while (!Window::isShouldClose()) {
        double currentTime = glfwGetTime();
        elapsedTime = static_cast<float>(currentTime - previousTime);
        previousTime = currentTime;

        frameCount++;
        if (currentTime - frameTime >= 1.0) {
            framesPerSecond = frameCount;
            frameCount = 0;
            frameTime = currentTime;
        }

        update();
        render();
    }
}

void Game::update() {
    if (Input::getKeyDown(GLFW_KEY_ESCAPE)) {
        Window::setShouldClose(true);
    }

    if (Input::getKeyDown(GLFW_KEY_TAB)) {
        Window::setCursorMode(Input::toggleCursor());
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