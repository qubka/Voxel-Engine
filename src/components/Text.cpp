#include "Text.h"

std::string& Text::operator()() {
    return text;
}

const std::string& Text::operator()() const {
    return text;
}
