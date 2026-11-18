double func0(int n) {
    double result;
    
    if (n < 0) {
        exit(1);
    }
    
    if (n <= 2) {
        result = (double)n * 3.14;
    } else {
        result = (double)((n - 2) * 4 + 21);
    }
    
    return result;
}