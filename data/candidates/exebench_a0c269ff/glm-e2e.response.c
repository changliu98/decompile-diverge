void swap_float_4(uint32_t *val) {
    uint32_t v = *val;
    
    // Swap the 4 bytes of the 32-bit integer
    // Byte 0 (Least Significant) goes to Byte 3 (Most Significant)
    // Byte 1 goes to Byte 2
    // Byte 2 goes to Byte 1
    // Byte 3 goes to Byte 0
    *val = ((v & 0x000000FF) << 24) | 
           ((v & 0x0000FF00) << 8)  | 
           ((v & 0x00FF0000) >> 8)  | 
           ((v & 0xFF000000) >> 24);
}