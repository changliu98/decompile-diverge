void convolve_4(double *out, const double *in1, const double *in2) {
    // Load inputs into local variables (mapped from stack variables)
    double a0 = in1[0];
    double a1 = in1[1];
    double a2 = in1[2];
    double a3 = in1[3];

    double b0 = in2[0];
    double b1 = in2[1];
    double b2 = in2[2];
    double b3 = in2[3];

    // out[0] = a0*b0
    out[0] = a0 * b0;

    // out[1] = a0*b1 + a1*b0
    out[1] = a0 * b1 + a1 * b0;

    // out[2] = a0*b2 + a1*b1 + a2*b0
    out[2] = a0 * b2 + a1 * b1 + a2 * b0;

    // out[3] = a0*b3 + a1*b2 + a2*b1 + a3*b0
    out[3] = a0 * b3 + a1 * b2 + a2 * b1 + a3 * b0;

    // out[4] = a1*b3 + a2*b2 + a3*b1
    out[4] = a1 * b3 + a2 * b2 + a3 * b1;

    // out[5] = a2*b3 + a3*b2
    out[5] = a2 * b3 + a3 * b2;

    // out[6] = a3*b3
    out[6] = a3 * b3;
}