int func0(int n) {
    int i = 1;
    int sum = 0;
    
    while (n / i > 0) {
        sum += n / i;
        i <<= 1; // Equivalent to i *= 2
    }
    
    return sum;
}