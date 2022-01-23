#ifndef VOX_TIME_H
#define VOX_TIME_H

class Time {
public:
    static float time;
    static float elapsedTime;
    static float frameTime;
    static int frameCount;
    static int framesPerSecond;

    static void init();
    static void update();
};

#endif //VOX_TIME_H
