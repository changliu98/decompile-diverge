int func0(int n) {
    int arr[100];
    memset(arr, 0, 0x190); // 0x190 = 400 bytes (100 * sizeof(int))
    
    arr[0] = 0;
    arr[1] = 1;
    
    for (int i = 3; i <= n; i++) {
        arr[i] = arr[i - 1] + arr[i - 2] + arr[i - 3];
    }
    
    return arr[n];
}