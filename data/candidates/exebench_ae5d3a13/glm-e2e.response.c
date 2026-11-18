void sum(double *arr, int n, double *result) {
    double total = 0.0;
    for (int i = 0; i < n; i++) {
        total += arr[i];
    }
    *result = total;
}