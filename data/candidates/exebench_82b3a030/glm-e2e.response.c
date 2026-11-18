int intwt(double x, double *out) {
    int result = 0;
    
    if (x < 1.0) {
        result = 1;
        *out = x;
    }
    
    if (x >= 1.0) {
        result = (int)x;
        *out = 1.0;
    }
    
    return result;
}