double func0(int n) {
    if (n < 0) {
        return 0.0;
    }
    
    double term = 1.0 / pow(2.0, (double)n);
    return term + func0(n - 1);
}