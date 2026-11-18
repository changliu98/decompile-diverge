int* func0(int *arr, int n, int *out) {
    int min_val = 0x7fffffff;
    int min_idx = -1;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            if (arr[i] < min_val || min_idx == -1) {
                min_val = arr[i];
                min_idx = i;
            }
        }
    }
    
    if (min_idx == -1) {
        return NULL;
    } else {
        out[0] = min_val;
        out[1] = min_idx;
        return out;
    }
}