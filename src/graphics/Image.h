#ifndef VOX_IMAGE_H
#define VOX_IMAGE_H

struct Image {
    unsigned char* pixels;
    int width{0};
    int height{0};
    int channels{0};

    explicit Image(const std::filesystem::path& path);
    ~Image();
};

#endif //VOX_IMAGE_H
