void clipmaxdouble(double *arr, double max_val, long n) {
    for (long i = 0; i < n; i++) {
        if (arr[i] > max_val) {
            arr[i] = max_val;
        }
    }
}