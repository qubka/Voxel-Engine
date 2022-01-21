#ifndef VOX_WINDOW_H
#define VOX_WINDOW_H

class GLFWwindow;

struct Window {
    static GLFWwindow* window;
    static GLFWcursor* cursor;
    static float width;
    static float height;
    static float aspect;
    static bool minimized;
    static bool wireframe;

    static void init(int width, int height, const std::string& title, bool vSync);
    static void terminate();
    static void clear();
    static void update();

    static bool isShouldClose();
    static void setShouldClose(bool flag);

    static void setCursor(const std::filesystem::path& path);
    static void setCursorMode(int mode);

    static void toggleWireframe();
    static void setWidthAndHeight(int width, int height);
};

#endif //VOX_WINDOW_H
