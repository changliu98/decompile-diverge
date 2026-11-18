
static void mult(double A[16], const double a[4], double b[4]) {

    enum {X, Y, Z, W};
    int c, i;
    for (i = c = 0; c < 4; c++) {
        b[c] = A[i++]*a[X];
        b[c] += A[i++]*a[Y];
        b[c] += A[i++]*a[Z];
        b[c] += A[i++]*a[W];
    }
}
