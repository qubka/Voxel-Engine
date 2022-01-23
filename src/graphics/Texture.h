#ifndef VOX_TEXTURE_H
#define VOX_TEXTURE_H

#include <assimp/material.h>

class Texture {
    GLuint textureId;
    std::filesystem::path filePath;
    aiTextureType aiType{aiTextureType_DIFFUSE};
public:
    Texture(const std::filesystem::path& path, bool linear, bool clamp);
    Texture(uint8_t r, uint8_t g, uint8_t b);
    ~Texture();

    void bind() const;
    void unbind() const;

    const std::filesystem::path& path() const;
    aiTextureType type() const;
};

#endif //VOX_TEXTURE_H
