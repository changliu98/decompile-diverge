int obdRevConvert_04(float val, int32_t *out1, void *out2, void *out3) {
    // val is passed in xmm0
    // out1 is passed in rdi
    // out2 is passed in rsi
    // out3 is passed in rdx
    
    // The 4th argument (rcx) is saved to the stack but never used.
    // It might be an artifact of calling conventions or unused parameter.
    
    // Multiply val by constant at 0x2004
    // Divide by constant at 0x2008
    // Convert to 32-bit integer
    *out1 = (int32_t)((val * 0.5f) / 1.0f);
    
    return 1;
}