void mdct_butterfly_8(float *x) {
    // x[0] and x[1] represent the real and imaginary parts of complex 0
    // x[2] and x[3] represent the real and imaginary parts of complex 1
    // x[4] and x[5] represent the real and imaginary parts of complex 2
    // x[6] and x[7] represent the real and imaginary parts of complex 3

    float t0 = x[6] + x[2];
    float t1 = x[6] - x[2];
    float t2 = x[4] + x[0];
    float t3 = x[4] - x[0];

    x[6] = t0 + t2;
    x[4] = t0 - t2;

    float t4 = x[5] - x[1];
    float t5 = x[7] - x[3];

    x[0] = t1 + t4;
    x[2] = t1 - t4;

    float t6 = x[5] + x[1];
    float t7 = x[7] + x[3];

    x[3] = t5 + t3;
    x[1] = t5 - t3;
    x[7] = t7 + t6;
    x[5] = t7 - t6;
}