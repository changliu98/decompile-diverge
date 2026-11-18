int func0(int n) {
    if (n <= 1) {
        return 1;
    }
    
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += func0(i) * func0(n - i - 1);
    }
    
    return sum;
}