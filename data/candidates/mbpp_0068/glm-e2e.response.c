bool func0(int *arr, int n) {
    bool is_non_decreasing = true;
    bool is_non_increasing = true;
    
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            is_non_decreasing = false;
        }
        if (arr[i] < arr[i + 1]) {
            is_non_increasing = false;
        }
    }
    
    return is_non_decreasing || is_non_increasing;
}