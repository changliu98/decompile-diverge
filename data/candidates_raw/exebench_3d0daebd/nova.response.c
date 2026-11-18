void func0(double *v, int n, double *max) {
    int i;
    *max = v[0];
    for (i = 1; i < n; i++) {
        if (v[i] > *max)
            *max = v[i];
    }
}