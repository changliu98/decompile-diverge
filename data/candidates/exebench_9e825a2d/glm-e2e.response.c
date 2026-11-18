int C_Utils_compare_float_ptr(const float *a, const float *b) {
    float val1 = *a;
    float val2 = *b;
    
    if (val1 == val2) {
        return 0;
    }
    
    if (val1 > val2) {
        return 1;
    } else {
        return -1;
    }
}