void __cdecl rifft1pt(float *ioptr, float scale)
{
    // Treat the 2 floats as a complex number: real + imaginary
    float real = ioptr[0];
    float imag = ioptr[1];

    // Compute the new real and imaginary parts
    float new_real = real + imag;
    float new_imag = real - imag;

    // Apply scale and store back into the buffer
    ioptr[0] = scale * new_real;
    ioptr[1] = scale * new_imag;
}