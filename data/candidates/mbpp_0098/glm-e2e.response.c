double func0(int *arr, int n) {
    double product = 1.0;
    for (int i = 0; i < n; i++) {
        product *= (double)arr[i];
    }
    return product / (double)n;
}