void func0(int *arr, int n) {
    if (n < 2) {
        return;
    }
    
    int mid = n / 2;
    int *left = (int *)malloc(mid * sizeof(int));
    int *right = (int *)malloc((n - mid) * sizeof(int));
    
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    
    for (int i = mid; i < n; i++) {
        right[i - mid] = arr[i];
    }
    
    func0(left, mid);
    func0(right, n - mid);
    merge(left, mid, right, n - mid, arr);
    
    free(left);
    free(right);
}