double func0(double *coeffs, int n) {
    double x = 0.0;
    double y = coeffs[0];
    int i, j;
    double t;

    for (i = 1; i < n; i++) {
        t = 1.0;
        for (j = 0; j < i; j++)
            t *= x;
        y += coeffs[i] * t;
    }

    do {
        x -= y / func0der(coeffs, n, x);
    } while (fabs(y) > EPS);

    return x;
}