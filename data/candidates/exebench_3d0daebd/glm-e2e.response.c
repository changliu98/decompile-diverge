void swt_max(double *arr, int n, double *max_val) {
    *max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > *max_val) {
            *max_val = arr[i];
        }
    }
}