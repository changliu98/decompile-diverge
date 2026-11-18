void AddArray2(float *arr1, float *arr2, int n) {
    for (int i = 0; i < n; i += 2) {
        arr2[i] += arr1[i];
        arr2[i + 1] += arr1[i + 1];
    }
}