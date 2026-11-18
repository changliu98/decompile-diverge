void __cdecl fft4pt(float *ioptr)
{
    complex_t *io = (complex_t *)ioptr;

    // Load the 4 complex input values
    complex_t f0 = io[0];
    complex_t f1 = io[1];
    complex_t f2 = io[2];
    complex_t f3 = io[3];

    // Stage 1: 2-point FFTs (Butterfly operations)
    // Sum and difference for the first pair (f0, f1)
    complex_t sum0 = { f0.real + f1.real, f0.imag + f1.imag };
    complex_t diff0 = { f0.real - f1.real, f0.imag - f1.imag };

    // Sum and difference for the second pair (f2, f3)
    complex_t sum1 = { f2.real + f3.real, f2.imag + f3.imag };
    complex_t diff1 = { f2.real - f3.real, f2.imag - f3.imag };

    // Stage 2: Combine the results
    // The twiddle factor for the 4-point FFT is W_4^1 = -j, which maps (a + jb) to (b - ja)
    // diff1 is multiplied by -j, effectively swapping real and imaginary parts and negating the new real part.
    complex_t diff1_twiddled = { diff1.imag, -diff1.real };

    // Final butterfly combining the two stages
    io[0] = (complex_t){ sum0.real + sum1.real, sum0.imag + sum1.imag };
    io[1] = (complex_t){ diff0.real + diff1_twiddled.real, diff0.imag + diff1_twiddled.imag };
    io[2] = (complex_t){ sum0.real - sum1.real, sum0.imag - sum1.imag };
    io[3] = (complex_t){ diff0.real - diff1_twiddled.real, diff0.imag - diff1_twiddled.imag };
}