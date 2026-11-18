void func0(int n, float *x) {
    int i;
    for (i = 0; i < n; i++) {
        x[i] = (x[i] > 0)? x[i] : -x[i];
    }
}