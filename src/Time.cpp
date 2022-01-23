#include "Time.h"

float Time::time{};
float Time::elapsedTime{};
float Time::frameTime{};
int Time::frameCount{};
int Time::framesPerSecond{};

void Time::init() {
    time = static_cast<float>(glfwGetTime());
}

void Time::update() {
    float currentTime = static_cast<float>(glfwGetTime());
    elapsedTime = currentTime - time;
    time = currentTime;

    frameCount++;
    if (currentTime - frameTime >= 1) {
        framesPerSecond = frameCount;
        frameCount = 0;
        frameTime = currentTime;
    }
}
