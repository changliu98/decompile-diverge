void swapfloat(float *f) {
    unsigned int *p = (unsigned int *)f;
    unsigned int v = *p;
    
    // Swap the 4 bytes of the float to reverse endianness
    *p = ((v & 0x000000FF) << 24) |
         ((v & 0x0000FF00) << 8)  |
         ((v & 0x00FF0000) >> 8)  |
         ((v & 0xFF000000) >> 24);
}