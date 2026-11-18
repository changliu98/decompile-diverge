void ZVdotC11(int n, double *a, double *b, double *result) {
    double sum_real = 0.0;
    double sum_imag = 0.0;

    // The loop increments by 2, processing one complex number (real + imag) per iteration.
    for (int i = 0; i < n; i++) {
        int idx_real = 2 * i;
        int idx_imag = 2 * i + 1;

        double a_real = a[idx_real];
        double a_imag = a[idx_imag];
        double b_real = b[idx_real];
        double b_imag = b[idx_imag];

        // Complex multiplication: (a_real + i*a_imag) * (b_real - i*b_imag)
        // Real part: a_real * b_real + a_imag * b_imag
        sum_real += a_real * b_real + a_imag * b_imag;

        // Imaginary part: a_imag * b_real - a_real * b_imag
        // The assembly explicitly performs the subtraction by XORing the sign bit of the product.
        sum_imag += a_imag * b_real - a_real * b_imag;
    }

    // Store the resulting complex number into the result array
    result[0] = sum_real;
    result[1] = sum_imag;
}