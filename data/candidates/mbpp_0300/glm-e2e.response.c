double func0(int n) {
    double term = 1.0;
    double sum = 1.0;
    int i = 1;
    
    while (i <= n) {
        term = term * (double)(n + 1 - i) / (double)i;
        sum = sum + term * term;
        i++;
    }
    
    return sum;
}