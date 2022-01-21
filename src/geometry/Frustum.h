#ifndef VOX_FRUSTUM_H
#define VOX_FRUSTUM_H

#include "Plane.h"

class Camera;

class Frustum {
public:
    enum FrustumSection { TOP, BOTTOM, LEFT, RIGHT, NEAR, FAR };
    
    explicit Frustum(const std::shared_ptr<Camera>& camera);
    Frustum(const glm::vec3& ntl, const glm::vec3& ntr, const glm::vec3& nbl, const glm::vec3& nbr, const glm::vec3& ftl, const glm::vec3& ftr, const glm::vec3& fbl, const glm::vec3& fbr);
    Frustum(const glm::mat4& mat);

    void set(const std::shared_ptr<Camera>& camera);
    void set(const std::shared_ptr<Camera>& camera, const glm::vec3& ntl, const glm::vec3& ntr, const glm::vec3& nbl, const glm::vec3& nbr);
    void set(const glm::vec3& ntl, const glm::vec3& ntr, const glm::vec3& nbl, const glm::vec3& nbr, const glm::vec3& ftl, const glm::vec3& ftr, const glm::vec3& fbl, const glm::vec3& fbr);
    void set(const glm::mat4& mat);

    /*bool contains(const glm::vec3& loc) const;
    bool contains(const glm::vec3& center, T radius) const;
    bool contains(const glm::vec3& center, const glm::vec3& size) const;
    bool contains(const Sphere &sphere) const;
    bool contains(const AxisAlignedBox &box) const;

    bool intersects(const glm::vec3& loc) const;
    bool intersects(const glm::vec3& center, T radius) const;
    bool intersects(const glm::vec3& center, const glm::vec3& size) const;
    bool intersects(const Sphere &sphere) const;
    bool intersects(const AxisAlignedBox &box) const;*/

    const Plane& getPlane(FrustumSection section) const { return planes[section]; }

private:
    Plane planes[6];
};

#endif //VOX_FRUSTUM_H
