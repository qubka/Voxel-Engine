#ifndef VOX_VISIBILITY_H
#define VOX_VISIBILITY_H

struct Visibility {
    bool visibility{false};

    bool& operator()();
    const bool& operator()() const;
};

#endif //VOX_VISIBILITY_H
