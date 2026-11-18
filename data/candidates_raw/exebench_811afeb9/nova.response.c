int func0(int n, double *x, double *y) {
    int i, j, k, l;
    double a, b;

    for (i = 0; i < 4; i++) {
        a = x[i];
        b = x[i];
        for (j = 1; j < n; j++) {
            for (k = 0; k < 3; k++) {
                if (x[i + j * 3] > a)
                    a = x[i + j * 3];
                if (x[i + j * 3] < b)
                    b = x[i + j * 3];
            }
            y[i + j * 3] = (x[i + j * 3] - b) / (a - b);
        }
    }
    return 0;
}