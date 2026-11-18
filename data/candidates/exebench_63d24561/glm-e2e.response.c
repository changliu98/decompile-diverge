int zmlt_(double *a_real, double *a_imag, double *b_real, double *b_imag, double *out_real, double *out_imag) {
    // Calculate the real part of the result
    // Standard formula: a_real * b_real - a_imag * b_imag
    // Here, the subtraction is performed by flipping the sign bit of (a_imag * b_imag) using XOR
    double term1 = *a_real * *b_real;
    double term2 = *a_imag * *b_imag;
    
    // Flip the sign bit of term2
    int64_t flipped_bits = *(int64_t*)&term2 ^ 0x8000000000000000;
    double term2_flipped = *(double*)&flipped_bits;
    
    double res_real = term1 + term2_flipped;
    
    // Calculate the imaginary part of the result
    // Standard formula: a_real * b_imag + a_imag * b_real
    double res_imag = (*a_real * *b_imag) + (*a_imag * *b_real);
    
    // Store the results into the output pointers
    *out_real = res_real;
    *out_imag = res_imag;
    
    // Return 0 (xor %eax, %eax)
    return 0;
}