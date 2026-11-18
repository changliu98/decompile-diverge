int func0(const char **arr, int n) {
    int min_val = 0x7fffffff;
    int current_val;
    
    for (int i = 0; i < n; i++) {
        if (sscanf(arr[i], "%d", &current_val) != 0) {
            if (current_val < min_val) {
                min_val = current_val;
            }
        }
    }
    
    return min_val;
}