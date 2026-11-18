float func0(float *arr, int n) {
    for (size_t i = 0; i < (size_t)n; i++) {
        for (size_t j = i + 1; j < (size_t)n; j++) {
            if (arr[i] > arr[j]) {
                float temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    
    if (n % 2 == 1) {
        return arr[n / 2];
    } else {
        return (arr[n / 2 - 1] + arr[n / 2]) * 0.5f;
    }
}