void lqtomat(double *in, double *out) {
    double in0 = in[0];
    double in1 = in[1];
    double in2 = in[2];
    double in3 = in[3];

    out[0] = in0 * in0 + in1 * in1 - in2 * in2 - in3 * in3;
    out[1] = 2.0 * (in1 * in2 - in0 * in3);
    out[2] = 2.0 * (in0 * in2 + in1 * in3);
    out[3] = 2.0 * (in1 * in2 + in0 * in3);

    out[4] = in0 * in0 - in1 * in1 + in2 * in2 - in3 * in3;
    out[5] = 2.0 * (in2 * in3 - in0 * in1);
    out[6] = 2.0 * (in0 * in1 + in2 * in3);
    out[7] = 2.0 * (in2 * in3 + in0 * in1);

    out[8] = in0 * in0 - in1 * in1 - in2 * in2 + in3 * in3;
}