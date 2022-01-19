#include "Input.h"
#include "Window.h"

bool Input::keys[];
uint32_t Input::frames[];
uint32_t Input::current;
float Input::deltaX;
float Input::deltaY;
float Input::x;
float Input::y;
bool Input::started;
bool Input::locked;

#define MOUSE_BUTTONS 1024

void cursorPositionCallback(GLFWwindow* window, double mouseX, double mouseY) {
    auto x = static_cast<float>(mouseX);
    auto y = static_cast<float>(mouseY);

    if (Input::started) {
        Input::deltaX += x - Input::x;
        Input::deltaY += y - Input::y;
    } else {
        Input::started = true;
    }

    Input::x = x;
    Input::y = y;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode) {
    int key = MOUSE_BUTTONS + button;
    if (action == GLFW_PRESS) {
        Input::keys[key] = true;
        Input::frames[key] = Input::current;
    } else if (action == GLFW_RELEASE) {
        Input::keys[key] = false;
        Input::frames[key] = Input::current;
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {
        Input::keys[key] = true;
        Input::frames[key] = Input::current;
    } else if (action == GLFW_RELEASE){
        Input::keys[key] = false;
        Input::frames[key] = Input::current;
    }
}

void windowSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Window::setWidthAndHeight(width, height);
}

void windowMaximizeCallback(GLFWwindow* window, int maximized) {

}

void Input::init() {
    GLFWwindow* window = Window::window;
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetWindowMaximizeCallback(window, windowMaximizeCallback);
}

bool Input::getKey(int keycode) {
    if (keycode < 0 || keycode >= MOUSE_BUTTONS)
        return false;
    return keys[keycode];
}

bool Input::getKeyDown(int keycode) {
    if (keycode < 0 || keycode >= MOUSE_BUTTONS)
        return false;
    return keys[keycode] && frames[keycode] == current;
}

bool Input::getMouseButton(int button) {
    int index = MOUSE_BUTTONS + button;
    return keys[index];
}

bool Input::getMouseButtonDown(int button) {
    int index = MOUSE_BUTTONS + button;
    return keys[index] && frames[index] == current;
}

void Input::update() {
    current++;
    deltaX = 0;
    deltaY = 0;
}

int Input::toggleCursor() {
    locked = !locked;
    return locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
}

glm::vec2 Input::mousePosition() {
    return { x, y };
}
