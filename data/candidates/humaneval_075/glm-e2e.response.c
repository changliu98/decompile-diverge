bool func0(int n) {
    int count = 0;
    
    if (n < 2) {
        return false;
    }
    
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            n /= i;
            count++;
        }
    }
    
    if (n > 1) {
        count++;
    }
    
    return count == 3;
}