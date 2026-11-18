int func0(int n) {
    int arr[n + 1];
    arr[0] = 0;
    arr[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        int x = arr[i / 2];
        int y = x + arr[i / 3];
        arr[i] = y + arr[i / 4];
        
        if (arr[i] < i) {
            arr[i] = i;
        }
    }
    
    return arr[n];
}