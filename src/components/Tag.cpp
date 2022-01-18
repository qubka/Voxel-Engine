#include "Tag.h"

std::string& Tag::operator()() {
    return tag;
}

const std::string& Tag::operator()() const {
    return tag;
}
