float func0(float *arr, int n) {
    float max_val = -3.40282347e+38f; // Corresponds to the constant loaded at 0xe11(%rip)
    
    for (size_t i = 0; i < (size_t)n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    
    return max_val;
}