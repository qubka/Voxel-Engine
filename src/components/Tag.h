#ifndef VOX_TAG_H
#define VOX_TAG_H

struct Tag {
    std::string tag{"NA"};

    std::string& operator()();
    const std::string& operator()() const;
};

#endif //VOX_TAG_H
