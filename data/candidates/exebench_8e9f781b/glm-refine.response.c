void __cdecl cftf040(float *a)
{
    // Load the 4 complex numbers
    float x0r = a[0], x0i = a[1];
    float x1r = a[2], x1i = a[3];
    float x2r = a[4], x2i = a[5];
    float x3r = a[6], x3i = a[7];

    // Stage 1: 2-point FFT butterflies (0-2 and 1-3)
    float t0r = x0r + x2r, t0i = x0i + x2i;
    float t1r = x0r - x2r, t1i = x0i - x2i;
    float t2r = x1r + x3r, t2i = x1i + x3i;
    float t3r = x1r - x3r, t3i = x1i - x3i;

    // Stage 2: 4-point FFT butterfly combining the halves
    // Multiplication by the twiddle factor W_4^1 = -j is done implicitly 
    // by swapping real and imaginary parts and applying signs.
    a[0] = t0r + t2r;
    a[1] = t0i + t2i;
    a[2] = t1r - t3i;
    a[3] = t1i + t3r;
    a[4] = t0r - t2r;
    a[5] = t0i - t2i;
    a[6] = t1r + t3i;
    a[7] = t1i - t3r;
}