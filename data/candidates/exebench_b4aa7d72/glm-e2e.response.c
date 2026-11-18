void grad1(int x, float *out) {
    int masked_x = x & 0xf;
    *out = (float)(masked_x & 0x7) + 1.0f;
    
    if (masked_x & 0x8) {
        // Bitwise XOR with 0x80000000 flips the sign bit of a 32-bit float.
        // This is functionally equivalent to multiplying by -1.0f.
        uint32_t *out_bits = (uint32_t *)out;
        *out_bits ^= 0x80000000;
    }
}