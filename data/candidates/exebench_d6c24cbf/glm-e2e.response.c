int obdRevConvert_31(float val, int* out_high, int* out_low, int* unused1, int* unused2) {
    int quotient = (int)val / 256;
    int remainder = (int)val % 256;
    
    *out_high = quotient;
    *out_low = remainder;
    
    return 2;
}