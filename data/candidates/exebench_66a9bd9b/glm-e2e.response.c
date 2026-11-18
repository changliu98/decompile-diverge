void fft4pt(float *data) {
    // Load the 4 complex numbers (8 floats)
    // data[0] = a, data[1] = b, data[2] = c, data[3] = d
    float a_re = data[0];
    float a_im = data[1];
    float c_re = data[4];
    float c_im = data[5];
    float b_re = data[2];
    float b_im = data[3];
    float d_re = data[6];
    float d_im = data[7];

    // Stage 1: 2-point FFTs (Butterfly 1)
    // Sum and difference of a and c
    float s1_re = a_re + c_re;
    float s1_im = a_im + c_im;
    float t1_re = a_re - c_re;
    float t1_im = a_im - c_im;

    // Sum and difference of b and d
    float t2_re = b_re - d_re;
    float t2_im = b_im - d_im;
    float s2_re = b_re + d_re;
    float s2_im = b_im + d_im;

    // Stage 2: 4-point FFT combination
    // Output 0: s1 + s2
    data[0] = s1_re + s2_re;
    data[1] = s1_im + s2_im;

    // Output 2: s1 - s2
    data[4] = s1_re - s2_re;
    data[5] = s1_im - s2_im;

    // Output 1: t1 - j*t2  (Multiplication by -j swaps real/imag and negates new real)
    data[2] = t1_re - t2_im;
    data[3] = t1_im + t2_re;

    // Output 3: t1 + j*t2  (Multiplication by +j swaps real/imag and negates new imag)
    data[6] = t1_re + t2_im;
    data[7] = t1_im - t2_re;
}