void put_num(unsigned short *p, unsigned int num, unsigned char width) {
    if (width > 4) {
        *p++ = 0x2110 + ((num / 10000) % 10);
    }
    if (width > 3) {
        *p++ = 0x2110 + ((num / 1000) % 10);
    }
    if (width > 2) {
        *p++ = 0x2110 + ((num / 100) % 10);
    }
    if (width > 1) {
        *p++ = 0x2110 + ((num / 10) % 10);
    }
    if (width > 0) {
        *p++ = 0x2110 + (num % 10);
    }
}