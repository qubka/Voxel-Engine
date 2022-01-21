#ifndef VOX_TEXT_H
#define VOX_TEXT_H

struct Text {
    std::string text{""};
    float x{0};
    float y{0};
    float scale{0};
    glm::vec4 color{1};

    std::string& operator()();
    const std::string& operator()() const;
};

#endif //VOX_TEXT_H
