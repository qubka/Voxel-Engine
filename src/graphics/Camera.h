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
    float speed_{1};
    float fov_{45};
    float far_{0.1};
    float near_{100};

    void updateViewMatrix();
public:
    Camera(float speed, float fov, float nearClip, float farClip);
    ~Camera();

    void update();

    glm::vec3 forward() const;
    glm::vec3 back() const ;
    glm::vec3 up() const;
    glm::vec3 right() const;

    const glm::mat4& projection() const;
    const glm::mat4& view() const;
    const glm::mat4& projview() const;

    float yaw() const;
    float pitch() const;
    float fov() const;
    float speed() const;

    float near() const;
    float far() const;

    const glm::vec3& position() const;
    const glm::quat& rotation() const;
    void position(const glm::vec3& pos);
    void rotation(const glm::quat& rot);
    void setPositionAndRotation(const glm::vec3& pos, const glm::quat& rot);

    Ray screenPointToRay(const glm::vec2& pos) const;
    glm::vec3 screenToWorldPoint(const glm::vec2& pos) const;
};

#endif //VOX_CAMERA_H
