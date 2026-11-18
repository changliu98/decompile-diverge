void __cdecl cmul(double *aa, double *bb)
{
    // Extract real and imaginary parts for readability
    double a_real = aa[0];
    double a_imag = aa[1];
    double b_real = bb[0];
    double b_imag = bb[1];

    // Calculate the new imaginary part: (a_real * b_imag) + (a_imag * b_real)
    double imag = a_real * b_imag + a_imag * b_real;
    
    // Calculate the new real part: (a_real * b_real) - (a_imag * b_imag)
    // We use a temporary variable here to preserve the original a_real for the imag calculation,
    // matching the execution order and semantics of the original decompiled output.
    double real = a_real * b_real - a_imag * b_imag;

    // Write the results back to the aa pointer
    aa[0] = real;
    aa[1] = imag;
}