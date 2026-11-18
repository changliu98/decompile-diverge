float* func0(float* arr, int n, int* out_count) {
    float* out = malloc(n * sizeof(float));
    *out_count = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0.0f) {
            out[*out_count] = arr[i];
            (*out_count)++;
        }
    }
    
    return out;
}