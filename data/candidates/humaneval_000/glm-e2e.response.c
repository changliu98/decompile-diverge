bool func0(float *arr, int n, float threshold) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            float diff = arr[i] - arr[j];
            if (fabsf(diff) > threshold) {
                return true;
            }
        }
    }
    return false;
}