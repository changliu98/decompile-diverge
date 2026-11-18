int __sw_hweight32(uint32_t w) {
    uint32_t res;
    
    // Step 1: Count bits in pairs
    res = w - ((w >> 1) & 0x55555555);
    
    // Step 2: Count bits in nibbles (4 bits)
    res = (res & 0x33333333) + ((res >> 2) & 0x33333333);
    
    // Step 3: Count bits in bytes (8 bits)
    res = (res + (res >> 4)) & 0x0F0F0F0F;
    
    // Step 4: Multiply to accumulate byte counts into the top byte, 
    // then shift down to leave just the final sum in the lower 8 bits.
    res = (res + (res >> 8));
    res = (res + (res >> 16)) & 0xFF;
    
    return (int)res;
}