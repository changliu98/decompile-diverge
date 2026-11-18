int func0(int n) {
    int arr[1000];
    memset(arr, 0, sizeof(arr));
    
    arr[0] = 0;
    arr[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
    
    return arr[n];
}