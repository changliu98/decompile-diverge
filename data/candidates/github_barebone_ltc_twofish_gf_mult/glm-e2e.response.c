uint32_t gf_mult(uint32_t a, uint32_t b, uint32_t p) {
    // Lookup table for conditional masking (avoids branching)
    // mask[0] = 0x00000000, mask[1] = 0xFFFFFFFF
    uint32_t mask[2] = {0, 0xFFFFFFFF};
    
    // Lookup table for the reduction polynomial
    // poly[0] = 0x00000000, poly[1] = p
    uint32_t poly[2] = {0, p};
    
    uint32_t res = 0;

    // The loop is unrolled 8 times in the assembly
    for (int i = 0; i < 8; i++) {
        // If the LSB of 'a' is 1, XOR 'b' into 'res'
        res ^= mask[a & 1] & b;
        
        // Shift 'a' right by 1
        a >>= 1;
        
        // If the MSB of 'b' is 1, XOR the reduction polynomial 'p' into 'b'
        b = (b << 1) ^ poly[b >> 7];
    }

    return res;
}