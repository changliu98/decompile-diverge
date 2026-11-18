void unscale(double *arr, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        arr[i] *= 0.001;
    }
}