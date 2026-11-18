void drwav_s24_to_s16(int16_t *dst, const uint8_t *src, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        // Read 3 bytes (24-bit signed integer) and combine them into a 32-bit variable
        int32_t s24 = (src[i * 3] << 8) | 
                      (src[i * 3 + 1] << 16) | 
                      (src[i * 3 + 2] << 24);
        
        // Arithmetic right shift to sign-extend the 24-bit value to 32 bits
        s24 >>= 8;
        
        // Shift right by 8 again to scale down from 24-bit to 16-bit
        int16_t s16 = (int16_t)(s24 >> 8);
        
        // Store the 16-bit result
        dst[i] = s16;
    }
}