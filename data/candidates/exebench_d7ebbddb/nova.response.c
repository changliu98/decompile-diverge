void raw_relu_bulk_apply_function(int n, float *x) {
    int i;
    for (i = 0; i < n; i++) {
        x[i] = (x[i] > 0)? x[i] : -x[i];
    }
}