int obdRevConvert_21(float val, int* out1, int* out2, int* out3) {
    int quotient = (int)val / 256;
    int remainder = (int)val % 256;
    
    *out1 = quotient;
    *out2 = remainder;
    
    return 2;
}