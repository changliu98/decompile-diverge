int obdRevConvert_3C_3F(float arg1, int *out1, int *out2, int *out3, int *out4) {
    // 0xe17(%rip) points to a constant, likely 40.0f based on OBD-II formulas
    arg1 += 40.0f; 
    
    // 0xe01(%rip) points to a constant, likely 2.55f
    arg1 *= 2.55f; 
    
    // Convert to integer and calculate quotient and remainder of division by 256
    int val = (int)arg1;
    *out1 = val / 256;
    *out2 = val % 256;
    
    // The function always returns 2
    return 2;
}