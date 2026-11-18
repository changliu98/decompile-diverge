void endian_swap32bit(uint32_t *val) {
    uint32_t v = *val;
    *val = ((v >> 24) & 0x000000FF) | 
           ((v << 8)  & 0x00FF0000) | 
           ((v >> 8)  & 0x0000FF00) | 
           ((v << 24) & 0xFF000000);
}