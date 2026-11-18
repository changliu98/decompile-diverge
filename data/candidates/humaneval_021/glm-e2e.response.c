void func0(float *arr, int n) {
    float min_val = arr[0];
    float max_val = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (min_val > arr[i]) {
            min_val = arr[i];
        }
        if (max_val < arr[i]) {
            max_val = arr[i];
        }
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = (arr[i] - min_val) / (max_val - min_val);
    }
}