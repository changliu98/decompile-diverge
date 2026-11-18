float add_denormal_prevention_white_noise(uint32_t *state) {
    // Advance the PRNG state
    *state = *state * 0x12d687 + 0xd950b;
    
    // Extract bits 16 to 22 (7 bits) from the state
    uint32_t extracted_bits = *state & 0x7f0000;
    
    // Construct a floating-point number in the normal range
    // by setting the exponent to 0x1e (which corresponds to 2^-7)
    // and using the extracted bits as the upper mantissa.
    uint32_t float_bits = extracted_bits | 0x1e000000;
    
    // Reinterpret the constructed bits as a float and return
    float result;
    *(uint32_t*)&result = float_bits;
    return result;
}