int sdram_convert(unsigned int freq, unsigned int *out_val) {
    // 0x3b9aca00 is 1,000,000,000 (1 GHz)
    unsigned int div = 1000000000 / freq;
    
    // 0x3d09 is 15625
    unsigned int val = 15625 / div;
    
    // Shift right by 6 (divide by 64) and add 1
    val = (val >> 6) + 1;
    
    // Clamp the value to a maximum of 255 (0xFF)
    if (val > 0xFF) {
        val = 0xFF;
    }
    
    // Dereference the pointer and store the result
    *out_val = val;
    
    return 0;
}