void fft8pt(float *data) {
    // data is an array of 16 floats: 8 complex numbers (real, imag) pairs
    // data[0], data[1] = Re(x0), Im(x0)
    // data[2], data[3] = Re(x1), Im(x1)
    // ...
    // data[14], data[15] = Re(x7), Im(x7)

    // Constants loaded from memory
    // 0x3f3504f3 is approximately 0.70710678f (1 / sqrt(2))
    const float c1 = 0.70710678f; 
    // 0xbf3504f3 is approximately -0.70710678f
    const float c2 = -0.70710678f;

    // Stage 1: Load inputs into local variables
    // The compiler maps local variables to stack offsets like:
    // -0x10: Re(x0), -0x14: Im(x0)
    // -0x18: Re(x4), -0x1c: Im(x4)
    // -0x20: Re(x2), -0x24: Im(x2)
    // -0x28: Re(x6), -0x2c: Im(x6)
    // -0x30: Re(x1), -0x34: Im(x1)
    // -0x38: Re(x5), -0x3c: Im(x5)
    // -0x40: Re(x3), -0x44: Im(x3)
    // -0x48: Re(x7), -0x4c: Im(x7)
    
    float x0r = data[0];
    float x0i = data[1];
    float x4r = data[8];
    float x4i = data[9];
    float x2r = data[4];
    float x2i = data[5];
    float x6r = data[12];
    float x6i = data[13];
    float x1r = data[2];
    float x1i = data[3];
    float x5r = data[10];
    float x5i = data[11];
    float x3r = data[6];
    float x3i = data[7];
    float x7r = data[14];
    float x7i = data[15];

    // Stage 2: First pass of butterflies (stride 4)
    // Butterfly 0: x0, x4
    float t0r = x0r + x4r;
    float t0i = x0i + x4i;
    x4r = x0r - x4r;
    x4i = x0i - x4i;

    // Butterfly 1: x2, x6
    float t1r = x2r - x6r;
    float t1i = x2i - x6i;
    x2r = x2r + x6r;
    x2i = x2i + x6i;

    // Butterfly 2: x1, x5
    float t2r = x1r + x5r;
    float t2i = x1i + x5i;
    x5r = x1r - x5r;
    x5i = x1i - x5i;

    // Butterfly 3: x3, x7
    float t3r = x3r - x7r;
    float t3i = x3i - x7i;
    x3r = x3r + x7r;
    x3i = x3i + x7i;

    // Stage 3: Second pass of butterflies (stride 2)
    // Butterfly 0: t0, x2
    x0r = t0r + x2r;
    x0i = t0i + x2i;
    x2r = t0r - x2r;
    x2i = t0i - x2i;

    // Butterfly 1: x4, t1 (twiddle factor W_8^1 = e^(-j*pi/4) = c1 - j*c1)
    x6r = x4r - t1i;
    x6i = x4i + t1r;
    x4r = x4r + t1i;
    x4i = x4i - t1r;

    // Butterfly 2: t2, x3
    x1r = t2r + x3r;
    x1i = t2i + x3i;
    x3r = t2r - x3r;
    x3i = t2i - x3i;

    // Butterfly 3: x5, t3 (twiddle factor W_8^1 = c1 - j*c1)
    x7r = x5r - t3i;
    x7i = x5i + t3r;
    x5r = x5r + t3i;
    x5i = x5i - t3r;

    // Stage 4: Third pass of butterflies (stride 1)
    // Butterfly 0: x0, x1
    float y0r = x0r - x1r;
    float y0i = x0i - x1i;
    x0r = x0r + x1r;
    x0i = x0i + x1i;

    // Butterfly 1: x2, x3 (twiddle factor W_8^2 = e^(-j*pi/2) = -j)
    float y1r = x2r - x3i;
    float y1i = x2i + x3r;
    x2r = x2r + x3i;
    x2i = x2i - x3r;

    // Butterfly 2: x4, x5 (twiddle factor W_8^3 = e^(-j*3*pi/4) = -c1 - j*c1)
    float y2r = x4r - x5i;
    float y2i = x4i + x5r;
    x4r = x4r + x5i;
    x4i = x4i - x5r;

    // Butterfly 3: x6, x7 (twiddle factor W_8^4 = e^(-j*pi) = -1)
    // The assembly uses bitwise XOR with 0x80000000 to flip the sign bit for floats
    float y3r = x6r - x7r;
    float y3i = x6i - x7i;
    x6r = x6r + x7r;
    x6i = x6i + x7i;

    // Stage 5: Final multiplications by 1/sqrt(2) for specific outputs
    // The assembly explicitly multiplies by c1 (0.7071...) and c2 (-0.7071...)
    // and adds the doubled original values, effectively computing:
    // out = 2*orig + c1*temp1 + c2*temp2
    
    // Output 2 (Re/Im)
    float out2r = 2.0f * x2r - y2r;
    float out2i = 2.0f * x2i - y2i;

    // Output 3 (Re/Im)
    float out3r = x3r + c1 * x7r + c2 * x7i;
    float out3i = x3i + c1 * x7i + c1 * x7r;

    // Output 6 (Re/Im)
    float out6r = 2.0f * x6r - y3r;
    float out6i = 2.0f * x6i - y3i;

    // Output 7 (Re/Im)
    float out7r = x7r + c1 * y3r + c2 * y3i;
    float out7i = x7i + c1 * y3i + c1 * y3r;

    // Store results back to the data array
    data[0] = x0r;
    data[1] = x0i;
    data[2] = x2r;
    data[3] = x2i;
    data[4] = x4r;
    data[5] = x4i;
    data[6] = out2r;
    data[7] = out2i;
    data[8] = y0r;
    data[9] = y0i;
    data[10] = y1r;
    data[11] = y1i;
    data[12] = out3r;
    data[13] = out3i;
    data[14] = out6r;
    data[15] = out6i;
}