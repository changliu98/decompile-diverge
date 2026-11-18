void func0(float *in, int n, float *out) {
    float *arr = (float *)malloc((n / 2 + 1) * sizeof(float));
    int k = 0;
    
    for (int i = 0; i < n; i += 2) {
        arr[k++] = in[i];
    }
    
    for (int i = 0; i < k - 1; i++) {
        for (int j = 0; j < k - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            out[i] = arr[i / 2];
        } else {
            out[i] = in[i];
        }
    }
    
    free(arr);
}