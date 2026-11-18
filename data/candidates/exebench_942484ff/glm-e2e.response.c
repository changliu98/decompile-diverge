void complexMultiplication(double a_real, double a_imag, double b_real, double b_imag, double *res_real, double *res_imag) {
    // Real part: (a_real * b_real) - (a_imag * b_imag)
    *res_real = (a_real * b_real) - (a_imag * b_imag);
    
    // Imaginary part: (a_real * b_imag) + (a_imag * b_real)
    *res_imag = (a_real * b_imag) + (a_imag * b_real);
}