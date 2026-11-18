void complexMultiplicationRI(double *real_out, double *imag_out, 
                             double real1, double imag1, 
                             double real2, double imag2) {
    // Real part: real1 * real2 - imag1 * imag2
    *real_out = (real1 * real2) - (imag1 * imag2);

    // Imaginary part: real1 * imag2 + imag1 * real2
    *imag_out = (real1 * imag2) + (imag1 * real2);
}