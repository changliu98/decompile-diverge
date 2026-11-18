int func0(int a, int b, int c, int d) {
    int sum = a + b;
    int result;
    
    if (sum >= c && sum <= d) {
        result = 20;
    } else {
        result = sum;
    }
    
    return result;
}