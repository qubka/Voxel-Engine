#ifndef VOX_CAMERA_H
#define VOX_CAMERA_H

#include "../geometry/Ray.h"

class Camera {
private:
    glm::mat4 projection_{1};
    glm::mat4 view_{1};
    glm::mat4 projview_{1};
    glm::vec3 position_{0};
    glm::quat rotation_{1, 0, 0, 0};
    float yaw_{0};
    float pitch_{0};
    float fov_;
    float near_;
    float far_;
    float speed_;

    void updateViewMatrix();
public:
    Camera(float speed, float fov, float near, float far);
    ~Camera();

    [[maybe_unused]] static std::shared_ptr<Camera> main;

    void update(const double& elapsed);

    [[nodiscard]] const glm::mat4& projection() const;
    [[nodiscard]] const glm::mat4& view() const;
    [[nodiscard]] const glm::mat4& projview() const;
    [[nodiscard]] const glm::vec3& position() const;
    [[nodiscard]] const glm::quat& rotation() const;
    [[nodiscard]] float yaw() const;
    [[nodiscard]] float pitch() const;
    [[nodiscard]] float fov() const;
    [[nodiscard]] float near() const;
    [[nodiscard]] float far() const;
    [[nodiscard]] float speed() const;

    void position(const glm::vec3& pos);
    void rotation(const glm::quat& rot);
    void setPositionAndRotation(const glm::vec3& pos, const glm::quat& rot);

    Ray screenPointToRay(const glm::vec2& pos);
    glm::vec3 screenToWorldPoint(const glm::vec2& pos);
};

#endif //VOX_CAMERA_H
