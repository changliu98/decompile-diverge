void rfft4pt(float *data) {
    // Constants loaded from memory
    // 0x2020: 0.5f
    // 0x2024: 0.70710678118654752440f (sqrt(0.5))
    // 0x2028: -0.70710678118654752440f (-sqrt(0.5))
    const float c0 = 0.5f;
    const float c1 = 0.70710678118654752440f;
    const float c2 = -0.70710678118654752440f;

    // Load the 4 complex input values
    // data[0] = (x0, y0), data[1] = (x1, y1), data[2] = (x2, y2), data[3] = (x3, y3)
    float x0 = data[0];
    float y0 = data[1];
    float x2 = data[4];
    float y2 = data[5];
    float x1 = data[2];
    float y1 = data[3];
    float x3 = data[6];
    float y3 = data[7];

    // Stage 1: 2-point FFTs on even and odd indexed elements
    float t0_re = x0 + x2;
    float t0_im = y0 + y2;
    float x2_re = x0 - x2;
    float y2_im = y0 - y2;

    float t1_re = x3 - y3;
    float t1_im = y3 + x3;
    float x3_re = x3 + y3;
    float y3_im = y3 - x3;

    // Stage 2: Combine the 2-point FFTs into a 4-point FFT
    float out0_re = t0_re + x3_re;
    float out0_im = t0_im + y3_im;
    float out2_re = t0_re - x3_re;
    float out2_im = y3_im - t0_im;

    float out3_re = x2_re - t1_im;
    float out3_im = y2_im + t1_re;
    float out1_re = x2_re + t1_im;
    float out1_im = y2_im - t1_re;

    // Stage 3: Final scaling and twiddle factor multiplications
    float sum0_re = out0_re + out0_im;
    float diff0_re = out0_re - out0_im;
    float sum1_re = out1_re + out3_re;
    float diff1_im = out1_im - out3_im;

    float sum1_im = out1_im + out3_im;
    float diff1_re = out3_re - out1_re;

    // Complex multiplications with twiddle factors (c1 and c2)
    float res1_re = c2 * sum1_im + sum1_re + c1 * diff1_re;
    float res1_im = -c2 * sum1_im + diff1_im + c1 * diff1_re;

    float res3_re = sum1_re * 2.0f - res1_re;
    float res3_im = out1_im - res1_im * 2.0f;

    // Store the computed results back into the array
    data[4] = out2_re;
    data[5] = out2_im;
    data[0] = sum0_re;
    data[1] = diff0_re;
    data[2] = c0 * res1_re;
    data[3] = c0 * res1_im;
    data[6] = c0 * res3_re;
    data[7] = c0 * res3_im;
}