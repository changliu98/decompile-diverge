void SJIStoJIS(unsigned char *first, unsigned char *second) {
    unsigned char c1 = *first;
    unsigned char c2 = *second;
    
    int is_less_than_9f = (c2 < 0x9f);
    int adjustment = (c1 < 0xa0) ? 0x70 : 0xb0;
    
    int second_offset;
    if (is_less_than_9f) {
        second_offset = (c2 > 0x7f) + 0x1f;
    } else {
        second_offset = 0x7e;
    }
    
    *first = (c1 - adjustment) * 2 - is_less_than_9f;
    *second = c2 - second_offset;
}