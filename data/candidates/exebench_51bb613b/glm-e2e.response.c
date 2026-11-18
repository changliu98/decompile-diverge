int rand_r(unsigned int *seed) {
    *seed = *seed * 0x41c64e6d + 0x3039;
    return (*seed >> 16) & 0x7fff;
}