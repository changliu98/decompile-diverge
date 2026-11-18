void cmatrix_from_frame(double *out, double *in1, double *in2, double *in3) {
    for (int i = 0; i < 3; i++) {
        out[i * 3 + 0] = in1[i];
        out[i * 3 + 1] = in2[i];
        out[i * 3 + 2] = in3[i];
    }
}