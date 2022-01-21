#ifndef VOX_GAME_H
#define VOX_GAME_H

class Scene;
class Renderer;
class System;
class TextRenderer;

class Game {
public:
    Game();
    ~Game();

    void init();
    void run();

    const std::unique_ptr<Scene>& defaultScene();

    static Game& instance() {
        static Game instance;
        return instance;
    }

    static float elapsedTime;
    static int framesPerSecond;

private:
    std::unique_ptr<Scene> scene;

    std::vector<std::shared_ptr<Renderer>> renders;
    std::vector<std::shared_ptr<System>> systems;

    void render();
    void update();
};

#endif //VOX_GAME_H
