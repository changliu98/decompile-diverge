void ee_readn(unsigned int addr, unsigned int *buf) {
    if (addr > 0x80) {
        *buf = 0x1f6;
    } else {
        *buf = 0;
        *(buf + 1) = (addr << 8) + 0x38000;
    }
}