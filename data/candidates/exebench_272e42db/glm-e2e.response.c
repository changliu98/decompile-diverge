void decode_mode10_short_delta(int32_t arg1, int32_t *arg2, int32_t *arg3, int32_t *arg4) {
    // Extract the lowest 5 bits
    *arg4 = arg1 & 0x1f;
    
    // Sign-extend from a 5-bit integer to a 32-bit integer
    if (*arg4 & 0x10) {
        *arg4 |= 0xfffffff0;
    }
    
    // Multiply by 2 (Left shift by 1)
    *arg4 <<= 1;
    
    // Extract bits 5 to 9
    *arg3 = (arg1 & 0x3e0) >> 5;
    
    // Sign-extend from a 5-bit integer to a 32-bit integer
    if (*arg3 & 0x10) {
        *arg3 |= 0xfffffff0;
    }
    
    // Extract bits 10 to 14
    *arg2 = (arg1 & 0x7c00) >> 10;
    
    // Sign-extend from a 5-bit integer to a 32-bit integer
    if (*arg2 & 0x10) {
        *arg2 |= 0xfffffff0;
    }
}