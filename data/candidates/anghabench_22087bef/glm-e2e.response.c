int8_t linear2ulaw(int16_t pcm_val) {
    int16_t mask;
    int16_t seg;
    int8_t uval;

    // Get the sign bit. If it's negative, mask becomes 0x80; otherwise 0.
    mask = (pcm_val >> 8) & 0x80;
    
    // If the value is negative, complement it to get the absolute value
    if (mask) {
        pcm_val = -pcm_val;
    }
    
    // Add the bias to the absolute value
    pcm_val += BIAS;
    
    // Find the segment by looking up the exponent LUT
    seg = linear2ulaw_exp_lut[(pcm_val >> 7) & 0xFF];
    
    // Combine the segment, mantissa, and sign
    uval = (mask | (seg << 4) | ((pcm_val >> (seg + 3)) & 0xF)) ^ 0xFF;
    
    return uval;
}