int func0(int n) {
    char is_prime[n + 1];
    
    for (int i = 0; i <= n; i++) {
        is_prime[i] = 1;
    }
    
    for (int p = 2; p * p <= n; p++) {
        if (is_prime[p] == 1) {
            for (int i = p * 2; i <= n; i += p) {
                is_prime[i] = 0;
            }
        }
    }
    
    int sum = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            sum += i;
        }
    }
    
    return sum;
}