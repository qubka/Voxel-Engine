#ifndef VOX_BLOCK_H
#define VOX_BLOCK_H

struct Block {
    uint8_t id;
                             //  0 1   2 3   4 5
    uint8_t textureFaces[6]; // -x,x, -y,y, -z,z
    uint8_t emission[3]{};
    uint8_t drawGroup{0};
    bool lightPassing{false};
    bool obstacle{true};

    Block(uint8_t id, uint8_t texture);
};


#endif //VOX_BLOCK_H
