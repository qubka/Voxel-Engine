#include "Camera.h"
#include "../window/Input.h"
#include "../window/Window.h"
#include "../Time.h"

// @brief https://github.com/cinder/Cinder/blob/master/src/cinder/Camera.cpp

Camera::Camera(float speed, float fov, float near, float far) : speed_(speed), fov_(fov), near_(near), far_(far) {
    updateViewMatrix();
}

Camera::~Camera() {
}

void Camera::update() {
    /*if (Input::getKey(GLFW_KEY_W)) {
        position_ += rotation_ * vec3::up * speed_ * Time::elapsedTime;
    }
    if (Input::getKey(GLFW_KEY_S)) {
        position_ -= rotation_ * vec3::up * speed_ * Time::elapsedTime;
    }
    if (Input::getKey(GLFW_KEY_D)) {
        position_ += rotation_ * vec3::right * speed_ * Time::elapsedTime;
    }
    if (Input::getKey(GLFW_KEY_A)) {
        position_ -= rotation_ * vec3::right * speed_ * Time::elapsedTime;
    }
    if (Input::getKey(GLFW_KEY_E)) {
        position_ -= rotation_ * vec3::forward * speed_ * Time::elapsedTime;
    }
    if (Input::getKey(GLFW_KEY_Q)) {
        position_ += rotation_ * vec3::forward * speed_ * Time::elapsedTime;
    }*/

    if (Input::getKey(GLFW_KEY_W)) {
        position_ -= rotation_ * vec3::forward * speed_ * Time::elapsedTime;
    }
    if (Input::getKey(GLFW_KEY_S)) {
        position_ += rotation_ * vec3::forward * speed_ * Time::elapsedTime;
    }
    if (Input::getKey(GLFW_KEY_D)) {
        position_ += rotation_ * glm::vec3(1,0,0) * speed_ * Time::elapsedTime;
    }
    if (Input::getKey(GLFW_KEY_A)) {
        position_ -= rotation_ * glm::vec3(1,0,0) * speed_ * Time::elapsedTime;
    }

    if (Window::locked) {
        glm::vec2 delta = Input::mouseDelta() / Window::height * 2;
        yaw_ -= delta.x;
        pitch_ -= delta.y;

        static constexpr float limit = glm::radians(89.0f);
        if (pitch_ > limit) {
            pitch_ = limit;
        }
        if (pitch_ < -limit) {
            pitch_ = -limit;
        }

        rotation_ = glm::quat{ glm::vec3(pitch_, yaw_, 0) };
    }

    updateViewMatrix();
}

void Camera::updateViewMatrix() {
    view_         = glm::lookAt(position_, position_ + rotation_ * vec3::back, rotation_ * vec3::up);
    projection_   = glm::perspective(fov_, Window::aspect, near_, far_);
    projview_     = projection_ * view_;
}

const glm::mat4& Camera::projection() const {
    return projection_;
}

const glm::mat4& Camera::view() const {
    return view_;
}

const glm::mat4& Camera::projview() const {
    return projview_;
}

const glm::vec3& Camera::position() const {
    return position_;
}

const glm::quat& Camera::rotation() const {
    return rotation_;
}

float Camera::yaw() const {
    return yaw_;
}

float Camera::pitch() const {
    return pitch_;
}

float Camera::fov() const {
    return fov_;
}

float Camera::near() const {
    return near_;
}

float Camera::far() const {
    return far_;
}

float Camera::speed() const {
    return speed_;
}

void Camera::position(const glm::vec3& pos) {
    position_ = pos;
    updateViewMatrix();
}

void Camera::rotation(const glm::quat& rot) {
    rotation_ = rot;
    updateViewMatrix();
}

void Camera::setPositionAndRotation(const glm::vec3 &pos, const glm::quat &rot) {
    position_ = pos;
    rotation_ = rot;
    updateViewMatrix();
}

glm::vec3 Camera::forward() const {
    return rotation_ * vec3::back;
}

glm::vec3 Camera::back() const {
    return rotation_ * vec3::forward;
}

glm::vec3 Camera::up() const {
    return rotation_ * vec3::up;
}

glm::vec3 Camera::right() const {
    return rotation_ * vec3::right;
}

/// @link https://antongerdelan.net/opengl/raycasting.html
Ray Camera::screenPointToRay(const glm::vec2& pos) const {
    float mouseX = 2 * pos.x / Window::width - 1;
    float mouseY = 2 * pos.y / Window::height - 1;

    glm::vec4 screenPos(mouseX, -mouseY, -1, 1);
    glm::vec4 eyeRay = glm::inverse(projection_) * screenPos;
    eyeRay.z = -1;
    eyeRay.w = 0;
    glm::vec4 worldRay = glm::inverse(view_) * eyeRay;

    return { position_, glm::normalize(glm::vec3(worldRay)) };
}

/// @link https://discourse.libcinder.org/t/screen-to-world-coordinates/1014/2
glm::vec3 Camera::screenToWorldPoint(const glm::vec2& pos) const {
    glm::vec4 viewport(0, Window::height, Window::width, -Window::height); // vertical flip is required
    return glm::unProject(glm::vec3(pos, 0), view_, projection_, viewport);
}