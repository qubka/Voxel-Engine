#include "Font.h"
#include "Glyph.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Font::Font(const FT_Face& face, int size) : width(0), height(0) {
    FT_Set_Pixel_Sizes(face, 0, size);
    const auto& glyph = face->glyph;

    FT_UInt index;
    FT_ULong character = FT_Get_First_Char(face, &index);
    while (index != 0) {
        if (FT_Load_Char(face, character, FT_LOAD_RENDER)) {
            BOOST_LOG_TRIVIAL(error) << "Failed to load glyph '" << character << "' at " << index;
            continue;
        }

        width= glyph->bitmap.width;
        height= glyph->bitmap.rows;

        /* Upload the "bitmap", which contains an 8-bit grayscale image, as an alpha texture */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width,height , 0, GL_ALPHA, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

        //GLubyte pixels[width * height * sizeof(GLubyte)];
        //glGetTexImage(GL_TEXTURE_2D, 0, GL_ALPHA, GL_UNSIGNED_BYTE, &pixels);
        stbi_write_png(std::string("res/atlas_" + std::to_string(index) + ".png").c_str(), width, height, 1, glyph->bitmap.buffer, width * 1);

        BOOST_LOG_TRIVIAL(info) << "Generated a " << width << "x " << height << " (" << width * height / 1024 << " kb) texture atlas.";

        character = FT_Get_Next_Char(face, character, &index);
    }

    /*glm::ivec2 r, o;
    FT_UInt index;
    FT_ULong character = FT_Get_First_Char(face, &index);
    while (index != 0) {
        if (FT_Load_Char(face, character, FT_LOAD_RENDER)) {
            BOOST_LOG_TRIVIAL(error) << "Failed to load glyph '" << character << "' at " << index;
            continue;
        }

        if (r.x + glyph->bitmap.width + 1 >= MAX_WIDTH) {
            width = std::max(width, r.x);
            height += r.y;
            r.x = 0;
            r.y = 0;
        }

        r.x += glyph->bitmap.width + 1;
        r.y = std::max(r.y, static_cast<int>(glyph->bitmap.rows));

        character = FT_Get_Next_Char(face, character, &index);
    }

    width = std::max(width, r.x);
    height += r.y;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    r.y = 0;

    character = FT_Get_First_Char(face, &index);
    while (index != 0) {
        if (FT_Load_Char(face, character, FT_LOAD_RENDER)) {
            BOOST_LOG_TRIVIAL(error) << "Failed to load glyph '" << character << "' at " << index;
            continue;
        }

        if (o.x + glyph->bitmap.width + 1 >= MAX_WIDTH) {
            o.y += r.y;
            r.y = 0;
            o.x = 0;
        }

        glTexSubImage2D(GL_TEXTURE_2D, 0, o.x, o.y, glyph->bitmap.width, glyph->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

        glyphs.emplace(character, Glyph {
            {glyph->advance.x >> 6, glyph->advance.y >> 6},
            {glyph->bitmap.width, glyph->bitmap.rows},
            {glyph->bitmap_left, glyph->bitmap_top},
            {o.x / static_cast<float>(width), o.y / static_cast<float>(height)}
        });

        r.y = std::max(r.y, static_cast<int>(glyph->bitmap.rows));
        o.x += glyph->bitmap.width + 1;

        character = FT_Get_Next_Char(face, character, &index);
    }*/
}

Font::~Font() {
    glDeleteTextures(1, &textureId);
}