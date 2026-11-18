int64_t func0(int64_t **arr, int n) {
    int64_t max_val = arr[0][0];
    int64_t current_val = arr[0][0];
    
    for (int i = 1; i < n; i++) {
        if (current_val < 0) {
            current_val += arr[i][0];
        } else {
            current_val = arr[i][0];
        }
        
        if (current_val > max_val) {
            max_val = current_val;
        }
    }
    
    return max_val;
}