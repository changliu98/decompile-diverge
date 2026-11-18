int find_max_idx(float *arr) {
    float max_val = 0.0f;
    int max_idx = -1;
    
    // First pass: find the maximum value and its index
    for (int i = 0; i < 16; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
            max_idx = i;
        }
    }
    
    // If no element was greater than 0.0f, return -1
    if (max_idx < 0) {
        return -1;
    }
    
    // Multiply the maximum value by 0.5 (or similar constant from memory)
    max_val *= 0.5f;
    
    // Second pass: ensure no other element (excluding the max index) is greater than the adjusted max_val
    for (int i = 0; i < 16; i++) {
        if (i != max_idx && arr[i] > max_val) {
            return -1;
        }
    }
    
    return max_idx;
}