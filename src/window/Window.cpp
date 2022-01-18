#include "Window.h"
#include "../graphics/Image.h"

GLFWwindow* Window::window;
GLFWcursor* Window::cursor;
float Window::width;
float Window::height;
float Window::aspect;
bool Window::wireframe;

void APIENTRY glDebugOutput(GLenum source,
                            GLenum type,
                            unsigned int id,
                            GLenum severity,
                            GLsizei length,
                            const char *message,
                            const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    BOOST_LOG_TRIVIAL(trace) << "---------------";
    BOOST_LOG_TRIVIAL(trace) << "Debug message (" << id << "): " <<  message;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             BOOST_LOG_TRIVIAL(trace) << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   BOOST_LOG_TRIVIAL(trace) << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: BOOST_LOG_TRIVIAL(trace) << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     BOOST_LOG_TRIVIAL(trace) << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     BOOST_LOG_TRIVIAL(trace) << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           BOOST_LOG_TRIVIAL(trace) << "Source: Other"; break;
    }

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               BOOST_LOG_TRIVIAL(trace) << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: BOOST_LOG_TRIVIAL(trace) << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  BOOST_LOG_TRIVIAL(trace) << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         BOOST_LOG_TRIVIAL(trace) << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         BOOST_LOG_TRIVIAL(trace) << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              BOOST_LOG_TRIVIAL(trace) << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          BOOST_LOG_TRIVIAL(trace) << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           BOOST_LOG_TRIVIAL(trace) << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               BOOST_LOG_TRIVIAL(trace) << "Type: Other"; break;
    }
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         BOOST_LOG_TRIVIAL(trace) << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       BOOST_LOG_TRIVIAL(trace) << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          BOOST_LOG_TRIVIAL(trace) << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: BOOST_LOG_TRIVIAL(trace) << "Severity: notification"; break;
    }
}

void Window::init(int width, int height, const std::string& title, bool vSync) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (window == nullptr){
        BOOST_LOG_TRIVIAL(error) << "Failed to create GLFW Window";
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(vSync ? 1 : 0);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        BOOST_LOG_TRIVIAL(error) << "Failed to init GLEW";
        glfwTerminate();
        return;
    }
    glViewport(0, 0, width, height);

    glClearColor(0.7f, 0.85f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT){
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    setWidthAndHeight(width, height);
}

void Window::terminate() {
    glfwTerminate();
}

void Window::clear() {
    //glFlush();
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

/*void Window::setCursor(const std::filesystem::path& path) {
    Image image{path};
    GLFWimage img{image.width, image.height, image.pixels};
    cursor = glfwCreateCursor(&img, 0, 0);
    glfwSetCursor(window, cursor);
}*/

void Window::setCursorMode(int mode) {
    glfwSetInputMode(window, GLFW_CURSOR, mode);
}

void Window::toogleWireframe() {
    wireframe =! wireframe;
    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
}

void Window::setWidthAndHeight(int w, int h) {
    width = static_cast<float>(w);
    height = static_cast<float>(h);
    aspect = width / height;
}