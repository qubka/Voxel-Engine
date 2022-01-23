#include "Window.h"

GLFWwindow* Window::window{};
float Window::width{};
float Window::height{};
float Window::aspect{};
bool Window::minimized{};
bool Window::wireframe{};
bool Window::locked{};

void Window::init(int width, int height, const char* title, bool vsync) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        BOOST_LOG_TRIVIAL(error) << "Failed to create GLFW Window";
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(vsync);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        BOOST_LOG_TRIVIAL(error) << "Failed to init GLEW";
        glfwTerminate();
        return;
    }

    setWidthAndHeight(width, height);

    glClearColor(0.7f, 0.85f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        BOOST_LOG_TRIVIAL(error) << "OpenGL error: " << err;
    }
}

void Window::terminate() {
    glfwTerminate();
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Window::isShouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::setShouldClose(bool flag) {
    glfwSetWindowShouldClose(window, flag);
}

void Window::toggleCursor() {
    locked = !locked;
    glfwSetInputMode(window, GLFW_CURSOR, locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Window::toggleWireframe() {
    wireframe = !wireframe;
    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
}

void Window::setWidthAndHeight(int w, int h) {
    glViewport(0, 0, w, h);
    width = static_cast<float>(w);
    height = static_cast<float>(h);
    aspect = width / height;
    minimized = (h == 0 || w == 0);
}