#include "Frustum.h"
#include "../graphics/Camera.h"

Frustum::Frustum(const std::shared_ptr<Camera>& camera) {
    set(camera);
}

Frustum::Frustum(const glm::vec3& ntl, const glm::vec3& ntr, const glm::vec3& nbl, const glm::vec3& nbr, const glm::vec3& ftl, const glm::vec3& ftr, const glm::vec3& fbl, const glm::vec3& fbr) {
    set(ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr);
}

Frustum::Frustum(const glm::mat4& mat) {
    set(mat);
}

void Frustum::set(const std::shared_ptr<Camera>& camera) {
    glm::vec3 ntl, ntr, nbl, nbr;
    camera->getNearClipCoordinates(ntl, ntr, nbl, nbr);

    glm::vec3 ftl, ftr, fbl, fbr;
    camera->getFarClipCoordinates(ftl, ftr, fbl, fbr);

    set(ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr);
}

void Frustum::set(const std::shared_ptr<Camera>& camera, const glm::vec3& ntl, const glm::vec3& ntr, const glm::vec3& nbl, const glm::vec3& nbr) {
    glm::vec3 eye = camera->position();
    float farClip = camera->farClip();

    glm::vec3 ftl = glm::normalize(ntl - eye) * farClip;
    glm::vec3 ftr = glm::normalize(ntr - eye) * farClip;
    glm::vec3 fbl = glm::normalize(nbl - eye) * farClip;
    glm::vec3 fbr = glm::normalize(nbr - eye) * farClip;

    set(ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr);
}

void Frustum::set(const glm::vec3& ntl, const glm::vec3& ntr, const glm::vec3& nbl, const glm::vec3& nbr,
                  const glm::vec3& ftl, const glm::vec3& ftr, const glm::vec3& fbl, const glm::vec3& fbr) {

    planes[TOP].set(ntr, ntl, ftl);
    planes[BOTTOM].set(nbl, nbr, fbr);
    planes[LEFT].set(ntl, nbl, fbl);
    planes[RIGHT].set(nbr, ntr, fbr);
    planes[NEAR].set(ntl, ntr, nbr);
    planes[FAR].set(ftr, ftl, fbl);
}

void Frustum::set(const glm::mat4& mat) {
    // Based on: Fast Extraction of Viewing Frustum Planes from the WorldView-Projection Matrix
    //       by: Gil Gribb and Klaus Hartmann
    planes[TOP].set({mat[0][3] - mat[0][1], mat[1][3] - mat[1][1], mat[2][3] - mat[2][1], -mat[3][3] + mat[3][1]});
    planes[BOTTOM].set({mat[0][3] + mat[0][1], mat[1][3] + mat[1][1], mat[2][3] + mat[2][1], -mat[3][3] - mat[3][1]});
    planes[LEFT].set({mat[0][3] + mat[0][0], mat[1][3] + mat[1][0], mat[2][3] + mat[2][0], -mat[3][3] - mat[3][0]});
    planes[RIGHT].set({mat[0][3] - mat[0][0], mat[1][3] - mat[1][0], mat[2][3] - mat[2][0], -mat[3][3] + mat[3][0]});
    planes[NEAR].set({mat[0][3] + mat[0][2], mat[1][3] + mat[1][2], mat[2][3] + mat[2][2], -mat[3][3] - mat[3][2]});
    planes[FAR].set({mat[0][3] - mat[0][2], mat[1][3] - mat[1][2], mat[2][3] - mat[2][2], -mat[3][3] + mat[3][2]});
}