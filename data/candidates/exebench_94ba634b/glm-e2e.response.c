void _jis_shift(unsigned char *c1, unsigned char *c2) {
    unsigned char v1 = *c1;
    unsigned char v2 = *c2;
    
    int add1 = (v1 < 0x5f) ? 0x70 : 0xb0;
    
    int add2;
    if (v1 % 2 != 0) {
        add2 = (v2 > 0x5f) ? 0x20 : 0x1f;
    } else {
        add2 = 0x7e;
    }
    
    *c1 = (v1 + 1) / 2 + add1;
    *c2 = v2 + add2;
}