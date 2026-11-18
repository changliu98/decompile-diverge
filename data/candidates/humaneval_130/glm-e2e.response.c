int* func0(int n) {
    int *arr = (int*)malloc((n + 1) * sizeof(int));
    arr[0] = 1;
    
    if (n == 0) {
        return arr;
    }
    
    arr[1] = 3;
    
    for (int i = 2; i <= n; i++) {
        if (i % 2 == 0) {
            arr[i] = (i / 2) + 1;
        } else {
            int temp = arr[i - 1] + arr[i - 2] + 1;
            arr[i] = temp + ((i + 1) / 2);
        }
    }
    
    return arr;
}