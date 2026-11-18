int func0(int n, int pos) {
    int arr[n];
    int idx = 0;
    
    for (int i = 1; i <= n; i += 2) {
        arr[idx++] = i;
    }
    
    for (int i = 2; i <= n; i += 2) {
        arr[idx++] = i;
    }
    
    return arr[pos - 1];
}