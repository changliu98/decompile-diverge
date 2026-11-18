int* func0(int* arr, int n) {
    if (n <= 0) {
        return NULL;
    }
    
    int* out = (int*)malloc(n * sizeof(int));
    if (out == NULL) {
        return NULL;
    }
    
    int max = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        out[i] = max;
    }
    
    return out;
}