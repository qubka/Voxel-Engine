#include "Visibility.h"

bool& Visibility::operator()() {
    return visibility;
}

const bool& Visibility::operator()() const {
    return visibility;
}
