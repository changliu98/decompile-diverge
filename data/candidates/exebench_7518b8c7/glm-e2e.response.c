int max(float *arr) {
    int max_idx = 0;
    float max_val = arr[0];
    
    for (int i = 0; i < 3; i++) {
        if (arr[i] > max_val) {
            max_idx = i;
            max_val = arr[i];
        }
    }
    
    return max_idx;
}