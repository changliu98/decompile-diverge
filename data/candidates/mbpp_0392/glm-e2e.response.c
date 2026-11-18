int func0(int n) {
    int *arr = __builtin_alloca((n + 1) * sizeof(int));
    arr[0] = 0;
    arr[1] = 1;
    
    for (int i = 2; i < n + 1; i++) {
        arr[i] = i;
        int a = arr[i / 2];
        int b = a + arr[i / 3];
        int c = b + arr[i / 4];
        int d = c + arr[i / 5];
        
        if (d > arr[i]) {
            arr[i] = d;
        }
    }
    
    return arr[n];
}