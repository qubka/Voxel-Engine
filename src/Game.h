#ifndef VOX_GAME_H
#define VOX_GAME_H

class Scene;
class Renderer;
class System;
class TextRenderer;

class Game {
public:
    Game() = default;
    ~Game();
    void init();
    void run();

    static const inline int TARGET_FPS = 120;
    static constexpr double MS_PER_UPDATE = (1.0 / TARGET_FPS);

    const std::unique_ptr<Scene>& defaultScene();
    std::shared_ptr<TextRenderer> defaultRenderer();

    static Game& getInstance() {
        static Game instance;
        return instance;
    }
private:
    std::unique_ptr<Scene> scene;

    std::vector<std::shared_ptr<Renderer>> renders;
    std::vector<std::shared_ptr<System>> systems;

    void input();
    void render();
    void update(double elapsedTime);
    void sync(double currentTime);
};

#endif //VOX_GAME_H
