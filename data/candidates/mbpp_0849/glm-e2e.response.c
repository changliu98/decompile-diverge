int func0(int n) {
    int *arr = __builtin_alloca((n + 1) * sizeof(int));
    
    for (int i = 0; i <= n; i++) {
        arr[i] = 0;
    }
    
    for (int i = 2; i <= n; i++) {
        if (arr[i] == 0) {
            for (int j = i; j <= n; j += i) {
                arr[j] += i;
            }
        }
    }
    
    return arr[n];
}