located at 0x2008

int obdRevConvert_2C(float val, int32_t *out1, void *unused1, void *unused2) {
    // val is passed in xmm0
    // out1 is passed in rdi
    // unused1 is passed in rsi
    // unused2 is passed in rdx
    // rcx is passed but unused
    
    *out1 = (int32_t)((val * CONST_1) / CONST_2);
    
    return 1;
}