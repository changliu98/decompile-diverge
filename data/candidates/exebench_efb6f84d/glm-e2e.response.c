int obdRevConvert_2D(float xmm0, int32_t *rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx) {
    // The constants loaded from memory (0xe0e and 0xe06 RIP-relative offsets)
    // are typically standard ECU scaling factors. 
    // E.g: xmm1_1 = 0.5 (offset) and xmm1_2 = 2.0 (divisor)
    
    *rdi = (int32_t)((xmm0 + 0.5f) / 2.0f);
    
    return 1;
}