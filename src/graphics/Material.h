#ifndef VOX_MATERIAL_H
#define VOX_MATERIAL_H

struct Material {
    glm::vec3 diffuse{0};
    glm::vec3 specular{0};
    glm::vec3 ambient{0};
    float shininess{0};
};

#endif //VOX_MATERIAL_H
