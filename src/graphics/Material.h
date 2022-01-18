#ifndef VOX_MATERIAL_H
#define VOX_MATERIAL_H

struct Material {
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 ambient;
    float shininess;
};

#endif //VOX_MATERIAL_H
