#ifndef VOX_EVENTS_H
#define VOX_EVENTS_H

class Input {
public:
    static bool keys[1032];
    static uint32_t frames[1032];
    static uint32_t current;
    static float deltaX;
    static float deltaY;
    static float x;
    static float y;
    static bool started;
    static bool locked;

    static void init();
    static void update();

    static bool getKey(int keycode);
    static bool getKeyDown(int keycode);

    static bool getMouseButton(int button);
    static bool getMouseButtonDown(int button);

    static int toggleCursor();
    static glm::vec2 mousePosition();
};

#endif //VOX_EVENTS_H
