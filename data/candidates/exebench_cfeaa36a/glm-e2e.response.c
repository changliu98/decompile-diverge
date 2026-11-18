void _sjis_shift(unsigned char *c1, unsigned char *c2) {
    unsigned char a = *c1;
    unsigned char b = *c2;
    
    int is_less_than_9f = (b < 0x9f) ? 1 : 0;
    int sub_val1 = (a < 0xa0) ? 0x70 : 0xb0;
    
    int sub_val2;
    if (is_less_than_9f) {
        sub_val2 = (b > 0x7f) ? 0x20 : 0x1f;
    } else {
        sub_val2 = 0x7e;
    }
    
    *c1 = (a - sub_val1) * 2 - is_less_than_9f;
    *c2 = *c2 - sub_val2;
}