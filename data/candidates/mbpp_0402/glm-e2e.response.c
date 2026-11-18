int func0(int n, int m, int k) {
    int size = m + 1;
    int *arr = __builtin_alloca(size * sizeof(int));
    
    for (int i = 0; i <= m; i++) {
        arr[i] = 0;
    }
    arr[1] = 1;
    
    for (int i = 1; i <= n; i++) {
        int j = (i < m) ? i : m;
        while (j > 0) {
            arr[j] = (arr[j] + arr[j - 1]) % k;
            j--;
        }
    }
    
    return arr[m];
}