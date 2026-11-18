void cquat_scale(double *out, double a, double *x) {
    out[0] = a * x[0];
    out[1] = a * x[1];
    out[2] = a * x[2];
    out[3] = a * x[3];
}