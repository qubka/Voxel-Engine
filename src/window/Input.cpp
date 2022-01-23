#include "Input.h"
#include "Window.h"

bool Input::keys[]{};
uint32_t Input::frames[]{};
uint32_t Input::current{};
glm::vec2 Input::delta{};
glm::vec2 Input::position{};

void Input::init() {
    GLFWwindow* window = Window::window;
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetWindowMaximizeCallback(window, windowMaximizeCallback);
    //glfwSetScrollCallback
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
    delta.x = 0;
    delta.y = 0;
}

glm::vec2& Input::mousePosition() {
    return position;
}

glm::vec2& Input::mouseDelta() {
    return delta;
}

void Input::cursorPositionCallback(GLFWwindow* window, double mouseX, double mouseY) {
    glm::vec2 mouse {mouseX, mouseY};
    delta += mouse - position;
    position = mouse;
}

void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mode) {
    int key = MOUSE_BUTTONS + button;
    if (action == GLFW_PRESS) {
        keys[key] = true;
        frames[key] = current;
    } else if (action == GLFW_RELEASE) {
        keys[key] = false;
        frames[key] = current;
    }
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {
        keys[key] = true;
        frames[key] = current;
    } else if (action == GLFW_RELEASE) {
        keys[key] = false;
        frames[key] = current;
    }
}

void Input::windowSizeCallback(GLFWwindow* window, int width, int height) {
    Window::setWidthAndHeight(width, height);
}

void Input::windowMaximizeCallback(GLFWwindow* window, int maximized) {

}