int* func0(int n, int *count) {
    int *res = (int *)malloc(256); // 0x100 bytes = 64 integers
    *count = 0;
    
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            n /= i;
            res[(*count)++] = i;
        }
    }
    
    if (n > 1) {
        res[(*count)++] = n;
    }
    
    return res;
}