#include "Camera.h"
#include "../window/Input.h"
#include "../window/Window.h"

Camera::Camera(float speed, float fov, float near, float far) : speed_(speed), fov_(fov), near_(near), far_(far) {
    updateViewMatrix();
}

Camera::~Camera() {
}

void Camera::update(const double& elapsed) {
    if (Input::getKey(GLFW_KEY_W)) {
        position_ += rotation_ * vec3::up * speed_ * (float) elapsed;
    }
    if (Input::getKey(GLFW_KEY_S)) {
        position_ -= rotation_ * vec3::up * speed_ * (float) elapsed;
    }
    if (Input::getKey(GLFW_KEY_D)) {
        position_ += rotation_ * vec3::right * speed_ * (float) elapsed;
    }
    if (Input::getKey(GLFW_KEY_A)) {
        position_ -= rotation_ * vec3::right * speed_ * (float) elapsed;
    }
    if (Input::getKey(GLFW_KEY_E)) {
        position_ -= rotation_ * vec3::forward * speed_ * (float) elapsed;
    }
    if (Input::getKey(GLFW_KEY_Q)) {
        position_ += rotation_ * vec3::forward * speed_ * (float) elapsed;
    }

    if (Input::locked) {
        float sensitivity = Window::height * 2.0f;
        yaw_ -= Input::deltaX / sensitivity;
        pitch_ -= Input::deltaY / sensitivity;

        static constexpr float limit = glm::radians(89.0f);
        if (pitch_ > limit) {
            pitch_ = limit;
        }
        if (pitch_ < -limit) {
            pitch_ = -limit;
        }

        rotation_ = glm::quat{ glm::vec3(pitch_, yaw_, 0.0f) };
    }

    updateViewMatrix();
}

void Camera::updateViewMatrix() {
    view_ = glm::lookAt(position_, position_ + rotation_ * vec3::back, rotation_ * vec3::up);
    projection_ = glm::perspective(fov_, Window::aspect, near_, far_);
    projview_ = projection_ * view_;
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

void Camera::setPositionAndRotation(const glm::vec3 &pos, const glm::quat &rot) {
    position_ = pos;
    rotation_ = rot;
    updateViewMatrix();
}

/// @link https://stackoverflow.com/questions/29997209/opengl-c-mouse-ray-picking-glmunproject
Ray Camera::screenPointToRay(const glm::vec2& pos) {
    float mouseX = 2.0f * pos.x / Window::width - 1.0f;
    float mouseY = 2.0f * pos.y / Window::height - 1.0f;

    glm::vec4 screenPos(mouseX, -mouseY, 1.0f, 1.0f);
    glm::mat4 inverseProjView = glm::inverse(projview_);
    glm::vec4 worldPos = inverseProjView * screenPos;

    return { position_, glm::normalize(glm::vec3(worldPos)) };
}

/// @link https://discourse.libcinder.org/t/screen-to-world-coordinates/1014/2
glm::vec3 Camera::screenToWorldPoint(const glm::vec2& pos) {
    glm::vec4 viewport(0.0, Window::height, Window::width, -Window::height); // vertical flip is required
    return glm::unProject(glm::vec3(pos, 0.0f), view_, projection_, viewport);
}