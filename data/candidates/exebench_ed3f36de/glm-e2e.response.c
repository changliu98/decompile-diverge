void test_mean2(double *out, double *in, int n) {
    double sum1 = 0.0;
    double sum2 = 0.0;
    int i;

    // Loop 1: Sum elements at indices 0, 2, 4, ... 2*(n-1)
    for (i = 0; i < n * 2; i += 2) {
        sum1 += in[i];
    }

    // Loop 2: Sum elements at indices 1, 3, 5, ... 2*n - 1
    for (i = 0; i < n * 2; i += 2) {
        sum2 += in[i + 1];
    }

    // Calculate means and store in the output array
    out[0] = sum1 / (double)n;
    out[1] = sum2 / (double)n;
}