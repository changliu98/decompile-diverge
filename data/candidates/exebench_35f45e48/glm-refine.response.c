void __cdecl fft4pt(float *ioptr)
{
    // Load the 4 complex inputs (8 floats)
    // f0 = ioptr[0], f1 = ioptr[1], f2 = ioptr[2], f3 = ioptr[3]
    float f0r = ioptr[0];
    float f0i = ioptr[1];
    float f1r = ioptr[2];
    float f1i = ioptr[3];
    float f2r = ioptr[4];
    float f2i = ioptr[5];
    float f3r = ioptr[6];
    float f3i = ioptr[7];

    // Stage 1: 2-point FFTs (Butterflies with twiddle factor = 1)
    // t0 = f0 + f1
    float t0r = f0r + f1r;
    float t0i = f0i + f1i;
    
    // f1' = f0 - f1
    float f1r_diff = f0r - f1r;
    float f1i_diff = f0i - f1i;
    
    // f2' = f2 + f3
    float f2r_sum = f2r + f3r;
    float f2i_sum = f2i + f3i;
    
    // t1 = f2 - f3
    float t1r = f2r - f3r;
    float t1i = f2i - f3i;

    // Stage 2: Combine with twiddle factor W = -j (swap real/imag and negate)
    // Output[0] = t0 + f2'
    ioptr[0] = t0r + f2r_sum;
    ioptr[1] = t0i + f2i_sum;
    
    // Output[1] = f1' + W * t1 = f1' + (-j) * (t1r + jt1i) = (f1r + t1i) + j(f1i - t1r)
    ioptr[2] = f1r_diff + t1i;
    ioptr[3] = f1i_diff - t1r;
    
    // Output[2] = t0 - f2'
    ioptr[4] = t0r - f2r_sum;
    ioptr[5] = t0i - f2i_sum;
    
    // Output[3] = f1' - W * t1 = f1' - (-j) * (t1r + jt1i) = (f1r - t1i) + j(f1i + t1r)
    ioptr[6] = f1r_diff - t1i;
    ioptr[7] = f1i_diff + t1r;
}