#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image(const std::filesystem::path& path) {
    //stbi_set_flip_vertically_on_load(flip);
    pixels = stbi_load(path.c_str(), &width, &height, &channels, 4);
    if (!pixels)
        BOOST_LOG_TRIVIAL(error) <<  "Failed to load image: " << path << " - " << stbi_failure_reason() << std::endl;
}

Image::~Image() {
    if (pixels)
        stbi_image_free(pixels);
}