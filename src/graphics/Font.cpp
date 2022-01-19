#include "Font.h"
#include "Glyph.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Font::Font(const FT_Face& face, int size) {
    FT_Set_Pixel_Sizes(face, 0, size);
    const auto& glyph = face->glyph;
    //FT_Set_Char_Size(face, 0, size << 6, 48, 48);

    int cell = 1 + (face->size->metrics.height >> 6);
    int ox = 0, oy = 0;
    int maxDim = cell * std::ceil(std::sqrt(NUM_GLYPHS / 2));

    width = 1;
    while (width < maxDim) width <<= 1;
    height = width;

    std::vector<unsigned char> pixels(width * height);

    for (unsigned char c = 32; c < NUM_GLYPHS; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_LIGHT)) {
            BOOST_LOG_TRIVIAL(error) << "Failed to load glyph '" << c << "'";
            continue;
        }

        FT_Bitmap* bmp = &glyph->bitmap;

        if (ox + bmp->width >= width) {
            ox = 0;
            oy += cell;
        }

        for (int row = 0; row < bmp->rows; ++row) {
            for (int col = 0; col < bmp->width; ++col) {
                int x = ox + col;
                int y = oy + row;
                pixels[y * width + x] = bmp->buffer[row * bmp->pitch + col];
            }
        }

        glyphs.emplace(c, Glyph {
            {glyph->advance.x >> 6, glyph->advance.y >> 6},
            {glyph->bitmap.width, glyph->bitmap.rows},
            {glyph->bitmap_left, glyph->bitmap_top},
            {ox / static_cast<float>(width), oy / static_cast<float>(height)}
        });

        ox += bmp->width + 1;
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, pixels.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::filesystem::path path = "res/atlas";
    path += std::to_string(size);
    path += ".png";
    stbi_write_png(path.c_str(), width, height, 1, pixels.data(), width * 1);

    BOOST_LOG_TRIVIAL(info) << "Generated a " << width << "x " << height << " (" << width * height / 1024 << " kb) texture atlas.";
}

Font::~Font() {
    glDeleteTextures(1, &textureId);
}