void c_saxpy(int N, double alpha, double *X, double *Y) {
    int i, ix, iy;

    if (N <= 0 || alpha == 0.0)
        return;

    if (alpha!= 1.0)
        for (i = 0; i < N; ++i)
            Y[i] += alpha * X[i];
    else
        for (i = 0; i < N; ++i)
            Y[i] = alpha * X[i];
}