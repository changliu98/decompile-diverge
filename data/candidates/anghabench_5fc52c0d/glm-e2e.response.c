void sjis2jis(unsigned char *h, unsigned char *l) {
    unsigned char c1 = *h;
    unsigned char c2 = *l;
    
    // Check if c2 is less than 0x9f
    int is_less_than_9f = (c2 < 0x9f) ? 1 : 0;
    
    // Determine the base offset for c1
    int offset = (c1 < 0xa0) ? 0x70 : 0xb0;
    
    int sub_val;
    if (is_less_than_9f) {
        // If c2 > 0x7f, add 1 to 0x1f (resulting in 0x20), otherwise it stays 0x1f
        sub_val = (c2 > 0x7f) ? 0x20 : 0x1f;
    } else {
        sub_val = 0x7e;
    }
    
    // Update the first byte (high byte)
    *h = (unsigned char)((c1 - offset) * 2 - is_less_than_9f);
    
    // Update the second byte (low byte)
    *l = (unsigned char)(*l - sub_val);
}