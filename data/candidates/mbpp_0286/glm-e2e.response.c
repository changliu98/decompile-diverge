int func0(int *arr, int n, int m) {
    int max_val = -2147483648; // 0x80000000
    int current_val = 0;
    
    for (int i = 0; i < n * m; i++) {
        current_val += arr[i % n];
        
        if (max_val < current_val) {
            max_val = current_val;
        }
        
        if (current_val < 0) {
            current_val = 0;
        }
    }
    
    return max_val;
}