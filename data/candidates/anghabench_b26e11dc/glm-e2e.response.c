int __sw_hweight16(uint32_t n) {
    uint32_t x = n;
    
    // Step 1: (n & 0x5555) + ((n >> 1) & 0x5555)
    // Optimized in assembly as: n - ((n >> 1) & 0x5555)
    x = x - ((x >> 1) & 0x5555);
    
    // Step 2: (x & 0x3333) + ((x >> 2) & 0x3333)
    x = (x & 0x3333) + ((x >> 2) & 0x3333);
    
    // Step 3: (x + (x >> 4)) & 0x0F0F
    x = (x + (x >> 4)) & 0x0F0F;
    
    // Step 4: (x + (x >> 8)) & 0xFF
    x = (x + (x >> 8)) & 0xFF;
    
    return x;
}