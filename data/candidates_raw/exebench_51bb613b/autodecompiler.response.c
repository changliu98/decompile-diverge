int rand_r(unsigned int *seed) {
    *seed = (unsigned int)(1103515245 * (unsigned long long)*seed + 12345);
    return (*seed / 65536) & 0x7FFF;
}