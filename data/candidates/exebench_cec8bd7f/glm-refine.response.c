void __cdecl cftf082(float *a)
{
    // The input array 'a' represents an array of 8 complex numbers (16 floats).
    // a[2*k] is the real part, and a[2*k+1] is the imaginary part.
    
    // Stage 1: Decimation / Pre-processing
    float x0r = a[0] - a[9];
    float x0i = a[1] + a[8];
    float x1r = a[0] + a[9];
    float x1i = a[1] - a[8];

    float x2r = a[4] - a[13];
    float x2i = a[5] + a[12];
    float x3r = a[4] + a[13];
    float x3i = a[5] - a[12];

    float x4r = a[2] - a[11];
    float x4i = a[3] + a[10];
    float x5r = a[2] + a[11];
    float x5i = a[3] - a[10];

    float x6r = a[6] - a[15];
    float x6i = a[7] + a[14];
    float x7r = a[6] + a[15];
    float x7i = a[7] - a[14];

    // Stage 2: Twiddle factor multiplications
    // 0.70710677f is approximately sqrt(2)/2
    float y0r = x0r;
    float y0i = x0i;
    float y1r = x1r;
    float y1i = x1i;

    float y2r = 0.70710677f * (x2r - x2i);
    float y2i = 0.70710677f * (x2i + x2r);
    float y3r = 0.70710677f * (x3r - x3i);
    float y3i = 0.70710677f * (x3i + x3r);

    // 0.38268343f is approximately sin(pi/8)
    // 0.9238795f  is approximately cos(pi/8)
    float y4r = (0.9238795f * x4r) - (0.38268343f * x4i);
    float y4i = (0.9238795f * x4i) + (0.38268343f * x4r);
    float y5r = (0.38268343f * x5r) - (0.9238795f * x5i);
    float y5i = (0.38268343f * x5i) + (0.9238795f * x5r);

    float y6r = (0.38268343f * x6r) - (0.9238795f * x6i);
    float y6i = (0.38268343f * x6i) + (0.9238795f * x6r);
    float y7r = (0.9238795f * x7r) - (0.38268343f * x7i);
    float y7i = (0.9238795f * x7i) + (0.38268343f * x7r);

    // Stage 3: Butterfly combinations and final output assignments
    a[0]  = (y0r + y2r) + (y4r + y6r);
    a[1]  = (y0i + y2i) + (y4i + y6i);
    a[2]  = (y0r + y2r) - (y4r + y6r);
    a[3]  = (y0i + y2i) - (y4i + y6i);
    a[4]  = (y0r - y2r) - (y4i - y6i);
    a[5]  = (y0i - y2i) + (y4r - y6r);
    a[6]  = (y0r - y2r) + (y4i - y6i);
    a[7]  = (y0i - y2i) - (y4r - y6r);
    a[8]  = (y1r - y3i) + (y5r - y7r);
    a[9]  = (y1i + y3r) + (y5i - y7i);
    a[10] = (y1r - y3i) - (y5r - y7r);
    a[11] = (y1i + y3r) - (y5i - y7i);
    a[12] = (y1r + y3i) - (y5i + y7i);
    a[13] = (y1i - y3r) + (y5r + y7r);
    a[14] = (y1r + y3i) + (y5i + y7i);
    a[15] = (y1i - y3r) - (y5r + y7r);
}