unsigned char gfmul(unsigned char a, unsigned char b) {
    unsigned char res = 0;
    unsigned char tmp_a = a;
    unsigned char tmp_b = b;

    while (tmp_b != 0) {
        if (tmp_b & 1) {
            res ^= tmp_a;
        }
        
        tmp_a <<= 1;
        if (tmp_a & 0x80) {
            tmp_a ^= 0x1d;
        }
        
        tmp_b >>= 1;
    }
    
    return res;
}