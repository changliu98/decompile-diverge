int obdRevConvert_43(float arg1, int *out1, int *out2, int *out3) {
    // 0xe17(%rip) points to 2008 which holds the float value 100.0f
    // 0xe06(%rip) points to 2004 which holds the float value 1.0f
    arg1 = (arg1 * 100.0f) / 1.0f;
    
    long long val = (long long)arg1;
    
    if (out1) {
        *out1 = (int)(val / 256);
    }
    
    if (out2) {
        *out2 = (int)(val % 256);
    }
    
    // out3 (passed in %rcx) is unused in the assembly
    
    return 2;
}