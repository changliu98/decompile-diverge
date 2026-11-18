void AddArray4(float *a, float *b, int N) {
    int i;
    for (i = 0; i < N; i++) {
        b[i] = a[i] + b[i];
    }
}