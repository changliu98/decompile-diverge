void ifft8pt(float *data, float scale) {
    // 0.7071067811865476f is 1/sqrt(2), loaded from memory at 0x11fa
    float w2r = 0.7071067811865476f; 

    // Load the 8 complex numbers (16 floats) into local variables
    // Real and Imaginary parts are interleaved (stride of 2 floats per complex number)
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

    // Stage 1: 4-point radix-2 IFFTs
    float t0r = x0r + x4r;
    float t0i = x0i + x4i;
    x4r = x0r - x4r;
    x4i = x0i - x4i;

    float t1r = x2r - x6r;
    float t1i = x2i - x6i;
    x2r = x2r + x6r;
    x2i = x2i + x6i;

    x0r = t0r + x2r;
    x0i = t0i + x2i;
    x2r = t0r - x2r;
    x2i = t0i - x2i;

    x6r = x4r + t1i;
    x6i = x4i - t1r;
    x4r = x4r - t1i;
    x4i = x4i + t1r;

    float t2r = x1r + x5r;
    float t2i = x1i + x5i;
    x5r = x1r - x5r;
    x5i = x1i - x5i;

    float t3r = x3r - x7r;
    float t3i = x3i - x7i;
    x3r = x3r + x7r;
    x3i = x3i + x7i;

    x1r = t2r + x3r;
    x1i = t2i + x3i;
    x3r = t2r - x3r;
    x3i = t2i - x3i;

    x7r = x5r + t3i;
    x7i = x5i - t3r;
    x5r = x5r - t3i;
    x5i = x5i + t3r;

    // Stage 2: Combine the four 4-point IFFTs into an 8-point IFFT
    float t4r = x0r - x1r;
    float t4i = x0i - x1i;
    x0r = x0r + x1r;
    x0i = x0i + x1i;

    float t5r = x2r + x5i;
    float t5i = x2i - x5r;
    x2r = x2r - x5i;
    x2i = x2i + x5r;

    // Complex multiplication and addition for x1
    // (x4r + j*x4i) * (w2r - j*w2r) = (x4r*w2r + x4i*w2r) + j*(x4i*w2r - x4r*w2r)
    x1r = x4r * w2r + x4i * w2r + x6r;
    x1i = x4i * w2r - x4r * w2r + x6i;
    x6r = 2.0f * x6r - x1r;
    x6i = 2.0f * x6i - x1i;

    // Complex multiplication and addition for x3
    // (x6r + j*x6i) * (w2r + j*w2r) = (x6r*w2r - x6i*w2r) + j*(x6i*w2r + x6r*w2r)
    x3r = x6r * w2r - x6i * w2r + x2r;
    x3i = x6i * w2r + x6r * w2r + x2i;
    x2r = 2.0f * x2r - x3r;
    x2i = 2.0f * x2i - x3i;

    // Store the results back to the array, scaled by the 'scale' parameter
    data[0]  = x0r * scale;
    data[1]  = x0i * scale;
    data[2]  = x4r * scale;
    data[3]  = x4i * scale;
    data[4]  = x2r * scale;
    data[5]  = x2i * scale;
    data[6]  = x6r * scale;
    data[7]  = x6i * scale;
    data[8]  = t4r * scale;
    data[9]  = t4i * scale;
    data[10] = x1r * scale;
    data[11] = x1i * scale;
    data[12] = t5r * scale;
    data[13] = t5i * scale;
    data[14] = x3r * scale;
    data[15] = x3i * scale;
}