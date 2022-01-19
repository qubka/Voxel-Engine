#ifndef VOX_TEXTURE_H
#define VOX_TEXTURE_H

#include <assimp/material.h>

class Texture {
    GLuint textureId;
    std::filesystem::path filePath;
    aiTextureType aiType{aiTextureType_DIFFUSE};
public:
    Texture(const std::filesystem::path& path, bool linear, bool clamp);
    Texture(unsigned char r, unsigned char g, unsigned char b);
    ~Texture();

    void bind() const;
    void unbind() const;

    uint32_t id() const;
    [[nodiscard]] const std::filesystem::path& path() const;
    [[nodiscard]] aiTextureType type() const;
};

#endif //VOX_TEXTURE_H
