unsigned short getExtendTest(unsigned char b) {
    unsigned char i = b;
    unsigned short ret;

    if (i < 16)
        return func0_table[i];

    ret = 0;
    while (i > 0) {
        ret = 1;
        i >>= 1;
        ret <<= 1;
    }

    return ret;
}