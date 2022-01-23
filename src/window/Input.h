#ifndef VOX_EVENTS_H
#define VOX_EVENTS_H

#define MOUSE_BUTTONS 1024

class Input {
private:
    static bool keys[1032];
    static uint32_t frames[1032];
    static uint32_t current;
    static glm::vec2 delta;
    static glm::vec2 position;

public:
    static void init();
    static void update();

    static bool getKey(int keycode);
    static bool getKeyDown(int keycode);

    static bool getMouseButton(int button);
    static bool getMouseButtonDown(int button);

    static glm::vec2& mousePosition();
    static glm::vec2& mouseDelta();

protected:
    static void cursorPositionCallback(GLFWwindow* window, double mouseX, double mouseY);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void windowSizeCallback(GLFWwindow* window, int width, int height);
    static void windowMaximizeCallback(GLFWwindow* window, int maximized);
};

#endif //VOX_EVENTS_H
