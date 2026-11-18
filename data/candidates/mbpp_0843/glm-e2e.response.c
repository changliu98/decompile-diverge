long long func0(int n, int* arr, int m) {
    long long* a = malloc(n * sizeof(long long));
    int* count = calloc(m, sizeof(int));
    long long* b = malloc(m * sizeof(long long));
    
    a[0] = 1;
    
    for (int i = 0; i < m; i++) {
        b[i] = (long long)arr[i];
    }
    
    for (int i = 1; i < n; i++) {
        long long min_val = b[0];
        for (int j = 1; j < m; j++) {
            if (b[j] < min_val) {
                min_val = b[j];
            }
        }
        a[i] = min_val;
        
        for (int j = 0; j < m; j++) {
            if (b[j] == min_val) {
                count[j]++;
                b[j] = (long long)arr[j] * a[count[j]];
            }
        }
    }
    
    long long result = a[n - 1];
    
    free(a);
    free(count);
    free(b);
    
    return result;
}