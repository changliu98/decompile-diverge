short interpolate(void *state, short *samples, int pitch, int pos) {
    int acc = 0;
    int overflow_check = 0;
    
    // State struct field accesses based on offsets:
    // 0x44 -> int max_pos
    // 0x48 -> int pitch_offset
    // 0x50 -> int stride
    int *state_int = (int *)state;
    int max_pos = state_int[0x44 / 4];
    int pitch_offset = state_int[0x48 / 4];
    int stride = state_int[0x50 / 4];

    int v1 = pitch_offset * pitch;
    int v2 = max_pos * pos;
    int v3 = (max_pos + 1) * pos;
    
    int offset = v3 - v1 - 1;
    int denominator = v3 - v2;
    
    for (int i = 0; i < 12; i++) {
        int coef = findSincCoefficient(i, offset, denominator);
        int sample_val = samples[i * stride];
        int prod = sample_val * coef;
        
        int sign = getSign(acc);
        acc += prod;
        int sign2 = getSign(acc);
        
        // Check for 32-bit integer overflow/underflow
        if (sign2 != sign) {
            if (removePitchSamples(prod) == sign) {
                overflow_check += sign;
            }
        }
    }
    
    short out;
    if (overflow_check > 0) {
        out = 0x7FFF; // Clamp to max positive
    } else if (overflow_check < 0) {
        out = 0x8000; // Clamp to max negative
    } else {
        out = (short)(acc >> 16); // Extract 16-bit fixed-point result
    }
    
    return out;
}