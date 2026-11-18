int func0(int n) {
    int result;
    int p = 1;
    int i = 1;
    
    for (i = 1; i < n; i++) {
        p *= i;
        if (p % n == 0) {
            result = i;
            return result;
        }
    }
    
    result = i - 1;
    return result;
}