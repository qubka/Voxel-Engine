#ifndef VOX_WINDOW_H
#define VOX_WINDOW_H

class Window {
public:
    static GLFWwindow* window;
    static float width;
    static float height;
    static float aspect;
    static bool minimized;
    static bool wireframe;
    static bool locked;

    static void init(int width, int height, const char* title, bool vsync);
    static void terminate();
    static void clear();
    static void update();

    static bool isShouldClose();
    static void setShouldClose(bool flag);

    static void toggleCursor();
    static void toggleWireframe();
    static void setWidthAndHeight(int width, int height);
};

#endif //VOX_WINDOW_H
