void drmp3_L3_idct3(float a, float b, float c, float *out) {
    // 0xb75(%rip) points to a constant, likely sqrt(3)/2
    float k = sqrtf(3.0f) / 2.0f; 
    float t1 = k * b;
    
    // 0xb48(%rip) points to a constant, likely sqrt(3)/2
    // The xor $0x80000000 flips the sign bit of the float, which is equivalent to negating it
    float t2 = a - (sqrtf(3.0f) / 2.0f) * c;
    
    out[1] = a + c;
    out[0] = t2 + t1;
    out[2] = t2 - t1;
}