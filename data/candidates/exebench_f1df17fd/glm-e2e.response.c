int FNEGQ(unsigned long *dst, unsigned long *src) {
    dst[0] = src[0] ^ 0x8000000000000000UL;
    dst[1] = src[1];
    return 1;
}