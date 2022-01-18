#ifndef VOX_IMAGE_H
#define VOX_IMAGE_H

struct Image {
    unsigned char* pixels;
    int width;
    int height;
    int channels;

    explicit Image(const std::filesystem::path& path);
    ~Image();
};

#endif //VOX_IMAGE_H
