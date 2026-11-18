void f1(int n, float alpha, float *x, float *y) {
    int i;
    for (i = 0; i < n; i++) {
        y[i] += alpha * x[i];
    }
}