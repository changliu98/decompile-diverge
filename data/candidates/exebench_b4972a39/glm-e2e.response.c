void sub3x3(double *a, double *b) {
    for (int i = 0; i < 9; i++) {
        b[i] -= a[i];
    }
}