void r3sums(double *out, const double *v1, double s1, const double *v2, double s2) {
    out[0] = v1[0] * s1 + v2[0] * s2;
    out[1] = v1[1] * s1 + v2[1] * s2;
    out[2] = v1[2] * s1 + v2[2] * s2;
}