bool func0(const float *arr, int n) {
    bool is_non_decreasing = false;
    bool is_non_increasing = false;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i - 1]) {
            is_non_decreasing = true;
        }
        if (arr[i - 1] > arr[i]) {
            is_non_increasing = true;
        }
    }
    
    if (is_non_decreasing + is_non_increasing != 2) {
        return true;
    } else {
        return false;
    }
}