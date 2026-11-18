long __reverse_ffs(unsigned long x) {
    int pos = 0;

    if ((x & 0xffff0000UL) == 0) {
        pos += 16;
    } else {
        x >>= 16;
    }

    if ((x & 0xff00UL) == 0) {
        pos += 8;
    } else {
        x >>= 8;
    }

    if ((x & 0xf0UL) == 0) {
        pos += 4;
    } else {
        x >>= 4;
    }

    if ((x & 0xcUL) == 0) {
        pos += 2;
    } else {
        x >>= 2;
    }

    if ((x & 0x2UL) == 0) {
        pos += 1;
    }

    return (long)pos;
}