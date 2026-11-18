char* encode_int(char *buf, int val) {
    int is_neg = 0;
    
    if (val <= 0) {
        val = -val;
        is_neg = 1;
    }
    
    if (val & 0x7c00) {
        *buf++ = (val >> 10) | 0x40;
    }
    
    if (val & 0x3f0) {
        *buf++ = (val >> 4) | 0x40;
    }
    
    if (val & 0xf) {
        *buf = (val & 0xf) | 0x20;
    } else {
        *buf = 0x20;
    }
    
    if (!is_neg) {
        *buf |= 0x10;
    }
    
    buf++;
    *buf = 0;
    
    return buf;
}