double randlc(double *x, double *a) {
    long long mask = 0x3fffffffffff;
    double base = 1.0; // Loaded from memory constant at 0x2008
    
    long long i = (long long)(*x);
    long long j = (long long)(*a);
    
    i = (i * j) & mask;
    
    double result = (double)i * base;
    *x = (double)i;
    
    return result;
}